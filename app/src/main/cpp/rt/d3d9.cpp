// Camada Direct3D 9 do Bully: objetos COM falsos na memoria do jogo, todo o estado do D3D9 guardado aqui,
// recursos e desenhos repassados ao backend (gfx.h). Nada aqui sabe de OpenGL/Vulkan.
//
// COMO ESTENDER: cada metodo e uma funcao "static uint32_t Nome(Cpu &c, const uint32_t *a)"; a[0] = this,
// a[1..] = argumentos na ordem do d3d9.h. Metodos com fn = nullptr nas tabelas so registram no log e devolvem 0
// (S_OK). Floats chegam como bits em uint32 (use f32()).
#include "x86rt.h"
#include "d3d9_com.h"
#include "d3d9_internal.h"
#include "gfx.h"
#include <map>
#include <mutex>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>
#include <string.h>

#define F(name) static uint32_t name(Cpu &c, const uint32_t *a)
static inline float f32(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }
static inline uint32_t u32f(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }

// ---------------------------------------------------------------- formatos
#define FOURCC(a, b, c, d) ((uint32_t)(a) | ((uint32_t)(b) << 8) | ((uint32_t)(c) << 16) | ((uint32_t)(d) << 24))
enum : uint32_t {
    FMT_A8R8G8B8 = 21, FMT_X8R8G8B8 = 22, FMT_R5G6B5 = 23, FMT_X1R5G5B5 = 24, FMT_A1R5G5B5 = 25, FMT_A4R4G4B4 = 26,
    FMT_A8 = 28, FMT_A8B8G8R8 = 32, FMT_X8B8G8R8 = 33, FMT_G16R16 = 34, FMT_A2R10G10B10 = 35, FMT_A16B16G16R16 = 36,
    FMT_P8 = 41, FMT_L8 = 50, FMT_A8L8 = 51, FMT_V8U8 = 60, FMT_Q8W8V8U8 = 63, FMT_L16 = 81,
    FMT_D16_LOCKABLE = 70, FMT_D32 = 71, FMT_D15S1 = 73, FMT_D24S8 = 75, FMT_D24X8 = 77, FMT_D16 = 80, FMT_D32F_LOCKABLE = 82, FMT_D24FS8 = 83,
    FMT_INDEX16 = 101, FMT_INDEX32 = 102,
    FMT_R16F = 111, FMT_G16R16F = 112, FMT_A16B16G16R16F = 113, FMT_R32F = 114, FMT_G32R32F = 115, FMT_A32B32G32R32F = 116,
    FMT_DXT1 = FOURCC('D', 'X', 'T', '1'), FMT_DXT2 = FOURCC('D', 'X', 'T', '2'), FMT_DXT3 = FOURCC('D', 'X', 'T', '3'),
    FMT_DXT4 = FOURCC('D', 'X', 'T', '4'), FMT_DXT5 = FOURCC('D', 'X', 'T', '5'),
};
bool fmt_is_dxt(uint32_t f) { return f == FMT_DXT1 || f == FMT_DXT2 || f == FMT_DXT3 || f == FMT_DXT4 || f == FMT_DXT5; }
// bits por pixel (0 = desconhecido)
uint32_t fmt_bpp(uint32_t f) {
    switch (f) {
    case FMT_A8R8G8B8: case FMT_X8R8G8B8: case FMT_A8B8G8R8: case FMT_X8B8G8R8: case FMT_G16R16: case FMT_A2R10G10B10:
    case FMT_Q8W8V8U8: case FMT_D32: case FMT_D24S8: case FMT_D24X8: case FMT_D32F_LOCKABLE: case FMT_D24FS8: case FMT_G16R16F:
    case FMT_R32F: case FMT_INDEX32: return 32;
    case FMT_R5G6B5: case FMT_X1R5G5B5: case FMT_A1R5G5B5: case FMT_A4R4G4B4: case FMT_A8L8: case FMT_V8U8: case FMT_L16:
    case FMT_D16_LOCKABLE: case FMT_D15S1: case FMT_D16: case FMT_R16F: case FMT_INDEX16: return 16;
    case FMT_A8: case FMT_P8: case FMT_L8: return 8;
    case FMT_A16B16G16R16: case FMT_A16B16G16R16F: case FMT_G32R32F: return 64;
    case FMT_A32B32G32R32F: return 128;
    case FMT_DXT1: return 4;
    case FMT_DXT2: case FMT_DXT3: case FMT_DXT4: case FMT_DXT5: return 8;
    }
    return 0;
}
uint32_t fmt_pitch(uint32_t f, uint32_t w) {
    if (fmt_is_dxt(f)) return ((w + 3) / 4) * (f == FMT_DXT1 ? 8 : 16);
    return (w * fmt_bpp(f) + 7) / 8;
}
uint32_t fmt_rows(uint32_t f, uint32_t h) { return fmt_is_dxt(f) ? (h + 3) / 4 : h; }
uint32_t fmt_size(uint32_t f, uint32_t w, uint32_t h) { return fmt_pitch(f, w) * fmt_rows(f, h); }
static uint32_t mipdim(uint32_t v, uint32_t l) { v >>= l; return v ? v : 1; }
static uint32_t full_levels(uint32_t w, uint32_t h, uint32_t d = 1) { uint32_t m = w > h ? w : h; if (d > m) m = d; uint32_t n = 1; while (m > 1) { m >>= 1; ++n; } return n; }

// ---------------------------------------------------------------- objetos nativos
std::mutex g_d3d_mtx;

Res::~Res() {}
Device *g_dev = nullptr;
static uint32_t g_d3d_obj = 0;   // IDirect3D9 do jogo

// tamanhos das vtables (definidas mais abaixo)
extern uint32_t vt_surface(), vt_texture(), vt_cube(), vt_volume(), vt_voltex(), vt_vb(), vt_ib(), vt_vdecl(), vt_vs(), vt_ps(),
    vt_sblock(), vt_query(), vt_swap();

static uint32_t new_obj(uint32_t vt, Res *r) { r->obj = com_new(vt, r); return r->obj; }
Res *res_of(uint32_t obj) { return (Res *)com_host(obj); }

static void destroy(Res *r) {
    switch (r->type) {
    case RT_TEXTURE: case RT_CUBE: case RT_VOLTEX: {
        Tex *t = (Tex *)r;
        if (t->gfx) g_gfx->tex_destroy(t->gfx);
        for (uint32_t s : t->surf) if (s) { Surface *sf = (Surface *)res_of(s); if (sf) { sf->parent = nullptr; } }
        if (t->mem) rt_free(t->mem);
        break;
    }
    case RT_SURFACE: { Surface *s = (Surface *)r; if (!s->parent) { if (s->gfx) g_gfx->tex_destroy(s->gfx); if (s->mem) rt_free(s->mem); } break; }
    case RT_VB: case RT_IB: { Buf *b = (Buf *)r; if (b->gfx) g_gfx->buf_destroy(b->gfx); if (b->mem) rt_free(b->mem); break; }
    default: break;
    }
    delete r;
}

// metodos comuns IUnknown
F(Unk_QueryInterface) { com_addref(a[0]); if (a[2]) wr32(a[2], a[0]); return S_OK_; }
F(Unk_AddRef) { return com_addref(a[0]); }
F(Unk_Release) {
    const uint32_t n = com_release(a[0]);
    if (n == 0) {
        Res *r = res_of(a[0]);
        // superficies de textura vivem enquanto a textura viver
        if (r && r->type == RT_SURFACE && ((Surface *)r)->parent) { wr32(a[0] + 8, 1); return 0; }
        if (r) destroy(r);
    }
    return n;
}
F(Res_GetDevice) { if (a[1]) { com_addref(g_dev->obj); wr32(a[1], g_dev->obj); } return S_OK_; }
F(Res_GetType) { Res *r = res_of(a[0]); return r ? r->type : 0; }
F(Res_GetPriority) { return 0; }
F(Res_SetPriority) { return 0; }

// ---------------------------------------------------------------- texturas
// memoria do jogo: cada nivel (e face) tem um bloco proprio, guardado de forma continua em t->mem
static void tex_layout(Tex *t) {
    const uint32_t faces = t->type == RT_CUBE ? 6 : 1;
    uint32_t off = 0;
    t->lvl_off.clear();
    for (uint32_t f = 0; f < faces; ++f)
        for (uint32_t l = 0; l < t->levels; ++l) {
            t->lvl_off.push_back(off);
            off += fmt_size(t->fmt, mipdim(t->w, l), mipdim(t->h, l)) * mipdim(t->d, l);
        }
    t->mem_size = off;
}
uint32_t tex_level_addr(Tex *t, uint32_t face, uint32_t level) {
    if (!t->mem) t->mem = rt_alloc(t->mem_size ? t->mem_size : 16, true);
    return t->mem + t->lvl_off[face * t->levels + level];
}
void tex_upload_level(Tex *t, uint32_t face, uint32_t level) {
    if (t->rt) return;
    g_gfx->tex_upload(t->gfx, level, face, M + tex_level_addr(t, face, level), fmt_pitch(t->fmt, mipdim(t->w, level)));
}
Tex *tex_create(uint32_t type, uint32_t w, uint32_t h, uint32_t d, uint32_t levels, uint32_t usage, uint32_t fmt, uint32_t pool) {
    Tex *t = new Tex;
    t->type = type; t->w = w; t->h = h; t->d = d ? d : 1; t->fmt = fmt; t->usage = usage; t->pool = pool;
    t->rt = (usage & 3) != 0;   // D3DUSAGE_RENDERTARGET 1 | DEPTHSTENCIL 2
    const uint32_t full = full_levels(w, h, t->d);
    t->levels = (levels == 0 || levels > full) ? ((usage & 0x400) ? 1 : full) : levels;   // AUTOGENMIPMAP: 1 nivel visivel
    tex_layout(t);
    t->surf.assign(t->lvl_off.size(), 0);
    t->gfx = g_gfx->tex_create(type == RT_CUBE ? GfxTexType::Cube : type == RT_VOLTEX ? GfxTexType::Volume : GfxTexType::Tex2D,
                               w, h, t->d, t->levels, fmt, t->rt);
    const uint32_t vt = type == RT_CUBE ? vt_cube() : type == RT_VOLTEX ? vt_voltex() : vt_texture();
    new_obj(vt, t);
    return t;
}
static uint32_t tex_surface(Tex *t, uint32_t face, uint32_t level) {
    const uint32_t i = face * t->levels + level;
    if (i >= t->surf.size()) return 0;
    if (!t->surf[i]) {
        Surface *s = new Surface;
        s->type = RT_SURFACE; s->parent = t; s->face = face; s->level = level;
        s->w = mipdim(t->w, level); s->h = mipdim(t->h, level); s->fmt = t->fmt; s->usage = t->usage; s->pool = t->pool;
        s->gfx = t->gfx;
        t->surf[i] = new_obj(vt_surface(), s);
    } else com_addref(t->surf[i]);
    return t->surf[i];
}
static void put_level_desc(Tex *t, uint32_t level, uint32_t p) {
    wr32(p, t->fmt); wr32(p + 4, RT_SURFACE); wr32(p + 8, t->usage); wr32(p + 12, t->pool);
    wr32(p + 16, 0); wr32(p + 20, 0); wr32(p + 24, mipdim(t->w, level)); wr32(p + 28, mipdim(t->h, level));
}
F(Tex_GetLevelCount) { Tex *t = (Tex *)res_of(a[0]); return t ? t->levels : 1; }
F(Tex_GetLOD) { return 0; }
F(Tex_SetLOD) { return 0; }
F(Tex_SetAutoGenFilterType) { return S_OK_; }
F(Tex_GetAutoGenFilterType) { return 2; }
F(Tex_GenerateMipSubLevels) { return 0; }   // TODO backend: glGenerateMipmap
F(Tex_GetLevelDesc) { Tex *t = (Tex *)res_of(a[0]); if (!t || a[1] >= t->levels) return D3DERR_INVALIDCALL_; put_level_desc(t, a[1], a[2]); return S_OK_; }
F(Tex_GetSurfaceLevel) { Tex *t = (Tex *)res_of(a[0]); if (!t || a[1] >= t->levels) return D3DERR_INVALIDCALL_; wr32(a[2], tex_surface(t, 0, a[1])); return S_OK_; }
static uint32_t lock_rect(Tex *t, uint32_t face, uint32_t level, uint32_t locked, uint32_t rect) {
    if (!t || level >= t->levels) return D3DERR_INVALIDCALL_;
    uint32_t addr = tex_level_addr(t, face, level);
    const uint32_t pitch = fmt_pitch(t->fmt, mipdim(t->w, level));
    if (rect) {   // RECT {left, top, right, bottom}
        const uint32_t x = rd32(rect), y = rd32(rect + 4);
        addr += fmt_is_dxt(t->fmt) ? (y / 4) * pitch + (x / 4) * (t->fmt == FMT_DXT1 ? 8 : 16) : y * pitch + x * (fmt_bpp(t->fmt) / 8);
    }
    wr32(locked, pitch); wr32(locked + 4, addr);
    return S_OK_;
}
F(Tex_LockRect) { return lock_rect((Tex *)res_of(a[0]), 0, a[1], a[2], a[3]); }
F(Tex_UnlockRect) { Tex *t = (Tex *)res_of(a[0]); if (t && a[1] < t->levels) tex_upload_level(t, 0, a[1]); return S_OK_; }
F(Tex_AddDirtyRect) { return S_OK_; }
F(Cube_GetCubeMapSurface) { Tex *t = (Tex *)res_of(a[0]); if (!t || a[1] > 5 || a[2] >= t->levels) return D3DERR_INVALIDCALL_; wr32(a[3], tex_surface(t, a[1], a[2])); return S_OK_; }
F(Cube_LockRect) { return lock_rect((Tex *)res_of(a[0]), a[1], a[2], a[3], a[4]); }
F(Cube_UnlockRect) { Tex *t = (Tex *)res_of(a[0]); if (t && a[1] < 6 && a[2] < t->levels) tex_upload_level(t, a[1], a[2]); return S_OK_; }
F(Vol_GetLevelDesc) {
    Tex *t = (Tex *)res_of(a[0]); if (!t || a[1] >= t->levels) return D3DERR_INVALIDCALL_;
    const uint32_t p = a[2];
    wr32(p, t->fmt); wr32(p + 4, RT_VOLUME); wr32(p + 8, t->usage); wr32(p + 12, t->pool);
    wr32(p + 16, mipdim(t->w, a[1])); wr32(p + 20, mipdim(t->h, a[1])); wr32(p + 24, mipdim(t->d, a[1]));
    return S_OK_;
}
F(Vol_LockBox) {
    Tex *t = (Tex *)res_of(a[0]); if (!t || a[1] >= t->levels) return D3DERR_INVALIDCALL_;
    const uint32_t pitch = fmt_pitch(t->fmt, mipdim(t->w, a[1]));
    wr32(a[2], pitch); wr32(a[2] + 4, pitch * fmt_rows(t->fmt, mipdim(t->h, a[1]))); wr32(a[2] + 8, tex_level_addr(t, 0, a[1]));
    return S_OK_;   // TODO: pBox parcial (a[3])
}
F(Vol_UnlockBox) { Tex *t = (Tex *)res_of(a[0]); if (t && a[1] < t->levels) tex_upload_level(t, 0, a[1]); return S_OK_; }

// ---------------------------------------------------------------- superficies
Surface *surf_create(uint32_t w, uint32_t h, uint32_t fmt, uint32_t usage, uint32_t pool) {
    Surface *s = new Surface;
    s->type = RT_SURFACE; s->w = w; s->h = h; s->fmt = fmt; s->usage = usage; s->pool = pool;
    if (usage & 3) s->gfx = g_gfx->tex_create(GfxTexType::Tex2D, w, h, 1, 1, fmt, true);
    new_obj(vt_surface(), s);
    return s;
}
F(Surf_GetContainer) {
    Surface *s = (Surface *)res_of(a[0]);
    if (!s) return D3DERR_INVALIDCALL_;
    const uint32_t o = s->parent ? s->parent->obj : g_dev->obj;
    com_addref(o); wr32(a[2], o); return S_OK_;
}
F(Surf_GetDesc) {
    Surface *s = (Surface *)res_of(a[0]); if (!s) return D3DERR_INVALIDCALL_;
    const uint32_t p = a[1];
    wr32(p, s->fmt); wr32(p + 4, RT_SURFACE); wr32(p + 8, s->usage); wr32(p + 12, s->pool);
    wr32(p + 16, 0); wr32(p + 20, 0); wr32(p + 24, s->w); wr32(p + 28, s->h);
    return S_OK_;
}
F(Surf_LockRect) {
    Surface *s = (Surface *)res_of(a[0]); if (!s) return D3DERR_INVALIDCALL_;
    if (s->parent) return lock_rect(s->parent, s->face, s->level, a[1], a[2]);
    if (!s->mem) s->mem = rt_alloc(fmt_size(s->fmt, s->w, s->h), true);   // TODO: ler de volta do backend se for alvo de desenho
    wr32(a[1], fmt_pitch(s->fmt, s->w)); wr32(a[1] + 4, s->mem);
    return S_OK_;
}
F(Surf_UnlockRect) { Surface *s = (Surface *)res_of(a[0]); if (s && s->parent) tex_upload_level(s->parent, s->face, s->level); return S_OK_; }
F(Surf_GetDC) { return D3DERR_INVALIDCALL_; }
F(Surf_ReleaseDC) { return S_OK_; }

// ---------------------------------------------------------------- buffers de vertices / indices
static Buf *buf_create(bool index, uint32_t len, uint32_t usage, uint32_t fmt_or_fvf, uint32_t pool) {
    Buf *b = new Buf;
    b->type = index ? RT_IB : RT_VB; b->size = len; b->usage = usage; b->fmt = fmt_or_fvf; b->pool = pool;
    b->mem = rt_alloc(len ? len : 4, true);
    b->gfx = g_gfx->buf_create(index ? GfxBufKind::Index : GfxBufKind::Vertex, len);
    new_obj(index ? vt_ib() : vt_vb(), b);
    return b;
}
F(Buf_Lock) {   // Lock(OffsetToLock, SizeToLock, ppbData, Flags)
    Buf *b = (Buf *)res_of(a[0]); if (!b) return D3DERR_INVALIDCALL_;
    const uint32_t off = a[1] < b->size ? a[1] : 0;
    const uint32_t sz = a[2] ? a[2] : b->size - off;
    b->lk_off = off; b->lk_size = (off + sz <= b->size) ? sz : b->size - off;
    wr32(a[3], b->mem + off);
    return S_OK_;
}
F(Buf_Unlock) { Buf *b = (Buf *)res_of(a[0]); if (b && b->lk_size) { g_gfx->buf_upload(b->gfx, b->lk_off, M + b->mem + b->lk_off, b->lk_size); b->lk_size = 0; } return S_OK_; }
F(Buf_GetDesc) {
    Buf *b = (Buf *)res_of(a[0]); if (!b) return D3DERR_INVALIDCALL_;
    const uint32_t p = a[1];
    if (b->type == RT_VB) { wr32(p, 100 /*D3DFMT_VERTEXDATA*/); wr32(p + 4, RT_VB); wr32(p + 8, b->usage); wr32(p + 12, b->pool); wr32(p + 16, b->size); wr32(p + 20, b->fmt); }
    else { wr32(p, b->fmt); wr32(p + 4, RT_IB); wr32(p + 8, b->usage); wr32(p + 12, b->pool); wr32(p + 16, b->size); }
    return S_OK_;
}

// ---------------------------------------------------------------- declaracoes, shaders, queries
F(VDecl_GetDeclaration) {
    VDecl *v = (VDecl *)res_of(a[0]); if (!v) return D3DERR_INVALIDCALL_;
    const uint32_t n = (uint32_t)(v->elems.size() / 8);
    if (a[1]) memcpy(M + a[1], v->elems.data(), v->elems.size());
    wr32(a[2], n);
    return S_OK_;
}
F(Shader_GetFunction) {
    Shader *s = (Shader *)res_of(a[0]); if (!s) return D3DERR_INVALIDCALL_;
    const uint32_t bytes = (uint32_t)s->code.size() * 4;
    if (a[1]) memcpy(M + a[1], s->code.data(), bytes);
    wr32(a[2], bytes);
    return S_OK_;
}
// tamanho do bytecode de shader D3D9 em dwords (ate o token de fim 0x0000FFFF)
uint32_t shader_len(uint32_t p) {
    const uint32_t ver = rd32(p);
    const bool sm2 = ((ver >> 8) & 0xFF) >= 2;
    uint32_t i = 1;
    for (;;) {
        const uint32_t t = rd32(p + 4 * i);
        if (t == 0x0000FFFFu) return i + 1;
        if ((t & 0xFFFF) == 0xFFFE) { i += 1 + ((t >> 16) & 0x7FFF); continue; }
        if (sm2 && !(t & 0x80000000u)) { i += 1 + ((t >> 24) & 0xF); continue; }
        ++i;
        if (i > 1u << 20) return i;
    }
}
F(Query_GetType) { Query *q = (Query *)res_of(a[0]); return q ? q->qtype : 0; }
F(Query_GetDataSize) {
    Query *q = (Query *)res_of(a[0]); if (!q) return 0;
    switch (q->qtype) { case 8: return 4; /*EVENT: BOOL*/ case 9: return 4; /*OCCLUSION: DWORD*/ case 10: case 11: return 8; default: return 4; }
}
F(Query_Issue) { return S_OK_; }
F(Query_GetData) {   // GetData(pData, dwSize, dwGetDataFlags): resultado imediato
    Query *q = (Query *)res_of(a[0]);
    if (a[1] && a[2] >= 4) { wr32(a[1], (q && q->qtype == 9) ? 1000u : 1u); if (a[2] >= 8) wr32(a[1] + 4, 0); }
    return S_OK_;
}

// ---------------------------------------------------------------- state blocks
F(SB_Capture);
F(SB_Apply);

// ---------------------------------------------------------------- vtables
#define M_(n, k, f) {#n, k, f}
#define UNK M_(QueryInterface, 2, Unk_QueryInterface), M_(AddRef, 0, Unk_AddRef), M_(Release, 0, Unk_Release)
#define RES UNK, M_(GetDevice, 1, Res_GetDevice), M_(SetPrivateData, 4, nullptr), M_(GetPrivateData, 3, nullptr), \
    M_(FreePrivateData, 1, nullptr), M_(SetPriority, 1, Res_SetPriority), M_(GetPriority, 0, Res_GetPriority), M_(PreLoad, 0, nullptr), M_(GetType, 0, Res_GetType)
#define BASETEX RES, M_(SetLOD, 1, Tex_SetLOD), M_(GetLOD, 0, Tex_GetLOD), M_(GetLevelCount, 0, Tex_GetLevelCount), \
    M_(SetAutoGenFilterType, 1, Tex_SetAutoGenFilterType), M_(GetAutoGenFilterType, 0, Tex_GetAutoGenFilterType), M_(GenerateMipSubLevels, 0, Tex_GenerateMipSubLevels)
#define VT(fn, iface, ...) uint32_t fn() { static uint32_t v = 0; if (!v) { static const ComMethod m[] = {__VA_ARGS__}; v = com_vtable(iface, m, (int)(sizeof m / sizeof m[0])); } return v; }

VT(vt_texture, "IDirect3DTexture9", BASETEX, M_(GetLevelDesc, 2, Tex_GetLevelDesc), M_(GetSurfaceLevel, 2, Tex_GetSurfaceLevel),
   M_(LockRect, 4, Tex_LockRect), M_(UnlockRect, 1, Tex_UnlockRect), M_(AddDirtyRect, 1, Tex_AddDirtyRect))
VT(vt_cube, "IDirect3DCubeTexture9", BASETEX, M_(GetLevelDesc, 2, Tex_GetLevelDesc), M_(GetCubeMapSurface, 3, Cube_GetCubeMapSurface),
   M_(LockRect, 5, Cube_LockRect), M_(UnlockRect, 2, Cube_UnlockRect), M_(AddDirtyRect, 2, Tex_AddDirtyRect))
VT(vt_voltex, "IDirect3DVolumeTexture9", BASETEX, M_(GetLevelDesc, 2, Vol_GetLevelDesc), M_(GetVolumeLevel, 2, nullptr),
   M_(LockBox, 4, Vol_LockBox), M_(UnlockBox, 1, Vol_UnlockBox), M_(AddDirtyBox, 1, Tex_AddDirtyRect))
VT(vt_surface, "IDirect3DSurface9", RES, M_(GetContainer, 2, Surf_GetContainer), M_(GetDesc, 1, Surf_GetDesc),
   M_(LockRect, 3, Surf_LockRect), M_(UnlockRect, 0, Surf_UnlockRect), M_(GetDC, 1, Surf_GetDC), M_(ReleaseDC, 1, Surf_ReleaseDC))
VT(vt_vb, "IDirect3DVertexBuffer9", RES, M_(Lock, 4, Buf_Lock), M_(Unlock, 0, Buf_Unlock), M_(GetDesc, 1, Buf_GetDesc))
VT(vt_ib, "IDirect3DIndexBuffer9", RES, M_(Lock, 4, Buf_Lock), M_(Unlock, 0, Buf_Unlock), M_(GetDesc, 1, Buf_GetDesc))
VT(vt_vdecl, "IDirect3DVertexDeclaration9", UNK, M_(GetDevice, 1, Res_GetDevice), M_(GetDeclaration, 2, VDecl_GetDeclaration))
VT(vt_vs, "IDirect3DVertexShader9", UNK, M_(GetDevice, 1, Res_GetDevice), M_(GetFunction, 2, Shader_GetFunction))
VT(vt_ps, "IDirect3DPixelShader9", UNK, M_(GetDevice, 1, Res_GetDevice), M_(GetFunction, 2, Shader_GetFunction))
VT(vt_sblock, "IDirect3DStateBlock9", UNK, M_(GetDevice, 1, Res_GetDevice), M_(Capture, 0, SB_Capture), M_(Apply, 0, SB_Apply))
VT(vt_query, "IDirect3DQuery9", UNK, M_(GetDevice, 1, Res_GetDevice), M_(GetType, 0, Query_GetType), M_(GetDataSize, 0, Query_GetDataSize),
   M_(Issue, 1, Query_Issue), M_(GetData, 3, Query_GetData))

// ================================================================ dispositivo
static void put_display_mode(uint32_t p) { wr32(p, g_dev ? g_dev->bb_w : 1280); wr32(p + 4, g_dev ? g_dev->bb_h : 720); wr32(p + 8, 60); wr32(p + 12, FMT_X8R8G8B8); }

static void fix_ptrs(DevState &s) { s.g.vsc = s.vsc; s.g.psc = s.psc; s.g.vsi = s.vsi; s.g.psi = s.psi; s.g.vsb = s.vsb; s.g.psb = s.psb; s.g.xf = &s.xf[0][0]; s.g.tss = &s.tss[0][0]; }
static void set_defaults(Device *d) {
    DevState &s = d->st;
    memset(&s, 0, sizeof s);
    uint32_t *rs = s.g.rs;
    rs[7] = 1;            // ZENABLE
    rs[8] = 3;            // FILLMODE solid
    rs[9] = 2;            // SHADEMODE gouraud
    rs[14] = 1;           // ZWRITEENABLE
    rs[19] = 2;           // SRCBLEND one
    rs[20] = 1;           // DESTBLEND zero
    rs[22] = 3;           // CULLMODE ccw
    rs[23] = 4;           // ZFUNC lessequal
    rs[25] = 8;           // ALPHAFUNC always
    rs[52] = 0; rs[53] = 1; rs[54] = 1; rs[55] = 1; rs[56] = 8;   // STENCIL enable/fail/zfail/pass/func always
    rs[58] = 0xFFFFFFFF; rs[59] = 0xFFFFFFFF;                       // STENCILMASK / WRITEMASK
    rs[60] = 0xFFFFFFFF;  // TEXTUREFACTOR
    rs[137] = 1;          // LIGHTING
    rs[168] = 0xF;        // COLORWRITEENABLE
    rs[171] = 1;          // BLENDOP add
    rs[190] = rs[191] = rs[192] = 0xF;   // COLORWRITEENABLE1..3
    rs[186] = 1; rs[187] = 1; rs[188] = 1; rs[189] = 8;   // CCW_STENCIL*
    rs[207] = 2; rs[208] = 1; rs[209] = 1;   // SRCBLENDALPHA one / DESTBLENDALPHA zero / BLENDOPALPHA add
    for (int i = 0; i < 16; ++i) {
        uint32_t *ss = s.g.ss[i];
        ss[1] = ss[2] = ss[3] = 1;   // ADDRESSU/V/W wrap
        ss[5] = ss[6] = 1;           // MAG/MIN point
        ss[10] = 1;                  // MAXANISOTROPY
    }
    for (int i = 0; i < 8; ++i) {
        uint32_t *t = s.tss[i];
        t[1] = i == 0 ? 4 : 1; t[2] = 2; t[3] = 1;   // COLOROP modulate/disable, COLORARG1 texture, ARG2 current
        t[4] = i == 0 ? 2 : 1; t[5] = 2; t[6] = 1;   // ALPHAOP
        t[11] = (uint32_t)i;                          // TEXCOORDINDEX
    }
    s.g.vp_w = (int)d->bb_w; s.g.vp_h = (int)d->bb_h; s.g.vp_maxz = 1.0f;
    s.g.sc_r = (int)d->bb_w; s.g.sc_b = (int)d->bb_h;
    for (int i = 0; i < 16; ++i) s.freq[i] = 1;
    for (int i = 0; i < 512; ++i) { float *m = s.xf[i]; memset(m, 0, 64); m[0] = m[5] = m[10] = m[15] = 1.0f; }
    fix_ptrs(s);
}

// referencias do jogo guardadas no estado (para os Get*)
static void bind_ref(uint32_t &slot, uint32_t obj) { slot = obj; }
static uint32_t get_ref(uint32_t obj) { if (obj) com_addref(obj); return obj; }
static uint32_t gfx_of_tex(uint32_t obj) { Res *r = res_of(obj); if (!r) return 0; if (r->type == RT_SURFACE) return ((Surface *)r)->gfx; return ((Tex *)r)->gfx; }
static uint32_t gfx_of_buf(uint32_t obj) { Buf *b = (Buf *)res_of(obj); return b ? b->gfx : 0; }

// gravacao de state blocks (BeginStateBlock/EndStateBlock): cada Set* chama rec()
static SBlock *g_rec = nullptr;
static inline void rec(uint32_t kind, uint32_t i, uint32_t j = 0, uint32_t n = 1) { if (g_rec) g_rec->ops.push_back({kind, i, j, n}); }

F(Dev_TestCooperativeLevel) { return S_OK_; }
F(Dev_GetAvailableTextureMem) { return 512u << 20; }
F(Dev_EvictManagedResources) { return S_OK_; }
F(Dev_GetDirect3D) { com_addref(g_d3d_obj); wr32(a[1], g_d3d_obj); return S_OK_; }
uint32_t fill_caps(uint32_t p);
F(Dev_GetDeviceCaps) { fill_caps(a[1]); return S_OK_; }
F(Dev_GetDisplayMode) { put_display_mode(a[2]); return S_OK_; }
F(Dev_GetCreationParameters) { wr32(a[1], 0); wr32(a[1] + 4, 1); wr32(a[1] + 8, g_dev->hwnd); wr32(a[1] + 12, g_dev->create_flags); return S_OK_; }
F(Dev_SetCursorProperties) { return S_OK_; }
F(Dev_SetCursorPosition) { return 0; }
F(Dev_ShowCursor) { return 0; }
F(Dev_GetSwapChain) { com_addref(g_dev->swap); wr32(a[2], g_dev->swap); return S_OK_; }
F(Dev_GetNumberOfSwapChains) { return 1; }
F(Dev_Reset) {
    // TODO: recriar backbuffer se o tamanho mudar; por enquanto so le os parametros
    const uint32_t pp = a[1];
    rt_log("[d3d9] Reset %ux%u\n", rd32(pp), rd32(pp + 4));
    if (rd32(pp) && rd32(pp + 4)) { g_dev->bb_w = rd32(pp); g_dev->bb_h = rd32(pp + 4); }
    wr32(pp, g_dev->bb_w); wr32(pp + 4, g_dev->bb_h);
    set_defaults(g_dev);
    g_dev->st.rt[0] = g_dev->backbuf; g_dev->st.ds = g_dev->depth;
    g_dev->st.g.rt[0] = 0; g_dev->st.g.ds = 0;
    return S_OK_;
}
// Streaming do mundo (CStreaming do motor, como no GTA III): o jogo chama LoadRequestedModels (0x5330A0) uma vez por
// quadro e cada chamada atende um canal de leitura -> o mapa e os modelos das pessoas carregam na velocidade do FPS.
// No fim do quadro (Present: depois do Update e do Render) chamamos de novo enquanto houver pedidos, ate ~3 ms.
// CdStreamGetStatus espera a leitura do canal terminar, entao cada chamada extra sempre avanca.
static void stream_boost(Cpu &c) {
    static uint64_t calls = 0, frames = 0;
    if (rd32(0x20DCD94u) == 0 || M[0x20DCD9Cu] == 0) return;   // CdStream ainda nao iniciado (ou modo sem thread)
    if (M[0xCE6D1Cu] != 0) return;                               // dentro de LoadAllRequestedModels (tela de carregamento)
    ++frames;
    struct timespec t0; clock_gettime(CLOCK_MONOTONIC, &t0);
    // orcamento adaptativo: fila grande (subiu a escada, entrou em area nova) carrega mais rapido; fila pequena quase nao custa
    const int32_t fila = (int32_t)rd32(0xCA3988u);
    const double orc = fila > 60 ? 7.0 : fila > 25 ? 4.0 : 1.5; const int maxk = fila > 60 ? 12 : fila > 25 ? 6 : 3;
    for (int k = 0; k < maxk; ++k) {
        if ((int32_t)rd32(0xCA3920u) != -1) break;               // erro de leitura: o Update cuida
        const bool pend = (int32_t)rd32(0xCA3988u) > 0 || rd32(0xCA38D0u) != 0 || rd32(0xCA3908u) != 0;
        if (!pend) break;
        uint32_t sv[8]; memcpy(sv, c.r, sizeof sv);
        c.r[4] -= 4; wr32(c.r[4], 0xDEAD0003u);
        x86_call(c, 0x5330A0u);
        memcpy(c.r, sv, sizeof sv);
        ++calls;
        struct timespec t1; clock_gettime(CLOCK_MONOTONIC, &t1);
        if ((t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6 > orc) break;
    }
    if (frames % 300 == 0) { rt_log("[streaming] %.1f chamadas extras por quadro, %d pedidos na fila\n", calls / 300.0, (int)rd32(0xCA3988u)); calls = 0; }
}
F(Dev_Present) { g_gfx->present(); ++g_dev->frames; stream_boost(c); return S_OK_; }
F(Dev_GetBackBuffer) { com_addref(g_dev->backbuf); wr32(a[4], g_dev->backbuf); return S_OK_; }
F(Dev_GetRasterStatus) { wr32(a[2], 1); wr32(a[2] + 4, 0); return S_OK_; }
F(Dev_SetDialogBoxMode) { return S_OK_; }
F(Dev_SetGammaRamp) { return 0; }
F(Dev_GetGammaRamp) { for (int i = 0; i < 256; ++i) for (int k = 0; k < 3; ++k) { const uint16_t v = (uint16_t)(i * 257); memcpy(M + a[2] + k * 512 + i * 2, &v, 2); } return 0; }

F(Dev_CreateTexture) {   // (Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle)
    if (!fmt_bpp(a[5])) { rt_log("[d3d9] CreateTexture formato desconhecido %08X\n", a[5]); return D3DERR_INVALIDCALL_; }
    Tex *t = tex_create(RT_TEXTURE, a[1], a[2], 1, a[3], a[4], a[5], a[6]);
    wr32(a[7], t->obj); return S_OK_;
}
F(Dev_CreateVolumeTexture) {   // (W, H, D, Levels, Usage, Format, Pool, pp, shared)
    if (!fmt_bpp(a[6])) return D3DERR_INVALIDCALL_;
    Tex *t = tex_create(RT_VOLTEX, a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
    wr32(a[8], t->obj); return S_OK_;
}
F(Dev_CreateCubeTexture) {   // (EdgeLength, Levels, Usage, Format, Pool, pp, shared)
    if (!fmt_bpp(a[4])) return D3DERR_INVALIDCALL_;
    Tex *t = tex_create(RT_CUBE, a[1], a[1], 1, a[2], a[3], a[4], a[5]);
    wr32(a[6], t->obj); return S_OK_;
}
F(Dev_CreateVertexBuffer) { Buf *b = buf_create(false, a[1], a[2], a[3], a[4]); wr32(a[5], b->obj); return S_OK_; }
F(Dev_CreateIndexBuffer) { Buf *b = buf_create(true, a[1], a[2], a[3], a[4]); wr32(a[5], b->obj); return S_OK_; }
F(Dev_CreateRenderTarget) { Surface *s = surf_create(a[1], a[2], a[3], 1, 0); wr32(a[7], s->obj); return S_OK_; }
F(Dev_CreateDepthStencilSurface) { Surface *s = surf_create(a[1], a[2], a[3], 2, 0); wr32(a[7], s->obj); return S_OK_; }
F(Dev_CreateOffscreenPlainSurface) { Surface *s = surf_create(a[1], a[2], a[3], 0, a[4]); wr32(a[5], s->obj); return S_OK_; }
// memoria de uma superficie no jogo (nivel da textura-mae ou bloco proprio)
static bool surf_mem(Surface *s, uint32_t &addr, uint32_t &pitch) {
    if (!s) return false;
    if (s->parent) { addr = tex_level_addr(s->parent, s->face, s->level); pitch = fmt_pitch(s->fmt, s->w); return true; }
    if (s->usage & 3) return false;   // alvo de desenho / profundidade: so existe na GPU
    if (!s->mem) s->mem = rt_alloc(fmt_size(s->fmt, s->w, s->h), true);
    addr = s->mem; pitch = fmt_pitch(s->fmt, s->w); return true;
}
F(Dev_UpdateSurface) {   // (pSrc, pSrcRect, pDst, pDstPoint): memoria do sistema -> textura
    Surface *ss = (Surface *)res_of(a[1]), *ds = (Surface *)res_of(a[3]);
    uint32_t sa, sp, da, dp;
    static int n = 0;
    if (n < 6) { ++n; rt_log("[d3d9] UpdateSurface %ux%u fmt %u -> %ux%u fmt %u%s\n", ss ? ss->w : 0, ss ? ss->h : 0, ss ? ss->fmt : 0, ds ? ds->w : 0, ds ? ds->h : 0, ds ? ds->fmt : 0, ds && ds->parent ? " (textura)" : ""); }
    if (!ss || !ds || ss->fmt != ds->fmt || !surf_mem(ss, sa, sp) || !surf_mem(ds, da, dp)) return S_OK_;
    uint32_t x0 = 0, y0 = 0, x1 = ss->w, y1 = ss->h, dx = 0, dy = 0;
    if (a[2]) { x0 = rd32(a[2]); y0 = rd32(a[2] + 4); x1 = rd32(a[2] + 8); y1 = rd32(a[2] + 12); }
    if (a[4]) { dx = rd32(a[4]); dy = rd32(a[4] + 4); }
    const bool dxt = fmt_is_dxt(ss->fmt); const uint32_t bs = dxt ? (ss->fmt == FMT_DXT1 ? 8 : 16) : fmt_bpp(ss->fmt) / 8, q = dxt ? 4 : 1;
    if (x1 > ss->w) x1 = ss->w; if (y1 > ss->h) y1 = ss->h;
    if (x1 <= x0 || y1 <= y0) return S_OK_;
    uint32_t w = x1 - x0, h = y1 - y0;
    if (dx + w > ds->w) w = ds->w > dx ? ds->w - dx : 0;
    if (dy + h > ds->h) h = ds->h > dy ? ds->h - dy : 0;
    const uint32_t rows = (h + q - 1) / q, bytes = ((w + q - 1) / q) * bs;
    for (uint32_t r = 0; r < rows; ++r)
        memmove(M + da + (dy / q + r) * dp + (dx / q) * bs, M + sa + (y0 / q + r) * sp + (x0 / q) * bs, bytes);
    if (ds->parent) tex_upload_level(ds->parent, ds->face, ds->level);
    return S_OK_;
}
F(Dev_UpdateTexture) {                         // sysmem -> default: cada nivel do destino recebe o nivel da origem com o mesmo tamanho
    Tex *s = (Tex *)res_of(a[1]), *d = (Tex *)res_of(a[2]);
    static int n = 0;
    if (n < 6 && s && d) { ++n; rt_log("[d3d9] UpdateTexture %ux%u (%u niveis) -> %ux%u (%u niveis) fmt %u\n", s->w, s->h, s->levels, d->w, d->h, d->levels, d->fmt); }
    if (!s || !d || s->fmt != d->fmt || s->type != d->type) return S_OK_;
    const uint32_t faces = d->type == RT_CUBE ? 6 : 1;
    for (uint32_t l = 0; l < d->levels; ++l) {
        const uint32_t w = mipdim(d->w, l), h = mipdim(d->h, l);
        uint32_t sl = 0; while (sl < s->levels && (mipdim(s->w, sl) != w || mipdim(s->h, sl) != h)) ++sl;
        if (sl >= s->levels) continue;
        const uint32_t sz = fmt_size(d->fmt, w, h) * mipdim(d->d, l);
        for (uint32_t f = 0; f < faces; ++f) {
            memcpy(M + tex_level_addr(d, f, l), M + tex_level_addr(s, f, sl), sz);
            tex_upload_level(d, f, l);
        }
    }
    return S_OK_;
}
F(Dev_GetRenderTargetData) { static int n = 0; if (n < 4) { ++n; rt_log("[d3d9] GetRenderTargetData (nao implementado)\n"); } return S_OK_; }
F(Dev_GetFrontBufferData) { return S_OK_; }
// superficie -> id do backend: 0 = backbuffer; false se nao e alvo na GPU (memoria do sistema / depth)
static bool surf_target(uint32_t o, uint32_t &id, Surface *&s) {
    s = (Surface *)res_of(o); if (!s) return false;
    if (o == g_dev->backbuf) { id = 0; return true; }
    id = s->gfx; return id != 0 && !(s->usage & 2);
}
static const int *rect_of(uint32_t p, int r[4]) { if (!p) return nullptr; for (int k = 0; k < 4; ++k) r[k] = (int)rd32(p + 4 * k); return r; }
F(Dev_StretchRect) {   // (pSrc, pSrcRect, pDst, pDstRect, Filter)
    uint32_t si, di; Surface *ss, *ds;
    const bool ok = surf_target(a[1], si, ss) && surf_target(a[3], di, ds);
    static int n = 0;
    if (n < 8) { ++n; rt_log("[d3d9] StretchRect %ux%u(fmt %u, id %u) -> %ux%u(fmt %u, id %u) filtro %u%s\n", ss ? ss->w : 0, ss ? ss->h : 0, ss ? ss->fmt : 0, si,
                             ds ? ds->w : 0, ds ? ds->h : 0, ds ? ds->fmt : 0, di, a[5], ok ? "" : " (ignorado)"); }
    if (!ok) return S_OK_;
    int r1[4], r2[4];
    g_gfx->blit(si, rect_of(a[2], r1), di, rect_of(a[4], r2), a[5] >= 2);
    return S_OK_;
}
F(Dev_ColorFill) {     // (pSurface, pRect, color)
    uint32_t di; Surface *ds; int r[4];
    static int n = 0;
    if (n < 4) { ++n; rt_log("[d3d9] ColorFill %08X\n", a[3]); }
    if (surf_target(a[1], di, ds)) g_gfx->fill(di, rect_of(a[2], r), a[3]);
    return S_OK_;
}
F(Dev_SetRenderTarget) {
    if (a[1] > 3) return D3DERR_INVALIDCALL_;
    rec(SB_RT, a[1]);
    bind_ref(g_dev->st.rt[a[1]], a[2]);
    g_dev->st.g.rt[a[1]] = (a[2] == g_dev->backbuf) ? 0 : gfx_of_tex(a[2]);
    if (a[1] == 0 && a[2]) {   // D3D9: trocar o RT0 reinicia viewport e scissor para o tamanho dele
        Surface *s = (Surface *)res_of(a[2]);
        if (s) { DevState &st = g_dev->st; st.g.vp_x = st.g.vp_y = 0; st.g.vp_w = (int)s->w; st.g.vp_h = (int)s->h; st.g.vp_minz = 0; st.g.vp_maxz = 1;
                 st.g.sc_l = st.g.sc_t = 0; st.g.sc_r = (int)s->w; st.g.sc_b = (int)s->h; }
    }
    return S_OK_;
}
F(Dev_GetRenderTarget) { if (a[1] > 3) return D3DERR_INVALIDCALL_; const uint32_t o = g_dev->st.rt[a[1]]; wr32(a[2], get_ref(o)); return o ? S_OK_ : 0x8876087Cu /*NOTFOUND*/; }
F(Dev_SetDepthStencilSurface) { bind_ref(g_dev->st.ds, a[1]); g_dev->st.g.ds = a[1] == g_dev->depth ? 0 : a[1] ? gfx_of_tex(a[1]) : 0xFFFFFFFFu; return S_OK_; }
F(Dev_GetDepthStencilSurface) { const uint32_t o = g_dev->st.ds; wr32(a[1], get_ref(o)); return o ? S_OK_ : 0x8876087Cu; }
F(Dev_BeginScene) { return S_OK_; }
F(Dev_EndScene) { return S_OK_; }
F(Dev_Clear) {   // (Count, pRects, Flags, Color, Z, Stencil) — TODO: retangulos parciais
    g_gfx->clear(g_dev->st.g, a[3], a[4], f32(a[5]), a[6]);
    return S_OK_;
}
static uint32_t xf_index(uint32_t t) { return t < 512 ? t : 0; }   // D3DTS_WORLD = 256, VIEW 2, PROJECTION 3, TEXTUREn 16+n
F(Dev_SetTransform) { const uint32_t i = xf_index(a[1]); rec(SB_XF, i); memcpy(g_dev->st.xf[i], M + a[2], 64); return S_OK_; }
F(Dev_GetTransform) { memcpy(M + a[2], g_dev->st.xf[xf_index(a[1])], 64); return S_OK_; }
F(Dev_MultiplyTransform) {
    float *d = g_dev->st.xf[xf_index(a[1])], r[16], m[16]; memcpy(m, M + a[2], 64);
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) { float s = 0; for (int k = 0; k < 4; ++k) s += m[i * 4 + k] * d[k * 4 + j]; r[i * 4 + j] = s; }
    memcpy(d, r, 64); return S_OK_;
}
F(Dev_SetViewport) {   // D3DVIEWPORT9 {X, Y, Width, Height, MinZ, MaxZ}
    rec(SB_VP, 0);
    DevState &s = g_dev->st; const uint32_t p = a[1];
    s.g.vp_x = (int)rd32(p); s.g.vp_y = (int)rd32(p + 4); s.g.vp_w = (int)rd32(p + 8); s.g.vp_h = (int)rd32(p + 12);
    s.g.vp_minz = f32(rd32(p + 16)); s.g.vp_maxz = f32(rd32(p + 20));
    return S_OK_;
}
F(Dev_GetViewport) {
    DevState &s = g_dev->st; const uint32_t p = a[1];
    wr32(p, s.g.vp_x); wr32(p + 4, s.g.vp_y); wr32(p + 8, s.g.vp_w); wr32(p + 12, s.g.vp_h); wr32(p + 16, u32f(s.g.vp_minz)); wr32(p + 20, u32f(s.g.vp_maxz));
    return S_OK_;
}
F(Dev_SetMaterial) { rec(SB_MAT, 0); memcpy(g_dev->st.material, M + a[1], 68); return S_OK_; }
F(Dev_GetMaterial) { memcpy(M + a[1], g_dev->st.material, 68); return S_OK_; }
F(Dev_SetLight) { if (a[1] < 8) { rec(SB_LIGHT, a[1]); memcpy(g_dev->st.light[a[1]], M + a[2], 104); } return S_OK_; }
F(Dev_GetLight) { if (a[1] < 8) memcpy(M + a[2], g_dev->st.light[a[1]], 104); return S_OK_; }
F(Dev_LightEnable) { if (a[1] < 8) { rec(SB_LIGHT, a[1]); g_dev->st.light_on[a[1]] = a[2] != 0; } return S_OK_; }
F(Dev_GetLightEnable) { wr32(a[2], a[1] < 8 && g_dev->st.light_on[a[1]]); return S_OK_; }
F(Dev_SetClipPlane) { if (a[1] < 6) { rec(SB_CLIP, a[1]); memcpy(g_dev->st.clip[a[1]], M + a[2], 16); } return S_OK_; }
F(Dev_GetClipPlane) { if (a[1] < 6) memcpy(M + a[2], g_dev->st.clip[a[1]], 16); return S_OK_; }
F(Dev_SetRenderState) {
    if (a[1] == 168 && g_dev->st.g.rs[168] != a[2]) {   // diagnostico: quem muda o COLORWRITEENABLE
        static int n = 0; if (n < 30) { ++n; rt_log("[d3d9] SetRenderState(COLORWRITEENABLE, %X) chamado de %08X\n", a[2], c.r[4] ? rd32(c.r[4]) : 0u); }
    }
    if (a[1] < 256) { rec(SB_RS, a[1]); g_dev->st.g.rs[a[1]] = a[2]; }
    return S_OK_;
}
F(Dev_GetRenderState) { wr32(a[2], a[1] < 256 ? g_dev->st.g.rs[a[1]] : 0); return S_OK_; }
F(Dev_CreateStateBlock) {   // (Type, ppSB): bloco com o estado inteiro
    SBlock *b = new SBlock; b->type = RT_SBLOCK; b->full = true; b->snap = g_dev->st;
    wr32(a[2], new_obj(vt_sblock(), b)); return S_OK_;
}
F(Dev_BeginStateBlock) { g_rec = new SBlock; g_rec->type = RT_SBLOCK; return S_OK_; }
F(Dev_EndStateBlock) {
    if (!g_rec) return D3DERR_INVALIDCALL_;
    SBlock *b = g_rec; g_rec = nullptr;
    b->snap = g_dev->st;   // valores gravados = estado atual no fim da gravacao
    wr32(a[1], new_obj(vt_sblock(), b)); return S_OK_;
}
F(Dev_SetClipStatus) { return S_OK_; }
F(Dev_GetClipStatus) { memset(M + a[1], 0, 8); return S_OK_; }
static uint32_t sampler_slot(uint32_t s) { return s < 16 ? s : (s >= 257 && s <= 260) ? 16 + (s - 257) : 0xFFFFFFFF; }   // DMAP/vertex samplers
F(Dev_GetTexture) { const uint32_t i = sampler_slot(a[1]); wr32(a[2], i < 20 ? get_ref(g_dev->st.tex[i]) : 0); return S_OK_; }
F(Dev_SetTexture) {
    const uint32_t i = sampler_slot(a[1]); if (i >= 20) return D3DERR_INVALIDCALL_;
    rec(SB_TEX, i);
    bind_ref(g_dev->st.tex[i], a[2]);
    if (i < 16) g_dev->st.g.tex[i] = gfx_of_tex(a[2]);
    return S_OK_;
}
F(Dev_GetTextureStageState) { wr32(a[3], (a[1] < 8 && a[2] < 33) ? g_dev->st.tss[a[1]][a[2]] : 0); return S_OK_; }
F(Dev_SetTextureStageState) { if (a[1] < 8 && a[2] < 33) { rec(SB_TSS, a[1], a[2]); g_dev->st.tss[a[1]][a[2]] = a[3]; } return S_OK_; }
F(Dev_GetSamplerState) { const uint32_t i = sampler_slot(a[1]); wr32(a[3], (i < 16 && a[2] < 14) ? g_dev->st.g.ss[i][a[2]] : 0); return S_OK_; }
F(Dev_SetSamplerState) { const uint32_t i = sampler_slot(a[1]); if (i < 16 && a[2] < 14) { rec(SB_SS, i, a[2]); g_dev->st.g.ss[i][a[2]] = a[3]; } return S_OK_; }
F(Dev_ValidateDevice) { if (a[1]) wr32(a[1], 1); return S_OK_; }
F(Dev_SetPaletteEntries) { return S_OK_; }
F(Dev_GetPaletteEntries) { return S_OK_; }
F(Dev_SetCurrentTexturePalette) { return S_OK_; }
F(Dev_GetCurrentTexturePalette) { wr32(a[1], 0); return S_OK_; }
F(Dev_SetScissorRect) { rec(SB_SC, 0); DevState &s = g_dev->st; const uint32_t p = a[1]; s.g.sc_l = (int)rd32(p); s.g.sc_t = (int)rd32(p + 4); s.g.sc_r = (int)rd32(p + 8); s.g.sc_b = (int)rd32(p + 12); return S_OK_; }
F(Dev_GetScissorRect) { DevState &s = g_dev->st; const uint32_t p = a[1]; wr32(p, s.g.sc_l); wr32(p + 4, s.g.sc_t); wr32(p + 8, s.g.sc_r); wr32(p + 12, s.g.sc_b); return S_OK_; }
F(Dev_SetSoftwareVertexProcessing) { return S_OK_; }
F(Dev_GetSoftwareVertexProcessing) { return 0; }
F(Dev_SetNPatchMode) { return S_OK_; }
F(Dev_GetNPatchMode) { return 0; }

// D3DPRIMITIVETYPE: 1 points, 2 lines, 3 linestrip, 4 tris, 5 tristrip, 6 trifan
static uint32_t prim_verts(uint32_t prim, uint32_t n) {
    switch (prim) { case 1: return n; case 2: return n * 2; case 3: return n + 1; case 4: return n * 3; case 5: case 6: return n + 2; }
    return 0;
}
F(Dev_DrawPrimitive) {   // (Type, StartVertex, PrimitiveCount)
    ++g_dev->draws;
    for (int i = 0; i < 16; ++i) g_dev->st.g.freq[i] = 1;   // instancing so existe com indices
    g_gfx->draw(g_dev->st.g, a[1], a[2], prim_verts(a[1], a[3]), false, 0, 0, 0);
    return S_OK_;
}
// diagnostico dos personagens (pele/skinning): 1 linha por (tecnica, declaracao de vertices) com o maior indice de osso usado
extern const char *g_fx_tech;
static void skin_audit(uint32_t base, uint32_t minv, uint32_t nv) {
    if (!g_fx_tech || !strstr(g_fx_tech, "skin")) return;
    static std::map<std::string, int> seen; static int nlog = 0;
    if (nlog >= 80) return;
    char key[160]; snprintf(key, sizeof key, "%s/%08X", g_fx_tech, g_dev->st.vdecl);
    if (seen.count(key)) return;
    seen[key] = 1; ++nlog;
    VDecl *d = (VDecl *)res_of(g_dev->st.vdecl);
    std::string ds; int bi_s = -1, bi_o = 0, bi_t = 0, bw_t = -1;
    if (d) for (size_t k = 0; k + 8 <= d->elems.size(); k += 8) {
        const uint8_t *e = d->elems.data() + k; const uint16_t st = (uint16_t)(e[0] | e[1] << 8), off = (uint16_t)(e[2] | e[3] << 8);
        if (st == 0xFF) break;
        char b[48]; snprintf(b, sizeof b, " s%u+%u:t%u/u%u.%u", st, off, e[4], e[6], e[7]); ds += b;
        if (e[6] == 2) { bi_s = st; bi_o = off; bi_t = e[4]; }
        if (e[6] == 1) bw_t = e[4];
    }
    uint32_t maxb = 0; bool okb = false;
    if (bi_s >= 0) {
        Buf *b = (Buf *)res_of(g_dev->st.stream[bi_s]);
        const uint32_t stride = g_dev->st.g.vstride[bi_s], voff = g_dev->st.g.voff[bi_s];
        if (b && b->mem && stride) {
            okb = true;
            for (uint32_t v = 0; v < nv && v < 20000; ++v) {
                const uint64_t ad = (uint64_t)voff + (uint64_t)(base + minv + v) * stride + bi_o;
                if (ad + 4 > b->size) break;
                for (int q = 0; q < 4; ++q) { const uint32_t x = M[b->mem + ad + q]; if (x > maxb) maxb = x; }
            }
        }
    }
    int hi = -1; for (int r = 255; r >= 0; --r) { const float *p = g_dev->st.vsc + 4 * r; if (p[0] != 0 || p[1] != 0 || p[2] != 0 || p[3] != 0) { hi = r; break; } }
    rt_log("[pele] %s | decl%s | indice de osso: tipo %d, maior %s%u | peso tipo %d | %u vertices | maior registro vs nao-zero c%d\n",
           g_fx_tech, ds.c_str(), bi_t, okb ? "" : "?", maxb, bw_t, nv, hi);
}
// captura de UM desenho (o tronco do Jimmy: pele com mais de 8 ossos) para analise fora do celular: shaders,
// constantes, vertices, indices e estado -> <files>/captura_jimmy.bin
static void cap_put(FILE *f, uint32_t tag, const void *d, uint32_t n) { fwrite(&tag, 4, 1, f); fwrite(&n, 4, 1, f); if (n) fwrite(d, 1, n, f); }
static void capture_draw(const uint32_t *a) {
    static int ncap = 0;
    if (ncap >= 3 || !g_fx_tech || !strstr(g_fx_tech, "skin") || strstr(g_fx_tech, "depth")) return;
    VDecl *d = (VDecl *)res_of(g_dev->st.vdecl); if (!d) return;
    int bi_s = -1, bi_o = 0;
    for (size_t k = 0; k + 8 <= d->elems.size(); k += 8) { const uint8_t *e = d->elems.data() + k; if ((e[0] | e[1] << 8) == 0xFF) break; if (e[6] == 2) { bi_s = e[0]; bi_o = e[2] | e[3] << 8; } }
    if (bi_s < 0) return;
    Buf *vb = (Buf *)res_of(g_dev->st.stream[bi_s]); const uint32_t stride = g_dev->st.g.vstride[bi_s], voff = g_dev->st.g.voff[bi_s];
    if (!vb || !vb->mem || !stride) return;
    const uint32_t base = a[2], minv = a[3], nv = a[4];
    uint32_t maxb = 0;
    for (uint32_t v = 0; v < nv; ++v) { const uint64_t ad = (uint64_t)voff + (uint64_t)(base + minv + v) * stride + bi_o; if (ad + 4 > vb->size) break; for (int q = 0; q < 4; ++q) if (M[vb->mem + ad + q] > maxb) maxb = M[vb->mem + ad + q]; }
    if (maxb <= 8) return;
    { static int seen = 0; if (++seen < 90 || (seen - 90) % 60) return; }   // pula os primeiros quadros (dados ainda velhos no 1o quadro)
    char path[512]; snprintf(path, sizeof path, "%s/captura_jimmy%d.bin", g_files_dir.c_str(), ncap);
    FILE *f = fopen(path, "wb"); if (!f) return;
    ++ncap;
    fwrite("BCAP", 1, 4, f);
    cap_put(f, 1, g_fx_tech, (uint32_t)strlen(g_fx_tech));
    Shader *vs = (Shader *)res_of(g_dev->st.vs), *ps = (Shader *)res_of(g_dev->st.ps);
    if (vs) cap_put(f, 2, vs->code.data(), 4 * (uint32_t)vs->code.size());
    if (ps) cap_put(f, 3, ps->code.data(), 4 * (uint32_t)ps->code.size());
    cap_put(f, 4, g_dev->st.vsc, sizeof g_dev->st.vsc);
    cap_put(f, 5, g_dev->st.psc, sizeof g_dev->st.psc);
    cap_put(f, 6, d->elems.data(), (uint32_t)d->elems.size());
    {   // vertices de todos os streams usados (stream, stride, offset do primeiro vertice, dados)
        for (int st = 0; st < 4; ++st) {
            Buf *b = (Buf *)res_of(g_dev->st.stream[st]); const uint32_t sd = g_dev->st.g.vstride[st], so = g_dev->st.g.voff[st];
            if (!b || !b->mem || !sd) continue;
            const uint64_t a0 = (uint64_t)so + (uint64_t)(base + minv) * sd; uint64_t len = (uint64_t)nv * sd;
            if (a0 >= b->size) continue; if (a0 + len > b->size) len = b->size - a0;
            std::vector<uint8_t> blob(12 + len); uint32_t hd[3] = {(uint32_t)st, sd, minv}; memcpy(blob.data(), hd, 12); memcpy(blob.data() + 12, M + b->mem + a0, len);
            cap_put(f, 7, blob.data(), (uint32_t)blob.size());
        }
    }
    {
        Buf *ib = (Buf *)res_of(g_dev->st.ib);
        const uint32_t isz = g_dev->st.g.ifmt == 102 ? 4 : 2, ni = prim_verts(a[1], a[6]);
        if (ib && ib->mem && (uint64_t)(a[5] + ni) * isz <= ib->size) {
            std::vector<uint8_t> blob(4 + ni * isz); memcpy(blob.data(), &isz, 4); memcpy(blob.data() + 4, M + ib->mem + a[5] * isz, ni * isz);
            cap_put(f, 8, blob.data(), (uint32_t)blob.size());
        }
    }
    cap_put(f, 9, &g_dev->st.g, sizeof g_dev->st.g);
    cap_put(f, 10, a + 1, 6 * 4);
    cap_put(f, 11, g_dev->st.vsi, sizeof g_dev->st.vsi); cap_put(f, 12, g_dev->st.vsb, sizeof g_dev->st.vsb);
    cap_put(f, 13, g_dev->st.psi, sizeof g_dev->st.psi); cap_put(f, 14, g_dev->st.psb, sizeof g_dev->st.psb);
    {   // texturas ligadas: unidade, largura, altura, formato, niveis
        std::vector<uint32_t> ti;
        for (uint32_t u = 0; u < 16; ++u) { Tex *t = (Tex *)res_of(g_dev->st.tex[u]); if (!t) continue; ti.push_back(u); ti.push_back(t->w); ti.push_back(t->h); ti.push_back(t->fmt); ti.push_back(t->levels); }
        cap_put(f, 15, ti.data(), 4 * (uint32_t)ti.size());
    }
    fclose(f);
    rt_log("[captura] desenho com %u ossos (%s, %u vertices) salvo em %s\n", maxb + 1, g_fx_tech, nv, path);
}
F(Dev_DrawIndexedPrimitive) {   // (Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount)
    ++g_dev->draws;
    // capture_draw(a);   // captura de diagnostico (desligada)
    // skin_audit(a[2], a[3], a[4]);   // diagnostico de skinning (desligado)
    memcpy(g_dev->st.g.freq, g_dev->st.freq, sizeof g_dev->st.freq);
    { static int n = 0; if (n < 5 && (g_dev->st.freq[0] & 0x40000000u)) { ++n; rt_log("[d3d9] desenho com instancing: %u instancias (freq1=%08X)\n", g_dev->st.freq[0] & 0x3FFFFFFFu, g_dev->st.freq[1]); } }
    g_gfx->draw(g_dev->st.g, a[1], a[5], prim_verts(a[1], a[6]), true, (int32_t)a[2], a[3], a[4]);
    return S_OK_;
}
F(Dev_DrawPrimitiveUP) {   // (Type, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride)
    ++g_dev->draws;
    const uint32_t n = prim_verts(a[1], a[2]);
    g_gfx->draw_up(g_dev->st.g, a[1], n, M + a[3], a[4], nullptr, 0, n);
    // D3D9: depois de um *UP o stream 0 e os indices ficam desligados
    g_dev->st.stream[0] = 0; g_dev->st.g.vbuf[0] = 0; g_dev->st.g.vstride[0] = 0; g_dev->st.ib = 0; g_dev->st.g.ibuf = 0;
    return S_OK_;
}
F(Dev_DrawIndexedPrimitiveUP) {   // (Type, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, Stride)
    ++g_dev->draws;
    g_gfx->draw_up(g_dev->st.g, a[1], prim_verts(a[1], a[4]), M + a[7], a[8], M + a[5], a[6], a[2] + a[3]);
    g_dev->st.stream[0] = 0; g_dev->st.g.vbuf[0] = 0; g_dev->st.g.vstride[0] = 0; g_dev->st.ib = 0; g_dev->st.g.ibuf = 0;
    return S_OK_;
}
F(Dev_ProcessVertices) { return D3DERR_INVALIDCALL_; }
F(Dev_CreateVertexDeclaration) {   // (pVertexElements, ppDecl)
    VDecl *v = new VDecl; v->type = RT_VDECL;
    uint32_t p = a[1]; int n = 0;
    while (n <= 64 && (rd32(p + 8u * n) & 0xFFFF) != 0xFF) ++n;   // D3DDECL_END: Stream = 0xFF
    v->elems.assign(M + a[1], M + a[1] + 8 * (n + 1));
    v->gfx = g_gfx->vdecl_create(v->elems.data(), n);
    wr32(a[2], new_obj(vt_vdecl(), v)); return S_OK_;
}
F(Dev_SetVertexDeclaration) { rec(SB_VDECL, 0); bind_ref(g_dev->st.vdecl, a[1]); VDecl *v = (VDecl *)res_of(a[1]); g_dev->st.g.vdecl = v ? v->gfx : 0; if (v) g_dev->st.g.fvf = 0; return S_OK_; }
F(Dev_GetVertexDeclaration) { wr32(a[1], get_ref(g_dev->st.vdecl)); return S_OK_; }
F(Dev_SetFVF) { rec(SB_VDECL, 0); g_dev->st.g.fvf = a[1]; if (a[1]) { g_dev->st.vdecl = 0; g_dev->st.g.vdecl = 0; } return S_OK_; }
F(Dev_GetFVF) { wr32(a[1], g_dev->st.g.fvf); return S_OK_; }
static uint32_t make_shader(bool pixel, uint32_t code, uint32_t pp) {
    if (!code) return D3DERR_INVALIDCALL_;
    Shader *s = new Shader; s->type = pixel ? RT_PS : RT_VS;
    const uint32_t n = shader_len(code);
    s->code.resize(n); memcpy(s->code.data(), M + code, 4 * n);
    s->gfx = g_gfx->shader_create(pixel, s->code.data(), n);
    wr32(pp, new_obj(pixel ? vt_ps() : vt_vs(), s)); return S_OK_;
}
F(Dev_CreateVertexShader) { return make_shader(false, a[1], a[2]); }
F(Dev_SetVertexShader) { rec(SB_VS, 0); bind_ref(g_dev->st.vs, a[1]); Shader *s = (Shader *)res_of(a[1]); g_dev->st.g.vs = s ? s->gfx : 0; return S_OK_; }
F(Dev_GetVertexShader) { wr32(a[1], get_ref(g_dev->st.vs)); return S_OK_; }
// constantes: (StartRegister, pData, Count)
F(Dev_SetVertexShaderConstantF) { if (a[1] + a[3] > 256) return D3DERR_INVALIDCALL_; rec(SB_VSF, a[1], 0, a[3]); memcpy(g_dev->st.vsc + 4 * a[1], M + a[2], 16 * a[3]); return S_OK_; }
F(Dev_GetVertexShaderConstantF) { if (a[1] + a[3] > 256) return D3DERR_INVALIDCALL_; memcpy(M + a[2], g_dev->st.vsc + 4 * a[1], 16 * a[3]); return S_OK_; }
F(Dev_SetVertexShaderConstantI) { if (a[1] + a[3] > 16) return D3DERR_INVALIDCALL_; rec(SB_VSI, a[1], 0, a[3]); memcpy(g_dev->st.vsi + 4 * a[1], M + a[2], 16 * a[3]); return S_OK_; }
F(Dev_GetVertexShaderConstantI) { if (a[1] + a[3] > 16) return D3DERR_INVALIDCALL_; memcpy(M + a[2], g_dev->st.vsi + 4 * a[1], 16 * a[3]); return S_OK_; }
F(Dev_SetVertexShaderConstantB) { if (a[1] + a[3] > 16) return D3DERR_INVALIDCALL_; rec(SB_VSB, a[1], 0, a[3]); memcpy(g_dev->st.vsb + a[1], M + a[2], 4 * a[3]); return S_OK_; }
F(Dev_GetVertexShaderConstantB) { if (a[1] + a[3] > 16) return D3DERR_INVALIDCALL_; memcpy(M + a[2], g_dev->st.vsb + a[1], 4 * a[3]); return S_OK_; }
F(Dev_SetStreamSource) {   // (StreamNumber, pStreamData, OffsetInBytes, Stride)
    if (a[1] >= 16) return D3DERR_INVALIDCALL_;
    rec(SB_STREAM, a[1]);
    bind_ref(g_dev->st.stream[a[1]], a[2]);
    g_dev->st.g.vbuf[a[1]] = gfx_of_buf(a[2]); g_dev->st.g.voff[a[1]] = a[3]; g_dev->st.g.vstride[a[1]] = a[4];
    return S_OK_;
}
F(Dev_GetStreamSource) {
    if (a[1] >= 16) return D3DERR_INVALIDCALL_;
    wr32(a[2], get_ref(g_dev->st.stream[a[1]])); wr32(a[3], g_dev->st.g.voff[a[1]]); wr32(a[4], g_dev->st.g.vstride[a[1]]);
    return S_OK_;
}
F(Dev_SetStreamSourceFreq) { if (a[1] < 16) { rec(SB_STREAM, a[1]); g_dev->st.freq[a[1]] = a[2]; } return S_OK_; }   // TODO backend: instancing
F(Dev_GetStreamSourceFreq) { wr32(a[2], a[1] < 16 ? g_dev->st.freq[a[1]] : 1); return S_OK_; }
F(Dev_SetIndices) { rec(SB_IB, 0); bind_ref(g_dev->st.ib, a[1]); Buf *b = (Buf *)res_of(a[1]); g_dev->st.g.ibuf = b ? b->gfx : 0; g_dev->st.g.ifmt = b ? b->fmt : 0; return S_OK_; }
F(Dev_GetIndices) { wr32(a[1], get_ref(g_dev->st.ib)); return S_OK_; }
F(Dev_CreatePixelShader) { return make_shader(true, a[1], a[2]); }
F(Dev_SetPixelShader) { rec(SB_PS, 0); bind_ref(g_dev->st.ps, a[1]); Shader *s = (Shader *)res_of(a[1]); g_dev->st.g.ps = s ? s->gfx : 0; return S_OK_; }
F(Dev_GetPixelShader) { wr32(a[1], get_ref(g_dev->st.ps)); return S_OK_; }
F(Dev_SetPixelShaderConstantF) { if (a[1] + a[3] > 224) return D3DERR_INVALIDCALL_; rec(SB_PSF, a[1], 0, a[3]); memcpy(g_dev->st.psc + 4 * a[1], M + a[2], 16 * a[3]); return S_OK_; }
F(Dev_GetPixelShaderConstantF) { if (a[1] + a[3] > 224) return D3DERR_INVALIDCALL_; memcpy(M + a[2], g_dev->st.psc + 4 * a[1], 16 * a[3]); return S_OK_; }
F(Dev_SetPixelShaderConstantI) { if (a[1] + a[3] > 16) return D3DERR_INVALIDCALL_; rec(SB_PSI, a[1], 0, a[3]); memcpy(g_dev->st.psi + 4 * a[1], M + a[2], 16 * a[3]); return S_OK_; }
F(Dev_GetPixelShaderConstantI) { if (a[1] + a[3] > 16) return D3DERR_INVALIDCALL_; memcpy(M + a[2], g_dev->st.psi + 4 * a[1], 16 * a[3]); return S_OK_; }
F(Dev_SetPixelShaderConstantB) { if (a[1] + a[3] > 16) return D3DERR_INVALIDCALL_; rec(SB_PSB, a[1], 0, a[3]); memcpy(g_dev->st.psb + a[1], M + a[2], 4 * a[3]); return S_OK_; }
F(Dev_GetPixelShaderConstantB) { if (a[1] + a[3] > 16) return D3DERR_INVALIDCALL_; memcpy(M + a[2], g_dev->st.psb + a[1], 4 * a[3]); return S_OK_; }
F(Dev_CreateQuery) {   // (Type, ppQuery); ppQuery NULL = so pergunta se e suportado
    if (!a[2]) return S_OK_;
    Query *q = new Query; q->type = RT_QUERY; q->qtype = a[1];
    wr32(a[2], new_obj(vt_query(), q)); return S_OK_;
}

// ---- aplicar state blocks
static void sb_copy(DevState &dst, const DevState &src, const SBOp &o, bool to_dev) {
    DevState &d = dst; const DevState &s = src;
    switch (o.kind) {
    case SB_RS: d.g.rs[o.i] = s.g.rs[o.i]; break;
    case SB_SS: d.g.ss[o.i][o.j] = s.g.ss[o.i][o.j]; break;
    case SB_TSS: d.tss[o.i][o.j] = s.tss[o.i][o.j]; break;
    case SB_TEX: d.tex[o.i] = s.tex[o.i]; if (o.i < 16) d.g.tex[o.i] = to_dev ? gfx_of_tex(d.tex[o.i]) : s.g.tex[o.i]; break;
    case SB_STREAM: d.stream[o.i] = s.stream[o.i]; d.g.vbuf[o.i] = s.g.vbuf[o.i]; d.g.voff[o.i] = s.g.voff[o.i]; d.g.vstride[o.i] = s.g.vstride[o.i]; d.freq[o.i] = s.freq[o.i]; break;
    case SB_IB: d.ib = s.ib; d.g.ibuf = s.g.ibuf; d.g.ifmt = s.g.ifmt; break;
    case SB_VDECL: d.vdecl = s.vdecl; d.g.vdecl = s.g.vdecl; d.g.fvf = s.g.fvf; break;
    case SB_VS: d.vs = s.vs; d.g.vs = s.g.vs; break;
    case SB_PS: d.ps = s.ps; d.g.ps = s.g.ps; break;
    case SB_VSF: memcpy(d.vsc + 4 * o.i, s.vsc + 4 * o.i, 16 * o.n); break;
    case SB_PSF: memcpy(d.psc + 4 * o.i, s.psc + 4 * o.i, 16 * o.n); break;
    case SB_VSI: memcpy(d.vsi + 4 * o.i, s.vsi + 4 * o.i, 16 * o.n); break;
    case SB_PSI: memcpy(d.psi + 4 * o.i, s.psi + 4 * o.i, 16 * o.n); break;
    case SB_VSB: memcpy(d.vsb + o.i, s.vsb + o.i, 4 * o.n); break;
    case SB_PSB: memcpy(d.psb + o.i, s.psb + o.i, 4 * o.n); break;
    case SB_XF: memcpy(d.xf[o.i], s.xf[o.i], 64); break;
    case SB_VP: d.g.vp_x = s.g.vp_x; d.g.vp_y = s.g.vp_y; d.g.vp_w = s.g.vp_w; d.g.vp_h = s.g.vp_h; d.g.vp_minz = s.g.vp_minz; d.g.vp_maxz = s.g.vp_maxz; break;
    case SB_SC: d.g.sc_l = s.g.sc_l; d.g.sc_t = s.g.sc_t; d.g.sc_r = s.g.sc_r; d.g.sc_b = s.g.sc_b; break;
    case SB_MAT: memcpy(d.material, s.material, 68); break;
    case SB_LIGHT: memcpy(d.light[o.i], s.light[o.i], 104); d.light_on[o.i] = s.light_on[o.i]; break;
    case SB_CLIP: memcpy(d.clip[o.i], s.clip[o.i], 16); break;
    default: break;
    }
}
static void keep_targets(DevState &d, const DevState &cur) {   // state blocks nao guardam alvos de desenho
    memcpy(d.rt, cur.rt, sizeof d.rt); d.ds = cur.ds; memcpy(d.g.rt, cur.g.rt, sizeof d.g.rt); d.g.ds = cur.g.ds;
}
F(SB_Capture) {
    SBlock *b = (SBlock *)res_of(a[0]); if (!b) return D3DERR_INVALIDCALL_;
    if (b->full) b->snap = g_dev->st; else for (const SBOp &o : b->ops) sb_copy(b->snap, g_dev->st, o, false);
    return S_OK_;
}
F(SB_Apply) {
    SBlock *b = (SBlock *)res_of(a[0]); if (!b) return D3DERR_INVALIDCALL_;
    if (b->full) { DevState cur = g_dev->st; g_dev->st = b->snap; keep_targets(g_dev->st, cur); fix_ptrs(g_dev->st); }
    else for (const SBOp &o : b->ops) sb_copy(g_dev->st, b->snap, o, true);
    return S_OK_;
}

// ---- swap chain (so a implicita)
F(Swap_Present) { return Dev_Present(c, a); }
F(Swap_GetBackBuffer) { com_addref(g_dev->backbuf); wr32(a[3], g_dev->backbuf); return S_OK_; }
F(Swap_GetRasterStatus) { wr32(a[1], 1); wr32(a[1] + 4, 0); return S_OK_; }
F(Swap_GetDisplayMode) { put_display_mode(a[1]); return S_OK_; }
F(Swap_GetPresentParameters) { memcpy(M + a[1], g_dev->pp, 56); return S_OK_; }
VT(vt_swap, "IDirect3DSwapChain9", UNK, M_(Present, 5, Swap_Present), M_(GetFrontBufferData, 1, nullptr), M_(GetBackBuffer, 3, Swap_GetBackBuffer),
   M_(GetRasterStatus, 1, Swap_GetRasterStatus), M_(GetDisplayMode, 1, Swap_GetDisplayMode), M_(GetDevice, 1, Res_GetDevice),
   M_(GetPresentParameters, 1, Swap_GetPresentParameters))

#define D(n, k) M_(n, k, Dev_##n)
VT(vt_device, "IDirect3DDevice9", UNK,
   D(TestCooperativeLevel, 0), D(GetAvailableTextureMem, 0), D(EvictManagedResources, 0), D(GetDirect3D, 1), D(GetDeviceCaps, 1),
   D(GetDisplayMode, 2), D(GetCreationParameters, 1), D(SetCursorProperties, 3), D(SetCursorPosition, 3), D(ShowCursor, 1),
   M_(CreateAdditionalSwapChain, 2, nullptr), D(GetSwapChain, 2), D(GetNumberOfSwapChains, 0), D(Reset, 1), D(Present, 4),
   D(GetBackBuffer, 4), D(GetRasterStatus, 2), D(SetDialogBoxMode, 1), D(SetGammaRamp, 3), D(GetGammaRamp, 2),
   D(CreateTexture, 8), D(CreateVolumeTexture, 9), D(CreateCubeTexture, 7), D(CreateVertexBuffer, 6), D(CreateIndexBuffer, 6),
   D(CreateRenderTarget, 8), D(CreateDepthStencilSurface, 8), D(UpdateSurface, 4), D(UpdateTexture, 2), D(GetRenderTargetData, 2),
   D(GetFrontBufferData, 2), D(StretchRect, 5), D(ColorFill, 3), D(CreateOffscreenPlainSurface, 6), D(SetRenderTarget, 2),
   D(GetRenderTarget, 2), D(SetDepthStencilSurface, 1), D(GetDepthStencilSurface, 1), D(BeginScene, 0), D(EndScene, 0),
   D(Clear, 6), D(SetTransform, 2), D(GetTransform, 2), D(MultiplyTransform, 2), D(SetViewport, 1),
   D(GetViewport, 1), D(SetMaterial, 1), D(GetMaterial, 1), D(SetLight, 2), D(GetLight, 2),
   D(LightEnable, 2), D(GetLightEnable, 2), D(SetClipPlane, 2), D(GetClipPlane, 2), D(SetRenderState, 2),
   D(GetRenderState, 2), D(CreateStateBlock, 2), D(BeginStateBlock, 0), D(EndStateBlock, 1), D(SetClipStatus, 1),
   D(GetClipStatus, 1), D(GetTexture, 2), D(SetTexture, 2), D(GetTextureStageState, 3), D(SetTextureStageState, 3),
   D(GetSamplerState, 3), D(SetSamplerState, 3), D(ValidateDevice, 1), D(SetPaletteEntries, 2), D(GetPaletteEntries, 2),
   D(SetCurrentTexturePalette, 1), D(GetCurrentTexturePalette, 1), D(SetScissorRect, 1), D(GetScissorRect, 1), D(SetSoftwareVertexProcessing, 1),
   D(GetSoftwareVertexProcessing, 0), D(SetNPatchMode, 1), D(GetNPatchMode, 0), D(DrawPrimitive, 3), D(DrawIndexedPrimitive, 6),
   D(DrawPrimitiveUP, 4), D(DrawIndexedPrimitiveUP, 8), D(ProcessVertices, 6), D(CreateVertexDeclaration, 2), D(SetVertexDeclaration, 1),
   D(GetVertexDeclaration, 1), D(SetFVF, 1), D(GetFVF, 1), D(CreateVertexShader, 2), D(SetVertexShader, 1),
   D(GetVertexShader, 1), D(SetVertexShaderConstantF, 3), D(GetVertexShaderConstantF, 3), D(SetVertexShaderConstantI, 3), D(GetVertexShaderConstantI, 3),
   D(SetVertexShaderConstantB, 3), D(GetVertexShaderConstantB, 3), D(SetStreamSource, 4), D(GetStreamSource, 4), D(SetStreamSourceFreq, 2),
   D(GetStreamSourceFreq, 2), D(SetIndices, 1), D(GetIndices, 1), D(CreatePixelShader, 2), D(SetPixelShader, 1),
   D(GetPixelShader, 1), D(SetPixelShaderConstantF, 3), D(GetPixelShaderConstantF, 3), D(SetPixelShaderConstantI, 3), D(GetPixelShaderConstantI, 3),
   D(SetPixelShaderConstantB, 3), D(GetPixelShaderConstantB, 3), M_(DrawRectPatch, 3, nullptr), M_(DrawTriPatch, 3, nullptr), M_(DeletePatch, 1, nullptr),
   D(CreateQuery, 3))

// ================================================================ IDirect3D9
static const uint32_t kModes[][2] = {{640, 480}, {800, 600}, {1024, 768}, {1280, 960}, {1024, 600}, {1066, 600}, {1280, 720}, {1366, 768}, {1600, 900}, {1920, 1080}, {1600, 720}};   // 16:9 (o jogo exige largura >= 800 e altura >= 600)
static const uint32_t kNModes = sizeof kModes / sizeof kModes[0];
uint32_t g_screen_w = 1280, g_screen_h = 720;   // definido pelo main (tamanho da janela/tela)

F(D3D_RegisterSoftwareDevice) { return E_NOTIMPL_; }
F(D3D_GetAdapterCount) { return 1; }
F(D3D_GetAdapterIdentifier) {   // (Adapter, Flags, pIdentifier) D3DADAPTER_IDENTIFIER9 = 1100 bytes
    const uint32_t p = a[3]; memset(M + p, 0, 1100);
    strcpy((char *)M + p, "nv4_disp.dll"); strcpy((char *)M + p + 512, "NVIDIA GeForce 8800 GT"); strcpy((char *)M + p + 1024, "\\\\.\\DISPLAY1");
    wr32(p + 1056, 0x000A0000); wr32(p + 1060, 0x00060010);   // versao do driver
    wr32(p + 1064, 0x10DE); wr32(p + 1068, 0x0611); wr32(p + 1076, 0xA2);
    wr32(p + 1096, 1);
    return S_OK_;
}
F(D3D_GetAdapterModeCount) { return a[2] == FMT_X8R8G8B8 ? kNModes : 0; }
F(D3D_EnumAdapterModes) {   // (Adapter, Format, Mode, pMode)
    if (a[2] != FMT_X8R8G8B8 || a[3] >= kNModes) return D3DERR_INVALIDCALL_;
    const uint32_t p = a[4]; wr32(p, kModes[a[3]][0]); wr32(p + 4, kModes[a[3]][1]); wr32(p + 8, 60); wr32(p + 12, FMT_X8R8G8B8);
    return S_OK_;
}
F(D3D_GetAdapterDisplayMode) { const uint32_t p = a[2]; wr32(p, g_screen_w); wr32(p + 4, g_screen_h); wr32(p + 8, 60); wr32(p + 12, FMT_X8R8G8B8); return S_OK_; }
F(D3D_CheckDeviceType) { return S_OK_; }
F(D3D_CheckDeviceFormat) {   // (Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat)
    const uint32_t f = a[6];
    if (f == FOURCC('N', 'U', 'L', 'L') || f == FOURCC('I', 'N', 'T', 'Z') || f == FOURCC('R', 'A', 'W', 'Z') || f == FOURCC('D', 'F', '2', '4') ||
        f == FOURCC('D', 'F', '1', '6') || f == FOURCC('A', 'T', 'I', '1') || f == FOURCC('A', 'T', 'I', '2')) return D3DERR_NOTAVAILABLE_;
    return fmt_bpp(f) ? S_OK_ : D3DERR_NOTAVAILABLE_;
}
F(D3D_CheckDeviceMultiSampleType) { if (a[6]) wr32(a[6], 1); return a[5] <= 1 ? S_OK_ : D3DERR_NOTAVAILABLE_; }   // sem MSAA por enquanto
F(D3D_CheckDepthStencilMatch) { return S_OK_; }
F(D3D_CheckDeviceFormatConversion) { return S_OK_; }
F(D3D_GetDeviceCaps) { fill_caps(a[3]); return S_OK_; }
F(D3D_GetAdapterMonitor) { return 0x00010001u; }
F(D3D_CreateDevice) {   // (Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface)
    // sem D3DCREATE_FPU_PRESERVE (0x2) o D3D9 poe o x87 desta thread em precisao simples e arredondamento ao mais proximo
    if (!(a[4] & 2)) c.fcw = (uint16_t)(c.fcw & ~0xF00u);
    const uint32_t pp = a[5];
    std::lock_guard<std::mutex> lk(g_d3d_mtx);
    if (!g_dev) {
        g_dev = new Device;
        g_dev->type = RT_DEVICE;
        g_dev->hwnd = rd32(pp + 28) ? rd32(pp + 28) : a[3];
        g_dev->create_flags = a[4];
        g_dev->bb_w = rd32(pp) ? rd32(pp) : g_screen_w; g_dev->bb_h = rd32(pp + 4) ? rd32(pp + 4) : g_screen_h;
        wr32(pp, g_dev->bb_w); wr32(pp + 4, g_dev->bb_h);
        if (!rd32(pp + 8)) wr32(pp + 8, FMT_X8R8G8B8);
        memcpy(g_dev->pp, M + pp, 56);
        rt_log("[d3d9] CreateDevice %ux%u fmt=%u janela=%u autodepth=%u(%u) flags=%08X\n", g_dev->bb_w, g_dev->bb_h, rd32(pp + 8),
               rd32(pp + 32), rd32(pp + 36), rd32(pp + 40), a[4]);
        if (!g_gfx) g_gfx = gfx_create_null();
        g_gfx->init((int)g_dev->bb_w, (int)g_dev->bb_h);
        new_obj(vt_device(), g_dev);
        // backbuffer e depth implicitos: gfx = 0 significa "tela"
        Surface *bb = new Surface; bb->type = RT_SURFACE; bb->w = g_dev->bb_w; bb->h = g_dev->bb_h; bb->fmt = rd32(pp + 8); bb->usage = 1;
        g_dev->backbuf = new_obj(vt_surface(), bb);
        if (rd32(pp + 36)) {
            Surface *ds = new Surface; ds->type = RT_SURFACE; ds->w = g_dev->bb_w; ds->h = g_dev->bb_h; ds->fmt = rd32(pp + 40); ds->usage = 2;
            g_dev->depth = new_obj(vt_surface(), ds);
        }
        Res *sw = new Res; sw->type = RT_SWAP; g_dev->swap = new_obj(vt_swap(), sw);
        set_defaults(g_dev);
        g_dev->st.rt[0] = g_dev->backbuf; g_dev->st.ds = g_dev->depth;
    } else com_addref(g_dev->obj);
    wr32(a[6], g_dev->obj);
    return S_OK_;
}

#define D3(n, k) M_(n, k, D3D_##n)
VT(vt_d3d, "IDirect3D9", UNK, D3(RegisterSoftwareDevice, 1), D3(GetAdapterCount, 0), D3(GetAdapterIdentifier, 3), D3(GetAdapterModeCount, 2),
   D3(EnumAdapterModes, 4), D3(GetAdapterDisplayMode, 2), D3(CheckDeviceType, 5), D3(CheckDeviceFormat, 6), D3(CheckDeviceMultiSampleType, 6),
   D3(CheckDepthStencilMatch, 5), D3(CheckDeviceFormatConversion, 4), D3(GetDeviceCaps, 3), D3(GetAdapterMonitor, 1), D3(CreateDevice, 6))

static uint32_t Direct3DCreate9(Cpu &c, const uint32_t *a) {
    rt_log("[d3d9] Direct3DCreate9(%u)\n", a[0]);
    if (!g_d3d_obj) { Res *r = new Res; r->type = RT_D3D; g_d3d_obj = new_obj(vt_d3d(), r); }
    else com_addref(g_d3d_obj);
    return g_d3d_obj;
}

// ---------------------------------------------------------------- D3DCAPS9 (304 bytes): GPU de shader model 3.0
uint32_t fill_caps(uint32_t p) {
    memset(M + p, 0, 304);
    auto W = [&](uint32_t off, uint32_t v) { wr32(p + off, v); };
    auto Wf = [&](uint32_t off, float v) { wr32(p + off, u32f(v)); };
    W(0, 1);                    // DeviceType HAL
    W(8, 0x00020000);           // Caps: READ_SCANLINE
    W(12, 0xE0020000);          // Caps2: FULLSCREENGAMMA | CANCALIBRATEGAMMA | CANMANAGERESOURCE | DYNAMICTEXTURES | CANAUTOGENMIPMAP
    W(16, 0x000003A0);          // Caps3
    W(20, 0x8000000F);          // PresentationIntervals
    W(24, 0x00000001);          // CursorCaps
    W(28, 0x001BBEF0);          // DevCaps (HWTRANSFORMANDLIGHT, PUREDEVICE, ...)
    W(32, 0x000EFFF2);          // PrimitiveMiscCaps (sem NULLREFERENCE)
    W(36, 0x07732191);          // RasterCaps (SCISSORTEST, DEPTHBIAS, SLOPESCALEDEPTHBIAS, MIPMAPLODBIAS, ANISOTROPY, ...)
    W(40, 0xFF); W(52, 0xFF);   // Z/AlphaCmpCaps
    W(44, 0x3FFF); W(48, 0x3FFF);   // Src/DestBlendCaps
    W(56, 0x00084208);          // ShadeCaps
    W(60, 0x0001EC45);          // TextureCaps: PERSPECTIVE|ALPHA|TEXREPEATNOTSCALEDBYSIZE|PROJECTED|CUBEMAP|VOLUMEMAP|MIPMAP|MIPVOLUMEMAP|MIPCUBEMAP (sem POW2)
    W(64, 0x03030700); W(68, 0x03030300); W(72, 0x03030300);   // filtros
    W(76, 0x3F); W(80, 0x3F);   // AddressCaps
    W(84, 0x1F);                // LineCaps
    W(88, 4096); W(92, 4096); W(96, 512); W(100, 8192); W(104, 8192); W(108, 16);
    Wf(112, 1e10f); Wf(116, -1e8f); Wf(120, -1e8f); Wf(124, 1e8f); Wf(128, 1e8f);
    W(136, 0x1FF);              // StencilCaps (TWOSIDED incluso)
    W(140, 0x00180008);         // FVFCaps: 8 coordenadas, PSIZE
    W(144, 0x03FEFFFF);         // TextureOpCaps
    W(148, 8); W(152, 8);
    W(156, 0x0000017B);         // VertexProcessingCaps
    W(160, 8); W(164, 6); W(168, 4); W(172, 255);
    Wf(176, 8192.0f);
    W(180, 0x00FFFFFF); W(184, 0x00FFFFFF); W(188, 16); W(192, 255);
    W(196, 0xFFFE0300); W(200, 256);   // vs_3_0, 256 constantes
    W(204, 0xFFFF0300);                // ps_3_0
    Wf(208, 65504.0f);
    W(212, 0x51);               // DevCaps2: STREAMOFFSET | VERTEXELEMENTSCANSHARESTREAMOFFSET | CAN_STRETCHRECT_FROM_TEXTURES
    W(232, 1);                  // NumberOfAdaptersInGroup
    W(236, 0x30F);              // DeclTypes (UBYTE4, UBYTE4N, SHORT2N, SHORT4N, FLOAT16_2/4...)
    W(240, 4);                  // NumSimultaneousRTs
    W(244, 0x03000300);         // StretchRectFilterCaps
    W(248, 1); W(252, 24); W(256, 32); W(260, 4);         // VS20Caps
    W(264, 0x1F); W(268, 24); W(272, 32); W(276, 4); W(280, 512);   // PS20Caps
    W(284, 0x03000300);         // VertexTextureFilterCaps
    W(288, 65535); W(292, 65535); W(296, 32768); W(300, 32768);
    return S_OK_;
}

// ---------------------------------------------------------------- chamadas do dispositivo usadas por outros arquivos (ID3DXEffect)
static Cpu g_dummy_cpu;
void d3d_set_render_state(uint32_t rs, uint32_t v) { const uint32_t a[3] = {0, rs, v}; Dev_SetRenderState(g_dummy_cpu, a); }
void d3d_set_sampler_state(uint32_t s, uint32_t t, uint32_t v) { const uint32_t a[4] = {0, s, t, v}; Dev_SetSamplerState(g_dummy_cpu, a); }
void d3d_set_texture(uint32_t s, uint32_t tex) { const uint32_t a[3] = {0, s, tex}; Dev_SetTexture(g_dummy_cpu, a); }
void d3d_set_vs(uint32_t obj) { const uint32_t a[2] = {0, obj}; Dev_SetVertexShader(g_dummy_cpu, a); }
void d3d_set_ps(uint32_t obj) { const uint32_t a[2] = {0, obj}; Dev_SetPixelShader(g_dummy_cpu, a); }
// constantes direto do host (sem passar pela memoria do jogo)
void d3d_shader_const_f(bool pixel, uint32_t reg, const float *v, uint32_t n) {
    const uint32_t lim = pixel ? 224 : 256; if (reg >= lim) return; if (reg + n > lim) n = lim - reg;
    rec(pixel ? SB_PSF : SB_VSF, reg, 0, n);
    memcpy((pixel ? g_dev->st.psc : g_dev->st.vsc) + 4 * reg, v, 16 * n);
}
void d3d_shader_const_i(bool pixel, uint32_t reg, const int32_t *v, uint32_t n) {
    if (reg >= 16) return; if (reg + n > 16) n = 16 - reg;
    rec(pixel ? SB_PSI : SB_VSI, reg, 0, n);
    memcpy((pixel ? g_dev->st.psi : g_dev->st.vsi) + 4 * reg, v, 16 * n);
}
void d3d_shader_const_b(bool pixel, uint32_t reg, const uint32_t *v, uint32_t n) {
    if (reg >= 16) return; if (reg + n > 16) n = 16 - reg;
    rec(pixel ? SB_PSB : SB_VSB, reg, 0, n);
    memcpy((pixel ? g_dev->st.psb : g_dev->st.vsb) + reg, v, 4 * n);
}
// cria um shader a partir de bytecode no host; devolve o objeto do jogo (0 se falhar)
uint32_t d3d_create_shader(bool pixel, const uint32_t *code, uint32_t ndw) {
    const uint32_t g = rt_alloc(4 * ndw + 8, false), pp = g + 4 * ndw;
    memcpy(M + g, code, 4 * ndw);
    const uint32_t r = make_shader(pixel, g, pp) == S_OK_ ? rd32(pp) : 0;
    rt_free(g);
    return r;
}
// salvar/restaurar estado inteiro (Begin/End de efeito sem D3DXFX_DONOTSAVESTATE)
void *d3d_state_save() { return new DevState(g_dev->st); }
void d3d_state_restore(void *p) {
    DevState *s = (DevState *)p; DevState cur = g_dev->st;
    g_dev->st = *s; keep_targets(g_dev->st, cur); fix_ptrs(g_dev->st);
    delete s;
}
uint64_t d3d_frames() { return g_dev ? g_dev->frames : 0; }
uint32_t d3d_device_obj() { return g_dev ? g_dev->obj : 0; }
float *d3d_shader_consts(bool pixel) { return pixel ? g_dev->st.psc : g_dev->st.vsc; }

// ---------------------------------------------------------------- tabela de importacoes deste arquivo
const RtImport g_d3d9_imports[] = {
    {"Direct3DCreate9", 1, Direct3DCreate9},
};
const int g_d3d9_nimports = (int)(sizeof g_d3d9_imports / sizeof g_d3d9_imports[0]);
