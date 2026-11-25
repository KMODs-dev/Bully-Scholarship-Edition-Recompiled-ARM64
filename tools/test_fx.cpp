// Teste no PC: cria o dispositivo D3D9 falso e carrega todos os efeitos .fx de uma pasta pelo D3DXCreateEffect,
// chamando os metodos pelas vtables (mesmo caminho do jogo): tecnicas, passadas, Begin/BeginPass/CommitChanges/End.
#include "x86rt.h"
#include "rt.h"
#include <dirent.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "gfx.h"
#include "SDL_egl.h"

static Cpu c;
static uint32_t call(uint32_t obj, int idx, std::vector<uint32_t> args) {   // metodo COM stdcall
    const uint32_t fn = rd32(rd32(obj) + 4 * idx);
    for (size_t i = args.size(); i-- > 0;) { c.r[4] -= 4; wr32(c.r[4], args[i]); }
    c.r[4] -= 4; wr32(c.r[4], obj);
    c.r[4] -= 4; wr32(c.r[4], 0xDEAD0000u);
    x86_call(c, fn);
    return c.r[0];
}
static const RtImport *imp(const RtImport *t, int n, const char *name) { for (int i = 0; i < n; ++i) if (!strcmp(t[i].name, name)) return &t[i]; return nullptr; }

int main(int argc, char **argv) {
    if (!rt_mem_init()) return 1;
    rt_win32_init(".");
    if (getenv("GL")) {
        PFNEGLGETPLATFORMDISPLAYEXTPROC gpd = (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
        EGLDisplay d = gpd(0x31DD, EGL_DEFAULT_DISPLAY, NULL); EGLint a1, a2; eglInitialize(d, &a1, &a2); eglBindAPI(EGL_OPENGL_ES_API);
        EGLint cx[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE}; EGLContext ctx = eglCreateContext(d, NULL, EGL_NO_CONTEXT, cx);
        eglMakeCurrent(d, EGL_NO_SURFACE, EGL_NO_SURFACE, ctx);
        g_gfx = gfx_create_gles();
    }
    memset(&c, 0, sizeof c); c.r[4] = STACK_TOP - 64; c.fcw = 0x27F;
    uint32_t a1[1] = {32};
    const uint32_t d3d = imp(g_d3d9_imports, g_d3d9_nimports, "Direct3DCreate9")->fn(c, a1);
    const uint32_t pp = rt_alloc(64, true); wr32(pp, 800); wr32(pp + 4, 600); wr32(pp + 8, 21); wr32(pp + 32, 1); wr32(pp + 36, 1); wr32(pp + 40, 75);
    const uint32_t pdev = rt_alloc(4, true);
    call(d3d, 16, {0, 1, 0, 0x50, pp, pdev});
    const uint32_t dev = rd32(pdev);
    printf("dispositivo %08X\n", dev);
    const RtImport *ce = imp(g_d3dx9_imports, g_d3dx9_nimports, "D3DXCreateEffect");
    DIR *d = opendir(argv[1]); struct dirent *de; int ok = 0, bad = 0, passes = 0;
    const uint32_t out = rt_alloc(64, true);
    uint32_t tri = 0;
    if (getenv("GL")) {
        const float t[9] = {-1, -1, 0.5f, 1, -1, 0.5f, 0, 1, 0.5f}; tri = rt_alloc(36, false); memcpy(M + tri, t, 36);
        const uint8_t el[] = {0, 0, 0, 0, 2, 0, 0, 0, 0xFF, 0, 0, 0, 17, 0, 0, 0}; const uint32_t ge = rt_alloc(16, false); memcpy(M + ge, el, 16);
        call(dev, 86, {ge, out}); call(dev, 87, {rd32(out)});
    }
    while ((de = readdir(d))) {
        std::string n = de->d_name; if (n.size() < 4 || n.substr(n.size() - 3) != ".fx") continue;
        FILE *f = fopen((std::string(argv[1]) + "/" + n).c_str(), "rb"); fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET);
        const uint32_t g = rt_alloc((uint32_t)sz, false); fread(M + g, 1, sz, f); fclose(f);
        uint32_t a[9] = {dev, g, (uint32_t)sz, 0, 0, 0, 0, out, out + 4};
        if (ce->fn(c, a) != 0) { ++bad; continue; }
        const uint32_t fx = rd32(out);
        call(fx, 3, {out + 8});   // GetDesc
        const uint32_t ntech = rd32(out + 16);
        for (uint32_t t = 0; t < ntech; ++t) {
            const uint32_t ht = call(fx, 12, {t});
            call(fx, 58, {ht});        // SetTechnique
            call(fx, 63, {out + 40, 0});   // Begin
            const uint32_t np = rd32(out + 40);
            for (uint32_t p = 0; p < np; ++p) { call(fx, 64, {p}); call(fx, 65, {}); if (g_gfx && tri) call(dev, 83, {4, 1, tri, 12}); call(fx, 66, {}); ++passes; }
            call(fx, 67, {});          // End
        }
        // parametros: le a descricao de todos
        const uint32_t npar = rd32(out + 12);
        for (uint32_t i = 0; i < npar; ++i) { const uint32_t h = call(fx, 8, {0, i}); if (call(fx, 4, {h, out + 64 - 44 + 100}) != 0) printf("desc falhou\n"); }
        if (ok == 0) {
            const uint32_t h = call(fx, 8, {0, 0}); call(fx, 4, {h, out + 20});
            printf("%s: %u parametros, %u tecnicas; 1o parametro %s classe %u tipo %u\n", n.c_str(), npar, ntech, (const char *)M + rd32(out + 20), rd32(out + 28), rd32(out + 32));
        }
        ++ok;
    }
    printf("efeitos ok %d, falhas %d, passadas executadas %d\n", ok, bad, passes);
    return 0;
}
