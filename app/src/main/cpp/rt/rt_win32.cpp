// Camada do Windows (KERNEL32 e cia.) para o Bully PC recompilado. Cada import tem nome, numero de argumentos (stdcall:
// quem chama empilha, a funcao tira) e a implementacao nativa. Import sem implementacao para o jogo com o nome no log.
#include "x86rt.h"
#include "rt.h"
#include "input.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <atomic>
#include <map>
#include <set>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <condition_variable>
#include <signal.h>
#include <deque>
#include <dlfcn.h>
#include <sys/mman.h>
#include <ucontext.h>
#include <sys/syscall.h>
#include <sched.h>
#include <algorithm>

static std::string g_dir;
static thread_local uint32_t t_lasterr = 0;
static thread_local uint32_t t_tls[128];
static std::atomic<uint32_t> g_tls_next{1};
static std::atomic<uint32_t> g_tid_next{0x100};
static thread_local uint32_t t_tid = 0;

static const char *gstr(uint32_t a) { return a ? (const char *)(M + a) : ""; }
static uint32_t gstrdup(const char *s) { const uint32_t n = (uint32_t)strlen(s) + 1; const uint32_t p = rt_alloc(n, false); memcpy(M + p, s, n); return p; }
static uint32_t misc_top = MISC_BASE + 0x20000;
static uint32_t misc_alloc(uint32_t n) { const uint32_t p = misc_top; misc_top += (n + 15) & ~15u; memset(M + p, 0, n); return p; }

std::string rt_host_path(uint32_t gs) {
    std::string p = gstr(gs);
    for (auto &ch : p) if (ch == '\\') ch = '/';
    // tira "C:" e o diretorio do jogo
    if (p.size() > 1 && p[1] == ':') p = p.substr(2);
    if (!p.empty() && p[0] != '/') p = "/" + p;
    static const char *pre = "/bully";
    if (strncasecmp(p.c_str(), pre, strlen(pre)) == 0) p = p.substr(strlen(pre));
    // busca sem diferenciar maiusculas, parte por parte
    std::string cur = g_dir;
    size_t i = 1;
    while (i <= p.size()) {
        size_t j = p.find('/', i); if (j == std::string::npos) j = p.size();
        std::string part = p.substr(i, j - i); i = j + 1;
        if (part.empty() || part == ".") continue;
        std::string found = part;
        if (DIR *d = opendir(cur.c_str())) {
            while (dirent *e = readdir(d)) if (strcasecmp(e->d_name, part.c_str()) == 0) { found = e->d_name; break; }
            closedir(d);
        }
        cur += "/" + found;
    }
    return cur;
}

// ---------------------------------------------------------------- objetos (handles)
struct Obj {
    int kind = 0;                  // 1 arquivo, 2 evento, 3 mutex, 4 semaforo, 5 thread, 6 busca de arquivos
    FILE *f = nullptr;
    std::mutex m; std::condition_variable cv;
    bool manual = false, signaled = false; long count = 0, maxc = 0; uint32_t owner = 0; int rec = 0;
    int waiters = 0; uint64_t gen = 0, handoff = 0;   // mutex justo: quem ja esperava ganha a vez ao liberar (como no Windows)
    std::vector<std::string> list; size_t pos = 0;
    std::string path;              // arquivo: nome (estatistica de leitura)
};
static std::mutex g_obj_mtx;
static std::map<uint32_t, Obj *> g_objs;
static uint32_t g_next_handle = 0x1000;
static uint32_t new_handle(Obj *o) { std::lock_guard<std::mutex> lk(g_obj_mtx); const uint32_t h = g_next_handle; g_next_handle += 4; g_objs[h] = o; return h; }
static Obj *get_obj(uint32_t h) { std::lock_guard<std::mutex> lk(g_obj_mtx); auto it = g_objs.find(h); return it == g_objs.end() ? nullptr : it->second; }

static uint32_t cur_tid() { if (!t_tid) t_tid = g_tid_next++; return t_tid; }

// ---------------------------------------------------------------- diagnostico: ultima chamada ao Windows de cada thread
struct TRec { std::atomic<Cpu *> cpu{nullptr}; std::atomic<const char *> last{nullptr}; std::atomic<uint32_t> ret{0}; std::atomic<uint64_t> n{0}; uint32_t tid = 0; uint64_t seen = 0; };
static TRec g_trec[64]; static std::atomic<int> g_ntrec{0};
static thread_local TRec *t_rec = nullptr;
static inline void diag_note(Cpu &c, const char *name, uint32_t ret) {
    if (!t_rec) { const int i = g_ntrec++; t_rec = &g_trec[i < 64 ? i : 63]; t_rec->tid = cur_tid(); }
    t_rec->cpu.store(&c, std::memory_order_relaxed); t_rec->last.store(name, std::memory_order_relaxed); t_rec->ret.store(ret, std::memory_order_relaxed); t_rec->n.store(t_rec->n.load(std::memory_order_relaxed) + 1, std::memory_order_relaxed);   // so esta thread escreve: sem RMW atomico
}
uint64_t d3d_frames();
struct HookRec { uint64_t n = 0; std::map<uint32_t, uint64_t> callers; };
static std::mutex g_hook_mtx; static std::map<uint32_t, HookRec> g_hooks;
void rt_hook(Cpu &c, uint32_t addr) {
    if (addr == 0x7383F4u) { c.r[0] = 1; return; }   // retorno do IsXInputDevice (WMI): o controle enumerado e de Xbox 360
    std::lock_guard<std::mutex> lk(g_hook_mtx);
    HookRec &h = g_hooks[addr]; ++h.n;
    if (h.callers.size() < 4096) ++h.callers[rd32(c.r[4])];
}
// x86rc: todo "ret" confere se o endereco de retorno parece dado do heap (pilha sobrescrita por um array local que estourou)
void rt_badret(Cpu &c, uint32_t fn) {
    const uint32_t sp = c.r[4];
    if ((rd32(sp) >> 28) == 0xD) return;   // 0xDEADxxxx: retorno de callback chamado pelo runtime
    static std::atomic<int> n{0};
    if (n.fetch_add(1) >= 12) return;
    rt_log("[badret] f_%X retornando para %08X (esp=%08X eax=%08X ecx=%08X edx=%08X ebx=%08X ebp=%08X esi=%08X edi=%08X)\n",
           fn, rd32(sp), sp, c.r[0], c.r[1], c.r[2], c.r[3], c.r[5], c.r[6], c.r[7]);
    for (int k = -32; k < 16; k += 8) {
        rt_log("[badret]  %+4d:", k * 4);
        for (int j = 0; j < 8; ++j) rt_log(" %08X", rd32(sp + 4 * (k + j)));
        rt_log("\n");
    }
}
static void diag_dump(const char *why) {
    rt_log("[diag] %s | quadros apresentados: %llu\n", why, (unsigned long long)d3d_frames());
    const int n = g_ntrec.load() < 64 ? g_ntrec.load() : 64;
    for (int i = 0; i < n; ++i) {
        TRec &r = g_trec[i]; const uint64_t cnt = r.n.load();
        const char *l = r.last.load();
        rt_log("[diag]   thread %X: %llu chamadas (+%llu), ultima %s (retorno %08X)\n", r.tid, (unsigned long long)cnt,
               (unsigned long long)(cnt - r.seen), l ? l : "-", r.ret.load());
        r.seen = cnt;
    }
    {   // ganchos do recompilador (HOOKS no x86rc.py): contagem e quem chamou
        std::lock_guard<std::mutex> lk(g_hook_mtx);
        for (auto &h : g_hooks) {
            std::vector<std::pair<uint64_t, uint32_t>> v; for (auto &k : h.second.callers) v.push_back({k.second, k.first});
            std::sort(v.rbegin(), v.rend());
            std::string t; for (size_t i = 0; i < v.size() && i < 6; ++i) { char b[40]; snprintf(b, sizeof b, " %08X:%llu", v[i].second, (unsigned long long)v[i].first); t += b; }
            rt_log("[diag]   gancho %08X: %llu vezes; quem chamou:%s\n", h.first, (unsigned long long)h.second.n, t.c_str());
        }
    }
    // pools do jogo (estilo GTA: CPool em 0xC0F5F8..0xC0F654): ocupacao, para achar vazamento/estouro
    std::string pl;
    for (uint32_t ad = 0xC0F5F8u; ad <= 0xC0F654u; ad += 4) {
        const uint32_t p = rd32(ad); if (p < 0x400000u || p >= 0xE0000000u) continue;
        const uint32_t n = rd32(p + 8), fl = rd32(p + 4); if (!n || n > 100000 || fl < 0x400000u || fl >= 0xE0000000u) continue;
        uint32_t used = 0; for (uint32_t k = 0; k < n; ++k) if (!(M[fl + k] & 0x80)) ++used;
        if (used) { char b[48]; snprintf(b, sizeof b, " %X:%u/%u", ad, used, n); pl += b; }
    }
    if (!pl.empty()) rt_log("[diag]   pools usados:%s\n", pl.c_str());
}
// amostragem da thread do jogo (500 Hz, relogio de parede): mostra onde o tempo vai, inclusive esperas
static constexpr uint32_t kSamp = 8192;
static uintptr_t g_samp[kSamp][2]; static std::atomic<uint32_t> g_nsamp{0};
static void prof_signal(int, siginfo_t *, void *ucv) {
    const uint32_t i = g_nsamp.fetch_add(1, std::memory_order_relaxed);
    if (i >= kSamp) return;
    ucontext_t *u = (ucontext_t *)ucv;
#if defined(__aarch64__)
    g_samp[i][0] = (uintptr_t)u->uc_mcontext.pc; g_samp[i][1] = (uintptr_t)u->uc_mcontext.regs[30];
#elif defined(__x86_64__)
    g_samp[i][0] = (uintptr_t)u->uc_mcontext.gregs[REG_RIP]; g_samp[i][1] = 0;
#else
    (void)u; g_samp[i][0] = g_samp[i][1] = 0;
#endif
}
static const char *sym_of(uintptr_t pc) {
    Dl_info di; if (pc && dladdr((void *)pc, &di) && di.dli_sname) return di.dli_sname;
    return "?";
}
static void prof_dump() {
    uint32_t n = g_nsamp.load(); if (n > kSamp) n = kSamp;
    if (!n) return;
    std::map<std::string, uint32_t> fn, ctx;
    for (uint32_t i = 0; i < n; ++i) {
        const char *a = sym_of(g_samp[i][0]), *b = sym_of(g_samp[i][1]);
        ++fn[a]; ++ctx[std::string(a) + " <- " + b];
    }
    g_nsamp.store(0);
    auto top = [&](std::map<std::string, uint32_t> &m, const char *tit) {
        std::vector<std::pair<uint32_t, std::string>> v; for (auto &k : m) v.push_back({k.second, k.first});
        std::sort(v.rbegin(), v.rend());
        rt_log("[perfil] %s (%u amostras):", tit, n);
        for (size_t i = 0; i < v.size() && i < 12; ++i) rt_log(" %s %u%%%s", v[i].second.c_str(), v[i].first * 100 / n, i + 1 < 12 ? " |" : "");
        rt_log("\n");
    };
    top(fn, "funcoes"); top(ctx, "funcao <- chamador");
}
static void prof_start() {
    struct sigaction sa; memset(&sa, 0, sizeof sa); sa.sa_sigaction = prof_signal; sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sigaction(SIGPROF, &sa, nullptr);
    struct sigevent ev; memset(&ev, 0, sizeof ev);
    ev.sigev_notify = SIGEV_THREAD_ID; ev.sigev_signo = SIGPROF;
#ifdef sigev_notify_thread_id
    ev.sigev_notify_thread_id = (pid_t)syscall(SYS_gettid);
#else
    ev._sigev_un._tid = (pid_t)syscall(SYS_gettid);
#endif
    timer_t t; if (timer_create(CLOCK_MONOTONIC, &ev, &t) != 0) { rt_log("[perfil] timer_create falhou\n"); return; }
    struct itimerspec it; memset(&it, 0, sizeof it); it.it_interval.tv_nsec = 10000000; it.it_value.tv_nsec = 10000000;
    timer_settime(t, 0, &it, nullptr);
}
// pilha do jogo (enderecos de retorno na pilha x86) da thread principal: mostra a cadeia de chamadas onde ele esta preso
static bool is_ret_addr(uint32_t r) {
    if (r < 0x401005u || r >= 0x8F0000u) return false;
    return M[r - 5] == 0xE8 || M[r - 2] == 0xFF || M[r - 3] == 0xFF || M[r - 6] == 0xFF || M[r - 7] == 0xFF;
}
static void guest_stack_dump() {
    Cpu *c = g_trec[0].cpu.load(); if (!c) return;
    for (int rep = 0; rep < 3; ++rep) {
        const uint32_t sp = c->r[4];
        std::string t; int n = 0;
        for (uint32_t a = sp & ~3u; a < STACK_TOP - 4 && a < sp + 0x40000u && n < 48; a += 4) {
            const uint32_t v = rd32(a);
            if (is_ret_addr(v)) { char b[16]; snprintf(b, sizeof b, " %06X", v); t += b; ++n; }
        }
        rt_log("[pilha] esp=%08X:%s\n", sp, t.c_str());
        if (rep == 0) { const uint32_t ld = rd32(0xCF4290u);
            if (ld >= 0x400000u && ld < 0xE0000000u) rt_log("[pilha] carregador %08X: estado %u, +54=%08X +58=%08X +5C=%08X +84=%u +88=%08X +90=%02X%02X%02X\n", ld, rd32(ld), rd32(ld + 0x54), rd32(ld + 0x58), rd32(ld + 0x5C), rd32(ld + 0x84), rd32(ld + 0x88), M[ld + 0x90], M[ld + 0x91], M[ld + 0x92]); }
        usleep(150000);
    }
}
static void diag_watchdog() {
    uint64_t last_frames = 0;
    for (int k = 1;; ++k) {
        sleep(k <= 12 ? 5 : 30);
        char b[64]; snprintf(b, sizeof b, "%d s", k <= 12 ? 5 * k : 60 + 30 * (k - 12));
        diag_dump(b);
        prof_dump();
        const uint64_t fr = d3d_frames(); if (fr && fr == last_frames) guest_stack_dump(); last_frames = fr;
    }
}
// vigia de escrita: protege as paginas de um buffer do jogo e registra quem (funcao traduzida) escreve nele
static std::atomic<uintptr_t> g_watch_lo{0}, g_watch_hi{0}; static std::atomic<int> g_watch_hits{0};
static std::atomic<uintptr_t> g_watch_alo{0}, g_watch_ahi{0};   // faixa exata vigiada (a protecao e por pagina)
std::atomic<int> g_watch_rearm{0};                                  // escrita alheia na mesma pagina: proteger de novo na proxima chamada
void rt_watch_rearm() { if (g_watch_rearm.exchange(0) && g_watch_lo.load()) mprotect((void *)g_watch_lo.load(), g_watch_hi.load() - g_watch_lo.load(), PROT_READ); }
void rt_watch_writes(uint32_t addr, uint32_t len) {
    if (g_watch_hits.load() >= 12 || g_watch_lo.load()) return;
    const uintptr_t lo = ((uintptr_t)M + addr) & ~(uintptr_t)4095, hi = ((uintptr_t)M + addr + len + 4095) & ~(uintptr_t)4095;
    g_watch_lo = lo; g_watch_hi = hi; g_watch_alo = (uintptr_t)M + addr; g_watch_ahi = (uintptr_t)M + addr + len;
    mprotect((void *)lo, hi - lo, PROT_READ);
    rt_log("[vigia] protegendo %08X..%08X\n", (uint32_t)(lo - (uintptr_t)M), (uint32_t)(hi - (uintptr_t)M));
}
static void diag_signal(int sig, siginfo_t *si, void *uc) {
    const uintptr_t fa = (uintptr_t)si->si_addr, mb = (uintptr_t)M;
    if (sig == SIGSEGV && g_watch_lo.load() && fa >= g_watch_lo.load() && fa < g_watch_hi.load()) {
        uintptr_t pc = 0, lr = 0;
#if defined(__aarch64__)
        pc = (uintptr_t)((ucontext_t *)uc)->uc_mcontext.pc; lr = (uintptr_t)((ucontext_t *)uc)->uc_mcontext.regs[30];
#endif
        const uintptr_t lo = g_watch_lo.load(), hi = g_watch_hi.load();
        mprotect((void *)lo, hi - lo, PROT_READ | PROT_WRITE);
        if (fa < g_watch_alo.load() || fa >= g_watch_ahi.load()) {   // outro objeto na mesma pagina: deixa passar e arma de novo depois
            static int nf = 0; if (nf++ < 5) rt_log("[vigia] (escrita alheia em %08X por %s)\n", (uint32_t)(fa - mb), sym_of(pc));
            g_watch_rearm = 1; return;
        }
        g_watch_lo = 0; g_watch_hi = 0; ++g_watch_hits;
        rt_log("[vigia] escrita em %08X por %s <- %s\n", (uint32_t)(fa - mb), sym_of(pc), sym_of(lr));
        { Cpu *c = t_rec ? t_rec->cpu.load() : nullptr; if (c) { std::string t; int n = 0; uint32_t slot = 0;
            for (uint32_t a = c->r[4] & ~3u; a < STACK_TOP - 4 && n < 16; a += 4) { const uint32_t v = rd32(a); if (v == 0x4082F0u && !slot) slot = a; if (is_ret_addr(v)) { char b[16]; snprintf(b, sizeof b, " %06X", v); t += b; ++n; } }
            rt_log("[vigia]   pilha do jogo:%s\n", t.c_str());
            // f_408060(geometria, esqueleto): ossos = mundo[i] * skinToBone. Vigia agora o array de transformacoes do mundo dos ossos
            static int chained = 0;
            if (slot) {   // cada chamada da 408060 que escreve este buffer: qual esqueleto (a2) e a raiz dele; continua vigiando
                const uint32_t b1 = rd32(slot + 4), b2 = rd32(slot + 8), ar = (b2 >= 0x400000u && b2 < 0xE0000000u) ? rd32(b2 + 8) : 0;
                rt_log("[vigia]   chamada 408060(%08X, %08X) A=%08X raiz t=%.2f %.2f %.2f R00=%.3f | A[3] t=%.2f %.2f %.2f\n", b1, b2, ar,
                       ar ? rdf32(ar + 0x34 + 36) : 0.f, ar ? rdf32(ar + 0x34 + 40) : 0.f, ar ? rdf32(ar + 0x34 + 44) : 0.f, ar ? rdf32(ar + 0x34) : 0.f,
                       ar ? rdf32(ar + 0x34 * 3 + 36) : 0.f, ar ? rdf32(ar + 0x34 * 3 + 40) : 0.f, ar ? rdf32(ar + 0x34 * 3 + 44) : 0.f);
                {   // lista de ossos da particao (local da 408060: [esp+0x20] lista, [esp+0x24] quantidade; esp = slot - 0xC4)
                    static int nl = 0;
                    const uint32_t fe = slot - 0xC4, lst = rd32(fe + 0x20), cnt = rd32(fe + 0x24);
                    if (nl++ < 2 && lst >= 0x400000u && lst < 0xE0000000u && cnt < 64) {
                        std::string t; for (uint32_t k = 0; k < cnt; ++k) { const uint32_t ix = rd32(lst + 4 * k), p = ar + 0x34 * ix; char b[96];
                            snprintf(b, sizeof b, " %u:(%.2f,%.2f,%.2f r%.3f)", ix, rdf32(p + 36), rdf32(p + 40), rdf32(p + 44), rdf32(p)); t += b; }
                        rt_log("[vigia]   particao %u ossos:%s\n", cnt, t.c_str());
                        const uint32_t sb = rd32(fe + 0x18);   // B atual (ponteiro sequencial) e resultado esperado do 1o
                        rt_log("[vigia]   B0 em %08X t=%.3f %.3f %.3f\n", sb, rdf32(sb + 36), rdf32(sb + 40), rdf32(sb + 44));
                    }
                }
                {   // TESTE FINAL: (1) modo da montagem (3 ou 4 linhas por osso) e (2) valor previsto x gravado no quadro seguinte
                    static float pred[12]; static bool havep = false; static int nt = 0;
                    const uint32_t fe = slot - 0xC4, lst = rd32(fe + 0x20), sb = rd32(fe + 0x18);
                    const uint32_t e1 = rd32(b1 + 0xD0), regs = (e1 >= 0x400000u && e1 < 0xE0000000u) ? rd32(e1 + 0x20) : 0, dst = e1 ? rd32(e1 + 0x28) : 0;
                    if (nt++ < 8 && dst >= 0x400000u && dst < 0xE0000000u) {
                        float g[16]; for (int k = 0; k < 16; ++k) g[k] = rdf32(dst + 4 * k);
                        rt_log("[teste] thread %X | linhas por osso = %u | gravado(1o osso): %.3f %.3f %.3f %.2f | %.3f %.3f %.3f %.2f | %.3f %.3f %.3f %.2f | %.3f %.3f %.3f %.3f\n",
                               t_rec ? t_rec->tid : 0, regs, g[0], g[1], g[2], g[3], g[4], g[5], g[6], g[7], g[8], g[9], g[10], g[11], g[12], g[13], g[14], g[15]);
                        if (havep) rt_log("[teste] previsto no quadro anterior:  %.3f %.3f %.3f %.2f | %.3f %.3f %.3f %.2f | %.3f %.3f %.3f %.2f\n",
                               pred[0], pred[1], pred[2], pred[3], pred[4], pred[5], pred[6], pred[7], pred[8], pred[9], pred[10], pred[11]);
                        if (lst >= 0x400000u && lst < 0xE0000000u && sb >= 0x400000u && sb < 0xE0000000u) {   // A[lista[0]] * B0 (NiTransform)
                            const uint32_t pa = ar + 0x34 * rd32(lst);
                            double Ra[9], Rb[9], ta[3], tb[3]; for (int k = 0; k < 9; ++k) { Ra[k] = rdf32(pa + 4 * k); Rb[k] = rdf32(sb + 4 * k); }
                            for (int k = 0; k < 3; ++k) { ta[k] = rdf32(pa + 36 + 4 * k); tb[k] = rdf32(sb + 36 + 4 * k); }
                            const double sa = rdf32(pa + 48), sbb = rdf32(sb + 48);
                            for (int r = 0; r < 3; ++r) {
                                for (int cc = 0; cc < 3; ++cc) { double v = 0; for (int k = 0; k < 3; ++k) v += Ra[r * 3 + k] * Rb[k * 3 + cc]; pred[r * 4 + cc] = (float)(v * sa * sbb); }
                                double v = ta[r]; for (int k = 0; k < 3; ++k) v += sa * Ra[r * 3 + k] * tb[k]; pred[r * 4 + 3] = (float)v;
                            }
                            havep = true;
                            rt_log("[teste] entradas agora: A[%u] t=%.2f %.2f %.2f | B0 t=%.3f %.3f %.3f\n", rd32(lst), ta[0], ta[1], ta[2], tb[0], tb[1], tb[2]);
                        }
                    }
                }
                if (g_watch_hits.load() < 16) { g_watch_lo = lo; g_watch_hi = hi; g_watch_rearm = 1; }
            }
            if (false && slot && chained < 3) {
                const uint32_t a1 = rd32(slot + 4), a2 = rd32(slot + 8); uint32_t arr = (a2 >= 0x400000u && a2 < 0xE0000000u) ? rd32(a2 + 8) : 0;
                rt_log("[vigia]   408060(%08X, %08X): transformacoes do mundo dos ossos em %08X | osso0 t=%.2f %.2f %.2f s=%.3f\n", a1, a2, arr,
                       arr ? rdf32(arr + 0x24) : 0.f, arr ? rdf32(arr + 0x28) : 0.f, arr ? rdf32(arr + 0x2c) : 0.f, arr ? rdf32(arr + 0x30) : 0.f);
                // B: transformacoes dinamicas (passo 0x4C) da instancia de pele: [[[a1+0xD0]+8]+0x40]
                uint32_t barr = 0; { const uint32_t e1 = rd32(a1 + 0xD0); const uint32_t e2 = (e1 >= 0x400000u && e1 < 0xE0000000u) ? rd32(e1 + 8) : 0; barr = (e2 >= 0x400000u && e2 < 0xE0000000u) ? rd32(e2 + 0x40) : 0; }
                auto dumpT = [&](const char *nm, uint32_t p) { if (p < 0x400000u || p >= 0xE0000000u) return; rt_log("[vigia]     %s %08X: R %.3f %.3f %.3f | %.3f %.3f %.3f | %.3f %.3f %.3f  t %.2f %.2f %.2f  s %.3f\n", nm, p,
                    rdf32(p), rdf32(p + 4), rdf32(p + 8), rdf32(p + 12), rdf32(p + 16), rdf32(p + 20), rdf32(p + 24), rdf32(p + 28), rdf32(p + 32), rdf32(p + 36), rdf32(p + 40), rdf32(p + 44), rdf32(p + 48)); };
                static int full = 0;
                const int nb = full++ == 0 ? 30 : 3, na = full == 1 ? 80 : 4;   // na 1a vez: tudo (analise fora do celular)
                for (int k = 0; k < nb; ++k) { char nm[16]; snprintf(nm, sizeof nm, "B[%d]", k); dumpT(nm, barr + 0x4C * k); }
                for (int k = 0; k < na; ++k) { char nm[16]; snprintf(nm, sizeof nm, "A[%d]", k); dumpT(nm, arr + 0x34 * k); }
                {   // resultado ja calculado (buffer de destino da 408060: [[a1+0xD0]+0x28]) e lista de ossos da particao
                    const uint32_t e1 = rd32(a1 + 0xD0), dst = (e1 >= 0x400000u && e1 < 0xE0000000u) ? rd32(e1 + 0x28) : 0;
                    if (full == 1 && dst >= 0x400000u && dst < 0xE0000000u)
                        for (int k = 0; k < 24; ++k) { const uint32_t p = dst + 48 * k; rt_log("[vigia]     R[%d]: %.3f %.3f %.3f %.2f | %.3f %.3f %.3f %.2f | %.3f %.3f %.3f %.2f\n", k,
                            rdf32(p), rdf32(p + 4), rdf32(p + 8), rdf32(p + 12), rdf32(p + 16), rdf32(p + 20), rdf32(p + 24), rdf32(p + 28), rdf32(p + 32), rdf32(p + 36), rdf32(p + 40), rdf32(p + 44)); }
                }
                if (barr) arr = barr;   // vigia B (o que muda a cada quadro)
                if (arr >= 0x400000u && arr < 0xE0000000u) {
                    ++chained;
                    const uintptr_t lo2 = ((uintptr_t)M + arr) & ~(uintptr_t)4095, hi2 = ((uintptr_t)M + arr + 0x34 * 32 + 4095) & ~(uintptr_t)4095;
                    g_watch_lo = lo2; g_watch_hi = hi2; g_watch_alo = (uintptr_t)M + arr; g_watch_ahi = (uintptr_t)M + arr + 0x4C; mprotect((void *)lo2, hi2 - lo2, PROT_READ);
                }
            } } }
        return;
    }
    if (fa >= mb && fa < mb + 0x100000000ull) rt_log("[diag] SINAL %d: acesso invalido no endereco do jogo %08X\n", sig, (uint32_t)(fa - mb));
    else rt_log("[diag] SINAL %d: acesso invalido em %p (fora da memoria do jogo)\n", sig, si->si_addr);
    if (t_rec) rt_log("[diag]   thread %X, ultima chamada ao Windows: %s (retorno %08X)\n", t_rec->tid, t_rec->last.load() ? t_rec->last.load() : "-", t_rec->ret.load());
    diag_dump("no momento do erro");
    signal(sig, SIG_DFL); raise(sig);
}
static void diag_start() {
    struct sigaction sa; memset(&sa, 0, sizeof sa); sa.sa_sigaction = diag_signal; sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
    sigaction(SIGSEGV, &sa, nullptr); sigaction(SIGBUS, &sa, nullptr); sigaction(SIGILL, &sa, nullptr); sigaction(SIGFPE, &sa, nullptr);
    std::thread(diag_watchdog).detach();
    // prof_start();   // amostragem (100 Hz): ligar so para investigar
}

// ---------------------------------------------------------------- tabela
struct Imp { const char *name; int nargs; NativeFn fn; };
#define F(name) static uint32_t name(Cpu &c, const uint32_t *a)

// ---- versao, modulo, linha de comando, ambiente
F(K_GetVersionExA) { const uint32_t p = a[0]; wr32(p + 4, 5); wr32(p + 8, 1); wr32(p + 12, 2600); wr32(p + 16, 2); memset(M + p + 20, 0, 128); return 1; }
F(K_GetModuleHandleA) { if (!a[0]) return IMAGE_BASE; return 0x7C800000u; }
F(K_GetCommandLineA) { static uint32_t s = 0; if (!s) s = gstrdup("\"C:\\Bully\\Bully.exe\""); return s; }
F(K_GetStartupInfoA) { memset(M + a[0], 0, 68); wr32(a[0], 68); return 0; }
F(K_GetStdHandle) { return a[0]; }
F(K_GetFileType) { return (a[0] >= 0xFFFFFFF4u) ? 2 : 1; }
F(K_SetHandleCount) { return a[0]; }
F(K_GetEnvironmentStrings) { static uint32_t s = 0; if (!s) s = misc_alloc(16); return s; }
F(K_FreeEnvironmentStrings) { return 1; }
F(K_GetACP) { return 1252; }
F(K_GetOEMCP) { return 437; }
F(K_IsValidCodePage) { return 1; }
F(K_GetCPInfo) { memset(M + a[1], 0, 20); wr32(a[1], 1); M[a[1] + 4] = '?'; return 1; }
F(K_GetModuleFileNameA) { const char *s = "C:\\Bully\\Bully.exe"; const uint32_t n = (uint32_t)strlen(s); const uint32_t m = n < a[2] ? n : a[2] - 1; memcpy(M + a[1], s, m); M[a[1] + m] = 0; return m; }
F(K_GetCurrentDirectoryA) { const char *s = "C:\\Bully"; strcpy((char *)M + a[1], s); return (uint32_t)strlen(s); }
F(K_GetFullPathNameA) { const char *s = gstr(a[0]); std::string r = s; if (!(r.size() > 1 && r[1] == ':')) r = std::string("C:\\Bully\\") + s; strncpy((char *)M + a[2], r.c_str(), a[1]); if (a[3]) wr32(a[3], 0); return (uint32_t)r.size(); }
F(K_GetDriveTypeA) { return 3; }
F(K_SetEnvironmentVariableA) { return 1; }
// ---- heap / memoria virtual
F(K_HeapCreate) { return 0x10000; }
F(K_HeapDestroy) { return 1; }
F(K_GetProcessHeap) { return 0x10000; }
F(K_HeapAlloc) { return rt_alloc(a[2], (a[1] & 8) != 0); }
F(K_HeapFree) { rt_free(a[2]); return 1; }
F(K_HeapReAlloc) { const uint32_t r = rt_realloc(a[2], a[3]); return r; }
F(K_HeapSize) { return rt_size(a[2]); }
F(K_LocalAlloc) { return rt_alloc(a[1], (a[0] & 0x40) != 0); }
F(K_LocalFree) { rt_free(a[0]); return 0; }
F(K_VirtualAlloc) {
    if (a[0] && (a[2] & 0x1000) && !(a[2] & 0x2000)) return a[0];   // commit de area ja reservada
    const uint32_t p = rt_alloc(a[1] + 4096, true); return (p + 4095) & ~4095u;
}
F(K_VirtualFree) { return 1; }
F(K_VirtualQuery) { const uint32_t p = a[1]; memset(M + p, 0, 28); wr32(p, a[0] & ~4095u); wr32(p + 4, a[0] & ~4095u); wr32(p + 8, 4); wr32(p + 12, 0x100000); wr32(p + 16, 0x1000); wr32(p + 20, 4); wr32(p + 24, 0x20000); return 28; }
F(K_GlobalMemoryStatus) { const uint32_t p = a[0]; wr32(p, 32); wr32(p + 4, 50); wr32(p + 8, 0x40000000); wr32(p + 12, 0x30000000); wr32(p + 16, 0x80000000u); wr32(p + 20, 0x70000000); wr32(p + 24, 0x7FFE0000); wr32(p + 28, 0x70000000); return 0; }
F(K_GetSystemInfo) { const uint32_t p = a[0]; memset(M + p, 0, 36); wr32(p + 4, 4096); wr32(p + 8, 0x10000); wr32(p + 12, 0x7FFEFFFF); wr32(p + 16, 15); wr32(p + 20, 4); wr32(p + 24, 586); wr32(p + 28, 0x10000); return 0; }
// ---- TLS
F(K_TlsAlloc) { return g_tls_next++; }
F(K_TlsFree) { return 1; }
F(K_TlsGetValue) { t_lasterr = 0; return a[0] < 128 ? t_tls[a[0]] : 0; }
F(K_TlsSetValue) { if (a[0] < 128) t_tls[a[0]] = a[1]; return 1; }
// ---- secoes criticas (mutex recursivo por endereco)
static inline void sched_yield_if(int spin) { if (spin > 16) sched_yield(); }
static std::mutex g_cs_mtx; static std::map<uint32_t, std::recursive_mutex *> g_cs;
static std::recursive_mutex *g_cs_list[65536]; static uint32_t g_cs_n = 0;
static std::atomic<uint64_t> g_cs_cache[4096];   // (endereco<<32 | indice): evita trava global + std::map a cada Enter/Leave
static std::recursive_mutex *cs_of(uint32_t p) {
    std::atomic<uint64_t> &slot = g_cs_cache[(p >> 3) & 4095];
    const uint64_t e = slot.load(std::memory_order_acquire);
    if ((uint32_t)(e >> 32) == p && p) return g_cs_list[(uint32_t)e];
    std::lock_guard<std::mutex> lk(g_cs_mtx);
    auto &m = g_cs[p];
    if (!m) { m = new std::recursive_mutex; }
    uint32_t idx = 0xFFFFFFFFu;
    for (uint32_t i = 0; i < g_cs_n; ++i) if (g_cs_list[i] == m) { idx = i; break; }
    if (idx == 0xFFFFFFFFu && g_cs_n < 65536) { idx = g_cs_n; g_cs_list[g_cs_n++] = m; }
    if (idx != 0xFFFFFFFFu) slot.store(((uint64_t)p << 32) | idx, std::memory_order_release);
    return m;
}
F(K_InitializeCriticalSection) { memset(M + a[0], 0, 24); cs_of(a[0]); return 0; }
F(K_DeleteCriticalSection) { return 0; }
// secao critica direto na estrutura do jogo (CRITICAL_SECTION): +8 recursao, +12 dono, +16 quantos esperam.
// Sem disputa e so uma troca atomica (antes: tabela de mutex + std::recursive_mutex); com disputa, futex no campo do dono.
static inline void cs_enter(uint32_t p) {
    if (p & 3) { cs_of(p)->lock(); return; }
    std::atomic<uint32_t> *own = (std::atomic<uint32_t> *)(M + p + 12), *wt = (std::atomic<uint32_t> *)(M + p + 16);
    uint32_t *rec = (uint32_t *)(M + p + 8);
    const uint32_t me = cur_tid();
    if (own->load(std::memory_order_relaxed) == me) { ++*rec; return; }
    for (int spin = 0;; ++spin) {
        uint32_t z = 0;
        if (own->compare_exchange_weak(z, me, std::memory_order_acquire, std::memory_order_relaxed)) { *rec = 1; return; }
        if (spin < 64) { sched_yield_if(spin); continue; }
        wt->fetch_add(1);
        const uint32_t o = own->load();
        if (o != 0) syscall(SYS_futex, (uint32_t *)own, 128 /*FUTEX_WAIT_PRIVATE*/, o, nullptr, nullptr, 0);
        wt->fetch_sub(1);
    }
}
static inline void cs_leave(uint32_t p) {
    if (p & 3) { cs_of(p)->unlock(); return; }
    std::atomic<uint32_t> *own = (std::atomic<uint32_t> *)(M + p + 12), *wt = (std::atomic<uint32_t> *)(M + p + 16);
    uint32_t *rec = (uint32_t *)(M + p + 8);
    if (own->load(std::memory_order_relaxed) != cur_tid()) return;   // nao e o dono (o Windows tambem nao trava)
    if (--*rec != 0) return;
    own->store(0, std::memory_order_release);
    if (wt->load()) syscall(SYS_futex, (uint32_t *)own, 129 /*FUTEX_WAKE_PRIVATE*/, 1, nullptr, nullptr, 0);
}
F(K_EnterCriticalSection) { cs_enter(a[0]); return 0; }
F(K_LeaveCriticalSection) { cs_leave(a[0]); return 0; }
F(K_InterlockedIncrement) { return __atomic_add_fetch((uint32_t *)(M + a[0]), 1u, __ATOMIC_SEQ_CST); }
F(K_InterlockedDecrement) { return __atomic_sub_fetch((uint32_t *)(M + a[0]), 1u, __ATOMIC_SEQ_CST); }
F(K_InterlockedExchange) { return __atomic_exchange_n((uint32_t *)(M + a[0]), a[1], __ATOMIC_SEQ_CST); }
// ---- tempo
static uint64_t now_ns() { timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return (uint64_t)t.tv_sec * 1000000000ull + t.tv_nsec; }
F(K_GetTickCount) { return (uint32_t)(now_ns() / 1000000ull); }
F(K_QueryPerformanceCounter) { wr64(a[0], now_ns() / 100ull); return 1; }
F(K_QueryPerformanceFrequency) { wr64(a[0], 10000000ull); return 1; }
F(K_GetSystemTimeAsFileTime) { timespec t; clock_gettime(CLOCK_REALTIME, &t); wr64(a[0], ((uint64_t)t.tv_sec + 11644473600ull) * 10000000ull + t.tv_nsec / 100); return 0; }
F(K_GetLocalTime) { time_t s = time(nullptr); tm l; localtime_r(&s, &l); const uint32_t p = a[0]; wr16(p, l.tm_year + 1900); wr16(p + 2, l.tm_mon + 1); wr16(p + 4, l.tm_wday); wr16(p + 6, l.tm_mday); wr16(p + 8, l.tm_hour); wr16(p + 10, l.tm_min); wr16(p + 12, l.tm_sec); wr16(p + 14, 0); return 0; }
F(K_Sleep) { usleep(a[0] * 1000u); return 0; }
// ---- processo / thread
F(K_GetCurrentThreadId) { return cur_tid(); }
F(K_GetCurrentProcessId) { return 1234; }
F(K_GetCurrentProcess) { return 0xFFFFFFFFu; }
F(K_GetLastError) { return t_lasterr; }
F(K_SetLastError) { t_lasterr = a[0]; return 0; }
F(K_SetUnhandledExceptionFilter) { return 0; }
F(K_UnhandledExceptionFilter) { return 0; }
F(K_IsDebuggerPresent) { return 0; }
F(K_OutputDebugStringA) { rt_log("[jogo] %s", gstr(a[0])); return 0; }
F(K_DebugBreak) { rt_log("[bully] DebugBreak\n"); return 0; }
F(K_ExitProcess) { rt_log("[bully] ExitProcess(%u)\n", a[0]); exit((int)a[0]); }
F(K_TerminateProcess) { rt_log("[bully] TerminateProcess(%u)\n", a[1]); exit((int)a[1]); }
F(K_SetThreadPriority) { return 1; }
// ---- texto (so ASCII/Latin-1)
F(K_MultiByteToWideChar) {
    const uint8_t *s = M + a[2]; int n = (int)a[3]; if (n < 0) n = (int)strlen((const char *)s) + 1;
    if (!a[5]) return (uint32_t)n;
    int m = n < (int)a[5] ? n : (int)a[5]; for (int i = 0; i < m; ++i) wr16(a[4] + 2 * i, s[i]); return (uint32_t)m;
}
F(K_WideCharToMultiByte) {
    int n = (int)a[3]; if (n < 0) { n = 0; while (rd16(a[2] + 2 * n)) ++n; ++n; }
    if (!a[5]) return (uint32_t)n;
    int m = n < (int)a[5] ? n : (int)a[5]; for (int i = 0; i < m; ++i) { const uint16_t ch = rd16(a[2] + 2 * i); M[a[4] + i] = ch < 256 ? (uint8_t)ch : '?'; } return (uint32_t)m;
}
F(K_GetStringTypeA) { for (int i = 0; i < (int)a[3]; ++i) { const uint8_t ch = M[a[2] + i]; uint16_t t = 0; if (isupper(ch)) t |= 1; if (islower(ch)) t |= 2; if (isdigit(ch)) t |= 4; if (isspace(ch)) t |= 8; if (ispunct(ch)) t |= 0x10; if (iscntrl(ch)) t |= 0x20; if (isxdigit(ch)) t |= 0x80; if (isalpha(ch)) t |= 0x100; wr16(a[4] + 2 * i, t); } return 1; }
F(K_GetStringTypeW) { int n = (int)a[2]; if (n < 0) { n = 0; while (rd16(a[1] + 2 * n)) ++n; } for (int i = 0; i < n; ++i) { const uint16_t ch = rd16(a[1] + 2 * i); uint16_t t = 0; if (ch < 128) { if (isupper(ch)) t |= 1; if (islower(ch)) t |= 2; if (isdigit(ch)) t |= 4; if (isspace(ch)) t |= 8; if (ispunct(ch)) t |= 0x10; if (iscntrl(ch)) t |= 0x20; if (isxdigit(ch)) t |= 0x80; if (isalpha(ch)) t |= 0x100; } wr16(a[3] + 2 * i, t); } return 1; }
F(K_LCMapStringA) { int n = (int)a[3]; if (n < 0) n = (int)strlen(gstr(a[2])) + 1; if (!a[5]) return (uint32_t)n; for (int i = 0; i < n && i < (int)a[5]; ++i) { uint8_t ch = M[a[2] + i]; if (a[1] & 0x100) ch = (uint8_t)tolower(ch); if (a[1] & 0x200) ch = (uint8_t)toupper(ch); M[a[4] + i] = ch; } return (uint32_t)n; }
F(K_LCMapStringW) { int n = (int)a[3]; if (n < 0) { n = 0; while (rd16(a[2] + 2 * n)) ++n; ++n; } if (!a[5]) return (uint32_t)n; for (int i = 0; i < n && i < (int)a[5]; ++i) { uint16_t ch = rd16(a[2] + 2 * i); if (ch < 128) { if (a[1] & 0x100) ch = (uint16_t)tolower(ch); if (a[1] & 0x200) ch = (uint16_t)toupper(ch); } wr16(a[4] + 2 * i, ch); } return (uint32_t)n; }
F(K_CompareStringA) { int n1 = (int)a[3], n2 = (int)a[5]; if (n1 < 0) n1 = (int)strlen(gstr(a[2])); if (n2 < 0) n2 = (int)strlen(gstr(a[4])); int r = (a[1] & 1) ? strncasecmp(gstr(a[2]), gstr(a[4]), n1 < n2 ? n1 : n2) : strncmp(gstr(a[2]), gstr(a[4]), n1 < n2 ? n1 : n2); if (!r) r = n1 - n2; return r < 0 ? 1 : r > 0 ? 3 : 2; }
F(K_CompareStringW) { int n1 = (int)a[3], n2 = (int)a[5]; if (n1 < 0) { n1 = 0; while (rd16(a[2] + 2 * n1)) ++n1; } if (n2 < 0) { n2 = 0; while (rd16(a[4] + 2 * n2)) ++n2; } for (int i = 0; i < n1 && i < n2; ++i) { uint16_t x = rd16(a[2] + 2 * i), y = rd16(a[4] + 2 * i); if ((a[1] & 1) && x < 128 && y < 128) { x = (uint16_t)tolower(x); y = (uint16_t)tolower(y); } if (x != y) return x < y ? 1 : 3; } return n1 < n2 ? 1 : n1 > n2 ? 3 : 2; }
F(K_GetLocaleInfoA) { const char *s = "1"; switch (a[1] & 0xFFFF) { case 0x1004: s = "1252"; break; case 0xB: s = "437"; break; case 0xE: s = "."; break; case 0xF: s = ","; break; default: s = "0"; } if (!a[3]) return (uint32_t)strlen(s) + 1; strncpy((char *)M + a[2], s, a[3]); return (uint32_t)strlen(s) + 1; }
F(K_lstrlenA) { return (uint32_t)strlen(gstr(a[0])); }
// ---- bibliotecas
F(K_LoadLibraryA) { rt_log("[bully] LoadLibraryA(%s)\n", gstr(a[0])); return 0x70000000u + (uint32_t)(strlen(gstr(a[0])) << 12); }
F(K_FreeLibrary) { return 1; }
static uint32_t proc_by_name(const char *name);
F(K_GetProcAddress) { const uint32_t r = (a[1] >> 16) ? proc_by_name(gstr(a[1])) : 0; rt_log("[bully] GetProcAddress(%s) = %08X\n", (a[1] >> 16) ? gstr(a[1]) : "#ordinal", r); return r; }
// ---- arquivos
// amostras de audio para analise do formato: copia os primeiros 2 MB de cada arquivo de som aberto (uma vez por nome)
// para <pasta do jogo>/amostras/
static void sample_audio(const std::string &host, const std::string &guest) {
    std::string g = guest; for (auto &ch : g) ch = (char)tolower((unsigned char)ch);
    if (g.find("\\playlist\\") == std::string::npos && g.find("\\xact\\") == std::string::npos) return;
    static std::mutex m; static std::set<std::string> done; static int n = 0;
    std::lock_guard<std::mutex> lk(m);
    const std::string name = g.substr(g.find_last_of('\\') + 1);
    if (n >= 16 || !done.insert(name).second) return;
    ++n;
    const std::string dir = std::string(g_dir) + "/amostras"; mkdir(dir.c_str(), 0777);
    FILE *in = fopen(host.c_str(), "rb"); if (!in) return;
    FILE *out = fopen((dir + "/" + name).c_str(), "wb");
    if (out) { static char buf[1 << 16]; size_t tot = 0, k; while (tot < (2u << 20) && (k = fread(buf, 1, sizeof buf, in)) > 0) { fwrite(buf, 1, k, out); tot += k; } fclose(out); }
    fclose(in);
    rt_log("[audio] amostra salva: amostras/%s\n", name.c_str());
}
F(K_CreateFileA) {
    const std::string p = rt_host_path(a[0]);
    const uint32_t acc = a[1], disp = a[4];
    const char *mode = (acc & 0x40000000u) ? ((disp == 1 || disp == 2) ? "w+b" : (disp == 4 ? "a+b" : "r+b")) : "rb";
    FILE *f = fopen(p.c_str(), mode);
    if (!f && (acc & 0x40000000u) && (disp == 4 || disp == 3)) f = fopen(p.c_str(), "w+b");
    // arquivos copiados por outro app para Android/data podem ser so leitura para nos: abre para ler
    if (!f && (acc & 0x40000000u) && (disp == 3 || disp == 4)) f = fopen(p.c_str(), "rb");
    if (!f) { const int er = errno; t_lasterr = er == EACCES ? 5 : 2; rt_log("[bully] CreateFileA(%s) falhou (%s)\n", gstr(a[0]), strerror(er)); return 0xFFFFFFFFu; }
    // sample_audio(p, gstr(a[0]));   // (amostras de audio: so para analise)
    if (!(acc & 0x40000000u)) setvbuf(f, nullptr, _IOFBF, 128 * 1024);   // o jogo le muitos arquivos em pedacos minusculos (Trigger.IMG: ~170 mil leituras de bytes)
    Obj *o = new Obj; o->kind = 1; o->f = f; o->path = gstr(a[0]); return new_handle(o);
}
// estatistica de leitura de arquivos (por janela de 300 quadros): quantas leituras, tamanho, tempo, de quem
static void any_signal();
static thread_local bool tl_ipmain = false;   // thread do jogo (marcada a cada Present)
struct FStat { uint64_t n = 0, bytes = 0, ns = 0, n_main = 0, ovl = 0; std::map<uint32_t, uint64_t> sizes; std::map<std::string, uint64_t> files; std::map<uint32_t, uint64_t> rel_callers; };
static std::mutex g_fs_m; static FStat g_fs;
// contadores acumulados de leitura (para o detector de travadas no Present)
static std::atomic<uint64_t> g_fr_n{0}, g_fr_ns{0}, g_fr_b{0};
void rt_file_counters(uint64_t &n, uint64_t &ns, uint64_t &bytes) { n = g_fr_n.load(); ns = g_fr_ns.load(); bytes = g_fr_b.load(); }
static uint64_t now_ns();
void rt_file_stats_dump(int frames) {
    std::lock_guard<std::mutex> lk(g_fs_m); FStat &f = g_fs;
    rt_log("[arquivos] %.1f leituras/quadro (%.1f na thread do jogo, %.1f com OVERLAPPED) | %.1f KB/quadro | %.2f ms/quadro lendo\n",
           (double)f.n / frames, (double)f.n_main / frames, (double)f.ovl / frames, f.bytes / 1024.0 / frames, f.ns / 1e6 / frames);
    std::string t; char b[96];
    for (auto &kv : f.sizes) { snprintf(b, sizeof b, " <=%uK:%llu", kv.first, (unsigned long long)kv.second); t += b; }
    rt_log("[arquivos] tamanhos:%s\n", t.c_str()); t.clear();
    for (auto &kv : f.files) { snprintf(b, sizeof b, " %s:%llu", kv.first.c_str() + (kv.first.size() > 40 ? kv.first.size() - 40 : 0), (unsigned long long)kv.second); t += b; }
    rt_log("[arquivos] por arquivo:%s\n", t.c_str()); t.clear();
    for (auto &kv : f.rel_callers) { snprintf(b, sizeof b, " %08X:%llu", kv.first, (unsigned long long)kv.second); t += b; }
    if (!t.empty()) rt_log("[arquivos] ReleaseSemaphore chamado de:%s\n", t.c_str());
    f = FStat();
}
// leitura posicional para o audio (bancos de onda em streaming do XACT), feita na thread de audio
bool rt_file_pread(uint32_t h, uint64_t off, void *dst, uint32_t n, uint32_t *got) {
    Obj *o = get_obj(h); *got = 0;
    if (!o || o->kind != 1 || !o->f) return false;
    std::lock_guard<std::mutex> flk(o->m);
    const ssize_t r = pread(fileno(o->f), dst, n, (off_t)off);
    if (r > 0) *got = (uint32_t)r;
    return r >= 0;
}
F(K_ReadFile) {   // (h, buf, n, pRead, lpOverlapped): com OVERLAPPED le na posicao dele e completa na hora
    Obj *o = get_obj(a[0]); if (!o || !o->f) return 0;
    std::lock_guard<std::mutex> flk(o->m);   // o mesmo arquivo e lido pela thread principal e pela de streaming
    const uint64_t fs_t0 = now_ns();
    size_t n = 0;
    if (a[4]) {   // OVERLAPPED: le direto na posicao (pread), sem mexer no ponteiro do arquivo nem no buffer do stdio
        const uint64_t off = (uint64_t)rd32(a[4] + 8) | ((uint64_t)rd32(a[4] + 12) << 32);
        fflush(o->f);
        while (n < a[2]) { const ssize_t r = pread(fileno(o->f), M + a[1] + n, a[2] - n, (off_t)(off + n)); if (r <= 0) break; n += (size_t)r; }
        fseeko(o->f, (off_t)(off + n), SEEK_SET);   // handle sincrono com OVERLAPPED: o Windows deixa o ponteiro no fim da leitura
    } else n = fread(M + a[1], 1, a[2], o->f);
    { const uint64_t dt = now_ns() - fs_t0; g_fr_n.fetch_add(1, std::memory_order_relaxed); g_fr_ns.fetch_add(dt, std::memory_order_relaxed); g_fr_b.fetch_add(n, std::memory_order_relaxed);
      if (n <= 4096 && (g_fr_n.load(std::memory_order_relaxed) & 63)) goto fs_done;   // estatistica detalhada so por amostragem nas leituras pequenas
      std::lock_guard<std::mutex> lk(g_fs_m); ++g_fs.n; g_fs.bytes += n; g_fs.ns += dt; if (tl_ipmain) ++g_fs.n_main; if (a[4]) ++g_fs.ovl;
      uint32_t k = 1; while (k < 65536 && k * 1024 < n) k *= 4; ++g_fs.sizes[k]; if (n > 1024 || (g_fs.n & 255) == 0) { if (g_fs.files.size() < 24 || g_fs.files.count(o->path)) ++g_fs.files[o->path]; } }
fs_done:
    if (a[3]) wr32(a[3], (uint32_t)n);
    if (a[4]) {
        wr32(a[4], 0); wr32(a[4] + 4, (uint32_t)n);
        if (Obj *ev = get_obj(rd32(a[4] + 16))) { std::lock_guard<std::mutex> lk(ev->m); ev->signaled = true; ev->cv.notify_all(); } any_signal();
    }
    return 1;
}
F(K_WriteFile) {
    if (a[0] >= 0xFFFFFFF4u) { fwrite(M + a[1], 1, a[2], stderr); if (a[3]) wr32(a[3], a[2]); return 1; }
    Obj *o = get_obj(a[0]); if (!o || !o->f) return 0; std::lock_guard<std::mutex> flk(o->m); const size_t n = fwrite(M + a[1], 1, a[2], o->f); if (a[3]) wr32(a[3], (uint32_t)n); return 1;
}
F(K_SetFilePointer) { Obj *o = get_obj(a[0]); if (!o || !o->f) return 0xFFFFFFFFu; std::lock_guard<std::mutex> flk(o->m); int64_t off = (int32_t)a[1]; if (a[2]) off = (int64_t)(((uint64_t)rd32(a[2]) << 32) | a[1]); fseeko(o->f, off, a[3] == 0 ? SEEK_SET : a[3] == 1 ? SEEK_CUR : SEEK_END); const int64_t pos = ftello(o->f); if (a[2]) wr32(a[2], (uint32_t)(pos >> 32)); return (uint32_t)pos; }
F(K_GetFileSize) { Obj *o = get_obj(a[0]); if (!o || !o->f) return 0xFFFFFFFFu; std::lock_guard<std::mutex> flk(o->m); const long cur = ftell(o->f); fseek(o->f, 0, SEEK_END); const long n = ftell(o->f); fseek(o->f, cur, SEEK_SET); if (a[1]) wr32(a[1], 0); return (uint32_t)n; }
F(K_SetEndOfFile) { return 1; }
F(K_FlushFileBuffers) { Obj *o = get_obj(a[0]); if (o && o->f) fflush(o->f); return 1; }
F(K_CloseHandle) { Obj *o = get_obj(a[0]); if (o && o->f) { fclose(o->f); o->f = nullptr; } return 1; }
F(K_GetFileAttributesA) { struct stat st; const std::string p = rt_host_path(a[0]); if (stat(p.c_str(), &st)) { t_lasterr = 2; return 0xFFFFFFFFu; } return S_ISDIR(st.st_mode) ? 0x10 : 0x80; }
F(K_CreateDirectoryA) { mkdir(rt_host_path(a[0]).c_str(), 0755); return 1; }
F(K_DeleteFileA) { return unlink(rt_host_path(a[0]).c_str()) == 0; }
static void fill_find(uint32_t p, const std::string &dir, const std::string &name) {
    memset(M + p, 0, 320); struct stat st; std::string full = dir + "/" + name;
    if (!stat(full.c_str(), &st)) { wr32(p, S_ISDIR(st.st_mode) ? 0x10 : 0x80); wr32(p + 32, (uint32_t)st.st_size); }
    strncpy((char *)M + p + 44, name.c_str(), 259);
}
F(K_FindFirstFileA) {
    std::string pat = gstr(a[0]); for (auto &ch : pat) if (ch == '\\') ch = '/';
    const size_t sl = pat.rfind('/'); std::string dpart = sl == std::string::npos ? "" : pat.substr(0, sl); std::string mask = sl == std::string::npos ? pat : pat.substr(sl + 1);
    const uint32_t tmp = gstrdup(dpart.c_str()); const std::string hdir = rt_host_path(tmp); rt_free(tmp);
    Obj *o = new Obj; o->kind = 6;
    if (DIR *d = opendir(hdir.c_str())) {
        while (dirent *e = readdir(d)) {
            std::string n = e->d_name; bool ok = true;
            if (mask != "*" && mask != "*.*") { const size_t st = mask.find('*'); if (st == std::string::npos) ok = strcasecmp(n.c_str(), mask.c_str()) == 0; else { std::string suf = mask.substr(st + 1); ok = n.size() >= suf.size() && strcasecmp(n.c_str() + n.size() - suf.size(), suf.c_str()) == 0 && strncasecmp(n.c_str(), mask.c_str(), st) == 0; } }
            if (ok) o->list.push_back(n);
        }
        closedir(d);
    }
    if (o->list.empty()) { delete o; t_lasterr = 2; return 0xFFFFFFFFu; }
    o->list.insert(o->list.begin(), hdir); o->pos = 1;
    fill_find(a[1], hdir, o->list[o->pos++]);
    return new_handle(o);
}
F(K_FindNextFileA) { Obj *o = get_obj(a[0]); if (!o || o->pos >= o->list.size()) { t_lasterr = 18; return 0; } fill_find(a[1], o->list[0], o->list[o->pos++]); return 1; }
F(K_FindClose) { return 1; }
F(K_GetOverlappedResult) { if (a[2]) wr32(a[2], a[1] ? rd32(a[1] + 4) : 0); return 1; }
// ---- sincronizacao e threads
F(K_CreateEventA) { Obj *o = new Obj; o->kind = 2; o->manual = a[1] != 0; o->signaled = a[2] != 0; return new_handle(o); }
F(K_CreateMutexA) { Obj *o = new Obj; o->kind = 3; if (a[1]) { o->owner = cur_tid(); o->rec = 1; } return new_handle(o); }
F(K_CreateSemaphoreA) { Obj *o = new Obj; o->kind = 4; o->count = (long)a[1]; o->maxc = (long)a[2]; return new_handle(o); }
F(K_ReleaseMutex) { Obj *o = get_obj(a[0]); if (!o) return 0; std::lock_guard<std::mutex> lk(o->m); if (o->rec > 0 && --o->rec == 0) { o->owner = 0; if (o->waiters > 0) o->handoff = ++o->gen; o->cv.notify_all(); any_signal(); } return 1; }
F(K_ReleaseSemaphore) { Obj *o = get_obj(a[0]); if (!o) return 0; { std::lock_guard<std::mutex> fl(g_fs_m); if (g_fs.rel_callers.size() < 16) ++g_fs.rel_callers[rd32(c.r[4])]; } std::lock_guard<std::mutex> lk(o->m); if (a[2]) wr32(a[2], (uint32_t)o->count); o->count += (long)a[1]; o->cv.notify_all(); any_signal(); return 1; }
static bool try_take(Obj *o, uint64_t since = ~0ull) {
    switch (o->kind) {
    case 2: if (!o->signaled) return false; if (!o->manual) o->signaled = false; return true;
    case 3:
        if (o->owner && o->owner != cur_tid()) return false;
        if (!o->owner && o->handoff && since >= o->handoff) return false;   // reservado para quem ja esperava
        if (!o->owner) o->handoff = 0;
        o->owner = cur_tid(); ++o->rec; return true;
    case 4: if (o->count <= 0) return false; --o->count; return true;
    case 5: return o->signaled;
    default: return true;
    }
}
// qualquer objeto sinalizado acorda quem esta em WaitForMultipleObjects (antes: verificava a cada 0,5 ms)
static std::mutex g_any_m; static std::condition_variable g_any_cv; static std::atomic<uint64_t> g_any_gen{0};
static void any_signal() { g_any_gen.fetch_add(1); std::lock_guard<std::mutex> lk(g_any_m); g_any_cv.notify_all(); }
static uint32_t wait_one(uint32_t h, uint32_t ms) {
    Obj *o = get_obj(h); if (!o) return 0xFFFFFFFFu;
    std::unique_lock<std::mutex> lk(o->m);
    if (try_take(o)) return 0;
    if (ms == 0) return 0x102;
    const uint64_t since = o->gen; ++o->waiters;
    bool ok;
    if (ms == 0xFFFFFFFFu) { o->cv.wait(lk, [&] { return try_take(o, since); }); ok = true; }
    else ok = o->cv.wait_for(lk, std::chrono::milliseconds(ms), [&] { return try_take(o, since); });
    if (--o->waiters == 0 && !o->owner) o->handoff = 0;
    if (!ok && o->handoff && !o->owner) o->cv.notify_all();
    return ok ? 0 : 0x102;
}
F(K_WaitForSingleObject) { return wait_one(a[0], a[1]); }
F(K_WaitForMultipleObjects) {
    // simples: espera em sequencia (todos) ou o primeiro que der (um)
    const uint32_t n = a[0];
    if (a[2]) { for (uint32_t i = 0; i < n; ++i) wait_one(rd32(a[1] + 4 * i), a[3]); return 0; }
    const uint64_t end = now_ns() + (uint64_t)a[3] * 1000000ull;
    for (;;) {
        const uint64_t g = g_any_gen.load();
        for (uint32_t i = 0; i < n; ++i) if (wait_one(rd32(a[1] + 4 * i), 0) == 0) return i;
        if (a[3] != 0xFFFFFFFFu && now_ns() >= end) return 0x102;
        std::unique_lock<std::mutex> lk(g_any_m);
        g_any_cv.wait_for(lk, std::chrono::milliseconds(2), [&] { return g_any_gen.load() != g; });
    }
}
uint32_t rt_new_thread_stack();
void rt_thread_main(uint32_t start, uint32_t param, uint32_t h);
F(K_CreateThread) {
    Obj *o = new Obj; o->kind = 5; const uint32_t h = new_handle(o);
    const uint32_t start = a[2], param = a[3];
    rt_log("[bully] CreateThread(%08X, %08X)\n", start, param);
    std::thread([start, param, h] { rt_thread_main(start, param, h); }).detach();
    if (a[5]) wr32(a[5], h);
    return h;
}
F(K_SuspendThread) { return 0; }
F(K_ResumeThread) { return 1; }
F(K_RaiseException) { rt_fatal("RaiseException(%08X)\n", a[0]); }
F(K_RtlUnwind) { rt_fatal("RtlUnwind\n"); }
F(K_GetConsoleCP) { return 437; }
F(K_GetConsoleOutputCP) { return 437; }
F(K_GetConsoleMode) { return 0; }
F(K_WriteConsoleA) { fwrite(M + a[1], 1, a[2], stderr); if (a[3]) wr32(a[3], a[2]); return 1; }
F(K_WriteConsoleW) { return 0; }
F(K_SetStdHandle) { return 1; }

F(K_EncodePointer) { return a[0]; }
F(K_FlsAlloc) { return g_tls_next++; }
F(K_InitCSSpin) { memset(M + a[0], 0, 24); cs_of(a[0]); return 1; }
F(K_IsProcessorFeaturePresent) { return 0; }   // sem SSE2: o CRT usa o caminho x87 (o recompilador nao traduz SSE2)
F(K_HeapSetInformation) { return 1; }
F(K_Ret0) { return 0; }
F(K_Ret1) { return 1; }

// ---- registro: guardado em <files>/registro.txt (uma linha por valor: chave<TAB>nome<TAB>tipo<TAB>dados em hex).
// O launcher escreve ali as opcoes graficas (RESW/RESH/SHA... em HKCU\Software\Rockstar Games\Bully Scholarship Edition\A0)
// e o que o jogo grava pelo menu de opcoes tambem fica salvo.
struct RegVal { uint32_t type; std::vector<uint8_t> data; };
static std::mutex g_reg_mtx;
static std::map<std::string, RegVal> g_reg;            // "chave\nome" (minusculas)
static std::map<uint32_t, std::string> g_reg_keys;     // handle -> chave
static uint32_t g_reg_next = 0x20000u;
static bool g_reg_loaded = false;
static std::string reg_lower(std::string s) { for (char &ch : s) { if (ch == '/') ch = '\\'; ch = (char)tolower((unsigned char)ch); } while (!s.empty() && s.back() == '\\') s.pop_back(); return s; }
static std::string reg_file() { return g_files_dir + "/registro.txt"; }
static void reg_load() {
    if (g_reg_loaded) return; g_reg_loaded = true;
    FILE *fp = fopen(reg_file().c_str(), "r"); if (!fp) return;
    char line[4096];
    while (fgets(line, sizeof line, fp)) {
        char *t1 = strchr(line, '\t'); if (!t1) continue; *t1++ = 0;
        char *t2 = strchr(t1, '\t'); if (!t2) continue; *t2++ = 0;
        char *t3 = strchr(t2, '\t'); if (!t3) continue; *t3++ = 0;
        RegVal v; v.type = (uint32_t)strtoul(t2, nullptr, 10);
        for (char *p = t3; isxdigit((unsigned char)p[0]) && isxdigit((unsigned char)p[1]); p += 2) { char b[3] = {p[0], p[1], 0}; v.data.push_back((uint8_t)strtoul(b, nullptr, 16)); }
        g_reg[reg_lower(line) + "\\" + reg_lower(t1)] = v;
    }
    fclose(fp);
    rt_log("[bully] registro: %zu valores de %s\n", g_reg.size(), reg_file().c_str());
}
static void reg_save() {
    FILE *fp = fopen(reg_file().c_str(), "w"); if (!fp) return;
    for (auto &kv : g_reg) {
        const size_t sl = kv.first.rfind('\\');
        fprintf(fp, "%s\t%s\t%u\t", kv.first.substr(0, sl).c_str(), kv.first.substr(sl + 1).c_str(), kv.second.type);
        for (uint8_t b : kv.second.data) fprintf(fp, "%02x", b);
        fputc('\n', fp);
    }
    fclose(fp);
}
static std::string reg_root(uint32_t h) {
    switch (h) {
    case 0x80000000u: return "hkcr"; case 0x80000001u: return "hkcu"; case 0x80000002u: return "hklm"; case 0x80000003u: return "hku";
    default: { auto it = g_reg_keys.find(h); return it != g_reg_keys.end() ? it->second : "hkcu"; }
    }
}
static uint32_t reg_open(uint32_t root, uint32_t sub, uint32_t out) {
    std::lock_guard<std::mutex> lk(g_reg_mtx); reg_load();
    std::string k = reg_root(root); if (sub && *gstr(sub)) k += "\\" + reg_lower(gstr(sub));
    const uint32_t h = g_reg_next++; g_reg_keys[h] = k; if (out) wr32(out, h);
    return 0;
}
F(A_RegOpenKeyA) { rt_log("[bully] RegOpenKey(%s)\n", gstr(a[1])); return reg_open(a[0], a[1], a[2]); }
F(A_RegOpenKeyExA) { rt_log("[bully] RegOpenKeyEx(%s)\n", gstr(a[1])); return reg_open(a[0], a[1], a[4]); }
F(A_RegCreateKeyExA) { if (a[8]) wr32(a[8], 2); return reg_open(a[0], a[1], a[7]); }
F(A_RegQueryValueExA) {   // (hKey, name, reserved, *type, *data, *cbData)
    std::lock_guard<std::mutex> lk(g_reg_mtx); reg_load();
    auto it = g_reg.find(reg_root(a[0]) + "\\" + reg_lower(gstr(a[1])));
    if (it == g_reg.end()) { rt_log("[bully] RegQueryValueEx(%s): nao existe\n", gstr(a[1])); return 2; }
    const RegVal &v = it->second; const uint32_t n = (uint32_t)v.data.size();
    if (a[3]) wr32(a[3], v.type);
    uint32_t r = 0;
    if (a[4]) { const uint32_t cap = a[5] ? rd32(a[5]) : 0; if (cap < n) r = 234; else memcpy(M + a[4], v.data.data(), n); }
    if (a[5]) wr32(a[5], n);
    rt_log("[bully] RegQueryValueEx(%s) = %u bytes%s\n", gstr(a[1]), n, r ? " (buffer pequeno)" : "");
    return r;
}
F(A_RegSetValueExA) {     // (hKey, name, reserved, type, *data, cbData)
    std::lock_guard<std::mutex> lk(g_reg_mtx); reg_load();
    RegVal v; v.type = a[3]; v.data.assign(M + a[4], M + a[4] + (a[4] ? a[5] : 0));
    g_reg[reg_root(a[0]) + "\\" + reg_lower(gstr(a[1]))] = v;
    reg_save();
    return 0;
}
F(A_RegCloseKey) { std::lock_guard<std::mutex> lk(g_reg_mtx); g_reg_keys.erase(a[0]); return 0; }
// ---- shell / COM / controles
F(S_SHGetFolderPathA) { const char *p = "C:\\Bully\\userdata"; strcpy((char *)M + a[4], p); mkdir((g_dir + "/userdata").c_str(), 0755); return 0; }
F(O_CoInitialize) { return 0; }
F(O_CoUninitialize) { return 0; }
F(O_CoCreateInstance) {
    const uint8_t *g = M + a[0];
    rt_log("[bully] CoCreateInstance({%08X-%04X-%04X-%02X%02X-...})\n", rd32(a[0]), rd16(a[0] + 4), rd16(a[0] + 6), g[8], g[9]);
    extern uint32_t xact_create(uint32_t clsid);
    if (const uint32_t o = xact_create(a[0])) { wr32(a[4], o); return 0; }
    wr32(a[4], 0); return 0x80040154u;   // REGDB_E_CLASSNOTREG
}
F(O_CoSetProxyBlanket) { return 0; }
F(O_CoTaskMemFree) { return 0; }
F(O_SysAllocString) { int n = 0; while (rd16(a[0] + 2 * n)) ++n; const uint32_t p = rt_alloc(4 + 2 * n + 2, false); wr32(p, 2 * n); memcpy(M + p + 4, M + a[0], 2 * n + 2); return p + 4; }
F(O_SysFreeString) { if (a[0]) rt_free(a[0] - 4); return 0; }
F(C_InitCommonControlsEx) { return 1; }
// ---- janela (USER32/GDI32): uma janela falsa do tamanho da tela
static uint32_t g_wndproc = 0; static int g_scr_w = 1280, g_scr_h = 720;
// ---- janelas e mensagens: cada classe guarda o WndProc do jogo; mensagens postadas vao para uma fila que o
// PeekMessageA entrega e o DispatchMessageA leva ao WndProc (chamada ao codigo do jogo)
struct WMsg { uint32_t hwnd, msg, wp, lp; };
static std::mutex g_msg_mtx; static std::deque<WMsg> g_msgq;
static std::map<std::string, uint32_t> g_class_proc; static std::map<uint32_t, uint32_t> g_atom_proc, g_wnd_proc;
static uint32_t g_next_atom = 0xC001, g_next_hwnd = 0x10010;
static void post_msg(uint32_t h, uint32_t m, uint32_t wp, uint32_t lp) { std::lock_guard<std::mutex> lk(g_msg_mtx); g_msgq.push_back({h, m, wp, lp}); }
static uint32_t call_wndproc(Cpu &c, uint32_t h, uint32_t m, uint32_t wp, uint32_t lp) {
    uint32_t proc; { std::lock_guard<std::mutex> lk(g_msg_mtx); auto it = g_wnd_proc.find(h); proc = it != g_wnd_proc.end() ? it->second : g_wndproc; }
    if (!proc) return 0;
    const uint32_t save[4] = {c.r[1], c.r[2], c.r[0], c.r[4]};
    PUSH(lp); PUSH(wp); PUSH(m); PUSH(h); PUSH(0xDEAD0001u);
    x86_call(c, proc);
    const uint32_t r = c.r[0];
    c.r[1] = save[0]; c.r[2] = save[1]; c.r[4] = save[3];   // stdcall ja limpou, mas garante
    return r;
}
F(U_RegisterClassA) {
    const uint32_t proc = rd32(a[0] + 4), name = rd32(a[0] + 36);
    g_wndproc = proc;
    std::lock_guard<std::mutex> lk(g_msg_mtx);
    const uint32_t atom = g_next_atom++;
    g_atom_proc[atom] = proc;
    if (name >> 16) g_class_proc[gstr(name)] = proc;
    rt_log("[bully] RegisterClass(%s) WndProc=%08X\n", (name >> 16) ? gstr(name) : "#", proc);
    return atom;
}
F(U_CreateWindowExA) {
    uint32_t proc = 0, h;
    {
        std::lock_guard<std::mutex> lk(g_msg_mtx);
        if (a[1] >> 16) { auto it = g_class_proc.find(gstr(a[1])); if (it != g_class_proc.end()) proc = it->second; }
        else { auto it = g_atom_proc.find(a[1] & 0xFFFF); if (it != g_atom_proc.end()) proc = it->second; }
        if (!proc) proc = g_wndproc;
        h = g_next_hwnd; g_next_hwnd += 0x10; g_wnd_proc[h] = proc;
    }
    rt_log("[bully] CreateWindowEx(%s, %dx%d) = %08X\n", gstr(a[2]), (int)a[6], (int)a[7], h);
    if (!a[8]) {   // janela principal: o Windows a ativa (o jogo espera WM_ACTIVATE para comecar)
        post_msg(h, 0x18, 1, 0);        // WM_SHOWWINDOW
        post_msg(h, 0x1C, 1, 0);        // WM_ACTIVATEAPP
        post_msg(h, 0x06, 1, 0);        // WM_ACTIVATE (WA_ACTIVE)
        post_msg(h, 0x07, 0, 0);        // WM_SETFOCUS
        post_msg(h, 0x05, 0, (uint32_t)(g_scr_h << 16) | (uint32_t)g_scr_w);   // WM_SIZE
    }
    return h;
}
F(U_PeekMessageA) {   // (lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg)
    WMsg m;
    { std::lock_guard<std::mutex> lk(g_msg_mtx); if (g_msgq.empty()) return 0; m = g_msgq.front(); if (a[4] & 1) g_msgq.pop_front(); }
    const uint32_t p = a[0];
    wr32(p, m.hwnd); wr32(p + 4, m.msg); wr32(p + 8, m.wp); wr32(p + 12, m.lp); wr32(p + 16, (uint32_t)(clock() / (CLOCKS_PER_SEC / 1000))); wr32(p + 20, 0); wr32(p + 24, 0);
    return 1;
}
F(U_DispatchMessageA) { return call_wndproc(c, rd32(a[0]), rd32(a[0] + 4), rd32(a[0] + 8), rd32(a[0] + 12)); }
F(U_SendMessageA) { return call_wndproc(c, a[0], a[1], a[2], a[3]); }
F(U_PostMessageA) { post_msg(a[0], a[1], a[2], a[3]); return 1; }
F(U_DefWindowProcA) { return a[1] == 0x81 /*WM_NCCREATE*/ ? 1 : 0; }
F(U_Ret1) { return 1; }
F(U_Ret0) { return 0; }
F(U_GetClientRect) { wr32(a[1], 0); wr32(a[1] + 4, 0); wr32(a[1] + 8, g_scr_w); wr32(a[1] + 12, g_scr_h); return 1; }
F(U_GetMonitorInfoA) { const uint32_t p = a[1]; for (int k = 0; k < 2; ++k) { wr32(p + 4 + 16 * k, 0); wr32(p + 8 + 16 * k, 0); wr32(p + 12 + 16 * k, g_scr_w); wr32(p + 16 + 16 * k, g_scr_h); } wr32(p + 36, 1); return 1; }
F(U_GetCursorPos) { wr32(a[0], g_scr_w / 2); wr32(a[0] + 4, g_scr_h / 2); return 1; }
F(U_GetUserObjectInformationA) { if (a[2] && a[3] >= 12) { wr32(a[2], 0); wr32(a[2] + 4, 0); wr32(a[2] + 8, 1 /*WSF_VISIBLE*/); } if (a[4]) wr32(a[4], 12); return 1; }
F(U_MessageBoxA) { rt_log("[bully] MessageBox: %s | %s\n", gstr(a[2]), gstr(a[1])); return 1; }
F(U_wsprintfW) { wr16(a[0], 0); return 0; }   // cdecl
F(U_DialogBoxIndirectParamA) { rt_log("[bully] DialogBoxIndirectParam (ignorado)\n"); return 1; }
F(G_GetStockObject) { return 0x100 + a[0]; }
// O jogo usa DirectDraw so para ler a memoria de video total (DDCAPS.dwVidMemTotal) e grava em 0xBCBC28.
// Sem isso o orcamento de texturas do streaming (total - usado - 50 MB) fica negativo: toda TXD "nao cabe",
// o jogo descarrega e recarrega o mapa sem parar e o LoadAllRequestedModels das telas de loading nao termina.
// Preenchemos o valor aqui (512 MB, igual ao GetAvailableTextureMem) e devolvemos falha como antes.
F(D_DirectDrawCreateEx) { wr32(0xBCBC28u, 512u << 20); wr32(0xBCBC2Cu, 0); rt_log("[bully] DirectDrawCreateEx: memoria de video = 512 MB\n"); return 0x80004005u; }
// OpenMP (vcomp.dll) numa thread so: o "paralelo" roda uma vez, como thread 0 de 1. Funcoes cdecl (nargs 0 na tabela).
F(V_vcomp_fork) {   // (ifval, nargs, func, ...args)
    const uint32_t sp = c.r[4];
    const uint32_t n = rd32(sp + 8), fn = rd32(sp + 12);
    for (uint32_t k = n; k-- > 0;) { c.r[4] -= 4; wr32(c.r[4], rd32(sp + 16 + 4 * k)); }
    c.r[4] -= 4; wr32(c.r[4], 0xDEAD0003u);
    x86_call(c, fn);
    c.r[4] = sp;
    return 0;
}
F(V_vcomp_for_static_simple_init) {   // (first, last, step, increment, *begin, *end)
    const uint32_t sp = c.r[4];
    wr32(rd32(sp + 20), rd32(sp + 4)); wr32(rd32(sp + 24), rd32(sp + 8));
    return 0;
}
F(V_vcomp_for_static_end) { return 0; }
// XInput: controle 0 = controles na tela + controle fisico (input.cpp); os outros nao existem
F(X_XInputGetState) { static bool lg = false; if (!lg) { lg = true; rt_log("[xinput] o jogo leu o controle %u\n", a[0]); } if (a[0] != 0 || !a[1]) return 1167; uint8_t st[16]; if (!input_get_xinput(st)) return 1167; memcpy(M + a[1], st, 16); return 0; }
F(X_XInputSetState) { return a[0] == 0 ? 0 : 1167; }   // vibracao: ignorada
F(X_XInputGetCapabilities) {   // (user, flags, XINPUT_CAPABILITIES 20 bytes)
    if (a[0] != 0) return 1167;
    const uint32_t p = a[2]; memset(M + p, 0, 20); M[p] = 1; M[p + 1] = 1;   // gamepad
    wr16(p + 4, 0xF3FF); M[p + 6] = 255; M[p + 7] = 255; wr16(p + 8, 0xFFC0); wr16(p + 10, 0xFFC0); wr16(p + 12, 0xFFC0); wr16(p + 14, 0xFFC0);
    wr16(p + 16, 0xFFFF); wr16(p + 18, 0xFFFF);
    return 0;
}

#define E(n, k, f) {n, k, f}
static const Imp g_tab[] = {
    E("GetVersionExA", 1, K_GetVersionExA), E("GetModuleHandleA", 1, K_GetModuleHandleA), E("GetCommandLineA", 0, K_GetCommandLineA),
    E("GetStartupInfoA", 1, K_GetStartupInfoA), E("GetStdHandle", 1, K_GetStdHandle), E("GetFileType", 1, K_GetFileType),
    E("SetHandleCount", 1, K_SetHandleCount), E("GetEnvironmentStrings", 0, K_GetEnvironmentStrings), E("GetEnvironmentStringsW", 0, K_GetEnvironmentStrings),
    E("FreeEnvironmentStringsA", 1, K_FreeEnvironmentStrings), E("FreeEnvironmentStringsW", 1, K_FreeEnvironmentStrings), E("GetACP", 0, K_GetACP),
    E("GetOEMCP", 0, K_GetOEMCP), E("IsValidCodePage", 1, K_IsValidCodePage), E("GetCPInfo", 2, K_GetCPInfo), E("GetModuleFileNameA", 3, K_GetModuleFileNameA),
    E("GetCurrentDirectoryA", 2, K_GetCurrentDirectoryA), E("GetFullPathNameA", 4, K_GetFullPathNameA), E("GetDriveTypeA", 1, K_GetDriveTypeA),
    E("SetEnvironmentVariableA", 2, K_SetEnvironmentVariableA),
    E("HeapCreate", 3, K_HeapCreate), E("HeapDestroy", 1, K_HeapDestroy), E("GetProcessHeap", 0, K_GetProcessHeap), E("HeapAlloc", 3, K_HeapAlloc),
    E("HeapFree", 3, K_HeapFree), E("HeapReAlloc", 4, K_HeapReAlloc), E("HeapSize", 3, K_HeapSize), E("LocalAlloc", 2, K_LocalAlloc), E("LocalFree", 1, K_LocalFree),
    E("VirtualAlloc", 4, K_VirtualAlloc), E("VirtualFree", 3, K_VirtualFree), E("VirtualQuery", 3, K_VirtualQuery), E("GlobalMemoryStatus", 1, K_GlobalMemoryStatus),
    E("GetSystemInfo", 1, K_GetSystemInfo), E("TlsAlloc", 0, K_TlsAlloc), E("TlsFree", 1, K_TlsFree), E("TlsGetValue", 1, K_TlsGetValue), E("TlsSetValue", 2, K_TlsSetValue),
    E("InitializeCriticalSection", 1, K_InitializeCriticalSection), E("DeleteCriticalSection", 1, K_DeleteCriticalSection),
    E("EnterCriticalSection", 1, K_EnterCriticalSection), E("LeaveCriticalSection", 1, K_LeaveCriticalSection),
    E("InterlockedIncrement", 1, K_InterlockedIncrement), E("InterlockedDecrement", 1, K_InterlockedDecrement), E("InterlockedExchange", 2, K_InterlockedExchange),
    E("GetTickCount", 0, K_GetTickCount), E("QueryPerformanceCounter", 1, K_QueryPerformanceCounter), E("QueryPerformanceFrequency", 1, K_QueryPerformanceFrequency),
    E("GetSystemTimeAsFileTime", 1, K_GetSystemTimeAsFileTime), E("GetLocalTime", 1, K_GetLocalTime), E("Sleep", 1, K_Sleep),
    E("GetCurrentThreadId", 0, K_GetCurrentThreadId), E("GetCurrentProcessId", 0, K_GetCurrentProcessId), E("GetCurrentProcess", 0, K_GetCurrentProcess),
    E("GetLastError", 0, K_GetLastError), E("SetLastError", 1, K_SetLastError), E("SetUnhandledExceptionFilter", 1, K_SetUnhandledExceptionFilter),
    E("UnhandledExceptionFilter", 1, K_UnhandledExceptionFilter), E("IsDebuggerPresent", 0, K_IsDebuggerPresent), E("OutputDebugStringA", 1, K_OutputDebugStringA),
    E("DebugBreak", 0, K_DebugBreak), E("ExitProcess", 1, K_ExitProcess), E("TerminateProcess", 2, K_TerminateProcess), E("SetThreadPriority", 2, K_SetThreadPriority),
    E("MultiByteToWideChar", 6, K_MultiByteToWideChar), E("WideCharToMultiByte", 8, K_WideCharToMultiByte), E("GetStringTypeA", 5, K_GetStringTypeA),
    E("GetStringTypeW", 4, K_GetStringTypeW), E("LCMapStringA", 6, K_LCMapStringA), E("LCMapStringW", 6, K_LCMapStringW), E("CompareStringA", 6, K_CompareStringA),
    E("CompareStringW", 6, K_CompareStringW), E("GetLocaleInfoA", 4, K_GetLocaleInfoA), E("lstrlenA", 1, K_lstrlenA),
    E("LoadLibraryA", 1, K_LoadLibraryA), E("FreeLibrary", 1, K_FreeLibrary), E("GetProcAddress", 2, K_GetProcAddress),
    E("CreateFileA", 7, K_CreateFileA), E("ReadFile", 5, K_ReadFile), E("WriteFile", 5, K_WriteFile), E("SetFilePointer", 4, K_SetFilePointer),
    E("GetFileSize", 2, K_GetFileSize), E("SetEndOfFile", 1, K_SetEndOfFile), E("FlushFileBuffers", 1, K_FlushFileBuffers), E("CloseHandle", 1, K_CloseHandle),
    E("GetFileAttributesA", 1, K_GetFileAttributesA), E("CreateDirectoryA", 2, K_CreateDirectoryA), E("DeleteFileA", 1, K_DeleteFileA),
    E("FindFirstFileA", 2, K_FindFirstFileA), E("FindNextFileA", 2, K_FindNextFileA), E("FindClose", 1, K_FindClose), E("GetOverlappedResult", 4, K_GetOverlappedResult),
    E("CreateEventA", 4, K_CreateEventA), E("CreateMutexA", 3, K_CreateMutexA), E("CreateSemaphoreA", 4, K_CreateSemaphoreA), E("ReleaseMutex", 1, K_ReleaseMutex),
    E("ReleaseSemaphore", 3, K_ReleaseSemaphore), E("WaitForSingleObject", 2, K_WaitForSingleObject), E("WaitForMultipleObjects", 4, K_WaitForMultipleObjects),
    E("CreateThread", 6, K_CreateThread), E("SuspendThread", 1, K_SuspendThread), E("ResumeThread", 1, K_ResumeThread), E("RaiseException", 4, K_RaiseException),
    E("RtlUnwind", 4, K_RtlUnwind), E("GetConsoleCP", 0, K_GetConsoleCP), E("GetConsoleOutputCP", 0, K_GetConsoleOutputCP), E("GetConsoleMode", 2, K_GetConsoleMode),
    E("WriteConsoleA", 5, K_WriteConsoleA), E("EncodePointer", 1, K_EncodePointer), E("DecodePointer", 1, K_EncodePointer),
    E("FlsAlloc", 1, K_FlsAlloc), E("FlsGetValue", 1, K_TlsGetValue), E("FlsSetValue", 2, K_TlsSetValue), E("FlsFree", 1, K_TlsFree),
    E("InitializeCriticalSectionAndSpinCount", 2, K_InitCSSpin), E("IsProcessorFeaturePresent", 1, K_IsProcessorFeaturePresent),
    E("HeapSetInformation", 4, K_HeapSetInformation),
    E("RegOpenKeyA", 3, A_RegOpenKeyA), E("RegOpenKeyExA", 5, A_RegOpenKeyExA), E("RegCreateKeyExA", 9, A_RegCreateKeyExA),
    E("RegQueryValueExA", 6, A_RegQueryValueExA), E("RegSetValueExA", 6, A_RegSetValueExA), E("RegCloseKey", 1, A_RegCloseKey),
    E("SHGetFolderPathA", 5, S_SHGetFolderPathA), E("CoInitialize", 1, O_CoInitialize), E("CoInitializeEx", 2, O_CoInitialize),
    E("CoUninitialize", 0, O_CoUninitialize), E("CoCreateInstance", 5, O_CoCreateInstance), E("CoSetProxyBlanket", 8, O_CoSetProxyBlanket),
    E("CoTaskMemFree", 1, O_CoTaskMemFree), E("OLEAUT32.dll!#2", 1, O_SysAllocString), E("OLEAUT32.dll!#6", 1, O_SysFreeString),
    E("InitCommonControlsEx", 1, C_InitCommonControlsEx),
    E("RegisterClassA", 1, U_RegisterClassA), E("CreateWindowExA", 12, U_CreateWindowExA), E("ShowWindow", 2, U_Ret1), E("UpdateWindow", 1, U_Ret1),
    E("SetWindowPos", 7, U_Ret1), E("MoveWindow", 6, U_Ret1), E("GetClientRect", 2, U_GetClientRect), E("GetWindowRect", 2, U_GetClientRect),
    E("AdjustWindowRect", 3, U_Ret1), E("PeekMessageA", 5, U_PeekMessageA), E("TranslateMessage", 1, U_Ret0), E("DispatchMessageA", 1, U_DispatchMessageA),
    E("DefWindowProcA", 4, U_DefWindowProcA), E("LoadIconA", 2, U_Ret1), E("LoadCursorA", 2, U_Ret1), E("ShowCursor", 1, U_Ret0),
    E("SystemParametersInfoA", 4, U_Ret1), E("GetMonitorInfoA", 2, U_GetMonitorInfoA), E("GetCursorPos", 1, U_GetCursorPos), E("ScreenToClient", 2, U_Ret1),
    E("IsWindow", 1, U_Ret1), E("SetWindowTextA", 2, U_Ret1), E("GetWindowLongA", 2, U_Ret0), E("SendMessageA", 4, U_SendMessageA), E("PostMessageA", 4, U_PostMessageA),
    E("PostQuitMessage", 1, U_Ret0), E("DestroyWindow", 1, U_Ret1), E("ChangeDisplaySettingsA", 2, U_Ret0), E("MessageBoxA", 4, U_MessageBoxA), E("GetProcessWindowStation", 0, U_Ret1), E("GetUserObjectInformationA", 5, U_GetUserObjectInformationA),
    E("GetActiveWindow", 0, U_Ret0), E("GetLastActivePopup", 1, U_Ret0),
    E("MessageBoxW", 4, U_Ret1), E("mouse_event", 5, U_Ret0), E("TranslateAcceleratorA", 3, U_Ret0), E("wsprintfW", 0, U_wsprintfW),
    E("DialogBoxIndirectParamA", 5, U_DialogBoxIndirectParamA), E("EndDialog", 2, U_Ret1), E("SendDlgItemMessageA", 5, U_Ret0), E("CheckDlgButton", 3, U_Ret1),
    E("GetStockObject", 1, G_GetStockObject), E("DirectDrawCreateEx", 4, D_DirectDrawCreateEx), 
    E("_vcomp_fork", 0, V_vcomp_fork), E("_vcomp_for_static_simple_init", 0, V_vcomp_for_static_simple_init), E("_vcomp_for_static_end", 0, V_vcomp_for_static_end),
    E("XINPUT1_3.dll!#2", 2, X_XInputGetState), E("XINPUT1_3.dll!#3", 2, X_XInputSetState), E("XINPUT1_3.dll!#4", 3, X_XInputGetCapabilities),
 E("WriteConsoleW", 5, K_WriteConsoleW), E("SetStdHandle", 2, K_SetStdHandle),
};

static const Imp *find_imp(const char *full) {
    for (const Imp &i : g_tab) if (strchr(i.name, '!') && !strcasecmp(i.name, full)) return &i;
    const char *n = strchr(full, '!'); n = n ? n + 1 : full;
    for (const Imp &i : g_tab) if (!strcmp(i.name, n)) return &i;
    for (int k = 0; k < g_d3d9_nimports; ++k) if (!strcmp(g_d3d9_imports[k].name, n)) return (const Imp *)&g_d3d9_imports[k];
    for (int k = 0; k < g_dinput8_nimports; ++k) if (!strcmp(g_dinput8_imports[k].name, n)) return (const Imp *)&g_dinput8_imports[k];
    for (int k = 0; k < g_d3dx9_nimports; ++k) if (!strcmp(g_d3dx9_imports[k].name, n)) return (const Imp *)&g_d3dx9_imports[k];
    return nullptr;
}
// ---- tempo por import/metodo COM (so a thread do jogo, tempo proprio sem filhos) ----
struct IpE { std::atomic<const char *> k{nullptr}; std::atomic<uint64_t> ns{0}, n{0}; };
static const bool k_ipprof = false;   // medicao por import (custa ~2 leituras de relogio por chamada; ligar so para investigar)
static IpE g_ip[2048], g_ip2[2048];   // g_ip2 = outras threads (carregamento etc.)
static thread_local uint64_t tl_ipchild = 0;
static inline uint64_t ip_now() { timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return (uint64_t)t.tv_sec * 1000000000ull + (uint64_t)t.tv_nsec; }
static void ip_add(const char *k, uint64_t ns) {
    IpE *g_ipx = tl_ipmain ? g_ip : g_ip2;
    size_t h = ((uintptr_t)k >> 3) & 2047;
    for (int i = 0; i < 2048; ++i, h = (h + 1) & 2047) {
        const char *e = g_ipx[h].k.load(std::memory_order_relaxed);
        if (!e && g_ipx[h].k.compare_exchange_strong(e, k)) e = k;
        if (e == k) { g_ipx[h].ns.fetch_add(ns, std::memory_order_relaxed); g_ipx[h].n.fetch_add(1, std::memory_order_relaxed); return; }
    }
}
void rt_ip_mark_main() { tl_ipmain = true; }
void rt_ip_dump(int frames) {
    rt_file_stats_dump(frames);
    if (!k_ipprof) return;
    struct R { const char *k; uint64_t ns, n; }; std::vector<R> v; uint64_t sum = 0;
    for (auto &e : g_ip) { const char *k = e.k.load(); if (!k) continue; R r{k, e.ns.exchange(0), e.n.exchange(0)}; sum += r.ns; if (r.n) v.push_back(r); }
    std::sort(v.begin(), v.end(), [](const R &a, const R &b) { return a.ns > b.ns; });
    rt_log("[imports] total %.1f ms/quadro dentro do runtime (o resto e codigo do jogo)\n", sum / 1e6 / frames);
    for (size_t i = 0; i < v.size() && i < 16; ++i)
        rt_log("[imports]  %6.2f ms  %7.1f chamadas  %s\n", v[i].ns / 1e6 / frames, (double)v[i].n / frames, v[i].k);
    v.clear();
    for (auto &e : g_ip2) { const char *k = e.k.load(); if (!k) continue; R r{k, e.ns.exchange(0), e.n.exchange(0)}; if (r.n) v.push_back(r); }
    std::sort(v.begin(), v.end(), [](const R &a, const R &b) { return a.ns > b.ns; });
    for (size_t i = 0; i < v.size() && i < 10; ++i)
        rt_log("[imports-outras]  %6.2f ms  %7.1f chamadas  %s\n", v[i].ns / 1e6 / frames, (double)v[i].n / frames, v[i].k);
}
#define IP_BEGIN uint64_t ip_t0 = 0, ip_sv = 0; const bool ip_on = k_ipprof; if (ip_on) { ip_t0 = ip_now(); ip_sv = tl_ipchild; tl_ipchild = 0; }
#define IP_END(nm) if (ip_on) { const uint64_t dt = ip_now() - ip_t0; ip_add(nm, dt > tl_ipchild ? dt - tl_ipchild : 0); tl_ipchild = ip_sv + dt; }

#define FASTI(nm, nargs, body) static void FI_##nm(Cpu &c) { const uint32_t sp = c.r[4]; (void)sp; body; c.r[4] = sp + 4 + 4 * nargs; }
#define FARG(i) rd32(sp + 4 + 4 * (i))
FASTI(EnterCriticalSection, 1, cs_enter(FARG(0)))
FASTI(LeaveCriticalSection, 1, cs_leave(FARG(0)))
FASTI(InterlockedIncrement, 1, c.r[0] = __atomic_add_fetch((uint32_t *)(M + FARG(0)), 1u, __ATOMIC_SEQ_CST))
FASTI(InterlockedDecrement, 1, c.r[0] = __atomic_sub_fetch((uint32_t *)(M + FARG(0)), 1u, __ATOMIC_SEQ_CST))
FASTI(InterlockedExchange, 2, c.r[0] = __atomic_exchange_n((uint32_t *)(M + FARG(0)), FARG(1), __ATOMIC_SEQ_CST))
FASTI(GetCurrentThreadId, 0, c.r[0] = cur_tid())
FASTI(TlsGetValue, 1, { const uint32_t i = FARG(0); t_lasterr = 0; c.r[0] = i < 128 ? t_tls[i] : 0; })
FASTI(GetLastError, 0, c.r[0] = t_lasterr)
FASTI(SetLastError, 1, t_lasterr = FARG(0))
typedef void (*FastImp)(Cpu &);
FastImp rt_fast_import(const char *name) {
    static const struct { const char *n; FastImp f; } tab[] = {
        {"EnterCriticalSection", FI_EnterCriticalSection}, {"LeaveCriticalSection", FI_LeaveCriticalSection},
        {"InterlockedIncrement", FI_InterlockedIncrement}, {"InterlockedDecrement", FI_InterlockedDecrement},
        {"InterlockedExchange", FI_InterlockedExchange}, {"GetCurrentThreadId", FI_GetCurrentThreadId},
        {"TlsGetValue", FI_TlsGetValue}, {"GetLastError", FI_GetLastError}, {"SetLastError", FI_SetLastError}};
    if (const char *x = strchr(name, '!')) name = x + 1;   // nomes da tabela vem como "KERNEL32.dll!Nome"
    for (auto &e : tab) if (!strcmp(e.n, name)) return e.f;
    return nullptr;
}
void rt_call_import(Cpu &c, int id, const char *name) {
    static const Imp *cache[512]; static bool miss[512];
    const Imp *imp = id >= 0 && id < 512 ? cache[id] : nullptr;
    if (!imp && !(id >= 0 && id < 512 && miss[id])) { imp = find_imp(name); if (id >= 0 && id < 512) { cache[id] = imp; miss[id] = !imp; } }
    if (!imp) rt_fatal("import sem implementacao: %s (chamado de %08X)\n", name, rd32(c.r[4]));
    diag_note(c, imp->name, rd32(c.r[4]));
    uint32_t args[16]; for (int k = 0; k < imp->nargs && k < 16; ++k) args[k] = rd32(c.r[4] + 4 + 4 * k);
    IP_BEGIN
    const uint32_t r = imp->fn(c, args);
    IP_END(imp->name)
    c.r[0] = r;
    c.r[4] += 4 + 4u * (uint32_t)imp->nargs;
}

// ---------------------------------------------------------------- thunks dinamicos (GetProcAddress, COM)
struct Dyn { const char *name; int nargs; NativeFn fn; };
static std::vector<Dyn> g_dyn;
static std::mutex g_dyn_mtx;
static Dyn g_dyn_fast[16384]; static std::atomic<uint32_t> g_dyn_pub{0};   // copia sem trava (metodos COM: toda chamada D3D)
uint32_t rt_make_thunk(const char *name, int nargs, NativeFn fn) {
    std::lock_guard<std::mutex> lk(g_dyn_mtx);
    g_dyn.push_back({name, nargs, fn});
    const uint32_t i = (uint32_t)(g_dyn.size() - 1);
    if (i < 16384 && i == g_dyn_pub.load()) { g_dyn_fast[i] = g_dyn.back(); g_dyn_pub.store(i + 1, std::memory_order_release); }
    return DYN_THUNK_BASE + 16u * i;
}
void rt_dyn_thunk(Cpu &c, uint32_t idx) {
    Dyn d;
    if (idx < g_dyn_pub.load(std::memory_order_acquire)) d = g_dyn_fast[idx];
    else { std::lock_guard<std::mutex> lk(g_dyn_mtx); if (idx >= g_dyn.size()) rt_fatal("thunk dinamico invalido %u\n", idx); d = g_dyn[idx]; }
    if (!d.fn) {
        // metodo de objeto COM ainda sem implementacao: avisa uma vez e devolve S_OK (o jogo segue); funcao solta: para
        if (strstr(d.name, "::")) {
            static std::mutex wm; static std::map<std::string, int> warned;
            { std::lock_guard<std::mutex> lk(wm); if (warned[d.name]++ == 0) rt_log("[com] sem implementacao (devolve 0): %s\n", d.name); }
            c.r[0] = 0; c.r[4] += 4 + 4u * (uint32_t)d.nargs; return;
        }
        rt_fatal("funcao sem implementacao: %s\n", d.name);
    }
    diag_note(c, d.name, rd32(c.r[4]));
    uint32_t args[16]; for (int k = 0; k < d.nargs && k < 16; ++k) args[k] = rd32(c.r[4] + 4 + 4 * k);
    IP_BEGIN
    c.r[0] = d.fn(c, args);
    IP_END(d.name)
    c.r[4] += 4 + 4u * (uint32_t)d.nargs;
}
static uint32_t proc_by_name(const char *name) {
    static std::map<std::string, uint32_t> cache; static std::mutex mt; std::lock_guard<std::mutex> lk(mt);
    auto it = cache.find(name); if (it != cache.end()) return it->second;
    uint32_t r;
    if (const Imp *i = find_imp(name)) r = rt_make_thunk(i->name, i->nargs, i->fn);
    else r = rt_make_thunk(strdup(name), 0, nullptr);
    cache[name] = r; return r;
}
static uint32_t proc_by_name_old(const char *name) {
    if (const Imp *i = find_imp(name)) return rt_make_thunk(i->name, i->nargs, i->fn);
    return rt_make_thunk(strdup(name), 0, nullptr);   // cria assim mesmo: so falha se for chamada
}

// ---------------------------------------------------------------- inicio
void rt_trace_cut_init();
void rt_extra_funcs_init();
void rt_win32_init(const char *game_dir) {
    // rt_trace_cut_init();   // rastreio das cutscenes (diagnostico, desligado)
    rt_extra_funcs_init();   // funcoes que o recompilador tinha perdido (so chamadas por vtable)
    { void rt_silentpatch_init(); rt_silentpatch_init(); }   // correcoes do SilentPatch (rt/silentpatch.cpp)
    g_dir = game_dir;
    // TEB/PEB falsos em FSBASE
    memset(M + FSBASE, 0, 0x1000);
    wr32(FSBASE + 0x00, 0xFFFFFFFFu);
    wr32(FSBASE + 0x04, STACK_TOP);
    wr32(FSBASE + 0x08, STACK_TOP - STACK_SIZE);
    wr32(FSBASE + 0x18, FSBASE);
    wr32(FSBASE + 0x30, FSBASE + 0x800);
    misc_top = MISC_BASE + 0x20000;
    diag_start();
}
