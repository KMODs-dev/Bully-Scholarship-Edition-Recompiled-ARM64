// Tradutor de bytecode de shader D3D9 (vs/ps 2.0 a 3.0) para GLSL ES 3.00. Nao depende de GL (testavel no PC).
// A traducao fica em partes; o programa final (VS+PS) e montado na ligacao, porque as variaveis que passam do VS
// para o PS precisam existir dos dois lados com o mesmo nome (V_<semantica>, ex.: V_TEXCOORD0).
#pragma once
#include <stdint.h>
#include <string>
#include <vector>

struct SmIO { uint32_t usage, index, reg; };
struct SmShader {
    bool ok = false, pixel = false; int major = 0, minor = 0; std::string err;
    std::string globals, protos, funcs, body;
    std::vector<SmIO> inputs;                                   // VS: atributos (registrador v# + semantica)
    std::vector<std::string> ps_inputs;                         // PS: semanticas lidas (ex.: "TEXCOORD0")
    std::vector<std::pair<std::string, std::string>> outputs;   // VS: (semantica, variavel); "POSITION0" = posicao
    int sampler_type[20] = {0};                                 // 2 = 2D, 3 = cubo, 4 = volume (16..19 = samplers do VS)
    int ncolor_out = 0; bool depth_out = false;
};
bool sm_translate(const uint32_t *code, uint32_t ndw, SmShader &out);
// color_bgra: bits dos registradores de entrada do VS cujo atributo e D3DCOLOR (precisa trocar R e B)
std::string sm_link_vs(const SmShader &vs, const std::vector<std::string> &ps_inputs, uint32_t color_bgra);
std::string sm_link_ps(const SmShader &ps, uint32_t shadow = 0);   // shadow: samplers 2D ligados a texturas de profundidade
const char *sm_usage_name(uint32_t usage);
