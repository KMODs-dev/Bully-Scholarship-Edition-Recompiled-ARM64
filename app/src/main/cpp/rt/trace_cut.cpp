// Diagnostico das cutscenes: registra quando o script (Lua) chama as funcoes de cutscene e com qual nome.
#include "x86rt.h"
#include "rt.h"
#include <stdio.h>
#include <string.h>

Fn rt_orig_func(uint32_t va);
void rt_override(uint32_t va, Fn fn);

struct CutFn { const char *name; uint32_t va; Fn orig; int n; };
static CutFn g_cut[] = {
    {"LoadCutscene", 0x5BB260}, {"LoadCutsceneSound", 0x5BB290}, {"StartCutscene", 0x5BB2B0}, {"StopCutscene", 0x5BB2C0},
    {"GetCutsceneRunning", 0x5BB2F0}, {"CutSetCutsceneName", 0x5BB360}, {"IsCutsceneLoaded", 0x5BB3A0},
    {"EnterNIS", 0x5BB520}, {"ExitNIS", 0x5BB560},
};
static int g_lines = 0;

// 1o argumento do Lua (5.1: L->base em +12; TValue de 16 bytes com tipo em +8; texto da TString em +16)
static void lua_arg_str(uint32_t L, char *out, size_t cap) {
    out[0] = 0;
    if (L < 0x10000u || L > 0xE0000000u) return;
    const uint32_t base = rd32(L + 12), top = rd32(L + 8);
    if (base < 0x10000u || base > 0xE0000000u || top <= base) { snprintf(out, cap, "(sem args)"); return; }
    const uint32_t tt = rd32(base + 8), v = rd32(base);
    if (tt == 4 && v > 0x10000u && v < 0xE0000000u) {
        size_t k = 0; for (; k + 1 < cap && k < 48; ++k) { const uint8_t ch = M[v + 16 + k]; if (ch < 32 || ch > 126) break; out[k] = (char)ch; }
        out[k] = 0;
    } else if (tt == 3) { double d; memcpy(&d, M + base, 8); snprintf(out, cap, "%g", d); }
    else snprintf(out, cap, "(tipo %u)", tt);
}
template <int I> static void cut_wrap(Cpu &c) {
    CutFn &f = g_cut[I];
    const uint32_t L = rd32(c.r[4] + 4);
    char a[64]; lua_arg_str(L, a, sizeof a);
    const bool loud = f.n < 3 || (strcmp(f.name, "IsCutsceneLoaded") && strcmp(f.name, "GetCutsceneRunning"));
    ++f.n;
    f.orig(c);
    if (loud && g_lines < 200) { ++g_lines; rt_log("[cutscene] %s(%s) -> eax=%u\n", f.name, a, c.r[0]); }
}
template <int I> static void reg_one() {
    if constexpr (I < (int)(sizeof g_cut / sizeof g_cut[0])) {
        g_cut[I].orig = rt_orig_func(g_cut[I].va);
        if (g_cut[I].orig) rt_override(g_cut[I].va, cut_wrap<I>);
        reg_one<I + 1>();
    }
}
void rt_trace_cut_init() { reg_one<0>(); rt_log("[cutscene] rastreio das funcoes de cutscene ligado\n"); }
