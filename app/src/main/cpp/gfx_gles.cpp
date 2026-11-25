// Ligacao do backend GLES (rt/gfx_gl.cpp) com a janela do SDL no Android.
// O contexto GL e criado no main e solto; a thread do jogo o pega no CreateDevice (gles_hook_make_current).
#include "gfx.h"
#include "rt.h"
#include <SDL.h>

static SDL_Window *g_win = nullptr;
static SDL_GLContext g_ctx = nullptr;
static void mk_current() {
    if (SDL_GL_MakeCurrent(g_win, g_ctx)) rt_log("[gles] MakeCurrent falhou: %s\n", SDL_GetError());
    SDL_GL_SetSwapInterval(0);
}
static void win_size(int *w, int *h) { SDL_GL_GetDrawableSize(g_win, w, h); }
static void swap() { SDL_GL_SwapWindow(g_win); }
void gles_set_window(SDL_Window *w, SDL_GLContext c) {
    g_win = w; g_ctx = c;
    gles_hook_make_current = mk_current; gles_hook_window_size = win_size; gles_hook_swap = swap;
}
