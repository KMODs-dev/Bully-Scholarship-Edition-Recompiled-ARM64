// Teste do caminho grafico inteiro no PC: D3D9 (objetos COM, chamados pelas vtables) -> backend GLES -> Mesa llvmpipe.
// Desenha: fundo azul (Clear), quadrado texturizado com os shaders fixos do Bully, triangulo do pipeline fixo (XYZRHW).
#include "x86rt.h"
#include "rt.h"
#include "gfx.h"
#include "SDL_egl.h"
#include <stdio.h>
#include <vector>
#include <string>

void gles_read_backbuffer(GfxBackend *g, std::vector<uint8_t> &px, int &w, int &h);
static Cpu c;
static uint32_t call(uint32_t obj, int idx, std::vector<uint32_t> args) {
    const uint32_t fn = rd32(rd32(obj) + 4 * idx);
    for (size_t i = args.size(); i-- > 0;) { c.r[4] -= 4; wr32(c.r[4], args[i]); }
    c.r[4] -= 4; wr32(c.r[4], obj); c.r[4] -= 4; wr32(c.r[4], 0xDEAD0000u);
    x86_call(c, fn); return c.r[0];
}
static uint32_t fbits(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }
static const RtImport *imp(const RtImport *t, int n, const char *name) { for (int i = 0; i < n; ++i) if (!strcmp(t[i].name, name)) return &t[i]; return nullptr; }
static std::vector<uint32_t> loadbin(const char *p) { std::vector<uint32_t> v; FILE *f = fopen(p, "rb"); fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET); v.resize(n / 4); fread(v.data(), 4, v.size(), f); fclose(f); return v; }
static uint32_t gcopy(const void *p, uint32_t n) { const uint32_t g = rt_alloc(n, false); memcpy(M + g, p, n); return g; }

int main(int argc, char **argv) {
    PFNEGLGETPLATFORMDISPLAYEXTPROC gpd = (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
    EGLDisplay d = gpd(0x31DD, EGL_DEFAULT_DISPLAY, NULL); EGLint a1, a2; eglInitialize(d, &a1, &a2); eglBindAPI(EGL_OPENGL_ES_API);
    EGLint cx[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE}; EGLContext ctx = eglCreateContext(d, NULL, EGL_NO_CONTEXT, cx);
    eglMakeCurrent(d, EGL_NO_SURFACE, EGL_NO_SURFACE, ctx);
    if (!rt_mem_init()) return 1;
    rt_win32_init(".");
    g_gfx = gfx_create_gles();
    memset(&c, 0, sizeof c); c.r[4] = STACK_TOP - 64; c.fcw = 0x27F;
    uint32_t v32[1] = {32};
    const uint32_t d3d = imp(g_d3d9_imports, g_d3d9_nimports, "Direct3DCreate9")->fn(c, v32);
    const uint32_t pp = rt_alloc(64, true); wr32(pp, 320); wr32(pp + 4, 240); wr32(pp + 8, 21); wr32(pp + 32, 1); wr32(pp + 36, 1); wr32(pp + 40, 75);
    const uint32_t out = rt_alloc(256, true);
    call(d3d, 16, {0, 1, 0, 0x50, pp, out}); const uint32_t dev = rd32(out);
    // 1) fundo azul
    call(dev, 41, {});
    call(dev, 43, {0, 0, 3, 0xFF203080u, fbits(1.0f), 0});
    // 2) textura xadrez 64x64 (vermelho/amarelo)
    call(dev, 23, {64, 64, 1, 0, 21, 1, out, 0}); const uint32_t tex = rd32(out);
    call(tex, 19, {0, out, 0, 0}); const uint32_t pitch = rd32(out), bits = rd32(out + 4);
    for (int y = 0; y < 64; ++y) for (int x = 0; x < 64; ++x) wr32(bits + y * pitch + 4 * x, ((x / 8 + y / 8) & 1) ? 0xFFFF0000u : 0xFFFFFF00u);
    call(tex, 20, {0});
    // shaders fixos do Bully (VS_COLOR_TEX + PS_TEX)
    std::vector<uint32_t> vsb = loadbin(argv[1]), psb = loadbin(argv[2]);
    call(dev, 91, {gcopy(vsb.data(), 4 * vsb.size()), out}); const uint32_t vs = rd32(out);
    call(dev, 106, {gcopy(psb.data(), 4 * psb.size()), out}); const uint32_t ps = rd32(out);
    // declaracao: pos float3, tex float2, cor UBYTE4
    const uint8_t el[] = {0, 0, 0, 0, 2, 0, 0, 0,   0, 0, 12, 0, 1, 0, 5, 0,   0, 0, 20, 0, 5, 0, 10, 0,   0xFF, 0, 0, 0, 17, 0, 0, 0};
    call(dev, 86, {gcopy(el, sizeof el), out}); const uint32_t vd = rd32(out);
    call(dev, 87, {vd}); call(dev, 92, {vs}); call(dev, 107, {ps}); call(dev, 65, {0, tex});
    const float ident[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    call(dev, 94, {0, gcopy(ident, 64), 4});
    call(dev, 57, {22, 1});   // sem cull
    struct V { float x, y, z, u, v; uint8_t c[4]; } q[4] = {
        {-0.6f, 0.6f, 0.5f, 0, 0, {255, 255, 255, 255}}, {0.2f, 0.6f, 0.5f, 1, 0, {255, 255, 255, 255}},
        {-0.6f, -0.4f, 0.5f, 0, 1, {255, 255, 255, 255}}, {0.2f, -0.4f, 0.5f, 1, 1, {255, 255, 255, 255}}};
    call(dev, 83, {5, 2, gcopy(q, sizeof q), sizeof(V)});
    // 3) pipeline fixo: triangulo XYZRHW|DIFFUSE (verde) no canto direito
    call(dev, 92, {0}); call(dev, 107, {0}); call(dev, 65, {0, 0}); call(dev, 89, {0x44});
    struct T { float x, y, z, w; uint32_t col; } t[3] = {{220, 20, 0.5f, 1, 0xFF00FF00u}, {310, 20, 0.5f, 1, 0xFF00FF00u}, {265, 110, 0.5f, 1, 0xFFFFFFFFu}};
    call(dev, 83, {4, 1, gcopy(t, sizeof t), sizeof(T)});
    call(dev, 42, {});
    call(dev, 17, {0, 0, 0, 0});
    std::vector<uint8_t> px; int w, h; gles_read_backbuffer(g_gfx, px, w, h);
    // grava PPM com a linha 0 do GL (= topo do D3D) primeiro
    FILE *f = fopen(argv[3], "wb"); fprintf(f, "P6\n%d %d\n255\n", w, h);
    for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) fwrite(&px[4 * (y * w + x)], 1, 3, f);
    fclose(f);
    auto P = [&](int x, int y) { const uint8_t *p = &px[4 * (y * w + x)]; printf("pixel (%d,%d) = %u %u %u\n", x, y, p[0], p[1], p[2]); };
    P(5, 5); P(100, 100); P(265, 40); P(300, 200);
    return 0;
}
