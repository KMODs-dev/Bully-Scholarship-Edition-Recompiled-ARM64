// Controles por toque + controle fisico -> XInput (ver input.h).
#include "input.h"
#include "gl_inc.h"
#include <math.h>
#include <string.h>
#include <mutex>
#include <map>
#include <vector>
#include <string>
#include <stdio.h>

enum : uint16_t { XB_UP = 0x1, XB_DOWN = 0x2, XB_LEFT = 0x4, XB_RIGHT = 0x8, XB_START = 0x10, XB_BACK = 0x20, XB_L3 = 0x40, XB_R3 = 0x80,
                  XB_LB = 0x100, XB_RB = 0x200, XB_A = 0x1000, XB_B = 0x2000, XB_X = 0x4000, XB_Y = 0x8000 };
enum { BT_LT = 0x10000, BT_RT = 0x20000 };   // gatilhos (fora dos bits do XInput)

struct Btn { const char *label; uint32_t bit; float x, y, r; bool dpad; };
enum FingerKind { F_NONE, F_BTN, F_LSTICK, F_RSTICK };
struct Finger { FingerKind kind = F_NONE; int btn = -1; float x0 = 0, y0 = 0, x = 0, y = 0; };

static std::mutex g_mtx;
static int g_w = 1612, g_h = 720;
static std::vector<Btn> g_btns;
static float g_ls_x, g_ls_y, g_ls_r, g_s;
static std::map<long long, Finger> g_fingers;
static bool g_pad = false; static uint16_t g_pad_b = 0; static int16_t g_pad_ax[4] = {0}; static uint8_t g_pad_lt = 0, g_pad_rt = 0;
static uint32_t g_packet = 0;
static float g_fps = 0;
void input_set_fps(float f) { g_fps = f; }
static bool g_opt_fps = true, g_opt_touch = true;
void input_set_options(bool show_fps, bool touch_controls) { g_opt_fps = show_fps; g_opt_touch = touch_controls; }

static void layout() {
    const float w = (float)g_w, h = (float)g_h, s = h / 720.0f; g_s = s;
    g_btns.clear();
    const float fx = w - 170 * s, fy = h - 200 * s, fo = 78 * s, fr = 46 * s;
    g_btns.push_back({"A", XB_A, fx, fy + fo, fr, false});
    g_btns.push_back({"B", XB_B, fx + fo, fy, fr, false});
    g_btns.push_back({"X", XB_X, fx - fo, fy, fr, false});
    g_btns.push_back({"Y", XB_Y, fx, fy - fo, fr, false});
    g_btns.push_back({"LT", BT_LT, 80 * s, 70 * s, 44 * s, false});
    g_btns.push_back({"LB", XB_LB, 200 * s, 70 * s, 44 * s, false});
    g_btns.push_back({"RB", XB_RB, w - 200 * s, 70 * s, 44 * s, false});
    g_btns.push_back({"RT", BT_RT, w - 80 * s, 70 * s, 44 * s, false});
    g_btns.push_back({"BK", XB_BACK, w * 0.5f - 80 * s, 38 * s, 32 * s, false});
    g_btns.push_back({"ST", XB_START, w * 0.5f + 80 * s, 38 * s, 32 * s, false});
    const float dx = 150 * s, dy = 250 * s, dof = 58 * s, dr = 36 * s;
    g_btns.push_back({"^", XB_UP, dx, dy - dof, dr, true});
    g_btns.push_back({"v", XB_DOWN, dx, dy + dof, dr, true});
    g_btns.push_back({"<", XB_LEFT, dx - dof, dy, dr, true});
    g_btns.push_back({">", XB_RIGHT, dx + dof, dy, dr, true});
    g_btns.push_back({"L3", XB_L3, 330 * s, h - 70 * s, 32 * s, false});
    g_btns.push_back({"R3", XB_R3, w - 330 * s, h - 70 * s, 32 * s, false});
    g_ls_x = 170 * s; g_ls_y = h - 190 * s; g_ls_r = 110 * s;
}
void input_set_window(int w, int h) { std::lock_guard<std::mutex> lk(g_mtx); if (w != g_w || h != g_h || g_btns.empty()) { g_w = w; g_h = h; layout(); } }
static int hit(float x, float y, bool dpad_only) {
    int best = -1; float bd = 1e9f;
    for (size_t i = 0; i < g_btns.size(); ++i) {
        const Btn &b = g_btns[i]; if (dpad_only && !b.dpad) continue;
        const float d = hypotf(x - b.x, y - b.y);
        if (d < b.r * 1.35f && d < bd) { bd = d; best = (int)i; }
    }
    return best;
}
void input_touch_down(long long id, float x, float y) {
    if (!g_opt_touch) return;
    std::lock_guard<std::mutex> lk(g_mtx); if (g_btns.empty()) layout();
    Finger f; f.x0 = f.x = x; f.y0 = f.y = y;
    const int b = hit(x, y, false);
    if (b >= 0) { f.kind = F_BTN; f.btn = b; }
    else if (x < g_w * 0.4f && y > g_h * 0.4f) f.kind = F_LSTICK;
    else if (x > g_w * 0.5f) f.kind = F_RSTICK;
    g_fingers[id] = f; ++g_packet;
}
void input_touch_move(long long id, float x, float y) {
    std::lock_guard<std::mutex> lk(g_mtx);
    auto it = g_fingers.find(id); if (it == g_fingers.end()) return;
    Finger &f = it->second; f.x = x; f.y = y;
    if (f.kind == F_BTN && g_btns[f.btn].dpad) { const int b = hit(x, y, true); if (b >= 0) f.btn = b; }   // desliza no direcional
    ++g_packet;
}
void input_touch_up(long long id) { std::lock_guard<std::mutex> lk(g_mtx); g_fingers.erase(id); ++g_packet; }
void input_set_pad(bool connected, uint16_t buttons, int16_t lx, int16_t ly, int16_t rx, int16_t ry, uint8_t lt, uint8_t rt) {
    std::lock_guard<std::mutex> lk(g_mtx);
    if (connected != g_pad || buttons != g_pad_b || lx != g_pad_ax[0] || ly != g_pad_ax[1] || rx != g_pad_ax[2] || ry != g_pad_ax[3] || lt != g_pad_lt || rt != g_pad_rt) ++g_packet;
    g_pad = connected; g_pad_b = buttons; g_pad_ax[0] = lx; g_pad_ax[1] = ly; g_pad_ax[2] = rx; g_pad_ax[3] = ry; g_pad_lt = lt; g_pad_rt = rt;
}
static int16_t ax(float v) { if (v > 1) v = 1; if (v < -1) v = -1; return (int16_t)lrintf(v * 32767.0f); }
static int16_t maxabs(int16_t a, int16_t b) { return abs(a) >= abs(b) ? a : b; }
bool input_get_xinput(uint8_t *st) {
    std::lock_guard<std::mutex> lk(g_mtx);
    uint32_t b = 0; int16_t lx = 0, ly = 0, rx = 0, ry = 0;
    for (auto &kv : g_fingers) {
        const Finger &f = kv.second;
        if (f.kind == F_BTN) b |= g_btns[f.btn].bit;
        else if (f.kind == F_LSTICK) { lx = ax((f.x - g_ls_x) / g_ls_r); ly = ax(-(f.y - g_ls_y) / g_ls_r); }
        else if (f.kind == F_RSTICK) { rx = ax((f.x - f.x0) / (90 * g_s)); ry = ax(-(f.y - f.y0) / (90 * g_s)); }
    }
    uint8_t lt = (b & BT_LT) ? 255 : 0, rt = (b & BT_RT) ? 255 : 0;
    uint16_t wb = (uint16_t)(b & 0xFFFF);
    if (g_pad) {
        wb |= g_pad_b; lx = maxabs(lx, g_pad_ax[0]); ly = maxabs(ly, g_pad_ax[1]); rx = maxabs(rx, g_pad_ax[2]); ry = maxabs(ry, g_pad_ax[3]);
        if (g_pad_lt > lt) lt = g_pad_lt; if (g_pad_rt > rt) rt = g_pad_rt;
    }
    memcpy(st, &g_packet, 4); memcpy(st + 4, &wb, 2); st[6] = lt; st[7] = rt;
    memcpy(st + 8, &lx, 2); memcpy(st + 10, &ly, 2); memcpy(st + 12, &rx, 2); memcpy(st + 14, &ry, 2);
    return true;   // sempre "conectado": os controles na tela contam como controle
}

// ================================================================ desenho dos controles na tela
static const char *kVS = "#version 300 es\nlayout(location=0) in vec2 p; layout(location=1) in vec2 t; layout(location=2) in vec4 c;\n"
                         "uniform vec2 u_sz; out vec2 vt; out vec4 vc;\n"
                         "void main(){ vt=t; vc=c; gl_Position=vec4(p.x/u_sz.x*2.0-1.0, 1.0-p.y/u_sz.y*2.0, 0.0, 1.0); }\n";
static const char *kFS = "#version 300 es\nprecision mediump float; in vec2 vt; in vec4 vc; uniform sampler2D u_t; out vec4 o;\n"
                         "void main(){ o = texture(u_t, vt) * vc; }\n";
// fonte 5x7 (so os caracteres usados)
struct Glyph { char ch; uint8_t rows[7]; };
static const Glyph kFont[] = {
    {'A', {0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11}}, {'B', {0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E}},
    {'X', {0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11}}, {'Y', {0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x04}},
    {'L', {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F}}, {'R', {0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11}},
    {'T', {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}}, {'S', {0x0F, 0x10, 0x10, 0x0E, 0x01, 0x01, 0x1E}},
    {'K', {0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11}}, {'3', {0x1E, 0x01, 0x01, 0x0E, 0x01, 0x01, 0x1E}},
    {'^', {0x04, 0x0E, 0x1F, 0x04, 0x04, 0x04, 0x04}}, {'v', {0x04, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x04}},
    {'0', {0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E}}, {'1', {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E}},
    {'2', {0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F}}, {'4', {0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02}},
    {'5', {0x1F, 0x10, 0x1E, 0x01, 0x01, 0x11, 0x0E}}, {'6', {0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E}},
    {'7', {0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08}}, {'8', {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E}},
    {'9', {0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C}}, {'F', {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10}},
    {'P', {0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10}}, {' ', {0, 0, 0, 0, 0, 0, 0}},
    {'<', {0x02, 0x06, 0x0E, 0x1E, 0x0E, 0x06, 0x02}}, {'>', {0x08, 0x0C, 0x0E, 0x0F, 0x0E, 0x0C, 0x08}},
};
static const int NG = sizeof kFont / sizeof kFont[0];
static GLuint g_prog = 0, g_tex = 0, g_vbo = 0, g_vao = 0; static GLint g_usz = -1;
struct OV { float x, y, u, v; uint8_t c[4]; };
static std::vector<OV> g_v;
// atlas 256x64: celula 0 (0..63) = circulo com borda; celulas de 32x32 a partir de x=64 = letras
static void build_atlas() {
    std::vector<uint8_t> px(256 * 128 * 4, 0);
    for (int y = 0; y < 64; ++y) for (int x = 0; x < 64; ++x) {
        const float d = hypotf(x + 0.5f - 32, y + 0.5f - 32);
        float a = 0;
        if (d < 31) a = 0.35f;                                       // preenchimento
        if (d > 27 && d < 31.5f) a = 0.9f;                           // borda
        if (d >= 31.5f) a = 0;
        uint8_t *p = &px[4 * (y * 256 + x)]; p[0] = p[1] = p[2] = 255; p[3] = (uint8_t)(a * 255);
    }
    for (int g = 0; g < NG; ++g) {
        const int cx = 64 + (g % 6) * 32, cy = (g / 6) * 21;
        (void)0;
        // letra lisa: os pontos da grade 5x7 viram tracos arredondados (pincel redondo entre pontos vizinhos), com borda suave
        auto on = [&](int r, int c) { return r >= 0 && r < 7 && c >= 0 && c < 5 && (kFont[g].rows[r] & (0x10 >> c)); };
        std::vector<float> seg;   // x0 y0 x1 y1
        for (int r = 0; r < 7; ++r) for (int c = 0; c < 5; ++c) if (on(r, c)) {
            const float x0 = cx + 4 + c * 3 + 1.5f, y0 = cy + r * 3 + 1.5f;
            seg.insert(seg.end(), {x0, y0, x0, y0});
            const int nb[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
            for (auto &d : nb) if (on(r + d[0], c + d[1])) {
                if (d[0] == 1 && d[1] != 0 && (on(r + 1, c) || on(r, c + d[1]))) continue;   // diagonal so quando nao ha caminho reto
                seg.insert(seg.end(), {x0, y0, x0 + d[1] * 3.0f, y0 + d[0] * 3.0f});
            }
        }
        for (int Y = cy; Y < cy + 21 && Y < 128; ++Y) for (int X = cx; X < cx + 32 && X < 256; ++X) {
            float best = 1e9f;
            for (size_t k = 0; k < seg.size(); k += 4) {
                const float ax = seg[k], ay = seg[k + 1], bx = seg[k + 2], by = seg[k + 3], px_ = X + 0.5f, py_ = Y + 0.5f;
                const float vx = bx - ax, vy = by - ay, l2 = vx * vx + vy * vy;
                float t = l2 > 0 ? ((px_ - ax) * vx + (py_ - ay) * vy) / l2 : 0; t = t < 0 ? 0 : t > 1 ? 1 : t;
                const float d = hypotf(px_ - ax - t * vx, py_ - ay - t * vy); if (d < best) best = d;
            }
            float a = 1.9f - best; a = a < 0 ? 0 : a > 1 ? 1 : a;
            if (a > 0) { uint8_t *p = &px[4 * (Y * 256 + X)]; p[0] = p[1] = p[2] = 255; if (a * 255 > p[3]) p[3] = (uint8_t)(a * 255); }
        }
    }
    glGenTextures(1, &g_tex); glBindTexture(GL_TEXTURE_2D, g_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, px.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
static void quad(float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, const uint8_t *c) {
    const OV a = {x0, y0, u0, v0, {c[0], c[1], c[2], c[3]}}, b = {x1, y0, u1, v0, {c[0], c[1], c[2], c[3]}},
             d = {x0, y1, u0, v1, {c[0], c[1], c[2], c[3]}}, e = {x1, y1, u1, v1, {c[0], c[1], c[2], c[3]}};
    g_v.push_back(a); g_v.push_back(b); g_v.push_back(d); g_v.push_back(b); g_v.push_back(e); g_v.push_back(d);
}
static void circle(float x, float y, float r, const uint8_t *c) { quad(x - r, y - r, x + r, y + r, 0, 0, 64 / 256.0f, 64 / 128.0f, c); }
static void text(float x, float y, float size, const char *s, const uint8_t *c) {
    const int n = (int)strlen(s); const float cw = size * 0.75f;
    float px = x - cw * n * 0.5f;
    for (int i = 0; i < n; ++i, px += cw) {
        if (s[i] == ' ') continue;
        int g = -1; for (int k = 0; k < NG; ++k) if (kFont[k].ch == s[i]) g = k;
        if (g < 0) continue;
        const float cx = 64 + (g % 6) * 32, cy = (g / 6) * 21;
        quad(px, y - size * 0.5f, px + cw, y + size * 0.5f, (cx + 2) / 256.0f, (cy - 0.5f) / 128.0f, (cx + 22) / 256.0f, (cy + 21.5f) / 128.0f, c);
    }
}
void input_overlay_draw(int w, int h) {
    input_set_window(w, h);
    if (!g_prog) {
        auto sh = [](GLenum t, const char *src) { GLuint s = glCreateShader(t); glShaderSource(s, 1, &src, nullptr); glCompileShader(s); return s; };
        g_prog = glCreateProgram(); GLuint a = sh(GL_VERTEX_SHADER, kVS), b = sh(GL_FRAGMENT_SHADER, kFS);
        glAttachShader(g_prog, a); glAttachShader(g_prog, b); glLinkProgram(g_prog); glDeleteShader(a); glDeleteShader(b);
        g_usz = glGetUniformLocation(g_prog, "u_sz");
        glUseProgram(g_prog); glUniform1i(glGetUniformLocation(g_prog, "u_t"), 0);
        build_atlas(); glGenBuffers(1, &g_vbo); glGenVertexArrays(1, &g_vao);
    }
    g_v.clear();
    {
        std::lock_guard<std::mutex> lk(g_mtx);
        if (g_opt_fps) { char b[16]; snprintf(b, sizeof b, "FPS %d", (int)(g_fps + 0.5f)); const uint8_t yel[4] = {255, 230, 60, 255}; text(70 * g_s, h - 22 * g_s, 26 * g_s, b, yel); }
        if (!g_pad && g_opt_touch) {
        uint32_t pressed = 0; float kx = g_ls_x, ky = g_ls_y; bool rs = false; float rx0 = 0, ry0 = 0, rx = 0, ry = 0;
        for (auto &kv : g_fingers) {
            const Finger &f = kv.second;
            if (f.kind == F_BTN) pressed |= 1u << f.btn;
            else if (f.kind == F_LSTICK) { float dx = f.x - g_ls_x, dy = f.y - g_ls_y; const float d = hypotf(dx, dy); if (d > g_ls_r) { dx *= g_ls_r / d; dy *= g_ls_r / d; } kx = g_ls_x + dx; ky = g_ls_y + dy; }
            else if (f.kind == F_RSTICK) { rs = true; rx0 = f.x0; ry0 = f.y0; rx = f.x; ry = f.y; }
        }
        const uint8_t base[4] = {255, 255, 255, 110}, hi[4] = {255, 210, 80, 200}, lbl[4] = {255, 255, 255, 230};
        circle(g_ls_x, g_ls_y, g_ls_r, base); circle(kx, ky, g_ls_r * 0.45f, hi);
        if (rs) { circle(rx0, ry0, 90 * g_s, base); circle(rx, ry, 40 * g_s, hi); }
        for (size_t i = 0; i < g_btns.size(); ++i) {
            const Btn &b = g_btns[i]; const bool on = (pressed >> i) & 1;
            // cores dos botoes do controle de Xbox 360
            const char *L = b.label; uint8_t col[4] = {base[0], base[1], base[2], base[3]};
            if (!strcmp(L, "A")) { col[0] = 80; col[1] = 190; col[2] = 60; col[3] = 170; }
            else if (!strcmp(L, "B")) { col[0] = 225; col[1] = 55; col[2] = 50; col[3] = 170; }
            else if (!strcmp(L, "X")) { col[0] = 40; col[1] = 120; col[2] = 230; col[3] = 170; }
            else if (!strcmp(L, "Y")) { col[0] = 240; col[1] = 195; col[2] = 30; col[3] = 170; }
            circle(b.x, b.y, b.r, on ? hi : col);
            text(b.x, b.y, b.r * (strlen(b.label) > 1 ? 0.7f : 0.9f), b.label, lbl);
        }
        }
    }
    glViewport(0, 0, w, h);   // desenha no framebuffer de desenho atual (a janela, no Present) glDisable(GL_DEPTH_TEST); glDisable(GL_CULL_FACE); glDisable(GL_STENCIL_TEST); glDisable(GL_SCISSOR_TEST);
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glBlendEquation(GL_FUNC_ADD); glColorMask(1, 1, 1, 1);
    glUseProgram(g_prog); glUniform2f(g_usz, (float)w, (float)h);
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, g_tex); glBindSampler(0, 0);
    glBindVertexArray(g_vao);
    glBindBuffer(GL_ARRAY_BUFFER, g_vbo); glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(g_v.size() * sizeof(OV)), g_v.data(), GL_STREAM_DRAW);
    glEnableVertexAttribArray(0); glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(OV), (void *)0);
    glEnableVertexAttribArray(1); glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(OV), (void *)8);
    glEnableVertexAttribArray(2); glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(OV), (void *)16);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)g_v.size());
    glBindVertexArray(0);
}
