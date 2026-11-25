#include "x86rt.h"
#ifdef __clang__
#define TAILCALL(x) [[clang::musttail]] return x
#else
#define TAILCALL(x) return x
#endif
#include <setjmp.h>
static inline uint16_t FSWT(const Cpu &c, int d) { return (uint16_t)((c.fsw & ~0x3800u) | ((((unsigned)c.top - (unsigned)d) & 7u) << 11)); }
void rt_jmp_register(uint32_t, jmp_buf *);
#define rd8(a) (Mloc[(uint32_t)(a)])
#define wr8(a, v) (Mloc[(uint32_t)(a)] = (uint8_t)(v))
static inline uint16_t g_rd16(const uint8_t *m, uint32_t a) { uint16_t v; memcpy(&v, m + a, 2); return v; }
static inline uint32_t g_rd32(const uint8_t *m, uint32_t a) { uint32_t v; memcpy(&v, m + a, 4); return v; }
static inline uint64_t g_rd64(const uint8_t *m, uint32_t a) { uint64_t v; memcpy(&v, m + a, 8); return v; }
static inline float g_rdf32(const uint8_t *m, uint32_t a) { float v; memcpy(&v, m + a, 4); return v; }
static inline double g_rdf64(const uint8_t *m, uint32_t a) { double v; memcpy(&v, m + a, 8); return v; }
static inline void g_wr16(uint8_t *m, uint32_t a, uint16_t v) { memcpy(m + a, &v, 2); }
static inline void g_wr32(uint8_t *m, uint32_t a, uint32_t v) { memcpy(m + a, &v, 4); }
static inline void g_wr64(uint8_t *m, uint32_t a, uint64_t v) { memcpy(m + a, &v, 8); }
static inline void g_wrf32(uint8_t *m, uint32_t a, float v) { memcpy(m + a, &v, 4); }
static inline void g_wrf64(uint8_t *m, uint32_t a, double v) { memcpy(m + a, &v, 8); }
#define rd16(a) g_rd16(Mloc, (a))
#define rd32(a) g_rd32(Mloc, (a))
#define rd64(a) g_rd64(Mloc, (a))
#define rdf32(a) g_rdf32(Mloc, (a))
#define rdf64(a) g_rdf64(Mloc, (a))
#define wr16(a, v) g_wr16(Mloc, (a), (v))
#define wr32(a, v) g_wr32(Mloc, (a), (v))
#define wr64(a, v) g_wr64(Mloc, (a), (v))
#define wrf32(a, v) g_wrf32(Mloc, (a), (v))
#define wrf64(a, v) g_wrf64(Mloc, (a), (v))
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F6F60(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F6F60:
  c.r[1] = (uint32_t)(0x1B65CD4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F6F70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F6F70:
  c.r[1] = (uint32_t)(0x1B65CD8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F6F80(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F6F80:
  c.r[1] = (uint32_t)(0x1B65CDCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F6F90(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F6F90:
  c.r[1] = (uint32_t)(0x1B65CE0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F6FA0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F6FA0:
  c.r[1] = (uint32_t)(0x1B65CE4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F6FB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F6FB0:
  c.r[1] = (uint32_t)(0x1B65CE8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F6FC0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F6FC0:
  c.r[1] = (uint32_t)(0x1B65CECu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F6FD0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F6FD0:
  c.r[1] = (uint32_t)(0x1B65CF0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F6FE0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F6FE0:
  c.r[1] = (uint32_t)(0x1B65CF4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F6FF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F6FF0:
  c.r[1] = (uint32_t)(0x1B65CF8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7000(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7000:
  c.r[1] = (uint32_t)(0x1B65CFCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7010(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7010:
  c.r[1] = (uint32_t)(0x1B65D00u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7020(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7020:
  c.r[1] = (uint32_t)(0x1B65D04u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7030(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7030:
  c.r[1] = (uint32_t)(0x1B65D08u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7040(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7040:
  c.r[1] = (uint32_t)(0x1B65D0Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7050(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7050:
  c.r[1] = (uint32_t)(0x1B65D10u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7060(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7060:
  c.r[1] = (uint32_t)(0x1B65D14u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7070(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7070:
  c.r[1] = (uint32_t)(0x1B65D18u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7080(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7080:
  c.r[1] = (uint32_t)(0x1B65D1Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7090(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7090:
  c.r[1] = (uint32_t)(0x1B65D20u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F70A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F70A0:
  c.r[1] = (uint32_t)(0x1B65D24u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F70B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F70B0:
  c.r[1] = (uint32_t)(0x1B65D28u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F70C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F70C0:
  c.r[1] = (uint32_t)(0x1B65D2Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F70D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F70D0:
  c.r[1] = (uint32_t)(0x1B65D30u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F70E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F70E0:
  c.r[1] = (uint32_t)(0x1B65D34u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F70F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F70F0:
  c.r[1] = (uint32_t)(0x1B65D38u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7100(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7100:
  c.r[1] = (uint32_t)(0x1B65D3Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7110(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7110:
  c.r[1] = (uint32_t)(0x1B65D40u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7120(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7120:
  c.r[1] = (uint32_t)(0x1B65D44u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7130(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7130:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1]; c.r[3] = cg.r[3]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.r[7] = cg.r[7]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F7140(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
  goto L_8F7140;
L_669A30:
  PUSH(c.r[3]);
  PUSH(c.r[6]);
  c.r[3] = (uint32_t)(c.r[1]);
  PUSH(c.r[7]);
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0x12574u));
  c.r[7] = (uint32_t)(0x95u);
L_669A40:
  c.r[6] -= 0x24u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669A4Au);
  ({ SO_ f_667790(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669A40;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0x1105Cu));
  c.r[7] = (uint32_t)(0x36u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669A60:
  c.r[6] -= 0x58u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669A6Au);
  ({ SO_ f_668A00(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669A60;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xFD74u));
  c.r[7] = (uint32_t)(0x9u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669A80:
  c.r[6] -= 0x28u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669A8Au);
  ({ SO_ f_66DC70(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669A80;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xFBE4u));
  c.r[7] = (uint32_t)(0x9u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669AA0:
  c.r[6] -= 0x38u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669AAAu);
  ({ SO_ f_66D290(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669AA0;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xF9B4u));
  c.r[7] = (uint32_t)(0x1Du);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669AC0:
  c.r[6] -= 0x1Cu;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669ACAu);
  ({ SO_ f_66A690(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669AC0;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xF66Cu));
  c.r[7] = (uint32_t)(0x13u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669AE0:
  c.r[6] -= 0x24u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669AEAu);
  ({ SO_ f_66DFF0(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669AE0;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xF39Cu));
  c.r[7] = (uint32_t)(0x13u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669B00:
  c.r[6] -= 0x28u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669B0Au);
  ({ SO_ f_667790(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669B00;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xF07Cu));
  c.r[7] = (uint32_t)(0x9u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669B20:
  c.r[6] -= 0x8u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669B2Au);
  ({ SO_ f_667790(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669B20;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xF02Cu));
  c.r[7] = (uint32_t)(0x13u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669B40:
  c.r[6] -= 0x24u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669B4Au);
  ({ SO_ f_66A690(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669B40;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xED5Cu));
  c.r[7] = (uint32_t)(0x1Du);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669B60:
  c.r[6] -= 0xF8u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669B6Du);
  ({ SO_ f_667790(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669B60;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xD04Cu));
  c.r[7] = (uint32_t)(0x1Du);
  c.r[1] = (uint32_t)((uint32_t)(c.r[1]));
L_669B80:
  c.r[6] -= 0x38u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669B8Au);
  ({ SO_ f_6726C0(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669B80;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xC9BCu));
  c.r[7] = (uint32_t)(0xC7u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669BA0:
  c.r[6] -= 0x14u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669BAAu);
  ({ SO_ f_667790(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669BA0;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xBA1Cu));
  c.r[7] = (uint32_t)(0x59u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669BC0:
  c.r[6] -= 0x10u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669BCAu);
  ({ SO_ f_671A90(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669BC0;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xB47Cu));
  c.r[7] = (uint32_t)(0x45u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669BE0:
  c.r[6] -= 0x10u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669BEAu);
  ({ SO_ f_671BC0(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669BE0;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xB01Cu));
  c.r[7] = (uint32_t)(0x63u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669C00:
  c.r[6] -= 0x10u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669C0Au);
  ({ SO_ f_6718F0(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669C00;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xA9DCu));
  c.r[7] = (uint32_t)(0x31u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669C20:
  c.r[6] -= 0x1Cu;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669C2Au);
  ({ SO_ f_671630(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669C20;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0xA464u));
  c.r[7] = (uint32_t)(0xBDu);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669C40:
  c.r[6] -= 0x1Cu;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669C4Au);
  ({ SO_ f_672390(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669C40;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0x8F9Cu));
  c.r[7] = (uint32_t)(0x8Bu);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669C60:
  c.r[6] -= 0x20u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669C6Au);
  ({ SO_ f_672190(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669C60;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0x7E1Cu));
  c.r[7] = (uint32_t)(0xF9u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669C80:
  c.r[6] -= 0x1Cu;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669C8Au);
  ({ SO_ f_671EA0(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669C80;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0x62C4u));
  c.r[7] = (uint32_t)(0x59u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669CA0:
  c.r[6] -= 0x14u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669CAAu);
  ({ SO_ f_66EA90(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669CA0;
  c.r[1] = (uint32_t)((uint32_t)(c.r[3] + 0x5BBCu));
  c.r[1] -= 0x4u;
  c.r[4] -= 4; wr32(c.r[4], 0x669CBDu);
  ({ SO_ f_6693F0(cg); SI_ });
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0x5BB8u));
  c.r[7] = (uint32_t)(0x59u);
  goto L_669CD0;
L_669CD0:
  c.r[6] -= 0x48u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669CDAu);
  ({ SO_ f_66F9D0(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669CD0;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0x4268u));
  c.r[7] = (uint32_t)(0xF9u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669CF0:
  c.r[6] -= 0x14u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669CFAu);
  ({ SO_ f_6713D0(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669CF0;
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0x2EE0u));
  c.r[7] = (uint32_t)(0x257u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_669D10:
  c.r[6] -= 0x14u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669D1Au);
  ({ SO_ f_667790(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669D10;
  POP(c.r[7]);
  POP(c.r[6]);
  POP(c.r[3]);
  c.r[4] += 4u; { SR_ return; }
L_8F7140:
  c.r[1] = (uint32_t)(0x1B65D50u);
  goto L_669A30;
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6];
#define SO_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6];
#define SR_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6];
#define SF_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6];
#define SIC_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
void f_8F7150(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
  goto L_8F7150;
L_667E70:
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[1]);
  c.r[1] = (uint32_t)((uint32_t)(c.r[6] + 0x20u));
  wr32((uint32_t)(c.r[6]), (uint32_t)(0x93D6D4u));
  c.r[4] -= 4; wr32(c.r[4], 0x667E81u);
  ({ SO_ f_49A650(cg); SI_ });
  c.r[1] = (uint32_t)((uint32_t)(c.r[6] + 0x1Cu));
  c.r[4] -= 4; wr32(c.r[4], 0x667E89u);
  ({ SO_ f_49A650(cg); SI_ });
  c.r[1] = (uint32_t)((uint32_t)(c.r[6] + 0x14u));
  c.r[4] -= 4; wr32(c.r[4], 0x667E91u);
  ({ SO_ f_49A650(cg); SI_ });
  c.r[1] = (uint32_t)((uint32_t)(c.r[6] + 0x10u));
  POP(c.r[6]);
  { SR_ TAILCALL(f_49A650(cg)); return; }
L_8F7150:
  c.r[1] = (uint32_t)(0x1B782C8u);
  goto L_667E70;
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
#define SO_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SR_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SF_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SIC_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
void f_8F7160(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
  goto L_8F7160;
L_66B560:
  wr32((uint32_t)(c.r[1]), (uint32_t)(0x93D738u));
  c.r[4] += 4u; { SR_ return; }
L_8F7160:
  c.r[1] = (uint32_t)(0x1B782ECu);
  goto L_66B560;
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7170(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7170:
  c.r[1] = (uint32_t)(0x1B78318u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.r[7] = cg.r[7]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F7180(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
  goto L_8F7180;
L_669D90:
  PUSH(c.r[6]);
  PUSH(c.r[7]);
  c.r[6] = (uint32_t)((uint32_t)(c.r[1] + 0x2A0u));
  c.r[7] = (uint32_t)(0x17u);
  c.r[1] = (uint32_t)((uint32_t)(c.r[1]));
L_669DA0:
  c.r[6] -= 0x4u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x669DAAu);
  ({ SO_ f_49A650(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_669DA0;
  POP(c.r[7]);
  POP(c.r[6]);
  c.r[4] += 4u; { SR_ return; }
L_8F7180:
  c.r[1] = (uint32_t)(0x1B78408u);
  goto L_669D90;
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7190(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7190:
  c.r[1] = (uint32_t)(0x1B786A8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
#define SO_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SR_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SF_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SIC_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
void f_8F71A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
  goto L_8F71A0;
L_667990:
  wr32((uint32_t)(c.r[1]), (uint32_t)(0x93D6C4u));
  c.r[4] += 4u; { SR_ return; }
L_8F71A0:
  c.r[1] = (uint32_t)(0x1B82AC0u);
  goto L_667990;
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F71B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F71B0:
  c.r[1] = (uint32_t)(0x1B83278u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
#define SO_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SR_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SF_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SIC_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
void f_8F71C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
  goto L_8F71C0;
L_667BE0:
  wr32((uint32_t)(c.r[1]), (uint32_t)(0x93D6CCu));
  c.r[4] += 4u; { SR_ return; }
L_8F71C0:
  c.r[1] = (uint32_t)(0x1B782FCu);
  goto L_667BE0;
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F71D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F71D0:
  wr32((uint32_t)(0xB6F1D0u), (uint32_t)(0x93D718u));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F71E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F71E0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F71F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F71F0:
  c.r[1] = (uint32_t)(0x1B890CCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7200(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7200:
  c.r[1] = (uint32_t)(0x1B890D0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7210(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7210:
  c.r[1] = (uint32_t)(0x1B890D4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7220(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7220:
  c.r[1] = (uint32_t)(0x1B890D8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7230(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7230:
  c.r[1] = (uint32_t)(0x1B890DCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7240(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7240:
  c.r[1] = (uint32_t)(0x1B890E0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7250(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7250:
  c.r[1] = (uint32_t)(0x1B890E4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7260(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7260:
  c.r[1] = (uint32_t)(0x1B890E8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7270(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7270:
  c.r[1] = (uint32_t)(0x1B890ECu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7280(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7280:
  c.r[1] = (uint32_t)(0x1B890F0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7290(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7290:
  c.r[1] = (uint32_t)(0x1B890F4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F72A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F72A0:
  c.r[1] = (uint32_t)(0x1B890F8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F72B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F72B0:
  c.r[1] = (uint32_t)(0x1B890FCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F72C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F72C0:
  c.r[1] = (uint32_t)(0x1B89100u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F72D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F72D0:
  c.r[1] = (uint32_t)(0x1B89104u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F72E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F72E0:
  c.r[1] = (uint32_t)(0x1B89108u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F72F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F72F0:
  c.r[1] = (uint32_t)(0x1B8910Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7300(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7300:
  c.r[1] = (uint32_t)(0x1B89110u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7310(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7310:
  c.r[1] = (uint32_t)(0x1B89114u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7320(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7320:
  c.r[1] = (uint32_t)(0x1B89118u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7330(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7330:
  c.r[1] = (uint32_t)(0x1B8911Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7340(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7340:
  c.r[1] = (uint32_t)(0x1B89120u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7350(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7350:
  c.r[1] = (uint32_t)(0x1B89124u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7360(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7360:
  c.r[1] = (uint32_t)(0x1B89128u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7370(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7370:
  c.r[1] = (uint32_t)(0x1B8912Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7380(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7380:
  c.r[1] = (uint32_t)(0x1B89130u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7390(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7390:
  c.r[1] = (uint32_t)(0x1B89134u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F73A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F73A0:
  c.r[1] = (uint32_t)(0x1B89138u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F73B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F73B0:
  c.r[1] = (uint32_t)(0x1B8913Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F73C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F73C0:
  c.r[1] = (uint32_t)(0x1B89140u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F73D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F73D0:
  c.r[1] = (uint32_t)(0x1B89144u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F73E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F73E0:
  c.r[1] = (uint32_t)(0x1B89148u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F73F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F73F0:
  c.r[1] = (uint32_t)(0x1B8914Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7400(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7400:
  c.r[1] = (uint32_t)(0x1B89164u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7410(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7410:
  c.r[1] = (uint32_t)(0x1B89168u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7420(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7420:
  c.r[1] = (uint32_t)(0x1B89178u);
  { SR_ TAILCALL(f_5D9C50(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7430(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7430:
  c.r[1] = (uint32_t)(0x1B8917Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7440(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7440:
  c.r[1] = (uint32_t)(0x1B89180u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7450(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7450:
  c.r[1] = (uint32_t)(0x1B89184u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7460(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7460:
  c.r[1] = (uint32_t)(0x1B89188u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7470(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7470:
  c.r[1] = (uint32_t)(0x1B8918Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7480(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7480:
  c.r[1] = (uint32_t)(0x1B89190u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7490(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7490:
  c.r[1] = (uint32_t)(0x1B89194u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F74A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F74A0:
  c.r[1] = (uint32_t)(0x1B891E0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F74B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F74B0:
  c.r[1] = (uint32_t)(0x1B891E4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F74C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F74C0:
  c.r[1] = (uint32_t)(0x1B891E8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F74D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F74D0:
  c.r[1] = (uint32_t)(0x1B891ECu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F74E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F74E0:
  c.r[1] = (uint32_t)(0x1B891F0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F74F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F74F0:
  c.r[1] = (uint32_t)(0x1B891F4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7500(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7500:
  c.r[1] = (uint32_t)(0x1B891F8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7510(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7510:
  c.r[1] = (uint32_t)(0x1B891FCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7520(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7520:
  c.r[1] = (uint32_t)(0x1B89200u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7530(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7530:
  c.r[1] = (uint32_t)(0x1B89204u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7540(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7540:
  c.r[1] = (uint32_t)(0x1B89208u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7550(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7550:
  c.r[1] = (uint32_t)(0x1B8920Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7560(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7560:
  c.r[1] = (uint32_t)(0x1B89210u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7570(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7570:
  c.r[1] = (uint32_t)(0x1B89214u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7580(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7580:
  c.r[1] = (uint32_t)(0x1B89218u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7590(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7590:
  c.r[1] = (uint32_t)(0x1B8921Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F75A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F75A0:
  c.r[1] = (uint32_t)(0x1B89220u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F75B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F75B0:
  c.r[1] = (uint32_t)(0x1B89224u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F75C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F75C0:
  c.r[1] = (uint32_t)(0x1B89228u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F75D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F75D0:
  c.r[1] = (uint32_t)(0x1B8922Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F75E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F75E0:
  c.r[1] = (uint32_t)(0xB9DAB8u);
  { SR_ TAILCALL(f_684CF0(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F75F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F75F0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7600(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7600:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7610(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7610:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7620(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7620:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[3] = cg.r[3]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F7630(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7630:
  c.r[0] = (uint32_t)(0x208B9C0u);
  c.r[1] = (uint32_t)(0x7u);
  c.r[3] = (uint32_t)((uint32_t)(c.r[3]));
L_8F7640:
  c.r[0] -= 0x38u;
  { const uint32_t a_ = c.r[1], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[1] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  wr32((uint32_t)(c.r[0]), (uint32_t)(0x900CDCu));
  if (COND_NS(c)) goto L_8F7640;
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7650(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7650:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7660(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7660:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7670(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7670:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7680(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7680:
  c.r[1] = (uint32_t)(0x20C2FA4u);
  { SR_ TAILCALL(f_68FB40(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7690(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7690:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F76A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F76A0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F76B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F76B0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F76C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F76C0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F76D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F76D0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F76E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F76E0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F76F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F76F0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7700(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7700:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7710(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7710:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7720(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7720:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7730(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7730:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7740(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7740:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7750(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7750:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7760(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7760:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7770(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7770:
  wr32((uint32_t)(0x20C33F8u), (uint32_t)(0x941004u));
  c.r[1] = (uint32_t)(0x20C33F8u);
  { SR_ TAILCALL(f_69AB40(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7790(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7790:
  wr32((uint32_t)(0x20C3488u), (uint32_t)(0x93FCFCu));
  c.r[1] = (uint32_t)(0x20C3488u);
  { SR_ TAILCALL(f_69B8E0(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F77B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F77B0:
  wr32((uint32_t)(0x20C3508u), (uint32_t)(0x93FCFCu));
  c.r[1] = (uint32_t)(0x20C3508u);
  { SR_ TAILCALL(f_69B8E0(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F77D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F77D0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F77E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F77E0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F77F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F77F0:
  c.r[1] = (uint32_t)(0x20C359Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7800(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7800:
  c.r[1] = (uint32_t)(0x20C35A0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7810(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7810:
  c.r[1] = (uint32_t)(0x20C3590u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7820(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7820:
  c.r[1] = (uint32_t)(0x20C3594u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7830(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7830:
  c.r[1] = (uint32_t)(0x20C35A4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7840(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7840:
  c.r[1] = (uint32_t)(0x20C35A8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7850(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7850:
  c.r[1] = (uint32_t)(0x20C35ACu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7860(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7860:
  c.r[1] = (uint32_t)(0x20C35B0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7870(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7870:
  c.r[1] = (uint32_t)(0x20C35B4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7880(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7880:
  c.r[1] = (uint32_t)(0x20C35B8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7890(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7890:
  c.r[1] = (uint32_t)(0x20C35BCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F78A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F78A0:
  c.r[1] = (uint32_t)(0x20C35C0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F78B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F78B0:
  c.r[1] = (uint32_t)(0x20C35C4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F78C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F78C0:
  c.r[1] = (uint32_t)(0x20C35C8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F78D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F78D0:
  c.r[1] = (uint32_t)(0x20C35CCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F78E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F78E0:
  c.r[1] = (uint32_t)(0x20C35D0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F78F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F78F0:
  c.r[1] = (uint32_t)(0x20C35D4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7900(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7900:
  c.r[1] = (uint32_t)(0x20C35D8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7910(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7910:
  c.r[1] = (uint32_t)(0x20C35DCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7920(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7920:
  c.r[1] = (uint32_t)(0x20C35E0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7930(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7930:
  c.r[1] = (uint32_t)(0x20C35E4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7940(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7940:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7950(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7950:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7960(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7960:
  c.r[1] = (uint32_t)(0x20C3CA0u);
  { SR_ TAILCALL(f_6AB6F0(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7970(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7970:
  c.r[1] = (uint32_t)(0x20C4420u);
  { SR_ TAILCALL(f_6AE220(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7980(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7980:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7990(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7990:
  wr32((uint32_t)(0xBB6130u), (uint32_t)(0x92D0ACu));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F79A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F79A0:
  wr32((uint32_t)(0xBB615Cu), (uint32_t)(0x92D0ACu));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4];
#define SO_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4];
#define SR_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4];
#define SF_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4];
#define SIC_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4];
void f_8F79B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F79B0:
  c.r[0] = (uint32_t)(0x92D0ACu);
  wr32((uint32_t)(0x20C4A28u), (uint32_t)(c.r[0]));
  wr32((uint32_t)(0x20C49F8u), (uint32_t)(c.r[0]));
  wr32((uint32_t)(0x20C49C8u), (uint32_t)(c.r[0]));
  wr32((uint32_t)(0x20C4998u), (uint32_t)(c.r[0]));
  wr32((uint32_t)(0x20C496Cu), (uint32_t)(c.r[0]));
  wr32((uint32_t)(0x20C493Cu), (uint32_t)(c.r[0]));
  wr32((uint32_t)(0x20C4910u), (uint32_t)(c.r[0]));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F79E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F79E0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F79F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F79F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0xBB650Cu)));
  if (((uint32_t)((c.r[0]) & (c.r[0])) == 0)) goto L_8F7A07;
  PUSH(0xBB650Cu);
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F7A04u);
  ({ SO_ f_4657E0(cg); SI_ });
  c.r[4] += 0x8u;
L_8F7A07:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0xBB6508u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F7A1E;
  PUSH(0xBB6508u);
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F7A1Bu);
  ({ SO_ f_4657E0(cg); SI_ });
  { const uint32_t a_ = c.r[4], b_ = 0x8u;
    const uint32_t r_ = (uint32_t)(a_ + b_);
    c.r[4] = (uint32_t)(r_);
    FL(K_ADD, 0xFFFFFFFFu, r_, a_, b_); }
L_8F7A1E:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7A20(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7A20:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7A30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7A30:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F7A40(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
  goto L_8F7A40;
L_6D2150:
  wr32((uint32_t)(c.r[1]), (uint32_t)(0x943174u));
  { SR_ TAILCALL(f_6D1F50(cg)); return; }
L_8F7A40:
  c.r[1] = (uint32_t)(0x20C7BECu);
  goto L_6D2150;
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7A50(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7A50:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7A60(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7A60:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F7A70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7A70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0xBC5D08u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F7A82;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F7A7Fu);
  ({ SO_ f_5EEAB0(cg); SI_ });
  { const uint32_t a_ = c.r[4], b_ = 0x4u;
    const uint32_t r_ = (uint32_t)(a_ + b_);
    c.r[4] = (uint32_t)(r_);
    FL(K_ADD, 0xFFFFFFFFu, r_, a_, b_); }
L_8F7A82:
  wr32((uint32_t)(0xBC5D08u), (uint32_t)(0x0u));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F7A90(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7A90:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0xBC5D14u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F7AA2;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F7A9Fu);
  ({ SO_ f_5EEAB0(cg); SI_ });
  { const uint32_t a_ = c.r[4], b_ = 0x4u;
    const uint32_t r_ = (uint32_t)(a_ + b_);
    c.r[4] = (uint32_t)(r_);
    FL(K_ADD, 0xFFFFFFFFu, r_, a_, b_); }
L_8F7AA2:
  wr32((uint32_t)(0xBC5D14u), (uint32_t)(0x0u));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F7AB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7AB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0xBC5D20u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F7AC2;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F7ABFu);
  ({ SO_ f_5EEAB0(cg); SI_ });
  { const uint32_t a_ = c.r[4], b_ = 0x4u;
    const uint32_t r_ = (uint32_t)(a_ + b_);
    c.r[4] = (uint32_t)(r_);
    FL(K_ADD, 0xFFFFFFFFu, r_, a_, b_); }
L_8F7AC2:
  wr32((uint32_t)(0xBC5D20u), (uint32_t)(0x0u));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F7AD0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7AD0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0xBC5D2Cu)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F7AE2;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F7ADFu);
  ({ SO_ f_5EEAB0(cg); SI_ });
  { const uint32_t a_ = c.r[4], b_ = 0x4u;
    const uint32_t r_ = (uint32_t)(a_ + b_);
    c.r[4] = (uint32_t)(r_);
    FL(K_ADD, 0xFFFFFFFFu, r_, a_, b_); }
L_8F7AE2:
  wr32((uint32_t)(0xBC5D2Cu), (uint32_t)(0x0u));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F7AF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7AF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0xBC5D38u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F7B02;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F7AFFu);
  ({ SO_ f_5EEAB0(cg); SI_ });
  { const uint32_t a_ = c.r[4], b_ = 0x4u;
    const uint32_t r_ = (uint32_t)(a_ + b_);
    c.r[4] = (uint32_t)(r_);
    FL(K_ADD, 0xFFFFFFFFu, r_, a_, b_); }
L_8F7B02:
  wr32((uint32_t)(0xBC5D38u), (uint32_t)(0x0u));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7B10(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7B10:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7B20(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7B20:
  wr32((uint32_t)(0xBC5E7Cu), (uint32_t)(0x9437F8u));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7B30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7B30:
  wr32((uint32_t)(0x20C7E98u), (uint32_t)(0x943A44u));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7B40(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7B40:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7B50(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7B50:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7B60(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7B60:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7B70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7B70:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7B80(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7B80:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7B90(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7B90:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7BA0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7BA0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7BB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7BB0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7BC0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7BC0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7BD0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7BD0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7BE0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7BE0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7BF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7BF0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7C00(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7C00:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7C10(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7C10:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7C20(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7C20:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7C30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7C30:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7C40(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7C40:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7C50(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7C50:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7C60(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7C60:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7C70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7C70:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7C80(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7C80:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7C90(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7C90:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7CA0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7CA0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7CB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7CB0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7CC0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7CC0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7CD0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7CD0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7CE0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7CE0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7CF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7CF0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7D00(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7D00:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7D10(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7D10:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7D20(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7D20:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7D30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7D30:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7D40(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7D40:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7D50(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7D50:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7D60(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7D60:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7D70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7D70:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7D80(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7D80:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7D90(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7D90:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7DA0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7DA0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7DB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7DB0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7DC0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7DC0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7DD0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7DD0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7DE0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7DE0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7DF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7DF0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7E00(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7E00:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7E10(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7E10:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7E20(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7E20:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7E30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7E30:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7E40(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7E40:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7E50(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7E50:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7E60(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7E60:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7E70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7E70:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7E80(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7E80:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7E90(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7E90:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7EA0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7EA0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7EB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7EB0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7EC0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7EC0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7ED0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7ED0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7EE0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7EE0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7EF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7EF0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7F00(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7F00:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7F10(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7F10:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7F20(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7F20:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7F30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7F30:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7F40(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7F40:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7F50(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7F50:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7F60(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7F60:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7F70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7F70:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7F80(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7F80:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7F90(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7F90:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7FA0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7FA0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7FB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7FB0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7FC0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7FC0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7FD0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7FD0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7FE0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7FE0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F7FF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F7FF0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8000(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8000:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8010(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8010:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8020(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8020:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8030(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8030:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8040(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8040:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8050(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8050:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8060(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8060:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8070(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8070:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8080(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8080:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8090(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8090:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F80A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F80A0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F80B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F80B0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F80C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F80C0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F80D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F80D0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F80E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F80E0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F80F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F80F0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8100(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8100:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8110(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8110:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8120(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8120:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8130(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8130:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8140(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8140:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.r[7] = cg.r[7]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8150(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8150:
  PUSH(c.r[6]);
  PUSH(c.r[7]);
  c.r[6] = (uint32_t)(0x20C87F0u);
  c.r[7] = (uint32_t)(0x7u);
  c.r[4] = (uint32_t)((uint32_t)(c.r[4]));
L_8F8160:
  c.r[6] -= 0x8u;
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F816Au);
  ({ SO_ f_668EB0(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_8F8160;
  POP(c.r[7]);
  POP(c.r[6]);
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8180(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8180:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8190(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8190:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F81A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F81A0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F81B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F81B0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F81C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F81C0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F81D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F81D0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F81E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F81E0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F81F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F81F0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8200(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8200:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8210(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8210:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8220(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8220:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8230(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8230:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8240(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8240:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8250(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8250:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8260(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8260:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8270(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8270:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8280(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8280:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8290(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8290:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F82A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F82A0:
  c.r[1] = (uint32_t)(0x20C893Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F82B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F82B0:
  c.r[1] = (uint32_t)(0x20C8940u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F82C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F82C0:
  c.r[1] = (uint32_t)(0x20C8944u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F82D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F82D0:
  c.r[1] = (uint32_t)(0x20C8948u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F82E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F82E0:
  c.r[1] = (uint32_t)(0x20C894Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F82F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F82F0:
  c.r[1] = (uint32_t)(0x20C8950u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8300(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8300:
  c.r[1] = (uint32_t)(0x20C8954u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8310(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8310:
  c.r[1] = (uint32_t)(0x20C8958u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8320(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8320:
  c.r[1] = (uint32_t)(0x20C895Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8330(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8330:
  c.r[1] = (uint32_t)(0x20C8960u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8340(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8340:
  c.r[1] = (uint32_t)(0x20C8964u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8350(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8350:
  c.r[1] = (uint32_t)(0x20C8968u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8360(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8360:
  c.r[1] = (uint32_t)(0x20C896Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8370(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8370:
  c.r[1] = (uint32_t)(0x20C8970u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8380(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8380:
  c.r[1] = (uint32_t)(0x20C8974u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8390(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8390:
  c.r[1] = (uint32_t)(0x20C8978u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F83A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F83A0:
  c.r[1] = (uint32_t)(0x20C897Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F83B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F83B0:
  c.r[1] = (uint32_t)(0x20C8980u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F83C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F83C0:
  c.r[1] = (uint32_t)(0x20C8984u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F83D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F83D0:
  c.r[1] = (uint32_t)(0x20C8988u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F83E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F83E0:
  c.r[1] = (uint32_t)(0x20C898Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F83F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F83F0:
  c.r[1] = (uint32_t)(0x20C8990u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8400(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8400:
  c.r[1] = (uint32_t)(0x20C8994u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8410(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8410:
  c.r[1] = (uint32_t)(0x20C8998u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8420(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8420:
  c.r[1] = (uint32_t)(0x20C899Cu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8430(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8430:
  c.r[1] = (uint32_t)(0x20C89A0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8440(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8440:
  c.r[1] = (uint32_t)(0x20C89A4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8450(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8450:
  c.r[1] = (uint32_t)(0x20C89A8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8460(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8460:
  c.r[1] = (uint32_t)(0x20C89ACu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8470(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8470:
  c.r[1] = (uint32_t)(0x20C89B0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8480(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8480:
  c.r[1] = (uint32_t)(0x20C89B4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8490(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8490:
  c.r[1] = (uint32_t)(0x20C89B8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F84A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F84A0:
  c.r[1] = (uint32_t)(0x20C89BCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F84B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F84B0:
  c.r[1] = (uint32_t)(0x20C89C0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F84C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F84C0:
  c.r[1] = (uint32_t)(0x20C89C4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F84D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F84D0:
  c.r[1] = (uint32_t)(0x20C89C8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F84E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F84E0:
  c.r[1] = (uint32_t)(0x20C89CCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F84F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F84F0:
  c.r[1] = (uint32_t)(0x20C89D0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8500(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8500:
  c.r[1] = (uint32_t)(0x20C89D4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8510(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8510:
  c.r[1] = (uint32_t)(0x20C89D8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8520(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8520:
  c.r[1] = (uint32_t)(0x20C89DCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8530(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8530:
  c.r[1] = (uint32_t)(0x20C89E0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8540(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8540:
  c.r[1] = (uint32_t)(0x20C89E4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8550(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8550:
  c.r[1] = (uint32_t)(0x20C89E8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8560(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8560:
  c.r[1] = (uint32_t)(0x20C89ECu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8570(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8570:
  c.r[1] = (uint32_t)(0x20C89F0u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8580(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8580:
  c.r[1] = (uint32_t)(0x20C89F4u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F8590(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8590:
  c.r[1] = (uint32_t)(0x20C89F8u);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1];
#define SO_ cg.r[1] = c.r[1];
#define SR_ cg.r[1] = c.r[1];
#define SF_ cg.r[1] = c.r[1];
#define SIC_ c.r[1] = cg.r[1];
void f_8F85A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F85A0:
  c.r[1] = (uint32_t)(0x20C89FCu);
  { SR_ TAILCALL(f_49A650(cg)); return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1]; c.r[3] = cg.r[3]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.r[7] = cg.r[7]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F85B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
  goto L_8F85B0;
L_72C060:
  PUSH(c.r[3]);
  PUSH(c.r[6]);
  c.r[3] = (uint32_t)(c.r[1]);
  PUSH(c.r[7]);
  c.r[6] = (uint32_t)((uint32_t)(c.r[3] + 0x190u));
  c.r[7] = (uint32_t)(0x27u);
L_72C070:
  c.r[6] -= 0x4u;
  PUSH(0x0u);
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x72C07Cu);
  ({ SO_ f_5D7F10(cg); SI_ });
  { const uint32_t a_ = c.r[7], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[7] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_72C070;
  PUSH(0x0u);
  c.r[1] = (uint32_t)((uint32_t)(c.r[3] + 0xECu));
  c.r[4] -= 4; wr32(c.r[4], 0x72C08Eu);
  ({ SO_ f_59D110(cg); SI_ });
  PUSH(0x0u);
  c.r[1] = (uint32_t)((uint32_t)(c.r[3] + 0xE8u));
  c.r[4] -= 4; wr32(c.r[4], 0x72C09Bu);
  ({ SO_ f_5D7F10(cg); SI_ });
  POP(c.r[7]);
  POP(c.r[6]);
  POP(c.r[3]);
  c.r[4] += 4u; { SR_ return; }
L_8F85B0:
  c.r[1] = (uint32_t)(0x20C8A00u);
  goto L_72C060;
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F85C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F85C0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F85D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F85D0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F85E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F85E0:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F85F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F85F0:
  PUSH(0x20E21B8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F85FBu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[3] = cg.r[3]; c.r[4] = cg.r[4]; c.r[5] = cg.r[5]; c.r[6] = cg.r[6]; c.r[7] = cg.r[7]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8600(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8600:
  PUSH(c.r[3]);
  PUSH(c.r[5]);
  c.r[5] = (uint32_t)(rd32((uint32_t)(0x8FC170u)));
  PUSH(c.r[6]);
  PUSH(c.r[7]);
  c.r[7] = (uint32_t)(0x20E2200u);
  c.r[3] = (uint32_t)(0x9u);
L_8F8614:
  c.r[6] = (uint32_t)(rd32((uint32_t)(c.r[7] + 0xFFFFFFFCu)));
  c.r[7] -= 0x4u;
  if (((uint32_t)((c.r[6]) & (c.r[6])) == 0)) goto L_8F8631;
  c.r[0] = (uint32_t)((uint32_t)(c.r[6] + 0x4u));
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8624u);
  ({ SO_ x86_call(cg, c.r[5]); SI_ });
  if (!((uint32_t)((c.r[0]) & (c.r[0])) == 0)) goto L_8F8631;
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[2] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8631u);
  ({ SO_ x86_call(cg, c.r[0]); SI_ });
L_8F8631:
  { const uint32_t a_ = c.r[3], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[3] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_8F8614;
  POP(c.r[7]);
  POP(c.r[6]);
  POP(c.r[5]);
  POP(c.r[3]);
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[3] = cg.r[3]; c.r[4] = cg.r[4]; c.r[5] = cg.r[5]; c.r[6] = cg.r[6]; c.r[7] = cg.r[7]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8640(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8640:
  PUSH(c.r[3]);
  c.r[3] = (uint32_t)(rd32((uint32_t)(0x8FC170u)));
  PUSH(c.r[5]);
  PUSH(c.r[6]);
  PUSH(c.r[7]);
  c.r[7] = (uint32_t)(0x20E23FCu);
  c.r[5] = (uint32_t)(0x2u);
L_8F8654:
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[7] + 0xFFFFFFFCu)));
  c.r[7] -= 0x4u;
  if (((uint32_t)(c.r[0]) == (uint32_t)(rd32((uint32_t)(0x951028u))))) goto L_8F867E;
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F866Cu);
  ({ SO_ x86_call(cg, c.r[3]); SI_ });
  if (!((uint32_t)(c.r[0]) == (uint32_t)(0x1u))) goto L_8F867E;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(c.r[7]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F867Eu);
  ({ SO_ f_754550(cg); SI_ });
L_8F867E:
  { const uint32_t a_ = c.r[5], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[5] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_8F8654;
  POP(c.r[7]);
  POP(c.r[6]);
  POP(c.r[5]);
  POP(c.r[3]);
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8690(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8690:
  PUSH(0x20E2434u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F869Bu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F86A0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F86A0:
  PUSH(0x20E2414u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F86ABu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F86B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F86B0:
  PUSH(0x20E245Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F86BBu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F86C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F86C0:
  PUSH(0x20E248Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F86CBu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F86D0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F86D0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E25B0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8703;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F86ECu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8702;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E25B0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8702u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8702:
  POP(c.r[6]);
L_8F8703:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
void f_8F8710(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8710:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E25F4u)));
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F871Bu);
  ({ SO_ f_752380(cg); SI_ });
  POP(c.r[1]);
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8720(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8720:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E2810u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8753;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F873Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8752;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E2810u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8752u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8752:
  POP(c.r[6]);
L_8F8753:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8760(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8760:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E28F0u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8785;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8776u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8784;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F8784:
  POP(c.r[6]);
L_8F8785:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[3] = cg.r[3]; c.r[4] = cg.r[4]; c.r[5] = cg.r[5]; c.r[6] = cg.r[6]; c.r[7] = cg.r[7]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8790(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8790:
  PUSH(c.r[3]);
  c.r[3] = (uint32_t)(rd32((uint32_t)(0x8FC170u)));
  PUSH(c.r[5]);
  PUSH(c.r[6]);
  PUSH(c.r[7]);
  c.r[7] = (uint32_t)(0x20E291Cu);
  c.r[5] = (uint32_t)(0x9u);
L_8F87A4:
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[7] + 0xFFFFFFFCu)));
  c.r[7] -= 0x4u;
  if (((uint32_t)(c.r[0]) == (uint32_t)(rd32((uint32_t)(0x951028u))))) goto L_8F87CE;
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F87BCu);
  ({ SO_ x86_call(cg, c.r[3]); SI_ });
  if (!((uint32_t)(c.r[0]) == (uint32_t)(0x1u))) goto L_8F87CE;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(c.r[7]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F87CEu);
  ({ SO_ f_754550(cg); SI_ });
L_8F87CE:
  { const uint32_t a_ = c.r[5], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[5] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_8F87A4;
  POP(c.r[7]);
  POP(c.r[6]);
  POP(c.r[5]);
  POP(c.r[3]);
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[3] = cg.r[3]; c.r[4] = cg.r[4]; c.r[5] = cg.r[5]; c.r[6] = cg.r[6]; c.r[7] = cg.r[7]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F87E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F87E0:
  PUSH(c.r[3]);
  c.r[3] = (uint32_t)(rd32((uint32_t)(0x8FC170u)));
  PUSH(c.r[5]);
  PUSH(c.r[6]);
  PUSH(c.r[7]);
  c.r[7] = (uint32_t)(0x20E2ABCu);
  c.r[5] = (uint32_t)(0x3u);
L_8F87F4:
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[7] + 0xFFFFFFFCu)));
  c.r[7] -= 0x4u;
  if (((uint32_t)(c.r[0]) == (uint32_t)(rd32((uint32_t)(0x951028u))))) goto L_8F881E;
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F880Cu);
  ({ SO_ x86_call(cg, c.r[3]); SI_ });
  if (!((uint32_t)(c.r[0]) == (uint32_t)(0x1u))) goto L_8F881E;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(c.r[7]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F881Eu);
  ({ SO_ f_754550(cg); SI_ });
L_8F881E:
  { const uint32_t a_ = c.r[5], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[5] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_8F87F4;
  POP(c.r[7]);
  POP(c.r[6]);
  POP(c.r[5]);
  POP(c.r[3]);
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8830(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8830:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E2B24u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8855;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8846u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8854;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F8854:
  POP(c.r[6]);
L_8F8855:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8860(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8860:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E2B5Cu)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8885;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8876u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8884;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F8884:
  POP(c.r[6]);
L_8F8885:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8890(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8890:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E2D38u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F88B5;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F88A6u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F88B4;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F88B4:
  POP(c.r[6]);
L_8F88B5:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F88C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F88C0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E2DB8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F88F3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F88DCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F88F2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E2DB8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F88F2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F88F2:
  POP(c.r[6]);
L_8F88F3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8900(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8900:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E2DF0u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8925;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8916u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8924;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F8924:
  POP(c.r[6]);
L_8F8925:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8930(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8930:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E2F2Cu)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8955;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8946u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8954;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F8954:
  POP(c.r[6]);
L_8F8955:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8960(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8960:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E2F64u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8985;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8976u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8984;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F8984:
  POP(c.r[6]);
L_8F8985:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8990(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8990:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E2F9Cu)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F89B5;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F89A6u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F89B4;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F89B4:
  POP(c.r[6]);
L_8F89B5:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F89C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F89C0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E303Cu)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F89E5;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F89D6u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F89E4;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F89E4:
  POP(c.r[6]);
L_8F89E5:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F89F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F89F0:
  PUSH(0x20E30DCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F89FBu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[3] = cg.r[3]; c.r[4] = cg.r[4]; c.r[5] = cg.r[5]; c.r[6] = cg.r[6]; c.r[7] = cg.r[7]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[3] = c.r[3]; cg.r[4] = c.r[4]; cg.r[5] = c.r[5]; cg.r[6] = c.r[6]; cg.r[7] = c.r[7]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8A00(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8A00:
  PUSH(c.r[3]);
  c.r[3] = (uint32_t)(rd32((uint32_t)(0x8FC170u)));
  PUSH(c.r[5]);
  PUSH(c.r[6]);
  PUSH(c.r[7]);
  c.r[7] = (uint32_t)(0x20E3204u);
  c.r[5] = (uint32_t)(0xDu);
L_8F8A14:
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[7] + 0xFFFFFFFCu)));
  c.r[7] -= 0x4u;
  if (((uint32_t)(c.r[0]) == (uint32_t)(rd32((uint32_t)(0x951028u))))) goto L_8F8A3E;
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8A2Cu);
  ({ SO_ x86_call(cg, c.r[3]); SI_ });
  if (!((uint32_t)(c.r[0]) == (uint32_t)(0x1u))) goto L_8F8A3E;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(c.r[7]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8A3Eu);
  ({ SO_ f_754550(cg); SI_ });
L_8F8A3E:
  { const uint32_t a_ = c.r[5], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    c.r[5] = (uint32_t)(r_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NS(c)) goto L_8F8A14;
  POP(c.r[7]);
  POP(c.r[6]);
  POP(c.r[5]);
  POP(c.r[3]);
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8A50(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8A50:
  PUSH(0x20E32F0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8A5Bu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8A60(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8A60:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E35C4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8A93;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8A7Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8A92;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E35C4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8A92u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8A92:
  POP(c.r[6]);
L_8F8A93:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8AA0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8AA0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E393Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8AD3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8ABCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8AD2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E393Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8AD2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8AD2:
  POP(c.r[6]);
L_8F8AD3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8AE0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8AE0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E394Cu)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8B05;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8AF6u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8B04;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F8B04:
  POP(c.r[6]);
L_8F8B05:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8B10(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8B10:
  PUSH(0x20E398Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8B1Bu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8B20(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8B20:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E3AF8u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8B45;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8B36u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8B44;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F8B44:
  POP(c.r[6]);
L_8F8B45:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8B50(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8B50:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E3C9Cu)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8B75;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8B66u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8B74;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F8B74:
  POP(c.r[6]);
L_8F8B75:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8B80(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8B80:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E3DD8u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8BA5;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8B96u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8BA4;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F8BA4:
  POP(c.r[6]);
L_8F8BA5:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8BB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8BB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E3EB0u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8BD5;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8BC6u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8BD4;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F8BD4:
  POP(c.r[6]);
L_8F8BD5:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8BE0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8BE0:
  PUSH(0x20E40CCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8BEBu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
void f_8F8BF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8BF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0xBC8B78u)));
  PUSH(c.r[0]);
  wr32((uint32_t)(0xBC8B74u), (uint32_t)(0x9893C0u));
  c.r[4] -= 4; wr32(c.r[4], 0x8F8C05u);
  ({ SO_ f_836F80(cg); SI_ });
  POP(c.r[1]);
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8C10(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8C10:
  PUSH(0x20E4224u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8C1Bu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8C20(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8C20:
  PUSH(0x20E4A88u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8C2Bu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8F8C30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8C30:
  PUSH(0x20E4AB0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8C3Bu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8C40(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8C40:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E4AD0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8C73;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8C5Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8C72;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E4AD0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8C72u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8C72:
  POP(c.r[6]);
L_8F8C73:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8C80(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8C80:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E4AD4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8CB3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8C9Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8CB2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E4AD4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8CB2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8CB2:
  POP(c.r[6]);
L_8F8CB3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8CC0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8CC0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E59C8u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8CE5;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8CD6u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8CE4;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8F8CE4:
  POP(c.r[6]);
L_8F8CE5:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8CF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8CF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5BF4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8D23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8D0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8D22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5BF4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8D22u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8D22:
  POP(c.r[6]);
L_8F8D23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8D30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8D30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5BF8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8D63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8D4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8D62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5BF8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8D62u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8D62:
  POP(c.r[6]);
L_8F8D63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8D70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8D70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5BFCu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8DA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8D8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8DA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5BFCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8DA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8DA2:
  POP(c.r[6]);
L_8F8DA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8DB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8DB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C00u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8DE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8DCCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8DE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C00u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8DE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8DE2:
  POP(c.r[6]);
L_8F8DE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8DF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8DF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C04u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8E23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8E0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8E22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C04u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8E22u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8E22:
  POP(c.r[6]);
L_8F8E23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8E30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8E30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C08u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8E63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8E4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8E62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C08u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8E62u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8E62:
  POP(c.r[6]);
L_8F8E63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8E70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8E70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C0Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8EA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8E8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8EA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C0Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8EA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8EA2:
  POP(c.r[6]);
L_8F8EA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8EB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8EB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C10u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8EE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8ECCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8EE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C10u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8EE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8EE2:
  POP(c.r[6]);
L_8F8EE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8EF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8EF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C14u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8F23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8F0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8F22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C14u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8F22u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8F22:
  POP(c.r[6]);
L_8F8F23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8F30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8F30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C18u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8F63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8F4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8F62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C18u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8F62u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8F62:
  POP(c.r[6]);
L_8F8F63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8F70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8F70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C1Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8FA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8F8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8FA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C1Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8FA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8FA2:
  POP(c.r[6]);
L_8F8FA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8FB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8FB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C20u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F8FE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8FCCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F8FE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C20u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F8FE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F8FE2:
  POP(c.r[6]);
L_8F8FE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F8FF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F8FF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C24u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9023;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F900Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9022;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C24u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9022u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9022:
  POP(c.r[6]);
L_8F9023:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9030(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9030:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C28u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9063;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F904Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9062;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C28u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9062u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9062:
  POP(c.r[6]);
L_8F9063:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9070(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9070:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C2Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F90A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F908Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F90A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C2Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F90A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F90A2:
  POP(c.r[6]);
L_8F90A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F90B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F90B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C30u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F90E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F90CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F90E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C30u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F90E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F90E2:
  POP(c.r[6]);
L_8F90E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F90F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F90F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C34u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9123;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F910Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9122;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C34u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9122u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9122:
  POP(c.r[6]);
L_8F9123:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9130(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9130:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C38u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9163;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F914Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9162;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C38u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9162u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9162:
  POP(c.r[6]);
L_8F9163:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9170(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9170:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C3Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F91A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F918Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F91A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C3Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F91A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F91A2:
  POP(c.r[6]);
L_8F91A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F91B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F91B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C40u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F91E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F91CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F91E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C40u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F91E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F91E2:
  POP(c.r[6]);
L_8F91E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F91F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F91F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C44u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9223;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F920Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9222;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C44u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9222u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9222:
  POP(c.r[6]);
L_8F9223:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9230(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9230:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C48u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9263;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F924Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9262;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C48u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9262u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9262:
  POP(c.r[6]);
L_8F9263:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9270(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9270:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C4Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F92A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F928Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F92A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C4Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F92A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F92A2:
  POP(c.r[6]);
L_8F92A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F92B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F92B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C50u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F92E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F92CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F92E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C50u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F92E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F92E2:
  POP(c.r[6]);
L_8F92E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F92F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F92F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C54u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9323;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F930Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9322;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C54u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9322u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9322:
  POP(c.r[6]);
L_8F9323:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9330(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9330:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C58u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9363;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F934Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9362;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C58u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9362u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9362:
  POP(c.r[6]);
L_8F9363:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9370(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9370:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C5Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F93A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F938Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F93A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C5Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F93A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F93A2:
  POP(c.r[6]);
L_8F93A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F93B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F93B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C60u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F93E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F93CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F93E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C60u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F93E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F93E2:
  POP(c.r[6]);
L_8F93E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F93F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F93F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C78u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9423;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F940Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9422;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C78u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9422u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9422:
  POP(c.r[6]);
L_8F9423:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9430(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9430:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C7Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9463;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F944Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9462;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C7Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9462u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9462:
  POP(c.r[6]);
L_8F9463:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9470(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9470:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C80u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F94A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F948Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F94A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C80u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F94A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F94A2:
  POP(c.r[6]);
L_8F94A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F94B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F94B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C84u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F94E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F94CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F94E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C84u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F94E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F94E2:
  POP(c.r[6]);
L_8F94E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F94F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F94F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C88u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9523;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F950Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9522;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C88u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9522u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9522:
  POP(c.r[6]);
L_8F9523:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9530(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9530:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C8Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9563;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F954Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9562;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C8Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9562u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9562:
  POP(c.r[6]);
L_8F9563:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9570(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9570:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C90u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F95A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F958Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F95A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C90u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F95A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F95A2:
  POP(c.r[6]);
L_8F95A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F95B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F95B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5C94u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F95E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F95CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F95E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5C94u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F95E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F95E2:
  POP(c.r[6]);
L_8F95E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F95F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F95F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CACu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9623;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F960Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9622;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CACu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9622u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9622:
  POP(c.r[6]);
L_8F9623:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9630(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9630:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CB0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9663;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F964Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9662;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CB0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9662u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9662:
  POP(c.r[6]);
L_8F9663:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9670(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9670:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CB4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F96A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F968Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F96A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CB4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F96A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F96A2:
  POP(c.r[6]);
L_8F96A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F96B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F96B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CB8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F96E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F96CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F96E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CB8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F96E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F96E2:
  POP(c.r[6]);
L_8F96E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F96F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F96F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CBCu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9723;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F970Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9722;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CBCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9722u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9722:
  POP(c.r[6]);
L_8F9723:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9730(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9730:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CC0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9763;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F974Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9762;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CC0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9762u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9762:
  POP(c.r[6]);
L_8F9763:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9770(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9770:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CC4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F97A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F978Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F97A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CC4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F97A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F97A2:
  POP(c.r[6]);
L_8F97A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F97B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F97B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CC8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F97E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F97CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F97E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CC8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F97E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F97E2:
  POP(c.r[6]);
L_8F97E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F97F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F97F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CCCu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9823;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F980Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9822;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CCCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9822u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9822:
  POP(c.r[6]);
L_8F9823:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9830(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9830:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CD0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9863;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F984Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9862;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CD0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9862u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9862:
  POP(c.r[6]);
L_8F9863:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9870(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9870:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CD4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F98A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F988Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F98A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CD4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F98A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F98A2:
  POP(c.r[6]);
L_8F98A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F98B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F98B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CD8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F98E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F98CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F98E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CD8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F98E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F98E2:
  POP(c.r[6]);
L_8F98E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F98F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F98F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CDCu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9923;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F990Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9922;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CDCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9922u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9922:
  POP(c.r[6]);
L_8F9923:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9930(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9930:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CE0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9963;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F994Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9962;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CE0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9962u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9962:
  POP(c.r[6]);
L_8F9963:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9970(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9970:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CE4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F99A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F998Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F99A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CE4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F99A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F99A2:
  POP(c.r[6]);
L_8F99A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F99B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F99B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CE8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F99E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F99CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F99E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CE8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F99E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F99E2:
  POP(c.r[6]);
L_8F99E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F99F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F99F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CECu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9A23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9A0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9A22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CECu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9A22u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9A22:
  POP(c.r[6]);
L_8F9A23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9A30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9A30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CF0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9A63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9A4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9A62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CF0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9A62u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9A62:
  POP(c.r[6]);
L_8F9A63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9A70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9A70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CF4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9AA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9A8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9AA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CF4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9AA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9AA2:
  POP(c.r[6]);
L_8F9AA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9AB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9AB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CF8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9AE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9ACCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9AE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CF8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9AE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9AE2:
  POP(c.r[6]);
L_8F9AE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9AF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9AF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5CFCu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9B23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9B0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9B22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5CFCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9B22u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9B22:
  POP(c.r[6]);
L_8F9B23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9B30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9B30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D00u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9B63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9B4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9B62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D00u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9B62u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9B62:
  POP(c.r[6]);
L_8F9B63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9B70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9B70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D04u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9BA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9B8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9BA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D04u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9BA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9BA2:
  POP(c.r[6]);
L_8F9BA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9BB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9BB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D08u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9BE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9BCCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9BE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D08u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9BE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9BE2:
  POP(c.r[6]);
L_8F9BE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9BF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9BF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D0Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9C23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9C0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9C22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D0Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9C22u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9C22:
  POP(c.r[6]);
L_8F9C23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9C30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9C30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D10u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9C63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9C4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9C62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D10u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9C62u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9C62:
  POP(c.r[6]);
L_8F9C63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9C70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9C70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D14u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9CA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9C8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9CA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D14u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9CA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9CA2:
  POP(c.r[6]);
L_8F9CA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9CB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9CB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D18u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9CE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9CCCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9CE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D18u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9CE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9CE2:
  POP(c.r[6]);
L_8F9CE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9CF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9CF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D1Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9D23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9D0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9D22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D1Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9D22u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9D22:
  POP(c.r[6]);
L_8F9D23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9D30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9D30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D34u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9D63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9D4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9D62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D34u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9D62u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9D62:
  POP(c.r[6]);
L_8F9D63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9D70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9D70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D38u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9DA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9D8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9DA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D38u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9DA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9DA2:
  POP(c.r[6]);
L_8F9DA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9DB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9DB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D3Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9DE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9DCCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9DE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D3Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9DE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9DE2:
  POP(c.r[6]);
L_8F9DE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9DF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9DF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D40u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9E23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9E0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9E22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D40u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9E22u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9E22:
  POP(c.r[6]);
L_8F9E23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9E30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9E30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D44u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9E63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9E4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9E62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D44u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9E62u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9E62:
  POP(c.r[6]);
L_8F9E63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9E70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9E70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D48u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9EA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9E8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9EA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D48u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9EA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9EA2:
  POP(c.r[6]);
L_8F9EA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9EB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9EB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D4Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9EE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9ECCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9EE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D4Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9EE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9EE2:
  POP(c.r[6]);
L_8F9EE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9EF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9EF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D50u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9F23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9F0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9F22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D50u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9F22u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9F22:
  POP(c.r[6]);
L_8F9F23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9F30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9F30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D54u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9F63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9F4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9F62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D54u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9F62u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9F62:
  POP(c.r[6]);
L_8F9F63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9F70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9F70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D58u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9FA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9F8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9FA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D58u);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9FA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9FA2:
  POP(c.r[6]);
L_8F9FA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9FB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9FB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D5Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8F9FE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9FCCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8F9FE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D5Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8F9FE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8F9FE2:
  POP(c.r[6]);
L_8F9FE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8F9FF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8F9FF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D60u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA023;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA00Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA022;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D60u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA022u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA022:
  POP(c.r[6]);
L_8FA023:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA030(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA030:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D64u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA063;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA04Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA062;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D64u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA062u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA062:
  POP(c.r[6]);
L_8FA063:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA070(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA070:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D7Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA0A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA08Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA0A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D7Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA0A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA0A2:
  POP(c.r[6]);
L_8FA0A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA0B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA0B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D80u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA0E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA0CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA0E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D80u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA0E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA0E2:
  POP(c.r[6]);
L_8FA0E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA0F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA0F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D84u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA123;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA10Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA122;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D84u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA122u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA122:
  POP(c.r[6]);
L_8FA123:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA130(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA130:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D88u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA163;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA14Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA162;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D88u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA162u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA162:
  POP(c.r[6]);
L_8FA163:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA170(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA170:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D8Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA1A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA18Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA1A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D8Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA1A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA1A2:
  POP(c.r[6]);
L_8FA1A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA1B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA1B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D90u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA1E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA1CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA1E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D90u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA1E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA1E2:
  POP(c.r[6]);
L_8FA1E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA1F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA1F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D94u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA223;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA20Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA222;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D94u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA222u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA222:
  POP(c.r[6]);
L_8FA223:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA230(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA230:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D98u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA263;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA24Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA262;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D98u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA262u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA262:
  POP(c.r[6]);
L_8FA263:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA270(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA270:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5D9Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA2A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA28Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA2A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5D9Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA2A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA2A2:
  POP(c.r[6]);
L_8FA2A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA2B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA2B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DA0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA2E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA2CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA2E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DA0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA2E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA2E2:
  POP(c.r[6]);
L_8FA2E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA2F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA2F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DA4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA323;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA30Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA322;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DA4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA322u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA322:
  POP(c.r[6]);
L_8FA323:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA330(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA330:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DA8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA363;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA34Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA362;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DA8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA362u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA362:
  POP(c.r[6]);
L_8FA363:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA370(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA370:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DACu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA3A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA38Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA3A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DACu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA3A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA3A2:
  POP(c.r[6]);
L_8FA3A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA3B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA3B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DB0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA3E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA3CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA3E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DB0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA3E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA3E2:
  POP(c.r[6]);
L_8FA3E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA3F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA3F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DB4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA423;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA40Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA422;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DB4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA422u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA422:
  POP(c.r[6]);
L_8FA423:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA430(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA430:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DB8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA463;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA44Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA462;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DB8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA462u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA462:
  POP(c.r[6]);
L_8FA463:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA470(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA470:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DBCu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA4A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA48Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA4A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DBCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA4A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA4A2:
  POP(c.r[6]);
L_8FA4A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA4B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA4B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DC0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA4E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA4CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA4E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DC0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA4E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA4E2:
  POP(c.r[6]);
L_8FA4E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA4F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA4F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DC4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA523;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA50Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA522;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DC4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA522u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA522:
  POP(c.r[6]);
L_8FA523:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA530(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA530:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DC8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA563;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA54Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA562;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DC8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA562u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA562:
  POP(c.r[6]);
L_8FA563:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA570(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA570:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DCCu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA5A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA58Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA5A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DCCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA5A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA5A2:
  POP(c.r[6]);
L_8FA5A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA5B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA5B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DD0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA5E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA5CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA5E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DD0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA5E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA5E2:
  POP(c.r[6]);
L_8FA5E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA5F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA5F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DD4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA623;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA60Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA622;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DD4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA622u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA622:
  POP(c.r[6]);
L_8FA623:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA630(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA630:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DD8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA663;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA64Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA662;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DD8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA662u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA662:
  POP(c.r[6]);
L_8FA663:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA670(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA670:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DDCu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA6A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA68Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA6A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DDCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA6A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA6A2:
  POP(c.r[6]);
L_8FA6A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA6B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA6B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DE0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA6E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA6CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA6E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DE0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA6E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA6E2:
  POP(c.r[6]);
L_8FA6E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA6F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA6F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DE4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA723;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA70Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA722;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DE4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA722u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA722:
  POP(c.r[6]);
L_8FA723:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA730(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA730:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DE8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA763;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA74Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA762;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DE8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA762u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA762:
  POP(c.r[6]);
L_8FA763:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA770(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA770:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DECu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA7A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA78Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA7A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DECu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA7A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA7A2:
  POP(c.r[6]);
L_8FA7A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA7B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA7B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DF0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA7E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA7CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA7E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DF0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA7E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA7E2:
  POP(c.r[6]);
L_8FA7E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA7F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA7F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DF4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA823;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA80Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA822;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DF4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA822u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA822:
  POP(c.r[6]);
L_8FA823:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA830(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA830:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DF8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA863;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA84Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA862;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DF8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA862u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA862:
  POP(c.r[6]);
L_8FA863:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA870(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA870:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5DFCu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA8A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA88Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA8A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5DFCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA8A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA8A2:
  POP(c.r[6]);
L_8FA8A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA8B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA8B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E00u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA8E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA8CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA8E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E00u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA8E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA8E2:
  POP(c.r[6]);
L_8FA8E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA8F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA8F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E04u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA923;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA90Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA922;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E04u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA922u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA922:
  POP(c.r[6]);
L_8FA923:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA930(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA930:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E08u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA963;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA94Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA962;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E08u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA962u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA962:
  POP(c.r[6]);
L_8FA963:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA970(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA970:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E0Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA9A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA98Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA9A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E0Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA9A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA9A2:
  POP(c.r[6]);
L_8FA9A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA9B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA9B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E10u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FA9E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA9CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FA9E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E10u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FA9E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FA9E2:
  POP(c.r[6]);
L_8FA9E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FA9F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FA9F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E14u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAA23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAA0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAA22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E14u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAA22u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAA22:
  POP(c.r[6]);
L_8FAA23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAA30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAA30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E18u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAA63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAA4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAA62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E18u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAA62u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAA62:
  POP(c.r[6]);
L_8FAA63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAA70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAA70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E1Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAAA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAA8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAAA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E1Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAAA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAAA2:
  POP(c.r[6]);
L_8FAAA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAAB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAAB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E34u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAAE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAACCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAAE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E34u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAAE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAAE2:
  POP(c.r[6]);
L_8FAAE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAAF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAAF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E38u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAB23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAB0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAB22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E38u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAB22u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAB22:
  POP(c.r[6]);
L_8FAB23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAB30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAB30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E3Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAB63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAB4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAB62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E3Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAB62u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAB62:
  POP(c.r[6]);
L_8FAB63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAB70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAB70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E40u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FABA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAB8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FABA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E40u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FABA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FABA2:
  POP(c.r[6]);
L_8FABA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FABB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FABB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E44u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FABE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FABCCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FABE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E44u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FABE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FABE2:
  POP(c.r[6]);
L_8FABE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FABF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FABF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E48u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAC23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAC0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAC22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E48u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAC22u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAC22:
  POP(c.r[6]);
L_8FAC23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAC30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAC30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E4Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAC63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAC4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAC62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E4Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAC62u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAC62:
  POP(c.r[6]);
L_8FAC63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAC70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAC70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E50u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FACA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAC8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FACA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E50u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FACA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FACA2:
  POP(c.r[6]);
L_8FACA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FACB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FACB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E54u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FACE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FACCCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FACE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E54u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FACE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FACE2:
  POP(c.r[6]);
L_8FACE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FACF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FACF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E58u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAD23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAD0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAD22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E58u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAD22u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAD22:
  POP(c.r[6]);
L_8FAD23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAD30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAD30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E5Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAD63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAD4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAD62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E5Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAD62u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAD62:
  POP(c.r[6]);
L_8FAD63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAD70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAD70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E60u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FADA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAD8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FADA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E60u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FADA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FADA2:
  POP(c.r[6]);
L_8FADA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FADB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FADB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E64u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FADE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FADCCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FADE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E64u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FADE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FADE2:
  POP(c.r[6]);
L_8FADE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FADF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FADF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E68u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAE23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAE0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAE22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E68u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAE22u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAE22:
  POP(c.r[6]);
L_8FAE23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAE30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAE30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E6Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAE63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAE4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAE62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E6Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAE62u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAE62:
  POP(c.r[6]);
L_8FAE63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAE70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAE70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E70u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAEA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAE8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAEA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E70u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAEA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAEA2:
  POP(c.r[6]);
L_8FAEA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAEB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAEB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E74u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAEE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAECCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAEE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E74u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAEE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAEE2:
  POP(c.r[6]);
L_8FAEE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAEF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAEF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E78u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAF23;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAF0Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAF22;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E78u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAF22u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAF22:
  POP(c.r[6]);
L_8FAF23:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAF30(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAF30:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E7Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAF63;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAF4Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAF62;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E7Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAF62u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAF62:
  POP(c.r[6]);
L_8FAF63:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAF70(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAF70:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E80u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAFA3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAF8Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAFA2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E80u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAFA2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAFA2:
  POP(c.r[6]);
L_8FAFA3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAFB0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAFB0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E98u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FAFE3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAFCCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FAFE2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E98u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FAFE2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FAFE2:
  POP(c.r[6]);
L_8FAFE3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FAFF0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FAFF0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5E9Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB023;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB00Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB022;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5E9Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB022u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB022:
  POP(c.r[6]);
L_8FB023:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB030(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB030:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EA0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB063;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB04Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB062;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EA0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB062u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB062:
  POP(c.r[6]);
L_8FB063:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB070(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB070:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EA4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB0A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB08Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB0A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EA4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB0A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB0A2:
  POP(c.r[6]);
L_8FB0A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB0B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB0B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EA8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB0E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB0CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB0E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EA8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB0E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB0E2:
  POP(c.r[6]);
L_8FB0E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB0F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB0F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EACu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB123;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB10Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB122;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EACu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB122u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB122:
  POP(c.r[6]);
L_8FB123:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB130(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB130:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EB0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB163;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB14Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB162;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EB0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB162u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB162:
  POP(c.r[6]);
L_8FB163:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB170(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB170:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EB4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB1A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB18Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB1A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EB4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB1A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB1A2:
  POP(c.r[6]);
L_8FB1A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB1B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB1B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EB8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB1E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB1CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB1E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EB8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB1E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB1E2:
  POP(c.r[6]);
L_8FB1E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB1F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB1F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EBCu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB223;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB20Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB222;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EBCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB222u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB222:
  POP(c.r[6]);
L_8FB223:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB230(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB230:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EC0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB263;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB24Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB262;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EC0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB262u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB262:
  POP(c.r[6]);
L_8FB263:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB270(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB270:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EC4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB2A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB28Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB2A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EC4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB2A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB2A2:
  POP(c.r[6]);
L_8FB2A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB2B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB2B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EDCu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB2E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB2CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB2E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EDCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB2E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB2E2:
  POP(c.r[6]);
L_8FB2E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB2F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB2F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EE0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB323;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB30Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB322;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EE0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB322u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB322:
  POP(c.r[6]);
L_8FB323:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB330(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB330:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EE4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB363;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB34Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB362;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EE4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB362u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB362:
  POP(c.r[6]);
L_8FB363:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB370(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB370:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EE8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB3A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB38Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB3A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EE8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB3A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB3A2:
  POP(c.r[6]);
L_8FB3A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB3B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB3B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EECu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB3E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB3CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB3E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EECu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB3E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB3E2:
  POP(c.r[6]);
L_8FB3E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB3F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB3F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EF0u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB423;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB40Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB422;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EF0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB422u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB422:
  POP(c.r[6]);
L_8FB423:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB430(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB430:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EF4u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB463;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB44Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB462;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EF4u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB462u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB462:
  POP(c.r[6]);
L_8FB463:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB470(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB470:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EF8u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB4A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB48Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB4A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EF8u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB4A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB4A2:
  POP(c.r[6]);
L_8FB4A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB4B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB4B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5EFCu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB4E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB4CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB4E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5EFCu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB4E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB4E2:
  POP(c.r[6]);
L_8FB4E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB4F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB4F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F00u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB523;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB50Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB522;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F00u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB522u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB522:
  POP(c.r[6]);
L_8FB523:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB530(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB530:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F04u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB563;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB54Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB562;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F04u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB562u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB562:
  POP(c.r[6]);
L_8FB563:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB570(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB570:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F08u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB5A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB58Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB5A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F08u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB5A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB5A2:
  POP(c.r[6]);
L_8FB5A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB5B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB5B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F0Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB5E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB5CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB5E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F0Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB5E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB5E2:
  POP(c.r[6]);
L_8FB5E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB5F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB5F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F10u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB623;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB60Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB622;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F10u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB622u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB622:
  POP(c.r[6]);
L_8FB623:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB630(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB630:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F14u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB663;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB64Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB662;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F14u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB662u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB662:
  POP(c.r[6]);
L_8FB663:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB670(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB670:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F18u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB6A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB68Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB6A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F18u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB6A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB6A2:
  POP(c.r[6]);
L_8FB6A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB6B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB6B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F1Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB6E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB6CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB6E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F1Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB6E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB6E2:
  POP(c.r[6]);
L_8FB6E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB6F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB6F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F20u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB723;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB70Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB722;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F20u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB722u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB722:
  POP(c.r[6]);
L_8FB723:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB730(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB730:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F24u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB763;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB74Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB762;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F24u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB762u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB762:
  POP(c.r[6]);
L_8FB763:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB770(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB770:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F28u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB7A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB78Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB7A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F28u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB7A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB7A2:
  POP(c.r[6]);
L_8FB7A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB7B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB7B0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F2Cu)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB7E3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB7CCu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB7E2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F2Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB7E2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB7E2:
  POP(c.r[6]);
L_8FB7E3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB7F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB7F0:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E5F30u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB823;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB80Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB822;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E5F30u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB822u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB822:
  POP(c.r[6]);
L_8FB823:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8FB830(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB830:
  PUSH(0x20E6D4Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB83Bu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
#define SO_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SR_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SF_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SIC_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
void f_8FB840(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB840:
  c.r[1] = (uint32_t)(0xBCAE1Cu);
  wr32((uint32_t)(0xBCAE1Cu), (uint32_t)(0x952E10u));
  c.r[4] -= 4; wr32(c.r[4], 0x8FB854u);
  ({ SO_ f_75DB60(cg); SI_ });
  wr32((uint32_t)(0xBCAE1Cu), (uint32_t)(0x99C748u));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8FB860(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB860:
  PUSH(0x20E6D84u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB86Bu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB870(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB870:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E6E54u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB8A3;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB88Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB8A2;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E6E54u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB8A2u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB8A2:
  POP(c.r[6]);
L_8FB8A3:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8FB8B0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB8B0:
  PUSH(0x20E7210u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB8BBu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
#define SO_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SR_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SF_ cg.r[1] = c.r[1]; cg.r[4] = c.r[4];
#define SIC_ c.r[1] = cg.r[1]; c.r[4] = cg.r[4];
void f_8FB8C0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB8C0:
  c.r[1] = (uint32_t)(0xBCB930u);
  wr32((uint32_t)(0xBCB930u), (uint32_t)(0x952E10u));
  c.r[4] -= 4; wr32(c.r[4], 0x8FB8D4u);
  ({ SO_ f_75DB60(cg); SI_ });
  wr32((uint32_t)(0xBCB930u), (uint32_t)(0x99C748u));
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8FB8E0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB8E0:
  PUSH(0x20E7410u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB8EBu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8FB8F0(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB8F0:
  PUSH(0x20E75C0u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB8FBu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[4] = cg.r[4];
#define SO_ cg.r[4] = c.r[4];
#define SR_ cg.r[4] = c.r[4];
#define SF_ cg.r[4] = c.r[4];
#define SIC_ c.r[4] = cg.r[4];
void f_8FB900(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB900:
  PUSH(0x20E8F0Cu);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB90Bu);
  ({ SO_ x86_import(cg, 66); SI_ }); /* KERNEL32.dll!DeleteCriticalSection */
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB910(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB910:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E9260u)));
  { const uint32_t a_ = c.r[0], b_ = rd32((uint32_t)(0x951028u));
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB943;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(rd16((uint32_t)(c.r[0] + 0xFFFFFFFEu)));
  c.r[1] = (uint32_t)((uint32_t)(c.r[0] + 0xFFFFFFF8u));
  PUSH(c.r[1]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB92Cu);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = 0x1u;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB942;
  c.r[1] = (uint32_t)(rd32((uint32_t)(0x20E216Cu)));
  PUSH(c.r[6]);
  PUSH(0x20E9260u);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB942u);
  ({ SO_ f_754550(cg); SI_ });
L_8FB942:
  POP(c.r[6]);
L_8FB943:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.r[6] = cg.r[6]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[1] = c.r[1]; cg.r[2] = c.r[2]; cg.r[4] = c.r[4]; cg.r[6] = c.r[6]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[1] = cg.r[1]; c.r[2] = cg.r[2]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB950(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB950:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E9340u)));
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB975;
  PUSH(c.r[6]);
  c.r[6] = (uint32_t)(c.r[0]);
  c.r[0] += 0x4u;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB966u);
  ({ SO_ x86_import(cg, 4); SI_ }); /* KERNEL32.dll!InterlockedDecrement */
  { const uint32_t a_ = c.r[0], b_ = c.r[0];
    const uint32_t r_ = (uint32_t)(a_ & b_);
    FL(K_LOGIC, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_NE(c)) goto L_8FB974;
  c.r[0] = (uint32_t)(rd32((uint32_t)(c.r[6])));
  c.r[2] = (uint32_t)(rd32((uint32_t)(c.r[0] + 0x4u)));
  c.r[1] = (uint32_t)(c.r[6]);
  POP(c.r[6]);
  { SR_ x86_jump(cg, c.r[2]); return; }
L_8FB974:
  POP(c.r[6]);
L_8FB975:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
#undef ST
#define ST(i) cg.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)
#define SI_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
#define SO_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SR_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SF_ cg.r[0] = c.r[0]; cg.r[4] = c.r[4]; cg.fk = c.fk; cg.fmask = c.fmask; cg.fres = c.fres; cg.fa = c.fa; cg.fb = c.fb; cg.fcin = c.fcin; cg.fexpl_cf = c.fexpl_cf; cg.fexpl_of = c.fexpl_of; cg.fexpl = c.fexpl; cg.df = c.df; cg.eflags_hi = c.eflags_hi;
#define SIC_ c.r[0] = cg.r[0]; c.r[4] = cg.r[4]; c.fk = cg.fk; c.fmask = cg.fmask; c.fres = cg.fres; c.fa = cg.fa; c.fb = cg.fb; c.fcin = cg.fcin; c.fexpl_cf = cg.fexpl_cf; c.fexpl_of = cg.fexpl_of; c.fexpl = cg.fexpl; c.df = cg.df; c.eflags_hi = cg.eflags_hi;
void f_8FB980(Cpu &cg) {
  uint8_t *const Mloc = M;
  Cpu c; SI_
L_8FB980:
  c.r[0] = (uint32_t)(rd32((uint32_t)(0x20E93ACu)));
  { const uint32_t a_ = c.r[0], b_ = 0xFFFFFFFFu;
    const uint32_t r_ = (uint32_t)(a_ - b_);
    FL(K_SUB, 0xFFFFFFFFu, r_, a_, b_); }
  if (COND_E(c)) goto L_8FB991;
  PUSH(c.r[0]);
  c.r[4] -= 4; wr32(c.r[4], 0x8FB991u);
  ({ SO_ x86_import(cg, 133); SI_ }); /* KERNEL32.dll!TlsFree */
L_8FB991:
  c.r[4] += 4u; { SR_ return; }
#undef SI_
#undef SO_
#undef SR_
#undef SF_
#undef SIC_
#undef ST
#define ST(i) c.st[(c.top + (i)) & 7]
#undef FPUSH
#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)
}
