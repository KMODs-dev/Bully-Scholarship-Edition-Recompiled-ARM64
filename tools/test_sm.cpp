// Teste do tradutor no PC: traduz cada shader (.bin) e compila/liga no GLES 3.2 do Mesa (llvmpipe, EGL sem janela).
#include "rt/sm_translate.h"
#include "SDL_egl.h"
#include "SDL_opengles2.h"
#include <dirent.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

static std::vector<uint32_t> load(const std::string &p) {
    std::vector<uint32_t> v; FILE *f = fopen(p.c_str(), "rb"); if (!f) return v;
    fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET); v.resize(n / 4); fread(v.data(), 4, v.size(), f); fclose(f); return v;
}
static bool egl_init() {
    PFNEGLGETPLATFORMDISPLAYEXTPROC gpd = (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
    EGLDisplay d = gpd(0x31DD, EGL_DEFAULT_DISPLAY, NULL); EGLint a, b;
    if (!eglInitialize(d, &a, &b)) return false;
    eglBindAPI(EGL_OPENGL_ES_API);
    EGLint cx[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    EGLContext c = eglCreateContext(d, NULL, EGL_NO_CONTEXT, cx);
    return c && eglMakeCurrent(d, EGL_NO_SURFACE, EGL_NO_SURFACE, c);
}
static GLuint compile(GLenum t, const std::string &s, std::string &log) {
    GLuint h = glCreateShader(t); const char *p = s.c_str(); glShaderSource(h, 1, &p, 0); glCompileShader(h);
    GLint ok; glGetShaderiv(h, GL_COMPILE_STATUS, &ok);
    if (!ok) { char b[4096]; glGetShaderInfoLog(h, sizeof b, 0, b); log = b; glDeleteShader(h); return 0; }
    return h;
}
int main(int argc, char **argv) {
    if (!egl_init()) { printf("sem EGL\n"); return 1; }
    const std::string dir = argv[1];
    std::map<std::string, SmShader> sh; int tr_fail = 0, c_fail = 0, ok = 0, shown = 0;
    DIR *dd = opendir(dir.c_str()); struct dirent *de;
    while ((de = readdir(dd))) {
        std::string n = de->d_name; if (n.size() < 5 || n.substr(n.size() - 4) != ".bin") continue;
        std::vector<uint32_t> code = load(dir + "/" + n);
        SmShader s;
        if (!sm_translate(code.data(), (uint32_t)code.size(), s)) { ++tr_fail; if (shown++ < 10) printf("TRADUCAO %s: %s\n", n.c_str(), s.err.c_str()); continue; }
        std::string src, log;
        if (s.pixel) src = sm_link_ps(s);
        else { std::vector<std::string> outs; for (auto &o : s.outputs) if (o.first != "POSITION0" && o.first != "PSIZE0") outs.push_back(o.first); src = sm_link_vs(s, outs, 0); }
        GLuint h = compile(s.pixel ? GL_FRAGMENT_SHADER : GL_VERTEX_SHADER, src, log);
        if (!h) { ++c_fail; if (shown++ < 10) { printf("COMPILACAO %s:\n%s\n", n.c_str(), log.c_str()); FILE *f = fopen(("/tmp/claude-0/-home-claude/f174b2bc-b4b7-5724-a62f-868da52ebe4d/scratchpad/falha_" + n + ".glsl").c_str(), "w"); fputs(src.c_str(), f); fclose(f); } continue; }
        glDeleteShader(h); ++ok;
        sh[n.substr(0, n.size() - 4)] = s;
    }
    printf("shaders: %d ok, %d falha de traducao, %d falha de compilacao\n", ok, tr_fail, c_fail);
    // pares (ligacao VS+PS)
    FILE *pf = fopen((dir + "/pares.txt").c_str(), "r"); char a[64], b[64]; int lok = 0, lf = 0;
    while (pf && fscanf(pf, "%63s %63s", a, b) == 2) {
        if (!sh.count(a) || !sh.count(b)) continue;
        const SmShader &v = sh[a], &p = sh[b]; std::string log;
        GLuint hv = compile(GL_VERTEX_SHADER, sm_link_vs(v, p.ps_inputs, 0), log), hp = compile(GL_FRAGMENT_SHADER, sm_link_ps(p), log);
        if (!hv || !hp) { ++lf; continue; }
        GLuint pr = glCreateProgram(); glAttachShader(pr, hv); glAttachShader(pr, hp); glLinkProgram(pr);
        GLint okl; glGetProgramiv(pr, GL_LINK_STATUS, &okl);
        if (okl) ++lok; else { ++lf; if (lf < 4) { char lg[2048]; glGetProgramInfoLog(pr, sizeof lg, 0, lg); printf("LIGACAO %s %s: %s\n", a, b, lg); } }
        glDeleteProgram(pr); glDeleteShader(hv); glDeleteShader(hp);
    }
    printf("pares: %d ligados, %d falhas\n", lok, lf);
    return 0;
}
