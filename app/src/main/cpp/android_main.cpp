// Bully PC no Android: cria a janela (SDL + OpenGL ES 3), carrega o Bully.exe recompilado e roda o jogo numa thread.
// Pasta do jogo: <files>/Bully (a instalacao do PC copiada inteira). Log: <files>/bully-log.txt
#include <SDL.h>
#include <GLES3/gl3.h>
#include <stdio.h>
#include <string>
#include <thread>
#include <atomic>
#include "x86rt.h"
#include "rt.h"
#include "gfx.h"
#include "input.h"

void gles_set_window(SDL_Window *w, SDL_GLContext c);
extern uint32_t g_screen_w, g_screen_h;

static std::atomic<bool> g_game_done{false};
extern void (*g_fatal_hook)();
// erro fatal na thread do jogo: marca e dorme para sempre (o motivo esta no log)
// (se a thread ja tiver o contexto GL, pinta a tela de vermelho)
static void on_fatal() {
    g_game_done = true;
    glClearColor(0.35f, 0.05f, 0.05f, 1); glClear(GL_COLOR_BUFFER_BIT); SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
    for (;;) SDL_Delay(1000);
}

static void game_thread(std::string dir) {
    g_fatal_hook = on_fatal;
    std::string exe = dir + "/Bully.exe";
    if (!rt_mem_init()) { rt_log("[bully] sem janela de 4 GB\n"); g_game_done = true; return; }
    if (!rt_load_pe(exe.c_str())) { rt_log("[bully] nao achei %s (copie a instalacao do PC para a pasta Bully)\n", exe.c_str()); g_game_done = true; return; }
    rt_win32_init(dir.c_str());
    g_gfx = gfx_wrap_threaded(gfx_create_gles());   // GL roda numa thread de render propria (criada no CreateDevice)
    static Cpu c; memset(&c, 0, sizeof c);
    c.r[4] = STACK_TOP - 64; c.fcw = 0x27F;
    c.r[4] -= 4; wr32(c.r[4], 0xDEAD0000u);
    rt_log("[bully] entrada %08X\n", rt_entry());
    x86_call(c, rt_entry());
    rt_log("[bully] o jogo terminou (eax=%08X)\n", c.r[0]);
    g_game_done = true;
}

int main(int argc, char **argv) {
    // argumentos do launcher: <pasta de dados do app> <pasta do jogo> <opcoes "fps=1 toque=1">
    const std::string base = argc > 1 ? argv[1] : "/storage/emulated/0/Android/data/com.bully.pc/files";
    const std::string game_dir = argc > 2 && argv[2][0] ? argv[2] : base + "/Bully";
    const std::string opts = argc > 3 ? argv[3] : "";
    input_set_options(opts.find("fps=0") == std::string::npos, opts.find("toque=0") == std::string::npos);
    { extern bool g_tela_cheia; g_tela_cheia = opts.find("tela=1") != std::string::npos; }
    { void rt_set_fps_limit(uint32_t); rt_set_fps_limit(opts.find("limite=60") != std::string::npos ? 60 : 30); }
    const std::string log = base + "/bully-log.txt";
    freopen(log.c_str(), "w", stderr);
    setvbuf(stderr, nullptr, _IOLBF, 0);
    rt_log("[bully] Bully PC recompilado, pasta %s | jogo em %s | opcoes: %s\n", base.c_str(), game_dir.c_str(), opts.c_str());

    SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_Window *win = SDL_CreateWindow("Bully", 0, 0, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    SDL_GLContext gl = SDL_GL_CreateContext(win);
    rt_log("[bully] GL: %s | %s\n", (const char *)glGetString(GL_RENDERER), (const char *)glGetString(GL_VERSION));
    {   // tamanho real da tela: o jogo ve isso como resolucao do monitor
        int w = 1280, h = 720; SDL_GL_GetDrawableSize(win, &w, &h);
        if (w < h) std::swap(w, h);
        g_screen_w = (uint32_t)w; g_screen_h = (uint32_t)h;
        rt_log("[bully] tela %dx%d\n", w, h);
    }
    g_files_dir = base;
    gles_set_window(win, gl);

    // tela azul-escura ate o jogo desenhar; depois o contexto GL e solto para a thread do jogo pegar no CreateDevice
    glClearColor(0.05f, 0.08f, 0.2f, 1); glClear(GL_COLOR_BUFFER_BIT); SDL_GL_SwapWindow(win);
    SDL_GL_MakeCurrent(win, nullptr);
    std::thread(game_thread, game_dir).detach();

    bool run = true;
    SDL_GameController *pad = nullptr;
    for (int i = 0; i < SDL_NumJoysticks() && !pad; ++i) if (SDL_IsGameController(i)) pad = SDL_GameControllerOpen(i);
    while (run) {
        SDL_Event e;
        int dw = 1280, dh = 720; SDL_GL_GetDrawableSize(win, &dw, &dh);
        input_set_window(dw, dh);
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT: run = false; break;
            case SDL_FINGERDOWN: input_touch_down((long long)e.tfinger.fingerId, e.tfinger.x * dw, e.tfinger.y * dh); break;
            case SDL_FINGERMOTION: input_touch_move((long long)e.tfinger.fingerId, e.tfinger.x * dw, e.tfinger.y * dh); break;
            case SDL_FINGERUP: input_touch_up((long long)e.tfinger.fingerId); break;
            case SDL_CONTROLLERDEVICEADDED: if (!pad) { pad = SDL_GameControllerOpen(e.cdevice.which); rt_log("[bully] controle conectado: %s\n", pad ? SDL_GameControllerName(pad) : "?"); } break;
            case SDL_CONTROLLERDEVICEREMOVED: if (pad && e.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(pad))) { SDL_GameControllerClose(pad); pad = nullptr; rt_log("[bully] controle desconectado\n"); } break;
            }
        }
        if (pad) {   // controle fisico -> XInput
            auto B = [&](SDL_GameControllerButton b) { return SDL_GameControllerGetButton(pad, b) != 0; };
            uint16_t bt = 0;
            if (B(SDL_CONTROLLER_BUTTON_DPAD_UP)) bt |= 0x1; if (B(SDL_CONTROLLER_BUTTON_DPAD_DOWN)) bt |= 0x2;
            if (B(SDL_CONTROLLER_BUTTON_DPAD_LEFT)) bt |= 0x4; if (B(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) bt |= 0x8;
            if (B(SDL_CONTROLLER_BUTTON_START)) bt |= 0x10; if (B(SDL_CONTROLLER_BUTTON_BACK)) bt |= 0x20;
            if (B(SDL_CONTROLLER_BUTTON_LEFTSTICK)) bt |= 0x40; if (B(SDL_CONTROLLER_BUTTON_RIGHTSTICK)) bt |= 0x80;
            if (B(SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) bt |= 0x100; if (B(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) bt |= 0x200;
            if (B(SDL_CONTROLLER_BUTTON_A)) bt |= 0x1000; if (B(SDL_CONTROLLER_BUTTON_B)) bt |= 0x2000;
            if (B(SDL_CONTROLLER_BUTTON_X)) bt |= 0x4000; if (B(SDL_CONTROLLER_BUTTON_Y)) bt |= 0x8000;
            auto A = [&](SDL_GameControllerAxis x) { return (int)SDL_GameControllerGetAxis(pad, x); };
            auto inv = [](int v) { return (int16_t)(v <= -32767 ? 32767 : -v); };
            input_set_pad(true, bt, (int16_t)A(SDL_CONTROLLER_AXIS_LEFTX), inv(A(SDL_CONTROLLER_AXIS_LEFTY)), (int16_t)A(SDL_CONTROLLER_AXIS_RIGHTX),
                          inv(A(SDL_CONTROLLER_AXIS_RIGHTY)), (uint8_t)(A(SDL_CONTROLLER_AXIS_TRIGGERLEFT) >> 7), (uint8_t)(A(SDL_CONTROLLER_AXIS_TRIGGERRIGHT) >> 7));
        } else input_set_pad(false, 0, 0, 0, 0, 0, 0, 0);
        SDL_Delay(8);   // o GL e da thread do jogo; aqui so eventos e controles
    }
    SDL_GL_DeleteContext(gl);
    SDL_Quit();
    return 0;
}
