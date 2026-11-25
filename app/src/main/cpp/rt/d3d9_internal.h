// Objetos nativos por tras dos objetos COM do D3D9 (compartilhado entre d3d9.cpp e d3dx9.cpp).
#pragma once
#include <stdint.h>
#include <vector>
#include "gfx.h"
#include "rt.h"

// D3DRESOURCETYPE (1..7) + tipos internos
enum : uint32_t { RT_SURFACE = 1, RT_VOLUME = 2, RT_TEXTURE = 3, RT_VOLTEX = 4, RT_CUBE = 5, RT_VB = 6, RT_IB = 7,
                  RT_VDECL = 100, RT_VS, RT_PS, RT_SBLOCK, RT_QUERY, RT_SWAP, RT_DEVICE, RT_D3D, RT_XBUF, RT_XCTAB, RT_XEFFECT };

struct Res { virtual ~Res(); uint32_t type = 0; uint32_t obj = 0; };

struct Surface;
struct Tex : Res {
    uint32_t w = 0, h = 0, d = 1, levels = 1, fmt = 0, usage = 0, pool = 0;
    bool rt = false;
    uint32_t gfx = 0;                  // id no backend
    uint32_t mem = 0, mem_size = 0;    // copia na memoria do jogo (para LockRect), alocada no 1o Lock
    std::vector<uint32_t> lvl_off;     // [face*levels + level] -> deslocamento em mem
    std::vector<uint32_t> surf;        // objetos de superficie ja criados por nivel/face
};
struct Surface : Res {
    uint32_t w = 0, h = 0, fmt = 0, usage = 0, pool = 0;
    Tex *parent = nullptr; uint32_t face = 0, level = 0;
    uint32_t gfx = 0;                  // alvo no backend (0 = tela, para o backbuffer)
    uint32_t mem = 0;
};
struct Buf : Res { uint32_t size = 0, usage = 0, fmt = 0, pool = 0, gfx = 0, mem = 0, lk_off = 0, lk_size = 0; };
struct VDecl : Res { std::vector<uint8_t> elems; uint32_t gfx = 0; };
struct Shader : Res { std::vector<uint32_t> code; uint32_t gfx = 0; };
struct Query : Res { uint32_t qtype = 0; };

// estado completo do dispositivo; "g" e a parte que vai ao backend em cada desenho
struct DevState {
    GfxDrawState g;
    uint32_t tss[8][33];
    uint32_t tex[20];                  // objetos do jogo (16 de pixel + 4 de vertice)
    uint32_t stream[16], freq[16], ib, vdecl, vs, ps;
    uint32_t rt[4], ds;
    float vsc[256 * 4], psc[224 * 4];
    int32_t vsi[16 * 4], psi[16 * 4];
    uint32_t vsb[16], psb[16];
    float xf[512][16];                 // D3DTRANSFORMSTATETYPE
    uint8_t material[68], light[8][104]; bool light_on[8];
    float clip[6][4];
};
enum : uint32_t { SB_RS = 1, SB_SS, SB_TSS, SB_TEX, SB_STREAM, SB_IB, SB_VDECL, SB_VS, SB_PS, SB_VSF, SB_PSF, SB_VSI, SB_PSI, SB_VSB, SB_PSB,
                  SB_XF, SB_VP, SB_SC, SB_MAT, SB_LIGHT, SB_CLIP, SB_RT };
struct SBOp { uint32_t kind, i, j, n; };
struct SBlock : Res { bool full = false; std::vector<SBOp> ops; DevState snap; };

struct Device : Res {
    uint32_t hwnd = 0, create_flags = 0, bb_w = 0, bb_h = 0;
    uint8_t pp[56];
    uint32_t backbuf = 0, depth = 0, swap = 0;
    DevState st;
    uint64_t frames = 0, draws = 0;
};
extern Device *g_dev;
extern uint32_t g_screen_w, g_screen_h;

Res *res_of(uint32_t obj);
Tex *tex_create(uint32_t type, uint32_t w, uint32_t h, uint32_t d, uint32_t levels, uint32_t usage, uint32_t fmt, uint32_t pool);
uint32_t tex_level_addr(Tex *t, uint32_t face, uint32_t level);
void tex_upload_level(Tex *t, uint32_t face, uint32_t level);
bool fmt_is_dxt(uint32_t f);
uint32_t fmt_bpp(uint32_t f);
uint32_t fmt_pitch(uint32_t f, uint32_t w);
uint32_t fmt_rows(uint32_t f, uint32_t h);
uint32_t fmt_size(uint32_t f, uint32_t w, uint32_t h);
uint32_t shader_len(uint32_t p);
