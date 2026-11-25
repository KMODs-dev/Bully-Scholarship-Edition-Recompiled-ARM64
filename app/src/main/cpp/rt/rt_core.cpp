#include <atomic>
// Runtime do Bully PC recompilado: memoria, carga do PE, despacho de chamadas, x87 auxiliar, strings.
#include "x86rt.h"
#include "rt.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <algorithm>
#include <mutex>
#include <time.h>

uint8_t *M;
extern const FuncEnt g_funcs[];
extern const unsigned g_nfuncs;
extern const ImportEnt g_imports[];

static int g_nimports;
static uint32_t g_iat_thunk[512];   // id do import -> endereco do thunk

void rt_log(const char *fmt, ...) {
    va_list ap; va_start(ap, fmt); vfprintf(stderr, fmt, ap); va_end(ap); fflush(stderr);
}
void (*g_fatal_hook)() = nullptr;   // no Android: para so a thread do jogo (o app fica aberto com a tela vermelha)
[[noreturn]] void rt_fatal(const char *fmt, ...) {
    va_list ap; va_start(ap, fmt); fprintf(stderr, "[bully] FATAL: "); vfprintf(stderr, fmt, ap); va_end(ap); fflush(stderr);
    if (g_fatal_hook) g_fatal_hook();
    abort();
}

// ---------------------------------------------------------------- memoria
bool rt_mem_init() {
    M = (uint8_t *)mmap(nullptr, 1ull << 32, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
    return M != MAP_FAILED;
}

// alocador simples (heap do Windows/VirtualAlloc) numa faixa da janela de 4 GB
static std::mutex g_heap_mtx;
static uint32_t g_heap_top = HEAP_BASE;
uint32_t rt_heap_top() { return g_heap_top; }
static uint32_t g_free[64];   // listas livres por classe (16 * 2^k)
static int size_class(uint32_t n) { int k = 0; uint32_t s = 16; while (s < n) { s <<= 1; ++k; } return k; }
uint32_t rt_alloc(uint32_t n, bool zero) {
    std::lock_guard<std::mutex> lk(g_heap_mtx);
    const int k = size_class(n + 16); const uint32_t sz = 16u << k;
    uint32_t p;
    if (k < 64 && g_free[k]) { p = g_free[k]; g_free[k] = rd32(p); }
    else {
        p = g_heap_top; g_heap_top += sz;
        if (g_heap_top > HEAP_END || g_heap_top < p) rt_fatal("sem memoria (%u bytes)\n", n);
    }
    wr32(p, (uint32_t)k); wr32(p + 4, n); wr32(p + 8, 0xB011B011u);
    if (zero) memset(M + p + 16, 0, n);
    return p + 16;
}
uint32_t rt_size(uint32_t a) { return a ? rd32(a - 12) : 0; }
void rt_free(uint32_t a) {
    if (!a) return;
    if (rd32(a - 8) != 0xB011B011u) { rt_log("[bully] free invalido %08X\n", a); return; }
    std::lock_guard<std::mutex> lk(g_heap_mtx);
    const uint32_t p = a - 16; const int k = (int)rd32(p);
    wr32(p + 8, 0); wr32(p, g_free[k]); g_free[k] = p;
}
uint32_t rt_realloc(uint32_t a, uint32_t n) {
    if (!a) return rt_alloc(n, false);
    const uint32_t old = rt_size(a);
    const int k = (int)rd32(a - 16);
    if ((16u << k) >= n + 16) { wr32(a - 12, n); return a; }
    const uint32_t b = rt_alloc(n, false);
    memcpy(M + b, M + a, std::min(old, n));
    rt_free(a);
    return b;
}

// ---------------------------------------------------------------- PE
static uint32_t g_entry;
uint32_t rt_entry() { return g_entry; }
bool rt_load_pe(const char *path) {
    FILE *f = fopen(path, "rb"); if (!f) return false;
    fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET);
    uint8_t *d = (uint8_t *)malloc(n); fread(d, 1, n, f); fclose(f);
    uint32_t pe; memcpy(&pe, d + 0x3C, 4);
    uint16_t nsec, optsz; memcpy(&nsec, d + pe + 6, 2); memcpy(&optsz, d + pe + 20, 2);
    const uint32_t opt = pe + 24; uint32_t base, ep; memcpy(&base, d + opt + 28, 4); memcpy(&ep, d + opt + 16, 4);
    g_entry = base + ep;
    memcpy(M + base, d, 0x1000);
    for (int i = 0; i < nsec; ++i) {
        const uint32_t o = opt + optsz + 40 * i; uint32_t vsz, va, rsz, rptr;
        memcpy(&vsz, d + o + 8, 4); memcpy(&va, d + o + 12, 4); memcpy(&rsz, d + o + 16, 4); memcpy(&rptr, d + o + 20, 4);
        memcpy(M + base + va, d + rptr, std::min(rsz, vsz ? std::max(vsz, rsz) : rsz));
    }
    free(d);
    // IAT: cada entrada recebe o endereco de um thunk (para chamadas indiretas que copiam o ponteiro)
    for (int i = 0; g_imports[i].id >= 0; ++i) {
        const uint32_t th = THUNK_BASE + 16u * (uint32_t)g_imports[i].id;
        g_iat_thunk[g_imports[i].id] = th;
        wr32(g_imports[i].iat, th);
        ++g_nimports;
    }
    return true;
}

// ---------------------------------------------------------------- despacho
// chamadas indiretas (vtables): cache direto (endereco<<32 | indice) antes da busca binaria em ~30 mil funcoes
static std::atomic<uint64_t> g_fcache[1 << 16];
// substituicoes de funcoes chamadas por ponteiro (ex.: funcoes C do Lua): diagnostico/correcoes sem regerar o gen
static struct { uint32_t va; Fn fn; } g_ovr[64]; static int g_novr = 0;
Fn rt_orig_func(uint32_t va) {
    unsigned lo = 0, hi = g_nfuncs;
    while (lo < hi) { const unsigned mid = (lo + hi) / 2; if (g_funcs[mid].va < va) lo = mid + 1; else hi = mid; }
    return lo < g_nfuncs && g_funcs[lo].va == va ? g_funcs[lo].fn : nullptr;
}
void rt_override(uint32_t va, Fn fn) { if (g_novr < 64) { g_ovr[g_novr].va = va; g_ovr[g_novr].fn = fn; ++g_novr; } }
static Fn find_func(uint32_t va) {
    std::atomic<uint64_t> &slot = g_fcache[(va ^ (va >> 16)) & 0xFFFF];
    const uint64_t e = slot.load(std::memory_order_relaxed);
    if ((uint32_t)(e >> 32) == va && va) { const uint32_t i = (uint32_t)e; return (i & 0x80000000u) ? g_ovr[i & 0xFFFF].fn : g_funcs[i].fn; }
    for (int k = 0; k < g_novr; ++k) if (g_ovr[k].va == va) { slot.store(((uint64_t)va << 32) | 0x80000000u | (uint32_t)k, std::memory_order_relaxed); return g_ovr[k].fn; }
    unsigned lo = 0, hi = g_nfuncs;
    while (lo < hi) { const unsigned mid = (lo + hi) / 2; if (g_funcs[mid].va < va) lo = mid + 1; else hi = mid; }
    if (lo < g_nfuncs && g_funcs[lo].va == va) { slot.store(((uint64_t)va << 32) | lo, std::memory_order_relaxed); return g_funcs[lo].fn; }
    return nullptr;
}
extern std::atomic<int> g_watch_rearm; void rt_watch_rearm();
void x86_call(Cpu &c, uint32_t t) {
    if (t >= THUNK_BASE && t < THUNK_BASE + 0x100000u) {
        const uint32_t id = (t - THUNK_BASE) / 16u;
        if (t >= DYN_THUNK_BASE) { rt_dyn_thunk(c, (t - DYN_THUNK_BASE) / 16u); return; }
        x86_import(c, (int)id); return;
    }
    if (Fn f = find_func(t)) { f(c); return; }
    rt_log("[bully] registros: eax=%08X ecx=%08X edx=%08X ebx=%08X esp=%08X ebp=%08X esi=%08X edi=%08X\n", c.r[0], c.r[1], c.r[2], c.r[3], c.r[4], c.r[5], c.r[6], c.r[7]);
    for (int k = 5; k <= 7; ++k) { const uint32_t o = c.r[k]; if (o >= 0x400000u && o < 0xE0000000u) { const uint32_t vt = rd32(o); rt_log("[bully]   [reg%d]=%08X vtable[0..3]=%08X %08X %08X %08X +f8=%08X\n", k, vt, vt ? rd32(vt) : 0, vt ? rd32(vt + 4) : 0, vt ? rd32(vt + 8) : 0, vt ? rd32(vt + 12) : 0, vt ? rd32(vt + 0xF8) : 0); } }
    rt_log("[bully]   pilha:"); for (int k = 0; k < 16; ++k) rt_log(" %08X", rd32(c.r[4] + 4 * k)); rt_log("\n");
    rt_fatal("chamada para endereco sem traducao %08X (esp=%08X ret=%08X)\n", t, c.r[4], rd32(c.r[4]));
}
void x86_jump(Cpu &c, uint32_t t) {
    // salto para fora da funcao: equivale a chamar o destino sem empilhar retorno (o "ret" dele volta para o nosso chamador)
    if (t >= THUNK_BASE && t < THUNK_BASE + 0x100000u) { x86_call(c, t); return; }
    if (Fn f = find_func(t)) { f(c); return; }
    rt_fatal("salto para endereco sem traducao %08X\n", t);
}
typedef void (*FastImp)(Cpu &);
FastImp rt_fast_import(const char *name);
void x86_import(Cpu &c, int id) {
    static const char *names[1024];   // nome por id (antes: busca linear em todos os imports a cada chamada)
    static FastImp fast[1024];        // imports pequenos e muito chamados: direto, sem despachante
    if (id >= 0 && id < 1024 && fast[id]) { fast[id](c); return; }
    const char *name = id >= 0 && id < 1024 ? names[id] : nullptr;
    if (!name) {
        for (int i = 0; g_imports[i].id >= 0; ++i) if (g_imports[i].id == id) { name = g_imports[i].name; break; }
        if (!name) name = "?";
        if (id >= 0 && id < 1024) { fast[id] = rt_fast_import(name); names[id] = name; if (fast[id]) { fast[id](c); return; } }
    }
    rt_call_import(c, id, name);
}
void x86_unimpl(Cpu &c, uint32_t pc) { rt_fatal("instrucao sem traducao em %08X\n", pc); }
void x86_fell(Cpu &c, uint32_t pc) { rt_fatal("codigo caiu para fora da funcao em %08X\n", pc); }
void x86_int3(Cpu &c, uint32_t pc) { rt_fatal("int3 em %08X\n", pc); }
void x86_cpuid(Cpu &c) {
    // Pentium III "GenuineIntel": FPU, TSC, CX8, CMOV, MMX, FXSR, SSE; sem SSE2 (o recompilador nao traduz SSE2)
    const uint32_t leaf = c.r[0];
    if (leaf == 0) { c.r[0] = 1; c.r[3] = 0x756E6547; c.r[2] = 0x49656E69; c.r[1] = 0x6C65746E; return; }
    if (leaf == 1) { c.r[0] = 0x0673; c.r[3] = 0x00000000; c.r[1] = 0; c.r[2] = (1u << 0) | (1u << 4) | (1u << 8) | (1u << 15) | (1u << 23) | (1u << 24) | (1u << 25); return; }
    c.r[0] = c.r[1] = c.r[2] = c.r[3] = 0;
}
void x86_rdtsc(Cpu &c) { timespec t; clock_gettime(CLOCK_MONOTONIC, &t); const uint64_t v = (uint64_t)t.tv_sec * 2000000000ull + (uint64_t)t.tv_nsec * 2ull; c.r[0] = (uint32_t)v; c.r[2] = (uint32_t)(v >> 32); }
void x86_divzero(Cpu &c, uint32_t pc) { rt_fatal("divisao por zero em %08X\n", pc); }

// ---------------------------------------------------------------- x87 auxiliar
double rdf80(uint32_t a) {
    uint64_t man; uint16_t se; memcpy(&man, M + a, 8); memcpy(&se, M + a + 8, 2);
    const int e = se & 0x7FFF, s = se >> 15;
    if (e == 0 && man == 0) return s ? -0.0 : 0.0;
    if (e == 0x7FFF) { if (man << 1) { uint64_t q = 0x7FF8000000000000ull | ((uint64_t)s << 63); double v; memcpy(&v, &q, 8); return v; } return s ? -INFINITY : INFINITY; }
    const double v = ldexp((double)man, e - 16383 - 63); return s ? -v : v;
}
void wrf80(uint32_t a, double v) {
    uint64_t man = 0; uint16_t se = 0;
    if (v != v) { se = 0x7FFF | (signbit(v) ? 0x8000 : 0); man = 0xC000000000000000ull; }
    else if (isinf(v)) { se = 0x7FFF | (v < 0 ? 0x8000 : 0); man = 0x8000000000000000ull; }
    else if (v != 0) { int e; const double m = frexp(fabs(v), &e); man = (uint64_t)ldexp(m, 64); se = (uint16_t)((e - 1 + 16383) | (v < 0 ? 0x8000 : 0)); }
    else se = signbit(v) ? 0x8000 : 0;
    memcpy(M + a, &man, 8); memcpy(M + a + 8, &se, 2);
}
void FXAM(Cpu &c) {
    const double v = ST(0); uint16_t f = c.fsw & ~0x4700u;
    if (signbit(v)) f |= 0x200;
    if (v != v) f |= 0x100; else if (isinf(v)) f |= 0x500; else if (v == 0) f |= 0x4000; else if (fpclassify(v) == FP_SUBNORMAL) f |= 0x4400; else f |= 0x400;
    c.fsw = f;
}

// ---------------------------------------------------------------- instrucoes de string
#define STR_IMPL(B, T) \
void x86_str_movs##B(Cpu &c) { const int d = c.df ? -(B / 8) : (B / 8); T v; memcpy(&v, M + c.r[6], B / 8); memcpy(M + c.r[7], &v, B / 8); c.r[6] += d; c.r[7] += d; } \
void x86_str_movs_rep##B(Cpu &c) { if (!c.df && c.r[1]) { const uint32_t n = c.r[1] * (B / 8); memmove(M + c.r[7], M + c.r[6], n); c.r[6] += n; c.r[7] += n; c.r[1] = 0; return; } while (c.r[1]) { x86_str_movs##B(c); --c.r[1]; } } \
void x86_str_movs_repz##B(Cpu &c) { x86_str_movs_rep##B(c); } \
void x86_str_movs_repnz##B(Cpu &c) { x86_str_movs_rep##B(c); } \
void x86_str_stos##B(Cpu &c) { const int d = c.df ? -(B / 8) : (B / 8); T v = (T)c.r[0]; memcpy(M + c.r[7], &v, B / 8); c.r[7] += d; } \
void x86_str_stos_rep##B(Cpu &c) { if (B == 8 && !c.df && c.r[1]) { memset(M + c.r[7], (uint8_t)c.r[0], c.r[1]); c.r[7] += c.r[1]; c.r[1] = 0; return; } while (c.r[1]) { x86_str_stos##B(c); --c.r[1]; } } \
void x86_str_stos_repz##B(Cpu &c) { x86_str_stos_rep##B(c); } \
void x86_str_stos_repnz##B(Cpu &c) { x86_str_stos_rep##B(c); } \
void x86_str_lods##B(Cpu &c) { const int d = c.df ? -(B / 8) : (B / 8); T v; memcpy(&v, M + c.r[6], B / 8); if (B == 32) c.r[0] = v; else if (B == 16) c.r[0] = (c.r[0] & 0xFFFF0000u) | v; else c.r[0] = (c.r[0] & 0xFFFFFF00u) | v; c.r[6] += d; } \
void x86_str_lods_rep##B(Cpu &c) { while (c.r[1]) { x86_str_lods##B(c); --c.r[1]; } } \
void x86_str_lods_repz##B(Cpu &c) { x86_str_lods_rep##B(c); } \
void x86_str_lods_repnz##B(Cpu &c) { x86_str_lods_rep##B(c); } \
void x86_str_cmps##B(Cpu &c) { const int d = c.df ? -(B / 8) : (B / 8); T a, b; memcpy(&a, M + c.r[6], B / 8); memcpy(&b, M + c.r[7], B / 8); FL(K_SUB, (uint32_t)(T)~0u, (uint32_t)a - b, a, b); c.r[6] += d; c.r[7] += d; } \
void x86_str_cmps_rep##B(Cpu &c) { while (c.r[1]) { x86_str_cmps##B(c); --c.r[1]; if (!ZF(c)) break; } } \
void x86_str_cmps_repz##B(Cpu &c) { x86_str_cmps_rep##B(c); } \
void x86_str_cmps_repnz##B(Cpu &c) { while (c.r[1]) { x86_str_cmps##B(c); --c.r[1]; if (ZF(c)) break; } } \
void x86_str_scas##B(Cpu &c) { const int d = c.df ? -(B / 8) : (B / 8); T b; memcpy(&b, M + c.r[7], B / 8); const T a = (T)c.r[0]; FL(K_SUB, (uint32_t)(T)~0u, (uint32_t)a - b, a, b); c.r[7] += d; } \
void x86_str_scas_rep##B(Cpu &c) { while (c.r[1]) { x86_str_scas##B(c); --c.r[1]; if (!ZF(c)) break; } } \
void x86_str_scas_repz##B(Cpu &c) { x86_str_scas_rep##B(c); } \
void x86_str_scas_repnz##B(Cpu &c) { while (c.r[1]) { x86_str_scas##B(c); --c.r[1]; if (ZF(c)) break; } }
STR_IMPL(8, uint8_t) STR_IMPL(16, uint16_t) STR_IMPL(32, uint32_t)
