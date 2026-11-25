// Backend grafico em thread propria: a thread do jogo so grava comandos num buffer; outra thread (outro nucleo)
// executa no OpenGL. Assim o custo do driver (desenhos, uniforms, envio de texturas, decodificacao DXT) sai da
// thread do jogo. Ids de recursos sao "virtuais" (criados na hora pela thread do jogo) e traduzidos na thread de render.
#include "gfx.h"
#include "rt.h"
#include "x86rt.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

void rt_ip_mark_main();
void rt_ip_dump(int frames);
void rt_file_counters(uint64_t &n, uint64_t &ns, uint64_t &bytes);

namespace {
enum : uint8_t { C_TEXC = 1, C_TEXU, C_TEXD, C_BUFC, C_BUFU, C_BUFD, C_DECL, C_SHAD, C_CLEAR, C_DRAW, C_DRAWUP, C_PRESENT, C_BLIT, C_FILL };

struct Blob {
    uint8_t *p = nullptr; size_t n = 0, cap = 0;
    uint8_t *grow(size_t k) { if (n + k > cap) { cap = (n + k) * 2 + (1u << 20); p = (uint8_t *)realloc(p, cap); } uint8_t *r = p + n; n += k; return r; }
    void put(const void *d, size_t k) { memcpy(grow(k), d, k); }
    template <class T> void w(const T &v) { put(&v, sizeof v); }
};
struct Rd {
    const uint8_t *p;
    template <class T> T r() { T v; memcpy(&v, p, sizeof v); p += sizeof v; return v; }
    const uint8_t *take(size_t k) { const uint8_t *q = p; p += k; return q; }
};
static inline double now_s() { timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return t.tv_sec + t.tv_nsec * 1e-9; }

// blocos de constantes enviados so na parte que mudou desde o ultimo desenho
enum { B_VSC, B_PSC, B_VSI, B_PSI, B_VSB, B_PSB, B_TSS, B_N };
static const uint32_t k_bsz[B_N] = {256 * 16, 224 * 16, 16 * 16, 16 * 16, 16 * 4, 16 * 4, 8 * 33 * 4};

struct GfxMT : GfxBackend {
    GfxBackend *in;
    std::mutex qm; std::condition_variable cv_work, cv_idle;
    Blob cur, work; bool has_work = false, quit = false;
    std::thread th;
    // lado do jogo
    uint32_t next_id = 1;
    struct TI { uint32_t h, d; bool dxt; };
    std::unordered_map<uint32_t, TI> tinfo;
    alignas(16) uint8_t last[B_N][256 * 16];
    // lado do render
    std::vector<uint32_t> idmap;
    alignas(16) uint8_t rb[B_N][256 * 16];
    alignas(16) float rxf[512 * 16];
    // tempos (lado do jogo)
    double t_wait = 0, t_f0 = 0; uint64_t frames = 0;
    double t_last = 0, fr_wait = 0; uint64_t fr_fn = 0, fr_fns = 0, fr_fb = 0; uint32_t fr_texc = 0, fr_texb = 0, fr_bufb = 0, n_spikes = 0;

    explicit GfxMT(GfxBackend *b) : in(b) { memset(last, 0, sizeof last); memset(rb, 0, sizeof rb); memset(rxf, 0, sizeof rxf); idmap.resize(1 << 16, 0); }

    // ---------- thread de render
    uint32_t tr(uint32_t v) const { if (v == 0 || v == 0xFFFFFFFFu) return v; return v < idmap.size() ? idmap[v] : 0; }
    void setid(uint32_t v, uint32_t real) { if (v >= idmap.size()) idmap.resize(v * 2, 0); idmap[v] = real; }
    void read_state(Rd &r, GfxDrawState &s) {
        s = r.r<GfxDrawState>();
        for (int b = 0; b < B_N; ++b) {
            const uint8_t f = r.r<uint8_t>();
            if (f) { const uint16_t lo = r.r<uint16_t>(), hi = r.r<uint16_t>(); if (hi > lo) memcpy(rb[b] + lo * 16, r.take((hi - lo) * 16), (hi - lo) * 16); }
            const void *p = f ? rb[b] : nullptr;
            switch (b) {
            case B_VSC: s.vsc = (const float *)p; break; case B_PSC: s.psc = (const float *)p; break;
            case B_VSI: s.vsi = (const int32_t *)p; break; case B_PSI: s.psi = (const int32_t *)p; break;
            case B_VSB: s.vsb = (const uint32_t *)p; break; case B_PSB: s.psb = (const uint32_t *)p; break;
            case B_TSS: s.tss = (const uint32_t *)p; break;
            }
        }
        if (r.r<uint8_t>()) { memcpy(rxf + 256 * 16, r.take(64), 64); memcpy(rxf + 2 * 16, r.take(64), 64); memcpy(rxf + 3 * 16, r.take(64), 64); }
        s.xf = rxf;
        for (auto &t : s.tex) t = tr(t);
        for (auto &t : s.vbuf) t = tr(t);
        for (auto &t : s.rt) t = tr(t);
        s.ibuf = tr(s.ibuf); s.vdecl = tr(s.vdecl); s.vs = tr(s.vs); s.ps = tr(s.ps); s.ds = tr(s.ds);
    }
    void exec(const Blob &b) {
        Rd r{b.p}; const uint8_t *end = b.p + b.n;
        GfxDrawState s;
        while (r.p < end) {
            switch (r.r<uint8_t>()) {
            case C_TEXC: { const uint32_t id = r.r<uint32_t>(); const GfxTexType t = r.r<GfxTexType>(); const uint32_t w = r.r<uint32_t>(), h = r.r<uint32_t>(), d = r.r<uint32_t>(), l = r.r<uint32_t>(), f = r.r<uint32_t>(); const bool rt = r.r<uint8_t>();
                setid(id, in->tex_create(t, w, h, d, l, f, rt)); break; }
            case C_TEXU: { const uint32_t id = r.r<uint32_t>(), lv = r.r<uint32_t>(), fc = r.r<uint32_t>(), pitch = r.r<uint32_t>(), n = r.r<uint32_t>(); const uint8_t *d = r.take(n);
                in->tex_upload(tr(id), lv, fc, n ? d : nullptr, pitch); break; }
            case C_TEXD: { const uint32_t id = r.r<uint32_t>(); in->tex_destroy(tr(id)); setid(id, 0); break; }
            case C_BUFC: { const uint32_t id = r.r<uint32_t>(); const GfxBufKind k = r.r<GfxBufKind>(); const uint32_t sz = r.r<uint32_t>(); setid(id, in->buf_create(k, sz)); break; }
            case C_BUFU: { const uint32_t id = r.r<uint32_t>(), off = r.r<uint32_t>(), n = r.r<uint32_t>(); in->buf_upload(tr(id), off, r.take(n), n); break; }
            case C_BUFD: { const uint32_t id = r.r<uint32_t>(); in->buf_destroy(tr(id)); setid(id, 0); break; }
            case C_DECL: { const uint32_t id = r.r<uint32_t>(); const int n = r.r<int>(); setid(id, in->vdecl_create(r.take(8u * (n + 1)), n)); break; }
            case C_SHAD: { const uint32_t id = r.r<uint32_t>(); const bool px = r.r<uint8_t>(); const uint32_t n = r.r<uint32_t>();
                std::vector<uint32_t> code(n); memcpy(code.data(), r.take(4u * n), 4u * n); setid(id, in->shader_create(px, code.data(), n)); break; }
            case C_CLEAR: { read_state(r, s); const uint32_t fl = r.r<uint32_t>(), col = r.r<uint32_t>(); const float z = r.r<float>(); const uint32_t st = r.r<uint32_t>(); in->clear(s, fl, col, z, st); break; }
            case C_DRAW: { read_state(r, s); const uint32_t prim = r.r<uint32_t>(), start = r.r<uint32_t>(), count = r.r<uint32_t>(); const bool ix = r.r<uint8_t>(); const int32_t bv = r.r<int32_t>(); const uint32_t a6 = r.r<uint32_t>(), a7 = r.r<uint32_t>();
                in->draw(s, prim, start, count, ix, bv, a6, a7); break; }
            case C_DRAWUP: { read_state(r, s); const uint32_t prim = r.r<uint32_t>(), count = r.r<uint32_t>(), stride = r.r<uint32_t>(), ifmt = r.r<uint32_t>(), nv = r.r<uint32_t>(), vn = r.r<uint32_t>(), in_ = r.r<uint32_t>();
                const uint8_t *v = r.take(vn); const uint8_t *ix = r.take(in_); in->draw_up(s, prim, count, v, stride, in_ ? ix : nullptr, ifmt, nv); break; }
            case C_PRESENT: in->present(); break;
            case C_BLIT: { const uint32_t a = r.r<uint32_t>(), b2 = r.r<uint32_t>(); const uint8_t f = r.r<uint8_t>(); int ra[4], rb2[4]; memcpy(ra, r.take(16), 16); memcpy(rb2, r.take(16), 16); const bool lin = r.r<uint8_t>();
                in->blit(tr(a), (f & 1) ? ra : nullptr, tr(b2), (f & 2) ? rb2 : nullptr, lin); break; }
            case C_FILL: { const uint32_t d = r.r<uint32_t>(); const uint8_t f = r.r<uint8_t>(); int rr[4]; memcpy(rr, r.take(16), 16); const uint32_t col = r.r<uint32_t>(); in->fill(tr(d), f ? rr : nullptr, col); break; }
            default: rt_log("[gfx-mt] comando invalido\n"); return;
            }
        }
    }
    void loop() {
        for (;;) {
            std::unique_lock<std::mutex> lk(qm);
            cv_work.wait(lk, [&] { return has_work || quit; });
            if (quit) return;
            lk.unlock();
            exec(work);
            lk.lock(); work.n = 0; has_work = false; cv_idle.notify_all();
        }
    }
    // ---------- lado do jogo
    void flush() {   // entrega o lote atual; espera so se o lote anterior ainda esta sendo desenhado
        const double t0 = now_s();
        std::unique_lock<std::mutex> lk(qm);
        cv_idle.wait(lk, [&] { return !has_work; });
        std::swap(cur, work); has_work = true; cv_work.notify_one();
        t_wait += now_s() - t0;
    }
    void put_state(const GfxDrawState &s) {
        cur.w(s);
        const void *ps[B_N] = {s.vsc, s.psc, s.vsi, s.psi, s.vsb, s.psb, s.tss};
        for (int b = 0; b < B_N; ++b) {
            if (!ps[b]) { cur.w<uint8_t>(0); continue; }
            cur.w<uint8_t>(1);
            const uint8_t *p = (const uint8_t *)ps[b]; uint8_t *l = last[b]; const uint32_t nv = k_bsz[b] / 16;
            uint32_t lo = 0, hi = nv;
            while (lo < nv && !memcmp(p + lo * 16, l + lo * 16, 16)) ++lo;
            if (lo == nv) { cur.w<uint16_t>(0); cur.w<uint16_t>(0); continue; }
            while (hi > lo && !memcmp(p + (hi - 1) * 16, l + (hi - 1) * 16, 16)) --hi;
            cur.w<uint16_t>((uint16_t)lo); cur.w<uint16_t>((uint16_t)hi);
            cur.put(p + lo * 16, (hi - lo) * 16); memcpy(l + lo * 16, p + lo * 16, (hi - lo) * 16);
        }
        if (!s.vs && s.xf) { cur.w<uint8_t>(1); cur.put(s.xf + 256 * 16, 64); cur.put(s.xf + 2 * 16, 64); cur.put(s.xf + 3 * 16, 64); }
        else cur.w<uint8_t>(0);
    }
    void maybe_flush() { if (cur.n > (64u << 20)) flush(); }

    bool init(int w, int h) override {
        std::mutex m; std::condition_variable c; bool done = false, ok = false;
        th = std::thread([&, w, h] {
            const bool r = in->init(w, h);
            { std::lock_guard<std::mutex> lk(m); ok = r; done = true; } c.notify_one();
            if (r) loop();
        });
        std::unique_lock<std::mutex> lk(m); c.wait(lk, [&] { return done; });
        if (!ok) { th.join(); return false; }
        th.detach();
        rt_log("[gfx-mt] render em thread propria (outro nucleo)\n");
        return true;
    }
    uint32_t tex_create(GfxTexType t, uint32_t w, uint32_t h, uint32_t d, uint32_t levels, uint32_t fmt, bool rt) override {
        std::lock_guard<std::mutex> lk(qm_g);
        const uint32_t id = next_id++;
        const bool dxt = fmt == 0x31545844u || fmt == 0x32545844u || fmt == 0x33545844u || fmt == 0x34545844u || fmt == 0x35545844u;
        tinfo[id] = TI{h, t == GfxTexType::Volume ? d : 1, dxt};
        ++fr_texc;
        cur.w(C_TEXC); cur.w(id); cur.w(t); cur.w(w); cur.w(h); cur.w(d); cur.w(levels); cur.w(fmt); cur.w<uint8_t>(rt);
        return id;
    }
    void tex_upload(uint32_t id, uint32_t level, uint32_t face, const uint8_t *data, uint32_t pitch) override {
        std::lock_guard<std::mutex> lk(qm_g);
        auto it = tinfo.find(id); uint32_t n = 0;
        if (it != tinfo.end() && data) {
            const uint32_t h = std::max(1u, it->second.h >> level), d = std::max(1u, it->second.d >> level);
            n = pitch * (it->second.dxt ? (h + 3) / 4 : h) * d;
        }
        fr_texb += n;
        cur.w(C_TEXU); cur.w(id); cur.w(level); cur.w(face); cur.w(pitch); cur.w(n); if (n) cur.put(data, n);
        maybe_flush();
    }
    void tex_destroy(uint32_t id) override { std::lock_guard<std::mutex> lk(qm_g); tinfo.erase(id); cur.w(C_TEXD); cur.w(id); }
    uint32_t buf_create(GfxBufKind k, uint32_t size) override { std::lock_guard<std::mutex> lk(qm_g); const uint32_t id = next_id++; cur.w(C_BUFC); cur.w(id); cur.w(k); cur.w(size); return id; }
    void buf_upload(uint32_t id, uint32_t off, const uint8_t *data, uint32_t size) override {
        std::lock_guard<std::mutex> lk(qm_g); fr_bufb += size; cur.w(C_BUFU); cur.w(id); cur.w(off); cur.w(size); cur.put(data, size); maybe_flush();
    }
    void buf_destroy(uint32_t id) override { std::lock_guard<std::mutex> lk(qm_g); cur.w(C_BUFD); cur.w(id); }
    uint32_t vdecl_create(const uint8_t *e, int n) override { std::lock_guard<std::mutex> lk(qm_g); const uint32_t id = next_id++; cur.w(C_DECL); cur.w(id); cur.w(n); cur.put(e, 8u * (n + 1)); return id; }
    uint32_t shader_create(bool px, const uint32_t *code, uint32_t nd) override { std::lock_guard<std::mutex> lk(qm_g); const uint32_t id = next_id++; cur.w(C_SHAD); cur.w(id); cur.w<uint8_t>(px); cur.w(nd); cur.put(code, 4u * nd); return id; }
    void clear(const GfxDrawState &s, uint32_t fl, uint32_t col, float z, uint32_t st) override {
        std::lock_guard<std::mutex> lk(qm_g); cur.w(C_CLEAR); put_state(s); cur.w(fl); cur.w(col); cur.w(z); cur.w(st);
    }
    void draw(const GfxDrawState &s, uint32_t prim, uint32_t start, uint32_t count, bool ix, int32_t bv, uint32_t a6, uint32_t a7) override {
        std::lock_guard<std::mutex> lk(qm_g); cur.w(C_DRAW); put_state(s); cur.w(prim); cur.w(start); cur.w(count); cur.w<uint8_t>(ix); cur.w(bv); cur.w(a6); cur.w(a7);
    }
    void draw_up(const GfxDrawState &s, uint32_t prim, uint32_t count, const uint8_t *verts, uint32_t stride, const uint8_t *idx, uint32_t ifmt, uint32_t nverts) override {
        std::lock_guard<std::mutex> lk(qm_g);
        const uint32_t vn = (idx ? nverts : count) * stride, in_ = idx ? count * (ifmt == 102 ? 4 : 2) : 0;
        cur.w(C_DRAWUP); put_state(s); cur.w(prim); cur.w(count); cur.w(stride); cur.w(ifmt); cur.w(nverts); cur.w(vn); cur.w(in_);
        if (vn) cur.put(verts, vn); if (in_) cur.put(idx, in_);
    }
    void blit(uint32_t a, const int *ra, uint32_t b, const int *rb2, bool lin) override {
        std::lock_guard<std::mutex> lk(qm_g); int z[4] = {0, 0, 0, 0};
        cur.w(C_BLIT); cur.w(a); cur.w(b); cur.w<uint8_t>((ra ? 1 : 0) | (rb2 ? 2 : 0)); cur.put(ra ? ra : z, 16); cur.put(rb2 ? rb2 : z, 16); cur.w<uint8_t>(lin);
    }
    void fill(uint32_t d, const int *r, uint32_t col) override {
        std::lock_guard<std::mutex> lk(qm_g); int z[4] = {0, 0, 0, 0}; cur.w(C_FILL); cur.w(d); cur.w<uint8_t>(r ? 1 : 0); cur.put(r ? r : z, 16); cur.w(col);
    }
    void present() override {
        rt_ip_mark_main();
        { std::lock_guard<std::mutex> lk(qm_g); cur.w(C_PRESENT); flush(); }
        const double t = now_s();
        {   // detector de travadas: quadro da thread do jogo acima de 120 ms -> o que aconteceu nele
            uint64_t fn, fns, fb; rt_file_counters(fn, fns, fb);
            const double dt = t_last > 0 ? (t - t_last) * 1000.0 : 0;
            if (dt > 120.0 && n_spikes < 200) {
                ++n_spikes;
                rt_log("[travada] quadro %llu: %.0f ms | arquivos: %llu leituras, %.1f ms, %llu KB | esperando o render %.1f ms | texturas novas %u, envio %u KB | buffers %u KB | fila do streaming %u\n",
                       (unsigned long long)frames, dt, (unsigned long long)(fn - fr_fn), (fns - fr_fns) / 1e6, (unsigned long long)((fb - fr_fb) >> 10),
                       (t_wait - fr_wait) * 1000.0, fr_texc, fr_texb >> 10, fr_bufb >> 10, rd32(0xCA3988u));
            }
            t_last = t; fr_fn = fn; fr_fns = fns; fr_fb = fb; fr_wait = t_wait; fr_texc = 0; fr_texb = 0; fr_bufb = 0;
        }
        if (++frames % 300 == 0) {
            if (t_f0 > 0) { const double tot = (t - t_f0) * 1000.0 / 300.0;
                rt_log("[principal] thread do jogo: %.1f ms/quadro (%.1f FPS) | esperando o render %.1f ms\n", tot, 1000.0 / tot, t_wait * 1000.0 / 300.0); }
            rt_ip_dump(300);
            t_f0 = t; t_wait = 0; fr_wait = 0;
        }
    }
    std::mutex qm_g;   // serializa chamadas de threads diferentes do jogo
};
}  // namespace

GfxBackend *gfx_wrap_threaded(GfxBackend *b) { return b ? new GfxMT(b) : b; }
