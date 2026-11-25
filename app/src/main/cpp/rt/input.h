// Entrada: controle fisico (SDL) + controles na tela por toque -> estado de controle XInput que o jogo le.
#pragma once
#include <stdint.h>

// chamadas pela thread principal (eventos do SDL); coordenadas em pixels da janela
void input_set_window(int w, int h);
void input_touch_down(long long id, float x, float y);
void input_touch_move(long long id, float x, float y);
void input_touch_up(long long id);
void input_set_pad(bool connected, uint16_t buttons, int16_t lx, int16_t ly, int16_t rx, int16_t ry, uint8_t lt, uint8_t rt);
// XINPUT_STATE (16 bytes) para o jogo; devolve false se nao ha controle
bool input_get_xinput(uint8_t *state16);
// desenha os botoes na tela (thread do GL, depois do quadro do jogo)
void input_overlay_draw(int w, int h);
void input_set_fps(float fps);
// opcoes do launcher
void input_set_options(bool show_fps, bool touch_controls);
