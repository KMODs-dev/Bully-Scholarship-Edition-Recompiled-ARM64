#include <set>
// Backend OpenGL ES 3 da camada D3D9 (ver gfx.h). Roda na thread do jogo.
//  - O "backbuffer" do D3D e uma textura num FBO do tamanho pedido pelo jogo; o Present copia (escalando, com faixas
//    pretas) para a janela. Tudo e desenhado em FBO com Y invertido no VS, entao a linha 0 do GL = linha 0 do D3D
//    (topo), igual as texturas enviadas pelo jogo; viewport/scissor do D3D valem direto.
//  - Shaders: bytecode D3D9 -> GLSL pelo sm_translate; programa = (VS, PS, mascara de cores BGRA, variante do
//    pipeline fixo). Pipeline fixo (vs/ps = 0) simplificado: posicao transformada ou pretransformada, cor, textura 0.
#include "gfx.h"
#include "gl_inc.h"
#include "rt.h"
#include "sm_translate.h"
#include "input.h"
#include <map>
#include <initializer_list>
#include <sys/stat.h>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <time.h>

void (*gles_hook_make_current)() = nullptr;
void (*gles_hook_window_size)(int *, int *) = nullptr;
void (*gles_hook_swap)() = nullptr;

#define FOURCC(a, b, c, d) ((uint32_t)(a) | ((uint32_t)(b) << 8) | ((uint32_t)(c) << 16) | ((uint32_t)(d) << 24))
static const uint32_t FMT_DXT1 = FOURCC('D', 'X', 'T', '1'), FMT_DXT2 = FOURCC('D', 'X', 'T', '2'), FMT_DXT3 = FOURCC('D', 'X', 'T', '3'),
                      FMT_DXT4 = FOURCC('D', 'X', 'T', '4'), FMT_DXT5 = FOURCC('D', 'X', 'T', '5');

// ---------------------------------------------------------------- formatos
static const bool k_probe = false;
void rt_ip_mark_main();
void rt_ip_dump(int frames);
static inline double now_s() { struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts); return ts.tv_sec + ts.tv_nsec * 1e-9; }
// tempo por quadro: desenhos (CPU do driver), troca de buffer (espera da GPU), envio de texturas e o resto (jogo)
static double g_t_draw = 0, g_t_swap = 0, g_t_tex = 0, g_t_frame0 = 0;
static uint64_t g_skin_draws = 0;   // desenhos com ossos (personagens) nos ultimos 300 quadros
enum Conv { CV_COPY, CV_BGRA, CV_BGRX, CV_1555, CV_X555, CV_4444, CV_DXT1, CV_DXT3, CV_DXT5, CV_RGBA16, CV_L16, CV_S3TC };
bool g_tela_cheia = false;   // launcher: "tela=1"
static bool g_s3tc = false;
static bool g_flin = false;   // GL_OES_texture_float_linear: sem ela, textura float 32 com filtro linear fica incompleta (amostra 0)   // GPU aceita DXT direto (8x menos memoria e sem decodificar na CPU)
struct FmtInfo { GLenum ifmt, efmt, etype; Conv conv; uint32_t bpp; GLint swz[4]; bool depth; };
static const GLint SW_ID[4] = {GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA};
static bool fmt_info(uint32_t f, FmtInfo &o) {
    auto set = [&](GLenum i, GLenum e, GLenum t, Conv c, uint32_t bpp, GLint r = GL_RED, GLint g = GL_GREEN, GLint b = GL_BLUE, GLint a = GL_ALPHA) {
        o.ifmt = i; o.efmt = e; o.etype = t; o.conv = c; o.bpp = bpp; o.swz[0] = r; o.swz[1] = g; o.swz[2] = b; o.swz[3] = a; o.depth = false; };
    switch (f) {
    case 21: set(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, CV_BGRA, 32); return true;
    // X8R8G8B8 / X1R5G5B5: no D3D9 o alfa lido e sempre 1. Importa quando a textura e ALVO de desenho (as roupas do
    // jogador sao montadas em texturas 512x512 X8R8G8B8): no GL o alfa gravado ali era 0 e o tronco do Jimmy sumia
    case 22: set(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, CV_BGRX, 32, GL_RED, GL_GREEN, GL_BLUE, GL_ONE); return true;
    case 32: set(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, CV_COPY, 32); return true;
    case 33: set(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, CV_COPY, 32, GL_RED, GL_GREEN, GL_BLUE, GL_ONE); return true;
    case 23: set(GL_RGB565, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, CV_COPY, 16); return true;
    case 25: set(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, CV_1555, 16); return true;
    case 24: set(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, CV_X555, 16, GL_RED, GL_GREEN, GL_BLUE, GL_ONE); return true;
    case 26: set(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, CV_4444, 16); return true;
    case 28: set(GL_R8, GL_RED, GL_UNSIGNED_BYTE, CV_COPY, 8, GL_ZERO, GL_ZERO, GL_ZERO, GL_RED); return true;
    case 50: set(GL_R8, GL_RED, GL_UNSIGNED_BYTE, CV_COPY, 8, GL_RED, GL_RED, GL_RED, GL_ONE); return true;
    case 51: set(GL_RG8, GL_RG, GL_UNSIGNED_BYTE, CV_COPY, 16, GL_RED, GL_RED, GL_RED, GL_GREEN); return true;
    case 81: set(GL_R8, GL_RED, GL_UNSIGNED_BYTE, CV_L16, 16, GL_RED, GL_RED, GL_RED, GL_ONE); return true;
    case 60: set(GL_RG8_SNORM, GL_RG, GL_BYTE, CV_COPY, 16, GL_RED, GL_GREEN, GL_ONE, GL_ONE); return true;
    case 63: set(GL_RGBA8_SNORM, GL_RGBA, GL_BYTE, CV_COPY, 32); return true;
    case 35: set(GL_RGB10_A2, GL_RGBA, GL_UNSIGNED_INT_2_10_10_10_REV, CV_COPY, 32, GL_BLUE, GL_GREEN, GL_RED, GL_ALPHA); return true;
    case 36: set(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, CV_RGBA16, 64); return true;
    case 111: set(GL_R16F, GL_RED, GL_HALF_FLOAT, CV_COPY, 16, GL_RED, GL_ONE, GL_ONE, GL_ONE); return true;
    case 112: set(GL_RG16F, GL_RG, GL_HALF_FLOAT, CV_COPY, 32, GL_RED, GL_GREEN, GL_ONE, GL_ONE); return true;
    case 113: set(GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT, CV_COPY, 64); return true;
    case 114: set(GL_R32F, GL_RED, GL_FLOAT, CV_COPY, 32, GL_RED, GL_ONE, GL_ONE, GL_ONE); return true;
    case 115: set(GL_RG32F, GL_RG, GL_FLOAT, CV_COPY, 64, GL_RED, GL_GREEN, GL_ONE, GL_ONE); return true;
    case 116: set(GL_RGBA32F, GL_RGBA, GL_FLOAT, CV_COPY, 128); return true;
    case 70: case 80: set(GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, CV_COPY, 16); o.depth = true; return true;
    case 71: case 73: case 75: case 77: case 82: case 83: set(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, CV_COPY, 32); o.depth = true; return true;
    }
    // DXT: direto se a GPU tiver S3TC; senao decodifica na CPU para 16 bits (RGB5A1 / RGBA4: metade da memoria do RGBA8)
    if (f == FMT_DXT1) { if (g_s3tc) set(0x83F1, 0, 0, CV_S3TC, 4); else set(GL_RGB5_A1, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, CV_DXT1, 4); return true; }
    if (f == FMT_DXT2 || f == FMT_DXT3) { if (g_s3tc) set(0x83F2, 0, 0, CV_S3TC, 8); else set(GL_RGBA4, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, CV_DXT3, 8); return true; }
    if (f == FMT_DXT4 || f == FMT_DXT5) { if (g_s3tc) set(0x83F3, 0, 0, CV_S3TC, 8); else set(GL_RGBA4, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, CV_DXT5, 8); return true; }
    return false;
}

// ---- DXT na CPU (a Mali nao tem S3TC)
static void c565(uint16_t c, uint8_t *o) { o[0] = (uint8_t)(((c >> 11) & 31) * 255 / 31); o[1] = (uint8_t)(((c >> 5) & 63) * 255 / 63); o[2] = (uint8_t)((c & 31) * 255 / 31); }
static void dxt_color(const uint8_t *b, uint8_t out[16][4], bool dxt1) {
    uint16_t c0, c1; memcpy(&c0, b, 2); memcpy(&c1, b + 2, 2);
    uint8_t p[4][4]; c565(c0, p[0]); c565(c1, p[1]); p[0][3] = p[1][3] = 255;
    if (c0 > c1 || !dxt1) {
        for (int k = 0; k < 3; ++k) { p[2][k] = (uint8_t)((2 * p[0][k] + p[1][k]) / 3); p[3][k] = (uint8_t)((p[0][k] + 2 * p[1][k]) / 3); }
        p[2][3] = p[3][3] = 255;
    } else {
        for (int k = 0; k < 3; ++k) { p[2][k] = (uint8_t)((p[0][k] + p[1][k]) / 2); p[3][k] = 0; }
        p[2][3] = 255; p[3][3] = 0;
    }
    uint32_t idx; memcpy(&idx, b + 4, 4);
    for (int i = 0; i < 16; ++i) memcpy(out[i], p[(idx >> (2 * i)) & 3], 4);
}
// pool pequeno de threads para decodificar DXT em paralelo (o celular tem 8 nucleos; a thread de render usa 1)
struct DecPool {
    std::mutex m; std::condition_variable cv, done; const std::function<void(int)> *job = nullptr; int n = 0, next = 0, left = 0; uint64_t gen = 0;
    std::vector<std::thread> th;
    DecPool() { for (int i = 0; i < 3; ++i) th.emplace_back([this] { work(); }); for (auto &t : th) t.detach(); }
    void work() {
        uint64_t seen = 0;
        for (;;) {
            std::unique_lock<std::mutex> lk(m); cv.wait(lk, [&] { return gen != seen && next < n; }); seen = gen;
            while (next < n) { const int i = next++; const auto *f = job; lk.unlock(); (*f)(i); lk.lock(); if (--left == 0) done.notify_all(); }
        }
    }
    void run(int cnt, const std::function<void(int)> &f) {
        std::unique_lock<std::mutex> lk(m); job = &f; n = cnt; next = 0; left = cnt; ++gen; cv.notify_all();
        while (next < n) { const int i = next++; lk.unlock(); f(i); lk.lock(); --left; }
        done.wait(lk, [&] { return left == 0; }); job = nullptr; n = 0;
    }
};
static DecPool &dec_pool() { static DecPool *p = new DecPool; return *p; }   // nunca destruido (threads soltas)
static void dxt_decode(const uint8_t *src, uint32_t w, uint32_t h, uint32_t pitch, Conv cv, uint8_t *dst) {
    const uint32_t bw = (w + 3) / 4, bh = (h + 3) / 4, bs = cv == CV_DXT1 ? 8 : 16;
    uint8_t px[16][4];
    for (uint32_t by = 0; by < bh; ++by)
        for (uint32_t bx = 0; bx < bw; ++bx) {
            const uint8_t *b = src + by * pitch + bx * bs;
            if (cv == CV_DXT1) dxt_color(b, px, true);
            else {
                dxt_color(b + 8, px, false);
                if (cv == CV_DXT3) { for (int i = 0; i < 16; ++i) { const uint8_t a = (b[i / 2] >> ((i & 1) * 4)) & 15; px[i][3] = (uint8_t)(a * 17); } }
                else {
                    const uint8_t a0 = b[0], a1 = b[1]; uint8_t al[8]; al[0] = a0; al[1] = a1;
                    if (a0 > a1) for (int k = 1; k < 7; ++k) al[k + 1] = (uint8_t)(((7 - k) * a0 + k * a1) / 7);
                    else { for (int k = 1; k < 5; ++k) al[k + 1] = (uint8_t)(((5 - k) * a0 + k * a1) / 5); al[6] = 0; al[7] = 255; }
                    uint64_t bits = 0; for (int k = 0; k < 6; ++k) bits |= (uint64_t)b[2 + k] << (8 * k);
                    for (int i = 0; i < 16; ++i) px[i][3] = al[(bits >> (3 * i)) & 7];
                }
            }
            for (int y = 0; y < 4; ++y) for (int x = 0; x < 4; ++x) {
                const uint32_t X = bx * 4 + x, Y = by * 4 + y;
                if (X < w && Y < h) memcpy(dst + 4 * (Y * w + X), px[y * 4 + x], 4);
            }
        }
}
static void convert(const FmtInfo &fi, const uint8_t *src, uint32_t w, uint32_t h, uint32_t pitch, std::vector<uint8_t> &out) {
    out.resize((size_t)w * h * 4);
    uint8_t *d = out.data();
    for (uint32_t y = 0; y < h; ++y) {
        const uint8_t *s = src + (size_t)y * pitch; uint8_t *o = d + (size_t)y * w * 4;
        for (uint32_t x = 0; x < w; ++x, o += 4) {
            switch (fi.conv) {
            case CV_BGRA: o[0] = s[4 * x + 2]; o[1] = s[4 * x + 1]; o[2] = s[4 * x]; o[3] = s[4 * x + 3]; break;
            case CV_BGRX: o[0] = s[4 * x + 2]; o[1] = s[4 * x + 1]; o[2] = s[4 * x]; o[3] = 255; break;
            case CV_1555: case CV_X555: { uint16_t v; memcpy(&v, s + 2 * x, 2); o[0] = (uint8_t)(((v >> 10) & 31) * 255 / 31); o[1] = (uint8_t)(((v >> 5) & 31) * 255 / 31); o[2] = (uint8_t)((v & 31) * 255 / 31); o[3] = fi.conv == CV_X555 ? 255 : ((v >> 15) ? 255 : 0); break; }
            case CV_4444: { uint16_t v; memcpy(&v, s + 2 * x, 2); o[0] = (uint8_t)(((v >> 8) & 15) * 17); o[1] = (uint8_t)(((v >> 4) & 15) * 17); o[2] = (uint8_t)((v & 15) * 17); o[3] = (uint8_t)((v >> 12) * 17); break; }
            case CV_RGBA16: for (int k = 0; k < 4; ++k) o[k] = s[8 * x + 2 * k + 1]; break;
            case CV_L16: o[0] = s[2 * x + 1]; break;
            default: break;
            }
        }
    }
}

// ---------------------------------------------------------------- objetos
struct GTex { GLuint id = 0; GLenum target = GL_TEXTURE_2D; uint32_t w = 0, h = 0, d = 1, levels = 1, fmt = 0; bool rt = false, ok = false; FmtInfo fi{}; int pending = 0; uint32_t gen = 0; };
// decodificacao DXT assincrona: o render entrega a textura compactada a nucleos livres e segue desenhando; o envio
// para a GPU acontece quando a conversao fica pronta (no maximo espera se a textura for usada antes disso)
struct DxtJob { uint32_t id, gen, level, w, h, pitch, seq; GLenum tgt; Conv cv; std::vector<uint8_t> src; std::vector<uint16_t> out; };
struct AsyncDxt {
    std::mutex m; std::condition_variable cv_job, cv_done; std::deque<DxtJob *> todo, done; int busy = 0;
    AsyncDxt() { for (int i = 0; i < 3; ++i) std::thread([this] { work(); }).detach(); }
    void work();
    void push(DxtJob *j) { { std::lock_guard<std::mutex> lk(m); todo.push_back(j); } cv_job.notify_one(); }
};
static AsyncDxt &async_dxt() { static AsyncDxt *a = new AsyncDxt; return *a; }
void AsyncDxt::work() {
    std::vector<uint8_t> rgba;
    for (;;) {
        DxtJob *j;
        { std::unique_lock<std::mutex> lk(m); cv_job.wait(lk, [&] { return !todo.empty(); }); j = todo.front(); todo.pop_front(); ++busy; }
        const size_t np = (size_t)j->w * j->h; rgba.resize(np * 4); j->out.resize(np);
        dxt_decode(j->src.data(), j->w, j->h, j->pitch, j->cv, rgba.data());
        const uint8_t *q = rgba.data(); uint16_t *o = j->out.data();
        if (j->cv == CV_DXT1) for (size_t i = 0; i < np; ++i, q += 4) o[i] = (uint16_t)(((q[0] >> 3) << 11) | ((q[1] >> 3) << 6) | ((q[2] >> 3) << 1) | (q[3] >= 128));
        else for (size_t i = 0; i < np; ++i, q += 4) o[i] = (uint16_t)(((q[0] >> 4) << 12) | ((q[1] >> 4) << 8) | ((q[2] >> 4) << 4) | (q[3] >> 4));
        std::vector<uint8_t>().swap(j->src);
        { std::lock_guard<std::mutex> lk(m); done.push_back(j); --busy; }
        cv_done.notify_all();
    }
}

struct GBuf { GLuint id = 0; GLenum target = GL_ARRAY_BUFFER; uint32_t size = 0; };
struct GElem { uint32_t stream, off, type, usage, uidx; };
struct GDecl { std::vector<GElem> e; };
struct GShader { SmShader s; bool ok = false; };
struct GProg {
    GLuint prog = 0; bool ok = false;
    GLint vc = -1, vci = -1, vcb = -1, pc = -1, pci = -1, pcb = -1, fix = -1, at = -1, um = -1, uvp = -1;
    const SmShader *vs = nullptr, *ps = nullptr;
    SmShader ffvs, ffps;   // pipeline fixo (quando vs/ps = 0)
    // ultimo valor enviado de cada uniform: so os registradores que mudaram vao para a GPU
    bool sent = false;
    float svc[256 * 4], spc[224 * 4], sfix[4], sat[4], suvp[4];
    int32_t svi[64], spi[64], svb[16], spb[16];
};
// envia so a faixa de vec4 que mudou desde o ultimo envio deste programa
static void up4f(GLint loc, float *shadow, const float *v, int n, bool force) {
    if (loc < 0) return;
    int lo = 0, hi = n - 1;
    if (!force) {
        while (lo < n && !memcmp(shadow + 4 * lo, v + 4 * lo, 16)) ++lo;
        if (lo == n) return;
        while (hi > lo && !memcmp(shadow + 4 * hi, v + 4 * hi, 16)) --hi;
    }
    memcpy(shadow + 4 * lo, v + 4 * lo, 16 * (hi - lo + 1));
    glUniform4fv(loc + lo, hi - lo + 1, v + 4 * lo);
}
static void upiv(GLint loc, int32_t *shadow, const int32_t *v, int nint, int per, bool force) {
    if (loc < 0 || (!force && !memcmp(shadow, v, 4 * nint))) return;
    memcpy(shadow, v, 4 * nint);
    if (per == 4) glUniform4iv(loc, nint / 4, v); else glUniform1iv(loc, nint, v);
}
static void up4(GLint loc, float *shadow, float a, float b, float c, float d, bool force) {
    if (loc < 0) return;
    const float v[4] = {a, b, c, d};
    if (!force && !memcmp(shadow, v, 16)) return;
    memcpy(shadow, v, 16); glUniform4f(loc, a, b, c, d);
}
#ifndef GL_PROGRAM_BINARY_RETRIEVABLE_HINT
#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT 0x8257
#define GL_PROGRAM_BINARY_LENGTH 0x8741
#endif
#ifndef GL_TEXTURE_COMPARE_MODE
#define GL_TEXTURE_COMPARE_MODE 0x884C
#define GL_TEXTURE_COMPARE_FUNC 0x884D
#define GL_COMPARE_REF_TO_TEXTURE 0x884E
#endif
struct ProgKey { uint32_t vs, ps, mask, ff, shadow; bool operator<(const ProgKey &o) const { return memcmp(this, &o, sizeof *this) < 0; } };

static const GLenum kCmp_[9] = {GL_ALWAYS, GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, GL_ALWAYS};
static GLenum cmpf(uint32_t v) { return (v >= 1 && v <= 8) ? kCmp_[v] : GL_ALWAYS; }
static GLenum blend_f(uint32_t b, bool src) {
    switch (b) {
    case 1: return GL_ZERO; case 2: return GL_ONE; case 3: return GL_SRC_COLOR; case 4: return GL_ONE_MINUS_SRC_COLOR;
    case 5: return GL_SRC_ALPHA; case 6: return GL_ONE_MINUS_SRC_ALPHA; case 7: return GL_DST_ALPHA; case 8: return GL_ONE_MINUS_DST_ALPHA;
    case 9: return GL_DST_COLOR; case 10: return GL_ONE_MINUS_DST_COLOR; case 11: return GL_SRC_ALPHA_SATURATE;
    case 12: return src ? GL_SRC_ALPHA : GL_ONE_MINUS_SRC_ALPHA; case 13: return src ? GL_ONE_MINUS_SRC_ALPHA : GL_SRC_ALPHA;
    case 14: return GL_CONSTANT_COLOR; case 15: return GL_ONE_MINUS_CONSTANT_COLOR;
    }
    return src ? GL_ONE : GL_ZERO;
}
static GLenum blend_op(uint32_t o) { switch (o) { case 2: return GL_FUNC_SUBTRACT; case 3: return GL_FUNC_REVERSE_SUBTRACT; case 4: return GL_MIN; case 5: return GL_MAX; } return GL_FUNC_ADD; }
static GLenum sten_op(uint32_t o) { switch (o) { case 2: return GL_ZERO; case 3: return GL_REPLACE; case 4: return GL_INCR; case 5: return GL_DECR; case 6: return GL_INVERT; case 7: return GL_INCR_WRAP; case 8: return GL_DECR_WRAP; } return GL_KEEP; }
static GLenum wrap(uint32_t a) { switch (a) { case 2: case 5: return GL_MIRRORED_REPEAT; case 3: return GL_CLAMP_TO_EDGE; case 4: return GL_CLAMP_TO_BORDER; } return GL_REPEAT; }

struct GlesGfx : GfxBackend {
    uint32_t next = 1;
    std::unordered_map<uint32_t, GTex> tex;
    std::unordered_map<uint32_t, GBuf> buf;
    std::unordered_map<uint32_t, GDecl> decl;
    std::unordered_map<uint32_t, GShader> sh;
    std::map<ProgKey, GProg> progs;
    std::map<uint64_t, GLuint> fbos;
    std::map<uint32_t, GDecl> fvf_decl;
    int bb_w = 0, bb_h = 0;
    GLuint bb_fbo = 0, bb_tex = 0, bb_depth = 0, vao = 0, stream_vb = 0, stream_ib = 0, black_tex[3] = {0, 0, 0};
    GLuint samplers[20]; bool smp_cmp[20] = {};
    uint32_t samp_state[20][14];
    uint64_t frames = 0, draws = 0, draws_skipped = 0;
    std::vector<uint8_t> tmp;
    GLuint cur_prog = 0;
    uint32_t attr_on = 0;
    bool logged_noshader = false;

    // ---------------- init
    bool init(int w, int h) override {
        if (gles_hook_make_current) gles_hook_make_current();
        bb_w = w; bb_h = h;
        rt_log("[gles] %s | %s | backbuffer %dx%d\n", (const char *)glGetString(GL_RENDERER), (const char *)glGetString(GL_VERSION), w, h);
        {   GLint n = 0; glGetIntegerv(GL_NUM_EXTENSIONS, &n);
            for (GLint i = 0; i < n; ++i) { const char *e = (const char *)glGetStringi(GL_EXTENSIONS, (GLuint)i); if (e && !strcmp(e, "GL_EXT_texture_compression_s3tc")) g_s3tc = true; if (e && !strcmp(e, "GL_OES_texture_float_linear")) g_flin = true; }
            rt_log("[gles] float32 com filtro linear: %s\n", g_flin ? "sim" : "nao (forca NEAREST)");
            rt_log("[gles] DXT: %s\n", g_s3tc ? "direto na GPU (S3TC)" : "decodificado na CPU para 16 bits"); }
        glGenVertexArrays(1, &vao); glBindVertexArray(vao);
        glGenBuffers(1, &stream_vb); glGenBuffers(1, &stream_ib);
        glGenSamplers(20, samplers); memset(samp_state, 0xFF, sizeof samp_state);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        // backbuffer
        glGenTextures(1, &bb_tex); glBindTexture(GL_TEXTURE_2D, bb_tex); glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, w, h);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenRenderbuffers(1, &bb_depth); glBindRenderbuffer(GL_RENDERBUFFER, bb_depth); glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
        glGenFramebuffers(1, &bb_fbo); glBindFramebuffer(GL_FRAMEBUFFER, bb_fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bb_tex, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, bb_depth);
        const GLenum st = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (st != GL_FRAMEBUFFER_COMPLETE) rt_log("[gles] FBO do backbuffer incompleto %04X\n", st);
        glClearColor(0, 0, 0, 1); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        // texturas "sem textura" (o D3D devolve 0,0,0,1)
        const uint8_t blk[4 * 8] = {0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255};
        glGenTextures(3, black_tex);
        glBindTexture(GL_TEXTURE_2D, black_tex[0]); glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 1, 1); glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, blk);
        glBindTexture(GL_TEXTURE_CUBE_MAP, black_tex[1]); glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, GL_RGBA8, 1, 1);
        for (int f = 0; f < 6; ++f) glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + f, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, blk);
        glBindTexture(GL_TEXTURE_3D, black_tex[2]); glTexStorage3D(GL_TEXTURE_3D, 1, GL_RGBA8, 1, 1, 1); glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, blk);
        glFrontFace(GL_CCW);
        return true;
    }

    // ---------------- texturas
    uint32_t tex_create(GfxTexType t, uint32_t w, uint32_t h, uint32_t d, uint32_t levels, uint32_t fmt, bool rt) override {
        while (glGetError() != GL_NO_ERROR) {}   // erro antigo de outra chamada nao conta para esta textura
        const uint32_t id = next++;
        GTex &x = tex[id];
        x.w = w ? w : 1; x.h = h ? h : 1; x.d = d ? d : 1; x.levels = levels ? levels : 1; x.fmt = fmt; x.rt = rt;
        x.target = t == GfxTexType::Cube ? GL_TEXTURE_CUBE_MAP : t == GfxTexType::Volume ? GL_TEXTURE_3D : GL_TEXTURE_2D;
        if (!fmt_info(fmt, x.fi)) { rt_log("[gles] formato de textura %08X sem suporte (vira RGBA8)\n", fmt); fmt_info(21, x.fi); }
        if (rt && !x.fi.depth && x.fi.conv != CV_COPY) { x.fi.conv = CV_COPY; }
        if (rt) { static std::set<uint64_t> vistos; if (vistos.insert(((uint64_t)fmt << 32) | (w << 16) | h).second) rt_log("[gles] alvo de desenho %ux%u fmt %u%s\n", w, h, fmt, x.fi.depth ? " (profundidade)" : ""); }   // alvo de desenho: so a GPU escreve
        glGenTextures(1, &x.id); glActiveTexture(GL_TEXTURE31); glBindTexture(x.target, x.id);   // unidade 31: nao mexe no cache das unidades de desenho
        if (x.target == GL_TEXTURE_3D) glTexStorage3D(x.target, x.levels, x.fi.ifmt, x.w, x.h, x.d);
        else glTexStorage2D(x.target, x.levels, x.fi.ifmt, x.w, x.h);
        if (!x.fi.depth) {
            glTexParameteri(x.target, GL_TEXTURE_SWIZZLE_R, x.fi.swz[0]); glTexParameteri(x.target, GL_TEXTURE_SWIZZLE_G, x.fi.swz[1]);
            glTexParameteri(x.target, GL_TEXTURE_SWIZZLE_B, x.fi.swz[2]); glTexParameteri(x.target, GL_TEXTURE_SWIZZLE_A, x.fi.swz[3]);
        }
        const GLenum e = glGetError();
        x.ok = e == GL_NO_ERROR;
        if (!x.ok) rt_log("[gles] erro %04X ao criar textura %ux%u fmt %08X niveis %u\n", e, x.w, x.h, fmt, x.levels);
        return id;
    }
    void tex_upload(uint32_t id, uint32_t level, uint32_t face, const uint8_t *data, uint32_t pitch) override {
        const double t0 = now_s(); tex_upload_i(id, level, face, data, pitch); g_t_tex += now_s() - t0;
    }
    void tex_upload_i(uint32_t id, uint32_t level, uint32_t face, const uint8_t *data, uint32_t pitch) {
        auto it = tex.find(id); if (it == tex.end() || !it->second.ok) return;
        GTex &x = it->second;
        if (x.rt || x.fi.depth || level >= x.levels) return;
        const uint32_t w = std::max(1u, x.w >> level), h = std::max(1u, x.h >> level), d = std::max(1u, x.d >> level);
        glActiveTexture(GL_TEXTURE31); glBindTexture(x.target, x.id);
        const GLenum tgt = x.target == GL_TEXTURE_CUBE_MAP ? GL_TEXTURE_CUBE_MAP_POSITIVE_X + face : x.target;
        const uint8_t *src = data;
        const uint32_t rows = (x.fi.conv == CV_DXT1 || x.fi.conv == CV_DXT3 || x.fi.conv == CV_DXT5) ? (h + 3) / 4 : h;
        if ((x.fi.conv == CV_DXT1 || x.fi.conv == CV_DXT3 || x.fi.conv == CV_DXT5) && x.target != GL_TEXTURE_3D && w * h >= 64 * 64) {
            DxtJob *j = new DxtJob; j->id = id; j->gen = x.gen; j->level = level; j->w = w; j->h = h; j->pitch = pitch; j->tgt = tgt; j->cv = x.fi.conv;
            j->seq = ++dxt_seq[((uint64_t)id << 8) | (level << 3) | face];
            j->src.assign(data, data + (size_t)pitch * rows);
            ++x.pending; ++dxt_inflight;
            async_dxt().push(j);
            return;
        }
        for (uint32_t z = 0; z < d; ++z) {
            const uint8_t *sl = data + (size_t)z * pitch * rows;
            if (x.fi.conv == CV_S3TC) {   // blocos 4x4 compactados, linha a linha contiguas
                const uint32_t bw = (w + 3) / 4, bs = x.fi.bpp == 4 ? 8 : 16, row = bw * bs;
                if (pitch != row) { tmp.resize((size_t)row * rows); for (uint32_t r = 0; r < rows; ++r) memcpy(&tmp[(size_t)r * row], sl + (size_t)r * pitch, row); src = tmp.data(); }
                else src = sl;
                glCompressedTexSubImage2D(tgt, level, 0, 0, w, h, x.fi.ifmt, (GLsizei)(row * rows), src);
                break;
            }
            if (x.fi.conv == CV_DXT1 || x.fi.conv == CV_DXT3 || x.fi.conv == CV_DXT5) {
                tmp.resize((size_t)w * h * 6); uint8_t *rgba = tmp.data() + (size_t)w * h * 2;
                uint16_t *o16 = (uint16_t *)tmp.data();
                const Conv cvx = x.fi.conv; const uint32_t bh = (h + 3) / 4;
                const int nb = (w * h >= 128 * 128 && bh >= 8) ? 4 : 1; const uint32_t per = (bh + nb - 1) / nb;
                auto band = [&](int b) {   // faixa de linhas de blocos: decodifica e converte para 16 bits
                    const uint32_t b0 = b * per; if (b0 >= bh) return;
                    const uint32_t b1 = std::min(bh, b0 + per), y0 = b0 * 4, y1 = std::min(h, b1 * 4);
                    uint8_t *rg = rgba + (size_t)y0 * w * 4;
                    dxt_decode(sl + (size_t)b0 * pitch, w, y1 - y0, pitch, cvx, rg);
                    uint16_t *o = o16 + (size_t)y0 * w; const size_t np = (size_t)(y1 - y0) * w;
                    if (cvx == CV_DXT1) for (size_t i = 0; i < np; ++i) { const uint8_t *q = rg + 4 * i; o[i] = (uint16_t)(((q[0] >> 3) << 11) | ((q[1] >> 3) << 6) | ((q[2] >> 3) << 1) | (q[3] >= 128)); }
                    else for (size_t i = 0; i < np; ++i) { const uint8_t *q = rg + 4 * i; o[i] = (uint16_t)(((q[0] >> 4) << 12) | ((q[1] >> 4) << 8) | ((q[2] >> 4) << 4) | (q[3] >> 4)); }
                };
                if (nb == 1) band(0); else { const std::function<void(int)> f = band; dec_pool().run(nb, f); }
                src = tmp.data();
            }
            else if (x.fi.conv != CV_COPY) { convert(x.fi, sl, w, h, pitch, tmp); src = tmp.data(); }
            else { src = sl; glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); }
            if (x.target == GL_TEXTURE_3D) glTexSubImage3D(x.target, level, 0, 0, z, w, h, 1, x.fi.efmt, x.fi.etype, src);
            else glTexSubImage2D(tgt, level, 0, 0, w, h, x.fi.efmt, x.fi.etype, src);
            if (x.target != GL_TEXTURE_3D) break;
        }
    }
    std::unordered_map<uint64_t, uint32_t> dxt_seq; int dxt_inflight = 0;
    void dxt_apply(bool wait_all = false) {   // envia para a GPU as conversoes prontas (do render; a thread de render e a dona do GL)
        if (!dxt_inflight) return;
        AsyncDxt &q = async_dxt();
        std::deque<DxtJob *> ready;
        { std::unique_lock<std::mutex> lk(q.m); if (wait_all) q.cv_done.wait(lk, [&] { return (int)q.done.size() >= dxt_inflight; }); ready.swap(q.done); }
        for (DxtJob *j : ready) {
            --dxt_inflight;
            auto it = tex.find(j->id);
            if (it != tex.end() && it->second.gen == j->gen) {
                GTex &x = it->second; --x.pending;
                if (dxt_seq[((uint64_t)j->id << 8) | (j->level << 3) | (j->tgt == x.target ? 0 : j->tgt - GL_TEXTURE_CUBE_MAP_POSITIVE_X)] == j->seq) {
                    glActiveTexture(GL_TEXTURE31); glBindTexture(x.target, x.id);
                    glTexSubImage2D(j->tgt, j->level, 0, 0, j->w, j->h, x.fi.efmt, x.fi.etype, j->out.data());
                    tb_valid = false;
                }
            }
            delete j;
        }
    }
    void dxt_wait(GTex &x) {   // a textura vai ser usada agora: espera as conversoes dela
        while (x.pending > 0) {
            AsyncDxt &q = async_dxt();
            { std::unique_lock<std::mutex> lk(q.m); q.cv_done.wait(lk, [&] { return !q.done.empty(); }); }
            dxt_apply();
        }
    }
    void tex_destroy(uint32_t id) override {
        invalidate_cache();
        auto it = tex.find(id); if (it == tex.end()) return;
        if (it->second.pending) { dxt_wait(it->second); it = tex.find(id); if (it == tex.end()) return; }
        glDeleteTextures(1, &it->second.id);
        for (auto f = fbos.begin(); f != fbos.end();) {   // FBOs que usavam esta textura
            const uint64_t k = f->first;
            if ((k & 0xFFFFF) == id || ((k >> 20) & 0xFFFFF) == id) { glDeleteFramebuffers(1, &f->second); f = fbos.erase(f); } else ++f;
        }
        tex.erase(it);
    }
    // ---------------- buffers
    uint32_t buf_create(GfxBufKind k, uint32_t size) override {
        const uint32_t id = next++; GBuf &b = buf[id];
        b.target = k == GfxBufKind::Index ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER; b.size = size;
        glGenBuffers(1, &b.id); glBindBuffer(b.target, b.id); bound_vb = 0xFFFFFFFFu; glBufferData(b.target, size ? size : 4, nullptr, GL_DYNAMIC_DRAW);
        return id;
    }
    void buf_upload(uint32_t id, uint32_t off, const uint8_t *data, uint32_t size) override {
        auto it = buf.find(id); if (it == buf.end()) return;
        glBindBuffer(it->second.target, it->second.id); bound_vb = 0xFFFFFFFFu;
        if (off == 0 && size == it->second.size) glBufferData(it->second.target, size, data, GL_DYNAMIC_DRAW);   // reaproveita sem esperar a GPU
        else glBufferSubData(it->second.target, off, size, data);
    }
    void buf_destroy(uint32_t id) override { auto it = buf.find(id); if (it == buf.end()) return; glDeleteBuffers(1, &it->second.id); buf.erase(it); for (auto &a : attr_c) a.valid = false; bound_vb = 0xFFFFFFFFu; }
    // ---------------- declaracoes
    uint32_t vdecl_create(const uint8_t *el, int n) override {
        const uint32_t id = next++; GDecl &d = decl[id];
        for (int k = 0; k < n; ++k) {
            const uint8_t *e = el + 8 * k; uint16_t st, off; memcpy(&st, e, 2); memcpy(&off, e + 2, 2);
            if (e[4] == 17) continue;   // UNUSED
            d.e.push_back({st, off, e[4], e[6], e[7]});
        }
        return id;
    }
    const GDecl &decl_of(const GfxDrawState &s) {
        if (s.vdecl) { auto it = decl.find(s.vdecl); if (it != decl.end()) return it->second; }
        auto it = fvf_decl.find(s.fvf); if (it != fvf_decl.end()) return it->second;
        GDecl &d = fvf_decl[s.fvf]; uint32_t off = 0; const uint32_t f = s.fvf;
        const uint32_t pos = f & 0x400E;
        if (pos == 0x4) { d.e.push_back({0, off, 3, 9, 0}); off += 16; }
        else if (pos) {
            d.e.push_back({0, off, 2, 0, 0}); off += 12;
            if (pos == 0x4002) off += 4; else if (pos >= 6) off += 4 * ((pos - 4) / 2);   // XYZW / pesos de blend
        }
        if (f & 0x10) { d.e.push_back({0, off, 2, 3, 0}); off += 12; }
        if (f & 0x20) { d.e.push_back({0, off, 0, 4, 0}); off += 4; }
        if (f & 0x40) { d.e.push_back({0, off, 4, 10, 0}); off += 4; }
        if (f & 0x80) { d.e.push_back({0, off, 4, 10, 1}); off += 4; }
        const uint32_t nt = (f >> 8) & 15;
        for (uint32_t t = 0; t < nt; ++t) {
            const uint32_t fmt = (f >> (16 + 2 * t)) & 3; const uint32_t nc = fmt == 0 ? 2 : fmt == 1 ? 3 : fmt == 2 ? 4 : 1;
            d.e.push_back({0, off, nc - 1, 5, t}); off += 4 * nc;
        }
        return d;
    }
    // ---------------- shaders
    uint32_t shader_create(bool pixel, const uint32_t *code, uint32_t ndw) override {
        const uint32_t id = next++; GShader &g = sh[id];
        g.ok = sm_translate(code, ndw, g.s);
        if (!g.ok) rt_log("[gles] shader %s nao traduzido: %s\n", pixel ? "ps" : "vs", g.s.err.c_str());
        return id;
    }
    // ---------------- programas
    static GLuint compile(GLenum t, const std::string &src) {
        GLuint h = glCreateShader(t); const char *p = src.c_str(); glShaderSource(h, 1, &p, nullptr); glCompileShader(h);
        GLint ok = 0; glGetShaderiv(h, GL_COMPILE_STATUS, &ok);
        if (!ok) {
            char b[2048] = {0}; glGetShaderInfoLog(h, sizeof b, nullptr, b);
            rt_log("[gles] erro ao compilar %s: %s\n", t == GL_VERTEX_SHADER ? "vs" : "ps", b);
            static int dumped = 0; if (dumped++ < 3) rt_log("[gles] fonte:\n%s\n", src.c_str());
            glDeleteShader(h); return 0;
        }
        return h;
    }
    // pipeline fixo: gera "shaders traduzidos" equivalentes
    static void ff_vs(SmShader &v, bool post, bool color, bool texc) {
        v = SmShader(); v.ok = true;
        v.inputs.push_back({post ? 9u : 0u, 0, 0});
        if (color) v.inputs.push_back({10, 0, 1});
        if (texc) v.inputs.push_back({5, 0, 2});
        v.globals = "uniform mat4 u_m;\nuniform vec4 u_vp;\nvec4 oPos = vec4(0.0, 0.0, 0.0, 1.0);\nvec4 oD0 = vec4(1.0);\nvec4 oT0 = vec4(0.0, 0.0, 0.0, 1.0);\n";
        if (post) v.body = "  float W = a0.w != 0.0 ? 1.0 / a0.w : 1.0;\n  vec2 n = vec2((a0.x - u_vp.x) / u_vp.z * 2.0 - 1.0, 1.0 - (a0.y - u_vp.y) / u_vp.w * 2.0);\n  oPos = vec4(n * W, a0.z * W, W);\n";
        else v.body = "  oPos = u_m * vec4(a0.xyz, 1.0);\n";
        if (color) v.body += "  oD0 = a1;\n";
        if (texc) v.body += "  oT0 = a2;\n";
        v.outputs = {{"POSITION0", "oPos"}, {"COLOR0", "oD0"}, {"TEXCOORD0", "oT0"}};
    }
    static void ff_ps(SmShader &p, bool texb, uint32_t cop, uint32_t aop) {
        p = SmShader(); p.ok = true; p.pixel = true; p.ps_inputs = {"COLOR0", "TEXCOORD0"};
        p.globals = "vec4 oC0 = vec4(0.0);\n";
        std::string t = texb ? "texture(s0, V_TEXCOORD0.xy)" : "vec4(1.0)";
        if (texb) p.sampler_type[0] = 2;
        auto op = [&](uint32_t o, const char *c) {
            std::string T = t + c, D = std::string("V_COLOR0") + c;
            switch (o) { case 1: return D; case 2: return T; case 3: return D; case 5: return "(" + T + " * " + D + " * 2.0)"; case 7: return "(" + T + " + " + D + ")"; }
            return "(" + T + " * " + D + ")";
        };
        p.body = "  oC0 = vec4(" + op(cop, ".rgb") + ", " + op(aop, ".a") + ");\n";
    }
    GProg *program(const GfxDrawState &s, uint32_t mask, uint32_t ff, uint32_t shadow) {
        const ProgKey key{s.vs, s.ps, mask, ff, shadow};
        auto it = progs.find(key);
        if (it != progs.end()) return it->second.ok ? &it->second : nullptr;
        GProg &P = progs[key];
        const SmShader *vs = nullptr, *ps = nullptr;
        if (s.vs) { auto v = sh.find(s.vs); if (v == sh.end() || !v->second.ok) return nullptr; vs = &v->second.s; }
        else { ff_vs(P.ffvs, ff & 1, (ff >> 1) & 1, (ff >> 2) & 1); vs = &P.ffvs; }
        if (s.ps) { auto p = sh.find(s.ps); if (p == sh.end() || !p->second.ok) return nullptr; ps = &p->second.s; }
        else { ff_ps(P.ffps, (ff >> 3) & 1, (ff >> 4) & 15, (ff >> 8) & 15); ps = &P.ffps; }
        P.vs = vs; P.ps = ps;
        const std::string vsrc = sm_link_vs(*vs, ps->ps_inputs, mask), psrc = sm_link_ps(*ps, s.ps ? shadow : 0);
        // cache dos programas ja compilados (glProgramBinary): compilar um shader novo no Mali leva 100-300 ms e travava
        // o jogo na primeira vez que cada material aparecia; da segunda partida em diante vem pronto do disco
        uint64_t hsh = 1469598103934665603ull;
        for (const std::string *x : {&vsrc, &psrc}) for (unsigned char ch : *x) { hsh ^= ch; hsh *= 1099511628211ull; }
        char cpath[600]; snprintf(cpath, sizeof cpath, "%s/glcache/%016llx.bin", g_files_dir.c_str(), (unsigned long long)hsh);
        GLint ok = 0;
        P.prog = glCreateProgram();
        if (FILE *cf = fopen(cpath, "rb")) {
            uint32_t fmt = 0; fread(&fmt, 4, 1, cf); fseek(cf, 0, SEEK_END); const long n = ftell(cf) - 4; fseek(cf, 4, SEEK_SET);
            if (n > 0) { std::vector<uint8_t> bin((size_t)n); if (fread(bin.data(), 1, (size_t)n, cf) == (size_t)n) { glProgramBinary(P.prog, fmt, bin.data(), (GLsizei)n); glGetProgramiv(P.prog, GL_LINK_STATUS, &ok); } }
            fclose(cf);
            if (!ok) { glDeleteProgram(P.prog); P.prog = glCreateProgram(); }
            glGetError();
        }
        if (!ok) {
            GLuint hv = compile(GL_VERTEX_SHADER, vsrc);
            GLuint hp = compile(GL_FRAGMENT_SHADER, psrc);
            if (!hv || !hp) { if (hv) glDeleteShader(hv); if (hp) glDeleteShader(hp); return nullptr; }
            glAttachShader(P.prog, hv); glAttachShader(P.prog, hp);
            glProgramParameteri(P.prog, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);
            glLinkProgram(P.prog);
            glDeleteShader(hv); glDeleteShader(hp);
            glGetProgramiv(P.prog, GL_LINK_STATUS, &ok);
            if (!ok) { char b[2048] = {0}; glGetProgramInfoLog(P.prog, sizeof b, nullptr, b); rt_log("[gles] erro ao ligar programa: %s\n", b); return nullptr; }
            GLint blen = 0; glGetProgramiv(P.prog, GL_PROGRAM_BINARY_LENGTH, &blen);
            if (blen > 0) {
                std::vector<uint8_t> bin((size_t)blen); GLenum fmt = 0; GLsizei got = 0;
                glGetProgramBinary(P.prog, blen, &got, &fmt, bin.data());
                if (got > 0) {
                    static bool mk = false; if (!mk) { mk = true; mkdir((g_files_dir + "/glcache").c_str(), 0755); }
                    if (FILE *cf = fopen(cpath, "wb")) { const uint32_t f32 = fmt; fwrite(&f32, 4, 1, cf); fwrite(bin.data(), 1, (size_t)got, cf); fclose(cf); }
                }
            }
            glGetError();
        }
        P.vc = glGetUniformLocation(P.prog, "vc"); P.vci = glGetUniformLocation(P.prog, "vci"); P.vcb = glGetUniformLocation(P.prog, "vcb");
        P.pc = glGetUniformLocation(P.prog, "pc"); P.pci = glGetUniformLocation(P.prog, "pci"); P.pcb = glGetUniformLocation(P.prog, "pcb");
        P.fix = glGetUniformLocation(P.prog, "u_fix"); P.at = glGetUniformLocation(P.prog, "u_at");
        P.um = glGetUniformLocation(P.prog, "u_m"); P.uvp = glGetUniformLocation(P.prog, "u_vp");
        glUseProgram(P.prog); cur_prog = P.prog;
        for (int k = 0; k < 16; ++k) { char n[8]; snprintf(n, sizeof n, "s%d", k); const GLint l = glGetUniformLocation(P.prog, n); if (l >= 0) glUniform1i(l, k); }
        for (int k = 0; k < 4; ++k) { char n[8]; snprintf(n, sizeof n, "vs_s%d", k); const GLint l = glGetUniformLocation(P.prog, n); if (l >= 0) glUniform1i(l, 16 + k); }
        P.ok = true;
        return &P;
    }
    // ---------------- alvos de desenho
    GLuint target_fbo(const GfxDrawState &s, int &w, int &h) {
        const uint32_t r0 = s.rt[0];
        if (r0 == 0 && (s.ds == 0) && !s.rt[1]) { w = bb_w; h = bb_h; return bb_fbo; }
        const uint64_t key = (uint64_t)(r0 & 0xFFFFF) | ((uint64_t)(s.ds & 0xFFFFF) << 20) | ((uint64_t)(s.rt[1] & 0xFFFF) << 40) | ((uint64_t)(s.ds == 0xFFFFFFFFu) << 63);
        GTex *c0 = nullptr;
        if (r0) { auto it = tex.find(r0); if (it != tex.end()) c0 = &it->second; }
        w = c0 ? (int)c0->w : bb_w; h = c0 ? (int)c0->h : bb_h;
        auto f = fbos.find(key); if (f != fbos.end()) return f->second;
        GLuint fb; glGenFramebuffers(1, &fb); glBindFramebuffer(GL_FRAMEBUFFER, fb);
        if (c0) {
            if (c0->fi.depth) glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, c0->id, 0);
            else glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, c0->target == GL_TEXTURE_CUBE_MAP ? GL_TEXTURE_CUBE_MAP_POSITIVE_X : GL_TEXTURE_2D, c0->id, 0);
        } else glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bb_tex, 0);
        GLenum bufs[4] = {GL_COLOR_ATTACHMENT0, GL_NONE, GL_NONE, GL_NONE}; int nb = 1;
        for (int k = 1; k < 4; ++k) if (s.rt[k]) {
            auto it = tex.find(s.rt[k]); if (it == tex.end()) continue;
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + k, GL_TEXTURE_2D, it->second.id, 0); bufs[k] = GL_COLOR_ATTACHMENT0 + k; nb = k + 1;
        }
        glDrawBuffers(nb, bufs);
        if (s.ds == 0) { if (w == bb_w && h == bb_h) glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, bb_depth); }
        else if (s.ds != 0xFFFFFFFFu) {
            auto it = tex.find(s.ds);
            if (it != tex.end() && it->second.fi.depth) {
                const bool st = it->second.fi.ifmt == GL_DEPTH24_STENCIL8;
                glFramebufferTexture2D(GL_FRAMEBUFFER, st ? GL_DEPTH_STENCIL_ATTACHMENT : GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, it->second.id, 0);
            }
        }
        const GLenum stt = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (stt != GL_FRAMEBUFFER_COMPLETE) rt_log("[gles] FBO incompleto %04X (rt %u ds %u)\n", stt, r0, s.ds);
        fbos[key] = fb;
        return fb;
    }
    GLuint cur_fbo = 0xFFFFFFFFu; bool tgt_f32 = false, st_f32 = false;
    void bind_target(const GfxDrawState &s) {
        int w, h; const GLuint fb = target_fbo(s, w, h);
        if (fb != cur_fbo) {
            glBindFramebuffer(GL_FRAMEBUFFER, fb); cur_fbo = fb;
            // alvo float 32 (mapa de sombra R32F): a Mali nao mistura nesse formato (sem EXT_float_blend) e o desenho
            // inteiro falha se a mistura ficou ligada de um desenho anterior; no D3D9 a mistura so era ignorada
            bool f = false;
            if (s.rt[0]) { auto it = tex.find(s.rt[0]); if (it != tex.end()) { const GLenum fm = it->second.fi.ifmt; f = fm == GL_R32F || fm == GL_RG32F || fm == GL_RGBA32F; } }
            tgt_f32 = f;
        }
        glViewport(s.vp_x, s.vp_y, s.vp_w, s.vp_h);
        glDepthRangef(s.vp_minz, s.vp_maxz);
    }
    // ---------------- estados
    // cache do estado fixo do GL: se nada que apply_states usa mudou desde o ultimo desenho, nao reenvia
    bool st_valid = false; uint32_t st_rs[256]; int st_sc[4];
    bool tb_valid = true; GLuint tb_id[20] = {0}; GLenum tb_tg[20] = {0}; bool smp_bound[20] = {false};
    void invalidate_cache() { st_valid = false; for (int k = 0; k < 20; ++k) { tb_id[k] = 0xFFFFFFFFu; smp_bound[k] = false; } for (auto &a : attr_c) a.valid = false; bound_vb = 0xFFFFFFFFu; }
    void apply_states(const GfxDrawState &s) {
        // so reenvia ao GL os grupos de estado que mudaram (antes: qualquer render state diferente reaplicava tudo, ~25 chamadas GL)
        const uint32_t *rs = s.rs;
        const int sc[4] = {s.sc_l, s.sc_t, s.sc_r, s.sc_b};
        if (st_valid && st_f32 == tgt_f32 && !memcmp(st_rs, rs, sizeof st_rs) && !memcmp(st_sc, sc, sizeof sc)) return;
        const bool all = !st_valid || st_f32 != tgt_f32;
        auto D = [&](std::initializer_list<int> l) { if (all) return true; for (int i : l) if (st_rs[i] != rs[i]) return true; return false; };
        if (D({7, 23})) { if (rs[7]) { glEnable(GL_DEPTH_TEST); glDepthFunc(cmpf(rs[23])); } else glDisable(GL_DEPTH_TEST); }
        if (D({14})) glDepthMask(rs[14] ? GL_TRUE : GL_FALSE);
        if (D({168})) { const uint32_t cw = rs[168]; glColorMask(cw & 1, (cw >> 1) & 1, (cw >> 2) & 1, (cw >> 3) & 1); }
        if (D({27, 206, 19, 20, 207, 208, 171, 209, 193})) {
            if (rs[27] && !tgt_f32) {
                glEnable(GL_BLEND);
                if (rs[206]) { glBlendFuncSeparate(blend_f(rs[19], true), blend_f(rs[20], false), blend_f(rs[207], true), blend_f(rs[208], false)); glBlendEquationSeparate(blend_op(rs[171]), blend_op(rs[209])); }
                else { glBlendFunc(blend_f(rs[19], true), blend_f(rs[20], false)); glBlendEquation(blend_op(rs[171])); }
                const uint32_t bf = rs[193]; glBlendColor(((bf >> 16) & 255) / 255.0f, ((bf >> 8) & 255) / 255.0f, (bf & 255) / 255.0f, (bf >> 24) / 255.0f);
            } else glDisable(GL_BLEND);
        }
        if (D({22})) { if (rs[22] == 1) glDisable(GL_CULL_FACE); else { glEnable(GL_CULL_FACE); glCullFace(rs[22] == 2 ? GL_FRONT : GL_BACK); } }
        if (D({52, 53, 54, 55, 56, 57, 58, 59, 185, 186, 187, 188, 189})) {
            if (rs[52]) {
                glEnable(GL_STENCIL_TEST);
                glStencilFuncSeparate(GL_FRONT, cmpf(rs[56]), rs[57], rs[58]);
                glStencilOpSeparate(GL_FRONT, sten_op(rs[53]), sten_op(rs[54]), sten_op(rs[55]));
                if (rs[185]) { glStencilFuncSeparate(GL_BACK, cmpf(rs[189]), rs[57], rs[58]); glStencilOpSeparate(GL_BACK, sten_op(rs[186]), sten_op(rs[187]), sten_op(rs[188])); }
                else { glStencilFuncSeparate(GL_BACK, cmpf(rs[56]), rs[57], rs[58]); glStencilOpSeparate(GL_BACK, sten_op(rs[53]), sten_op(rs[54]), sten_op(rs[55])); }
                glStencilMask(rs[59]);
            } else glDisable(GL_STENCIL_TEST);
        }
        if (D({174}) || memcmp(st_sc, sc, sizeof sc)) {
            if (rs[174]) { glEnable(GL_SCISSOR_TEST); glScissor(s.sc_l, s.sc_t, std::max(0, s.sc_r - s.sc_l), std::max(0, s.sc_b - s.sc_t)); }
            else glDisable(GL_SCISSOR_TEST);
        }
        if (D({195, 175})) {
            float bias, slope; memcpy(&bias, &rs[195], 4); memcpy(&slope, &rs[175], 4);
            if (bias != 0.0f || slope != 0.0f) { glEnable(GL_POLYGON_OFFSET_FILL); glPolygonOffset(slope, bias * 16777216.0f); } else glDisable(GL_POLYGON_OFFSET_FILL);
        }
        memcpy(st_rs, rs, sizeof st_rs); memcpy(st_sc, sc, sizeof sc); st_valid = true; st_f32 = tgt_f32;
    }
    bool smp_near[20] = {};
    void apply_sampler(int unit, const uint32_t *ss, bool near = false) {
        uint32_t *c = samp_state[unit];
        if (smp_near[unit] == near && !memcmp(c + 1, ss + 1, 4 * 10)) return;
        memcpy(c, ss, 4 * 14); smp_near[unit] = near;
        const GLuint sm = samplers[unit];
        glSamplerParameteri(sm, GL_TEXTURE_WRAP_S, wrap(ss[1])); glSamplerParameteri(sm, GL_TEXTURE_WRAP_T, wrap(ss[2])); glSamplerParameteri(sm, GL_TEXTURE_WRAP_R, wrap(ss[3]));
        const bool magl = !near && ss[5] >= 2, minl = !near && ss[6] >= 2;
        glSamplerParameteri(sm, GL_TEXTURE_MAG_FILTER, magl ? GL_LINEAR : GL_NEAREST);
        GLenum mf = minl ? GL_LINEAR : GL_NEAREST;
        if (ss[7] == 1) mf = minl ? GL_LINEAR_MIPMAP_NEAREST : GL_NEAREST_MIPMAP_NEAREST;
        else if (ss[7] == 2) mf = minl ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR;
        glSamplerParameteri(sm, GL_TEXTURE_MIN_FILTER, mf);
        if (near && mf != GL_NEAREST) mf = GL_NEAREST_MIPMAP_NEAREST;
        glSamplerParameterf(sm, GL_TEXTURE_MIN_LOD, (float)ss[9]);
        if (ss[1] == 4 || ss[2] == 4) { const uint32_t b = ss[4]; const float bc[4] = {((b >> 16) & 255) / 255.0f, ((b >> 8) & 255) / 255.0f, (b & 255) / 255.0f, (b >> 24) / 255.0f}; glSamplerParameterfv(sm, GL_TEXTURE_BORDER_COLOR, bc); }
        glSamplerParameterf(sm, GL_TEXTURE_MAX_ANISOTROPY_EXT, (ss[5] == 3 || ss[6] == 3) ? (float)std::max(1u, std::min(ss[10], 8u)) : 1.0f);
    }
    void bind_textures(const GfxDrawState &s, const SmShader *ps, const SmShader *vs) {
        for (int k = 0; k < 20; ++k) {
            const int st = k < 16 ? ps->sampler_type[k] : vs->sampler_type[k];
            if (!st) continue;
            const uint32_t tid = k < 16 ? s.tex[k] : 0;
            const GLenum want = st == 3 ? GL_TEXTURE_CUBE_MAP : st == 4 ? GL_TEXTURE_3D : GL_TEXTURE_2D;
            auto it = tid ? tex.find(tid) : tex.end();
            if (it != tex.end() && it->second.pending) dxt_wait(it->second);
            GLuint gid;
            if (it != tex.end() && it->second.ok && it->second.target == want && !it->second.fi.depth) gid = it->second.id;
            else if (it != tex.end() && it->second.ok && it->second.fi.depth && want == GL_TEXTURE_2D) gid = it->second.id;
            else gid = black_tex[st == 3 ? 1 : st == 4 ? 2 : 0];
            const bool near = !g_flin && it != tex.end() && gid == it->second.id && (it->second.fi.ifmt == GL_R32F || it->second.fi.ifmt == GL_RG32F || it->second.fi.ifmt == GL_RGBA32F);
            if (tb_valid && tb_id[k] == gid && tb_tg[k] == want) { apply_sampler(k, s.ss[k < 16 ? k : 0], near); continue; }
            glActiveTexture(GL_TEXTURE0 + k);
            glBindTexture(want, gid); tb_id[k] = gid; tb_tg[k] = want;
            apply_sampler(k, s.ss[k < 16 ? k : 0], near);
            if (!smp_bound[k]) { glBindSampler(k, samplers[k]); smp_bound[k] = true; }
            {   // textura de profundidade: sem comparacao ela fica incompleta com filtro linear no GLES (amostra 0) e nao faz PCF
                const bool cmp = it != tex.end() && it->second.ok && it->second.fi.depth && gid == it->second.id;
                if (smp_cmp[k] != cmp) {
                    smp_cmp[k] = cmp;
                    glSamplerParameteri(samplers[k], GL_TEXTURE_COMPARE_MODE, cmp ? GL_COMPARE_REF_TO_TEXTURE : GL_NONE);
                    glSamplerParameteri(samplers[k], GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
                }
            }
        }
    }
    // ---------------- atributos
    static void attr_fmt(uint32_t t, GLint &n, GLenum &ty, GLboolean &norm) {
        switch (t) {
        case 0: n = 1; ty = GL_FLOAT; norm = 0; return; case 1: n = 2; ty = GL_FLOAT; norm = 0; return;
        case 2: n = 3; ty = GL_FLOAT; norm = 0; return; case 3: n = 4; ty = GL_FLOAT; norm = 0; return;
        case 4: n = 4; ty = GL_UNSIGNED_BYTE; norm = 1; return; case 5: n = 4; ty = GL_UNSIGNED_BYTE; norm = 0; return;
        case 6: n = 2; ty = GL_SHORT; norm = 0; return; case 7: n = 4; ty = GL_SHORT; norm = 0; return;
        case 8: n = 4; ty = GL_UNSIGNED_BYTE; norm = 1; return; case 9: n = 2; ty = GL_SHORT; norm = 1; return;
        case 10: n = 4; ty = GL_SHORT; norm = 1; return; case 11: n = 2; ty = GL_UNSIGNED_SHORT; norm = 1; return;
        case 12: n = 4; ty = GL_UNSIGNED_SHORT; norm = 1; return; case 13: n = 4; ty = GL_UNSIGNED_INT_2_10_10_10_REV; norm = 0; return;
        case 14: n = 4; ty = GL_INT_2_10_10_10_REV; norm = 1; return; case 15: n = 2; ty = GL_HALF_FLOAT; norm = 0; return;
        case 16: n = 4; ty = GL_HALF_FLOAT; norm = 0; return;
        }
        n = 4; ty = GL_FLOAT; norm = 0;
    }
    // associa as entradas do VS aos elementos da declaracao; up_stride != 0: vertices no stream_vb
    struct AttrC { bool valid; GLuint buf; GLint n; GLenum ty; GLboolean norm; GLsizei stride; uintptr_t off; GLuint div; };
    AttrC attr_c[16] = {}; GLuint bound_vb = 0xFFFFFFFFu;
    void bind_attribs(const GfxDrawState &s, const GDecl &d, const SmShader *vs, int32_t base_vertex, uint32_t up_stride) {
        uint32_t on = 0;
        for (const SmIO &io : vs->inputs) {
            const GElem *e = nullptr;
            for (const GElem &x : d.e) if (x.usage == io.usage && x.uidx == io.index) { e = &x; break; }
            if (!e && io.usage == 0) for (const GElem &x : d.e) if (x.usage == 9 && x.uidx == io.index) { e = &x; break; }
            if (!e && io.usage == 9) for (const GElem &x : d.e) if (x.usage == 0 && x.uidx == io.index) { e = &x; break; }
            const GLuint loc = io.reg;
            if (!e) { if (io.usage == 10) glVertexAttrib4f(loc, 1, 1, 1, 1); else glVertexAttrib4f(loc, 0, 0, 0, 1); continue; }
            GLint n; GLenum ty; GLboolean norm; attr_fmt(e->type, n, ty, norm);
            uintptr_t off; GLsizei stride;
            GLuint bid; GLuint div = 0;
            if (up_stride) { bid = stream_vb; off = e->off; stride = (GLsizei)up_stride; }
            else {
                auto b = buf.find(s.vbuf[e->stream & 15]); if (b == buf.end()) { glVertexAttrib4f(loc, 0, 0, 0, 1); continue; }
                bid = b->second.id;
                stride = (GLsizei)s.vstride[e->stream & 15];
                const uint32_t fq = s.freq[e->stream & 15];
                if (fq & 0x80000000u) { div = fq & 0x3FFFFFFFu; if (!div) div = 1; off = s.voff[e->stream & 15] + e->off; }   // dados por instancia: sem base_vertex
                else off = s.voff[e->stream & 15] + e->off + (intptr_t)base_vertex * stride;
            }
            AttrC &ac = attr_c[loc & 15];   // so reenvia o ponteiro do atributo se algo mudou
            if (!(ac.valid && ac.buf == bid && ac.n == n && ac.ty == ty && ac.norm == norm && ac.stride == stride && ac.off == off && ac.div == div)) {
                if (bound_vb != bid) { glBindBuffer(GL_ARRAY_BUFFER, bid); bound_vb = bid; }
                glVertexAttribPointer(loc, n, ty, norm, stride, (const void *)off);
                if (!ac.valid || ac.div != div) glVertexAttribDivisor(loc, div);
                ac = {true, bid, n, ty, norm, stride, off, div};
            }
            on |= 1u << loc;
        }
        for (int k = 0; k < 16; ++k) {
            const uint32_t b = 1u << k;
            if ((on & b) && !(attr_on & b)) glEnableVertexAttribArray(k);
            else if (!(on & b) && (attr_on & b)) glDisableVertexAttribArray(k);
        }
        attr_on = on;
    }
    uint32_t bgra_mask(const GDecl &d, const SmShader *vs) {
        uint32_t m = 0;
        for (const SmIO &io : vs->inputs)
            for (const GElem &x : d.e) if ((x.usage == io.usage || (io.usage == 0 && x.usage == 9) || (io.usage == 9 && x.usage == 0)) && x.uidx == io.index) { if (x.type == 4) m |= 1u << io.reg; break; }
        return m;
    }
    uint32_t ff_key(const GfxDrawState &s, const GDecl &d) {
        uint32_t k = 0; bool post = false, col = false, tc = false;
        for (const GElem &x : d.e) { if (x.usage == 9) post = true; if (x.usage == 10 && x.uidx == 0) col = true; if (x.usage == 5 && x.uidx == 0) tc = true; }
        if (!s.vs) k |= (post ? 1 : 0) | (col ? 2 : 0) | (tc ? 4 : 0);
        if (!s.ps) {
            const uint32_t cop = s.tss[1], aop = s.tss[4];
            const bool texb = s.tex[0] != 0 && cop != 1;
            k |= (texb ? 8 : 0) | ((cop & 15) << 4) | ((aop & 15) << 8);
        }
        return k;
    }
    // ---------------- desenho
    bool prepare(const GfxDrawState &s, const GDecl &d, GProg *&P) {
        const uint32_t ff = ff_key(s, d);
        // mesmo shader/declaracao/texturas do desenho anterior: reaproveita o programa (sem buscas em mapas por desenho)
        if (lp_ok && lp_vs == s.vs && lp_ps == s.ps && lp_decl == s.vdecl && lp_fvf == s.fvf && lp_ff == ff && lp_dptr == &d && !memcmp(lp_tex, s.tex, sizeof lp_tex)) P = lp_P;
        else { if (!pick_program(s, d, ff, P)) return false; lp_vs = s.vs; lp_ps = s.ps; lp_decl = s.vdecl; lp_fvf = s.fvf; lp_ff = ff; lp_dptr = &d; memcpy(lp_tex, s.tex, sizeof lp_tex); lp_P = P; lp_ok = true; }
        return prepare2(s, P);
    }
    uint32_t lp_vs = 0, lp_ps = 0, lp_decl = 0, lp_fvf = 0, lp_ff = 0, lp_tex[16] = {}; const GDecl *lp_dptr = nullptr; GProg *lp_P = nullptr; bool lp_ok = false;
    bool pick_program(const GfxDrawState &s, const GDecl &d, uint32_t ff, GProg *&P) {
        uint32_t mask = 0;
        if (s.vs) { auto v = sh.find(s.vs); if (v != sh.end() && v->second.ok) mask = bgra_mask(d, &v->second.s); }
        else { SmShader tmpv; ff_vs(tmpv, ff & 1, (ff >> 1) & 1, (ff >> 2) & 1); mask = bgra_mask(d, &tmpv); }
        uint32_t shadow = 0;   // samplers 2D com textura de profundidade (mapa de sombra): comparacao como no D3D9
        if (s.ps) {
            auto p = sh.find(s.ps);
            if (p != sh.end() && p->second.ok)
                for (int k = 0; k < 16; ++k) if (p->second.s.sampler_type[k] == 2 && s.tex[k]) {
                    auto t = tex.find(s.tex[k]); if (t != tex.end() && t->second.ok && t->second.fi.depth) shadow |= 1u << k;
                }
        }
        P = program(s, mask, ff, shadow);
        if (!P) { ++draws_skipped; if (!logged_noshader) { logged_noshader = true; rt_log("[gles] desenho ignorado: programa invalido (vs %u ps %u)\n", s.vs, s.ps); } return false; }
        return true;
    }
    bool prepare2(const GfxDrawState &s, GProg *P) {
        bind_target(s);
        apply_states(s);
        if (cur_prog != P->prog) { glUseProgram(P->prog); cur_prog = P->prog; }
        // constantes
        const bool force = !P->sent; P->sent = true;
        up4f(P->vc, P->svc, s.vsc, 256, force);
        up4f(P->pc, P->spc, s.psc, 224, force);
        upiv(P->vci, P->svi, (const int32_t *)s.vsi, 64, 4, force);
        upiv(P->pci, P->spi, (const int32_t *)s.psi, 64, 4, force);
        upiv(P->vcb, P->svb, (const int32_t *)s.vsb, 16, 1, force);
        upiv(P->pcb, P->spb, (const int32_t *)s.psb, 16, 1, force);
        up4(P->fix, P->sfix, -1.0f, 0.0f, s.vp_w ? 1.0f / s.vp_w : 0.0f, s.vp_h ? -1.0f / s.vp_h : 0.0f, force);
        up4(P->at, P->sat, s.rs[15] ? (float)s.rs[25] : 0.0f, (s.rs[24] & 255) / 255.0f, 0, 0, force);
        up4(P->uvp, P->suvp, (float)s.vp_x, (float)s.vp_y, (float)s.vp_w, (float)s.vp_h, force);
        if (P->um >= 0) {   // mundo * visao * projecao (linha a linha, como o D3D)
            const float *W = s.xf + 256 * 16, *V = s.xf + 2 * 16, *Pr = s.xf + 3 * 16; float t[16], m[16];
            for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) { float a = 0; for (int k = 0; k < 4; ++k) a += W[i * 4 + k] * V[k * 4 + j]; t[i * 4 + j] = a; }
            for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) { float a = 0; for (int k = 0; k < 4; ++k) a += t[i * 4 + k] * Pr[k * 4 + j]; m[i * 4 + j] = a; }
            glUniformMatrix4fv(P->um, 1, GL_FALSE, m);
        }
        bind_textures(s, P->ps, P->vs);
        return true;
    }
    static GLenum mode(uint32_t p) { switch (p) { case 1: return GL_POINTS; case 2: return GL_LINES; case 3: return GL_LINE_STRIP; case 5: return GL_TRIANGLE_STRIP; case 6: return GL_TRIANGLE_FAN; } return GL_TRIANGLES; }
    // diagnostico: em alguns quadros loga cada desenho e a cor media do alvo depois dele
    int probe_left = 0, probe_n = 0;
    void probe_after(const GfxDrawState &s, const char *what, uint32_t prim, uint32_t count) {
        if (!probe_left || probe_n >= 400) return;
        ++probe_n;
        int w, h; target_fbo(s, w, h);
        tmp.resize((size_t)w * h * 4);
        glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, tmp.data());
        uint64_t sr = 0, sg = 0, sb = 0, nz = 0; const size_t np = (size_t)w * h;
        for (size_t i = 0; i < np; ++i) { const uint8_t *q = &tmp[i * 4]; sr += q[0]; sg += q[1]; sb += q[2]; if (q[0] | q[1] | q[2]) ++nz; }
        int nan = 0; if (s.vsc) for (int i = 0; i < 1024; ++i) if (s.vsc[i] != s.vsc[i]) ++nan;
        rt_log("[probe] %s rt=%u ds=%u %ux%d prim=%u n=%u vs=%u ps=%u fvf=%X dcl=%u z=%u/%u ab=%u(%u,%u) at=%u cull=%u cw=%X vp=%d,%d,%d,%d media=(%llu,%llu,%llu) nz=%llu%% nanc=%d",
               what, s.rt[0], s.ds, w, h, prim, count, s.vs, s.ps, s.fvf, s.vdecl, s.rs[7], s.rs[14], s.rs[27], s.rs[19], s.rs[20], s.rs[15], s.rs[22], s.rs[168],
               s.vp_x, s.vp_y, s.vp_w, s.vp_h, (unsigned long long)(sr / np), (unsigned long long)(sg / np), (unsigned long long)(sb / np), (unsigned long long)(nz * 100 / np), nan);
        static uint32_t last_vs = 0; const bool newvs = s.vs != last_vs; last_vs = s.vs;
        if (newvs && s.vs && s.vsc) rt_log(" c0-3=[%.3g %.3g %.3g %.3g | %.3g %.3g %.3g %.3g | %.3g %.3g %.3g %.3g | %.3g %.3g %.3g %.3g]",
               s.vsc[0], s.vsc[1], s.vsc[2], s.vsc[3], s.vsc[4], s.vsc[5], s.vsc[6], s.vsc[7], s.vsc[8], s.vsc[9], s.vsc[10], s.vsc[11], s.vsc[12], s.vsc[13], s.vsc[14], s.vsc[15]);
        rt_log("\n");
    }
    GLuint fbo_of(uint32_t id, int &w, int &h, bool &depth) {
        depth = false;
        if (!id) { w = bb_w; h = bb_h; return bb_fbo; }
        auto it = tex.find(id); if (it == tex.end()) return 0;
        depth = it->second.fi.depth;
        static GfxDrawState s; memset(&s, 0, sizeof s); s.rt[0] = id; s.ds = 0xFFFFFFFFu;
        return target_fbo(s, w, h);
    }
    void blit(uint32_t src, const int *sr, uint32_t dst, const int *dr, bool linear) override {
        st_valid = false;
        int sw, sh, dw, dh; bool sd, dd;
        const GLuint fs = fbo_of(src, sw, sh, sd), fd = fbo_of(dst, dw, dh, dd);
        if (!fs || !fd || sd || dd) return;
        int a[4] = {0, 0, sw, sh}, b[4] = {0, 0, dw, dh};
        if (sr) memcpy(a, sr, sizeof a);
        if (dr) memcpy(b, dr, sizeof b);
        glDisable(GL_SCISSOR_TEST);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, fs); glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fd);
        const bool same = (a[2] - a[0] == b[2] - b[0]) && (a[3] - a[1] == b[3] - b[1]);
        glBlitFramebuffer(a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3], GL_COLOR_BUFFER_BIT, (linear && !same) ? GL_LINEAR : GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0); cur_fbo = 0xFFFFFFFFu;
    }
    void fill(uint32_t dst, const int *r, uint32_t color) override {
        st_valid = false;
        int w, h; bool d; const GLuint f = fbo_of(dst, w, h, d);
        if (!f || d) return;
        glBindFramebuffer(GL_FRAMEBUFFER, f); cur_fbo = f;
        if (r) { glEnable(GL_SCISSOR_TEST); glScissor(r[0], r[1], r[2] - r[0], r[3] - r[1]); } else glDisable(GL_SCISSOR_TEST);
        glColorMask(1, 1, 1, 1);
        glClearColor(((color >> 16) & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, (color & 0xFF) / 255.0f, (color >> 24) / 255.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void clear(const GfxDrawState &s, uint32_t flags, uint32_t color, float z, uint32_t stencil) override {
        st_valid = false;
        bind_target(s);
        GLbitfield m = 0;
        if (flags & 1) { glClearColor(((color >> 16) & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, (color & 0xFF) / 255.0f, (color >> 24) / 255.0f); glColorMask(1, 1, 1, 1); m |= GL_COLOR_BUFFER_BIT; }
        if (flags & 2) { glClearDepthf(z); glDepthMask(GL_TRUE); m |= GL_DEPTH_BUFFER_BIT; }
        if (flags & 4) { glClearStencil((GLint)stencil); glStencilMask(0xFF); m |= GL_STENCIL_BUFFER_BIT; }
        glEnable(GL_SCISSOR_TEST); glScissor(s.vp_x, s.vp_y, s.vp_w, s.vp_h);   // o Clear do D3D vale para o viewport
        glClear(m);
        if (probe_left && probe_n < 400) { ++probe_n; rt_log("[probe] Clear rt=%u ds=%u flags=%u cor=%08X z=%g vp=%d,%d,%d,%d\n", s.rt[0], s.ds, flags, color, z, s.vp_x, s.vp_y, s.vp_w, s.vp_h); }
    }
    void draw(const GfxDrawState &s, uint32_t prim, uint32_t start, uint32_t count, bool indexed, int32_t base_vertex, uint32_t a6, uint32_t a7) override {
        const double t0 = now_s(); draw_i(s, prim, start, count, indexed, base_vertex, a6, a7); g_t_draw += now_s() - t0;
        auto di = decl.find(s.vdecl); if (di != decl.end()) for (const GElem &x : di->second.e) if (x.usage == 2) { ++g_skin_draws; break; }
    }
    void draw_i(const GfxDrawState &s, uint32_t prim, uint32_t start, uint32_t count, bool indexed, int32_t base_vertex, uint32_t, uint32_t) {
        if (!count) return;
        const GDecl &d = decl_of(s); GProg *P;
        if (!prepare(s, d, P)) return;
        const bool i32 = s.ifmt == 102;
        auto issue = [&]() {
            const uint32_t ninst = (s.freq[0] & 0x40000000u) ? (s.freq[0] & 0x3FFFFFFFu) : 1;
            if (indexed && ninst > 1) glDrawElementsInstanced(mode(prim), (GLsizei)count, i32 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT, (const void *)(uintptr_t)(start * (i32 ? 4 : 2)), (GLsizei)ninst);
            else if (indexed) glDrawElements(mode(prim), (GLsizei)count, i32 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT, (const void *)(uintptr_t)(start * (i32 ? 4 : 2)));
            else glDrawArrays(mode(prim), (GLint)start, (GLsizei)count);
            if (tgt_f32) {   // diagnostico das sombras: erro do GL nos primeiros desenhos no mapa de sombra
                static int nchk = 0;
                if (nchk < 40) { ++nchk; const GLenum e = glGetError(); if (e) rt_log("[sombra] erro GL %04X no desenho %d no alvo float (blend %u, cw %X)\n", e, nchk, s.rs[27], s.rs[168]); else if (nchk == 40) rt_log("[sombra] 40 desenhos no mapa de sombra sem erro do GL\n"); }
            }
        };
        if (indexed) {
            auto ib = buf.find(s.ibuf); if (ib == buf.end()) return;
            bind_attribs(s, d, P->vs, base_vertex, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->second.id);
        } else bind_attribs(s, d, P->vs, 0, 0);
        const bool pr = probe_left && probe_n < 400;
        if (pr) {   // diagnostico: quantas amostras passam (com e sem teste de profundidade) e o 1o vertice cru
            GLuint q[2]; glGenQueries(2, q);
            glBeginQuery(GL_ANY_SAMPLES_PASSED, q[0]); issue(); glEndQuery(GL_ANY_SAMPLES_PASSED);
            GLboolean cm[4]; glGetBooleanv(GL_COLOR_WRITEMASK, cm); const GLboolean dt = glIsEnabled(GL_DEPTH_TEST), st = glIsEnabled(GL_STENCIL_TEST), cf = glIsEnabled(GL_CULL_FACE);
            glColorMask(0, 0, 0, 0); glDisable(GL_DEPTH_TEST); glDisable(GL_STENCIL_TEST); glDisable(GL_CULL_FACE);
            glBeginQuery(GL_ANY_SAMPLES_PASSED, q[1]); issue(); glEndQuery(GL_ANY_SAMPLES_PASSED);
            glColorMask(cm[0], cm[1], cm[2], cm[3]); if (dt) glEnable(GL_DEPTH_TEST); if (st) glEnable(GL_STENCIL_TEST); if (cf) glEnable(GL_CULL_FACE);
            GLuint r0 = 0, r1 = 0; glGetQueryObjectuiv(q[0], GL_QUERY_RESULT, &r0); glGetQueryObjectuiv(q[1], GL_QUERY_RESULT, &r1); glDeleteQueries(2, q);
            std::string ds; char bb[64];
            for (const GElem &x : d.e) { snprintf(bb, sizeof bb, " s%u+%u:t%u/u%u.%u", x.stream, x.off, x.type, x.usage, x.uidx); ds += bb; }
            float pv[4] = {0, 0, 0, 0};
            for (const GElem &x : d.e) if ((x.usage == 0 || x.usage == 9) && x.uidx == 0) {
                auto vb = buf.find(s.vbuf[x.stream & 15]); if (vb == buf.end()) break;
                uint32_t vi = 0;
                if (indexed) { auto ib = buf.find(s.ibuf); glBindBuffer(GL_COPY_READ_BUFFER, ib->second.id);
                    if (void *m = glMapBufferRange(GL_COPY_READ_BUFFER, start * (i32 ? 4 : 2), i32 ? 4 : 2, GL_MAP_READ_BIT)) { vi = i32 ? *(uint32_t *)m : *(uint16_t *)m; glUnmapBuffer(GL_COPY_READ_BUFFER); } }
                else vi = start;
                const size_t off = s.voff[x.stream & 15] + (size_t)((int64_t)vi + base_vertex) * s.vstride[x.stream & 15] + x.off;
                glBindBuffer(GL_COPY_READ_BUFFER, vb->second.id);
                if (off + 16 <= vb->second.size) if (void *m = glMapBufferRange(GL_COPY_READ_BUFFER, off, 16, GL_MAP_READ_BIT)) { memcpy(pv, m, 16); glUnmapBuffer(GL_COPY_READ_BUFFER); }
                break;
            }
            rt_log("[probe]   amostras: com z=%u sem z/cull=%u | decl%s | pos0=(%g %g %g %g) stride=%u\n", r0, r1, ds.c_str(), pv[0], pv[1], pv[2], pv[3], s.vstride[0]);
        } else issue();
        if (probe_left) probe_after(s, indexed ? "DIP" : "DP", prim, count);
        ++draws;
    }
    void draw_up(const GfxDrawState &s, uint32_t prim, uint32_t count, const uint8_t *verts, uint32_t stride, const uint8_t *idx, uint32_t ifmt, uint32_t nverts) override {
        const double t0 = now_s(); draw_up_i(s, prim, count, verts, stride, idx, ifmt, nverts); g_t_draw += now_s() - t0;
    }
    void draw_up_i(const GfxDrawState &s, uint32_t prim, uint32_t count, const uint8_t *verts, uint32_t stride, const uint8_t *idx, uint32_t ifmt, uint32_t nverts) {
        if (!count || !stride) return;
        const GDecl &d = decl_of(s); GProg *P;
        if (!prepare(s, d, P)) return;
        glBindBuffer(GL_ARRAY_BUFFER, stream_vb); bound_vb = stream_vb;
        const uint32_t nv = idx ? nverts : count;
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)nv * stride, verts, GL_STREAM_DRAW);
        bind_attribs(s, d, P->vs, 0, stride);
        if (idx) {
            const bool i32 = ifmt == 102;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, stream_ib);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)count * (i32 ? 4 : 2), idx, GL_STREAM_DRAW);
            glDrawElements(mode(prim), (GLsizei)count, i32 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT, nullptr);
        } else glDrawArrays(mode(prim), 0, (GLsizei)count);
        if (probe_left) probe_after(s, "UP", prim, count);
        ++draws;
    }
    void present() override {
        dxt_apply();
        invalidate_cache();
        if (probe_left) { rt_log("[probe] Present (fim do quadro %llu)\n", (unsigned long long)frames); if (--probe_left == 0) probe_n = 0; }
        if (k_probe && (frames == 800 || frames == 1600)) probe_left = 1;   // diagnostico: ligue k_probe para captar quadros
        int ww = bb_w, wh = bb_h;
        if (gles_hook_window_size) gles_hook_window_size(&ww, &wh);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, bb_fbo); glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glDisable(GL_SCISSOR_TEST); glColorMask(1, 1, 1, 1);
        glViewport(0, 0, ww, wh); glClearColor(0, 0, 0, 1); glClear(GL_COLOR_BUFFER_BIT);
        // mantem a proporcao do jogo (faixas pretas) e desvira o Y
        int dw = ww, dh = (int)((int64_t)ww * bb_h / bb_w);
        if (dh > wh) { dh = wh; dw = (int)((int64_t)wh * bb_w / bb_h); }
        if (g_tela_cheia) { dw = ww; dh = wh; }   // opcao do launcher: estica para a tela inteira, sem faixas pretas
        const int x0 = (ww - dw) / 2, y0 = (wh - dh) / 2;
        glBlitFramebuffer(0, 0, bb_w, bb_h, x0, y0 + dh, x0 + dw, y0, GL_COLOR_BUFFER_BIT, GL_LINEAR);
        {   // contador de FPS (media de meio segundo)
            static double t0 = 0; static int nf = 0; ++nf;
            struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts); const double t = ts.tv_sec + ts.tv_nsec * 1e-9;
            if (t0 == 0) t0 = t;
            if (t - t0 >= 0.5) { input_set_fps((float)(nf / (t - t0))); nf = 0; t0 = t; }
        }
        input_overlay_draw(ww, wh);   // controles na tela por cima
        glBindVertexArray(vao); cur_prog = 0;
        { const double t0 = now_s(); if (gles_hook_swap) gles_hook_swap(); g_t_swap += now_s() - t0; }
        glBindFramebuffer(GL_FRAMEBUFFER, bb_fbo); cur_fbo = bb_fbo;
        if (++frames % 300 == 0) {
            rt_log("[gles] %llu quadros, %llu desenhos (%llu ignorados), %zu programas, %zu texturas\n",
                   (unsigned long long)frames, (unsigned long long)draws, (unsigned long long)draws_skipped, progs.size(), tex.size());
            const double t = now_s();
            if (g_t_frame0 > 0) { const double tot = (t - g_t_frame0) * 1000.0 / 300.0, d = g_t_draw * 1000.0 / 300.0, sw = g_t_swap * 1000.0 / 300.0, tx = g_t_tex * 1000.0 / 300.0;
                rt_log("[tempo] por quadro: %.1f ms (%.1f FPS) | desenhos %.1f ms | troca/GPU %.1f ms | texturas %.1f ms | render ocioso/resto %.1f ms | partes de personagens por quadro %.1f\n", tot, 1000.0 / tot, d, sw, tx, tot - d - sw - tx, g_skin_draws / 300.0); }
            g_skin_draws = 0;
            g_t_frame0 = t; g_t_draw = g_t_swap = g_t_tex = 0;
        }
    }
};
GfxBackend *gfx_create_gles() { return new GlesGfx; }
// leitura do backbuffer (teste no PC)
void gles_read_backbuffer(GfxBackend *g, std::vector<uint8_t> &px, int &w, int &h) {
    GlesGfx *x = (GlesGfx *)g; w = x->bb_w; h = x->bb_h; px.resize((size_t)w * h * 4);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, x->bb_fbo); glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, px.data());
    glBindFramebuffer(GL_FRAMEBUFFER, x->bb_fbo);
}
