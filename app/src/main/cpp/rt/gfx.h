// Interface entre a camada D3D9 (d3d9.cpp) e a API grafica do aparelho. Hoje: OpenGL ES 3 (gfx_gles.cpp) ou nada
// (teste no PC). A camada D3D9 guarda todo o estado do Direct3D; o backend so recebe recursos e desenhos prontos.
// Pensado para ganhar um backend Vulkan depois sem mexer no d3d9.cpp.
#pragma once
#include <stdint.h>

enum class GfxTexType { Tex2D, Cube, Volume };
enum class GfxBufKind { Vertex, Index };

// estado de desenho que o backend precisa (copiado do estado do D3D9 a cada desenho)
struct GfxDrawState {
    uint32_t rs[256];               // render states do D3D9 (D3DRS_*)
    uint32_t ss[16][14];            // sampler states por estagio
    uint32_t tex[16];               // id de textura do backend por estagio (0 = nenhuma)
    uint32_t vbuf[16], vstride[16], voff[16];   // fontes de vertices (id do backend)
    uint32_t ibuf, ifmt;            // indices (id) e formato (101 = 16 bits, 102 = 32 bits)
    uint32_t vdecl;                 // id da declaracao de vertices (0 = usar fvf)
    uint32_t fvf;
    uint32_t vs, ps;                // ids de shader do backend (0 = pipeline fixo)
    const float *vsc; const float *psc;   // constantes float (256 e 224 vec4)
    const int32_t *vsi, *psi;             // constantes inteiras (16 ivec4)
    const uint32_t *vsb, *psb;            // constantes booleanas (16)
    const float *xf;                      // matrizes D3DTS (512 x 16, linha a linha) para o pipeline fixo
    const uint32_t *tss;                  // texture stage states (8 x 33) para o pipeline fixo
    int vp_x, vp_y, vp_w, vp_h; float vp_minz, vp_maxz;
    int sc_l, sc_t, sc_r, sc_b;
    uint32_t freq[16];              // SetStreamSourceFreq (instancing): stream 0 = 0x40000000|N, dados por instancia = 0x80000000|1
    uint32_t rt[4], ds;             // alvos de desenho (id de textura do backend; rt[0] = 0: backbuffer; ds = 0: depth do backbuffer, 0xFFFFFFFF: nenhum)
};

struct GfxBackend {
    virtual ~GfxBackend() {}
    virtual bool init(int w, int h) = 0;
    // texturas: formato = D3DFMT do jogo; o backend converte
    virtual uint32_t tex_create(GfxTexType t, uint32_t w, uint32_t h, uint32_t d, uint32_t levels, uint32_t fmt, bool rt) = 0;
    virtual void tex_upload(uint32_t id, uint32_t level, uint32_t face, const uint8_t *data, uint32_t pitch) = 0;
    virtual void tex_destroy(uint32_t id) = 0;
    virtual uint32_t buf_create(GfxBufKind k, uint32_t size) = 0;
    virtual void buf_upload(uint32_t id, uint32_t off, const uint8_t *data, uint32_t size) = 0;
    virtual void buf_destroy(uint32_t id) = 0;
    // declaracao de vertices: elementos D3DVERTEXELEMENT9 crus (8 bytes cada, termina com stream 0xFF)
    virtual uint32_t vdecl_create(const uint8_t *elems, int n) = 0;
    // shaders: bytecode D3D9 (vs_x_x / ps_x_x) gerado pelo D3DX
    virtual uint32_t shader_create(bool pixel, const uint32_t *code, uint32_t ndwords) = 0;
    virtual void clear(const GfxDrawState &s, uint32_t flags, uint32_t color, float z, uint32_t stencil) = 0;
    virtual void draw(const GfxDrawState &s, uint32_t prim, uint32_t start, uint32_t count, bool indexed, int32_t base_vertex, uint32_t min_index, uint32_t num_vertices) = 0;
    // desenho com vertices na memoria (DrawPrimitiveUP)
    virtual void draw_up(const GfxDrawState &s, uint32_t prim, uint32_t count, const uint8_t *verts, uint32_t stride, const uint8_t *idx, uint32_t ifmt, uint32_t nverts) = 0;
    virtual void present() = 0;
    // StretchRect / ColorFill: ids de textura do backend (0 = backbuffer); retangulos {l,t,r,b} ou nullptr = tudo
    virtual void blit(uint32_t, const int *, uint32_t, const int *, bool) {}
    virtual void fill(uint32_t, const int *, uint32_t) {}
};

GfxBackend *gfx_create_null();
GfxBackend *gfx_create_gles();
GfxBackend *gfx_wrap_threaded(GfxBackend *b);   // executa o backend em outra thread (gfx_mt.cpp)
// ganchos da plataforma para o backend GLES (Android: SDL; PC: EGL sem janela)
extern void (*gles_hook_make_current)();
extern void (*gles_hook_window_size)(int *w, int *h);
extern void (*gles_hook_swap)();
extern GfxBackend *g_gfx;
