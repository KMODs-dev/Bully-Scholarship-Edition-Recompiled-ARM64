// Runtime minimo do codigo x86 recompilado (Bully PC). Memoria do jogo: janela de 4 GB a partir de M.
#pragma once
#include <stdint.h>
#include <string.h>
#include <math.h>
struct Cpu {
    uint32_t r[8];                       // eax ecx edx ebx esp ebp esi edi
    uint32_t fk, fmask, fres, fa, fb;    // flags preguicosas
    uint32_t fcin, fexpl_cf, fexpl_of, fexpl;
    int df; uint32_t eflags_hi;
    double st[8]; int top; uint16_t fcw, fsw;
};
extern uint8_t *M;
#define FSBASE 0xE0010000u
enum { K_ADD, K_SUB, K_ADC, K_SBB, K_LOGIC, K_INC, K_DEC, K_SHIFT, K_MUL, K_EXPL };
static inline uint8_t rd8(uint32_t a) { return M[a]; }
static inline uint16_t rd16(uint32_t a) { uint16_t v; memcpy(&v, M + a, 2); return v; }
static inline uint32_t rd32(uint32_t a) { uint32_t v; memcpy(&v, M + a, 4); return v; }
static inline uint64_t rd64(uint32_t a) { uint64_t v; memcpy(&v, M + a, 8); return v; }
static inline void wr8(uint32_t a, uint8_t v) { M[a] = v; }
static inline void wr16(uint32_t a, uint16_t v) { memcpy(M + a, &v, 2); }
static inline void wr32(uint32_t a, uint32_t v) { memcpy(M + a, &v, 4); }
static inline void wr64(uint32_t a, uint64_t v) { memcpy(M + a, &v, 8); }
static inline float rdf32(uint32_t a) { float v; memcpy(&v, M + a, 4); return v; }
static inline double rdf64(uint32_t a) { double v; memcpy(&v, M + a, 8); return v; }
static inline void wrf32(uint32_t a, float v) { memcpy(M + a, &v, 4); }
static inline void wrf64(uint32_t a, double v) { memcpy(M + a, &v, 8); }
double rdf80(uint32_t a);
void wrf80(uint32_t a, double v);
#define FL(k, m, r, a_, b_) do { c.fk = (k); c.fmask = (m); c.fres = (r); c.fa = (a_); c.fb = (b_); } while (0)
static inline uint32_t MSB(const Cpu &c) { return (c.fmask >> 1) + 1u; }
static inline uint32_t CF(const Cpu &c) {
    const uint32_t m = c.fmask, r = c.fres & m, a = c.fa & m, b = c.fb & m;
    switch (c.fk) {
    case K_ADD: return r < a;
    case K_ADC: return r < a || (c.fcin && r == a);
    case K_SUB: return a < b;
    case K_SBB: return a < b || (c.fcin && a == b);
    case K_LOGIC: return 0;
    case K_INC: case K_DEC: return c.fcin;
    default: return c.fexpl_cf;
    }
}
static inline uint32_t ZF(const Cpu &c) { return c.fk == K_EXPL ? (c.fexpl >> 6) & 1u : (c.fres & c.fmask) == 0; }
static inline uint32_t SF(const Cpu &c) { return c.fk == K_EXPL ? (c.fexpl >> 7) & 1u : (c.fres & MSB(c)) != 0; }
static inline uint32_t PF(const Cpu &c) { return c.fk == K_EXPL ? (c.fexpl >> 2) & 1u : !__builtin_parity(c.fres & 0xFFu); }
static inline uint32_t OF(const Cpu &c) {
    const uint32_t s = MSB(c), r = c.fres, a = c.fa, b = c.fb;
    switch (c.fk) {
    case K_ADD: case K_ADC: return (((a ^ r) & (b ^ r)) & s) != 0;
    case K_SUB: case K_SBB: return (((a ^ b) & (a ^ r)) & s) != 0;
    case K_LOGIC: return 0;
    case K_INC: return (r & c.fmask) == s;
    case K_DEC: return (a & c.fmask) == s;
    default: return c.fexpl_of;
    }
}
static inline void FLX(Cpu &c, uint32_t cfof) { c.fexpl_cf = c.fexpl_of = cfof ? 1u : 0u; c.fk = K_MUL; c.fmask = 0xFFFFFFFFu; }
#define COND_O(c) (OF(c))
#define COND_NO(c) (!OF(c))
#define COND_B(c) (CF(c))
#define COND_NB(c) (!CF(c))
#define COND_E(c) (ZF(c))
#define COND_NE(c) (!ZF(c))
#define COND_BE(c) (CF(c) || ZF(c))
#define COND_NBE(c) (!CF(c) && !ZF(c))
#define COND_S(c) (SF(c))
#define COND_NS(c) (!SF(c))
#define COND_P(c) (PF(c))
#define COND_NP(c) (!PF(c))
#define COND_L(c) (SF(c) != OF(c))
#define COND_NL(c) (SF(c) == OF(c))
#define COND_LE(c) (ZF(c) || SF(c) != OF(c))
#define COND_NLE(c) (!ZF(c) && SF(c) == OF(c))
static inline void SET_EXPL(Cpu &c, uint32_t cf, uint32_t pf, uint32_t zf, uint32_t sf, uint32_t of) {
    c.fexpl = (cf) | (pf << 2) | (zf << 6) | (sf << 7); c.fexpl_cf = cf; c.fexpl_of = of; c.fk = K_EXPL; c.fmask = 0xFFFFFFFFu;
}
static inline void SAHF(Cpu &c) { const uint32_t ah = (c.r[0] >> 8) & 0xFFu, of = OF(c); SET_EXPL(c, ah & 1u, (ah >> 2) & 1u, (ah >> 6) & 1u, (ah >> 7) & 1u, of); }
static inline uint32_t PUSHF(Cpu &c) { return CF(c) | (PF(c) << 2) | (ZF(c) << 6) | (SF(c) << 7) | (OF(c) << 11) | (c.df ? 0x400u : 0u) | 2u | 0x200u | (c.eflags_hi & 0x200000u); }
static inline void POPF(Cpu &c, uint32_t v) { SET_EXPL(c, v & 1u, (v >> 2) & 1u, (v >> 6) & 1u, (v >> 7) & 1u, (v >> 11) & 1u); c.df = (v >> 10) & 1; c.eflags_hi = v & 0x200000u; }
static inline void LAHF(Cpu &c) { const uint32_t ah = (SF(c) << 7) | (ZF(c) << 6) | (PF(c) << 2) | 2u | CF(c); c.r[0] = (c.r[0] & 0xFFFF00FFu) | (ah << 8); }
#define SHIFTS(B, M_) \
static inline uint32_t SHL##B(Cpu &c, uint32_t a, uint32_t n) { a &= M_; const uint32_t r = (a << n) & M_; c.fexpl_cf = (a >> (B - n)) & 1u; c.fexpl_of = ((r >> (B - 1)) & 1u) ^ c.fexpl_cf; c.fk = K_SHIFT; c.fmask = M_; c.fres = r; return r; } \
static inline uint32_t SHR##B(Cpu &c, uint32_t a, uint32_t n) { a &= M_; const uint32_t r = a >> n; c.fexpl_cf = (a >> (n - 1)) & 1u; c.fexpl_of = (a >> (B - 1)) & 1u; c.fk = K_SHIFT; c.fmask = M_; c.fres = r; return r; } \
static inline uint32_t SAR##B(Cpu &c, uint32_t a, uint32_t n) { const int32_t s = (int32_t)(a << (32 - B)) >> (32 - B); const uint32_t r = (uint32_t)(s >> (n > B - 1 ? B - 1 : n)) & M_; c.fexpl_cf = (uint32_t)(s >> (n - 1)) & 1u; c.fexpl_of = 0; c.fk = K_SHIFT; c.fmask = M_; c.fres = r; return r; } \
static inline uint32_t ROL##B(Cpu &c, uint32_t a, uint32_t n) { a &= M_; n %= B; const uint32_t r = n ? ((a << n) | (a >> (B - n))) & M_ : a; const uint32_t of = OF(c), zf = ZF(c), sf = SF(c), pf = PF(c); SET_EXPL(c, r & 1u, pf, zf, sf, of); return r; } \
static inline uint32_t ROR##B(Cpu &c, uint32_t a, uint32_t n) { a &= M_; n %= B; const uint32_t r = n ? ((a >> n) | (a << (B - n))) & M_ : a; const uint32_t of = OF(c), zf = ZF(c), sf = SF(c), pf = PF(c); SET_EXPL(c, (r >> (B - 1)) & 1u, pf, zf, sf, of); return r; }
SHIFTS(8, 0xFFu)
SHIFTS(16, 0xFFFFu)
SHIFTS(32, 0xFFFFFFFFu)
static inline uint32_t SHLD32(Cpu &c, uint32_t d, uint32_t s, uint32_t n) { const uint32_t r = (d << n) | (s >> (32 - n)); c.fexpl_cf = (d >> (32 - n)) & 1u; c.fexpl_of = 0; c.fk = K_SHIFT; c.fmask = 0xFFFFFFFFu; c.fres = r; return r; }
static inline uint32_t SHRD32(Cpu &c, uint32_t d, uint32_t s, uint32_t n) { const uint32_t r = (d >> n) | (s << (32 - n)); c.fexpl_cf = (d >> (n - 1)) & 1u; c.fexpl_of = 0; c.fk = K_SHIFT; c.fmask = 0xFFFFFFFFu; c.fres = r; return r; }
// x87
#define ST(i) c.st[(c.top + (i)) & 7]
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
#define FPOP() (c.top = (c.top + 1) & 7)
#define PUSH(v) do { const uint32_t v__ = (v); c.r[4] -= 4; wr32(c.r[4], v__); } while (0)
#define POP(dst) do { (dst) = rd32(c.r[4]); c.r[4] += 4; } while (0)
static inline uint16_t FSW(const Cpu &c) { return (uint16_t)((c.fsw & ~0x3800u) | ((c.top & 7u) << 11)); }
// controle de precisao do x87 (bits 8-9 do fcw): 00 = 24 bits (o D3D9 liga isso na thread do jogo), senao double
static inline double FPR(const Cpu &c, double v) { return (c.fcw & 0x300u) ? v : (double)(float)v; }
static inline void FCOM(Cpu &c, double a, double b) {
    uint16_t f = c.fsw & ~0x4500u;
    if (a != a || b != b) f |= 0x4500u; else if (a < b) f |= 0x100u; else if (a == b) f |= 0x4000u;
    c.fsw = f;
}
static inline void FCOMI(Cpu &c, double a, double b) {
    if (a != a || b != b) SET_EXPL(c, 1, 1, 1, 0, 0); else SET_EXPL(c, a < b, 0, a == b, 0, 0);
}
void FXAM(Cpu &c);
static inline double FRND(const Cpu &c, double v) {
    switch ((c.fcw >> 10) & 3) { case 0: return nearbyint(v); case 1: return floor(v); case 2: return ceil(v); default: return trunc(v); }
}
static inline int64_t FIST64(const Cpu &c, double v) { const double r = FRND(c, v); if (!(r >= -9223372036854775808.0 && r < 9223372036854775808.0)) return INT64_MIN; return (int64_t)r; }
static inline int32_t FIST32(const Cpu &c, double v) { const double r = FRND(c, v); if (!(r >= -2147483648.0 && r < 2147483648.0)) return INT32_MIN; return (int32_t)r; }
static inline int16_t FIST16(const Cpu &c, double v) { const double r = FRND(c, v); if (!(r >= -32768.0 && r < 32768.0)) return INT16_MIN; return (int16_t)r; }
static inline int64_t FIST_TRUNC64(const Cpu &, double v) { if (!(v >= -9223372036854775808.0 && v < 9223372036854775808.0)) return INT64_MIN; return (int64_t)v; }
static inline int32_t FIST_TRUNC32(const Cpu &, double v) { if (!(v >= -2147483648.0 && v < 2147483648.0)) return INT32_MIN; return (int32_t)v; }
static inline int16_t FIST_TRUNC16(const Cpu &, double v) { if (!(v >= -32768.0 && v < 32768.0)) return INT16_MIN; return (int16_t)v; }
// ligacao com o runtime
typedef void (*Fn)(Cpu &);
struct FuncEnt { uint32_t va; Fn fn; };
struct ImportEnt { int id; uint32_t iat; const char *name; };
void x86_unimpl(Cpu &c, uint32_t pc);
void x86_fell(Cpu &c, uint32_t pc);
void x86_jump(Cpu &c, uint32_t target);
void x86_call(Cpu &c, uint32_t target);
void x86_import(Cpu &c, int id);
void x86_int3(Cpu &c, uint32_t pc);
void x86_divzero(Cpu &c, uint32_t pc);
void x86_cpuid(Cpu &c);
void x86_rdtsc(Cpu &c);
#define STRDECL(op, B) void x86_str_##op##B(Cpu &c); void x86_str_##op##_rep##B(Cpu &c); void x86_str_##op##_repz##B(Cpu &c); void x86_str_##op##_repnz##B(Cpu &c);
STRDECL(movs, 8) STRDECL(movs, 16) STRDECL(movs, 32) STRDECL(stos, 8) STRDECL(stos, 16) STRDECL(stos, 32)
STRDECL(lods, 8) STRDECL(lods, 16) STRDECL(lods, 32) STRDECL(cmps, 8) STRDECL(cmps, 16) STRDECL(cmps, 32)
STRDECL(scas, 8) STRDECL(scas, 16) STRDECL(scas, 32)
#include "funcs.h"
