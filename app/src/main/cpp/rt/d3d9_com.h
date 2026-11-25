// Objetos COM falsos na memoria do jogo (D3D9, D3DX, DInput...).
// Layout de cada objeto na janela de 4 GB: [0] ponteiro da vtable, [4] id do objeto nativo, [8] contador de referencias.
// A vtable e um vetor de enderecos de thunks (rt_make_thunk); cada metodo e stdcall com "this" como 1o argumento.
#pragma once
#include <stdint.h>
#include "rt.h"

struct ComMethod { const char *name; int nargs; NativeFn fn; };   // nargs SEM contar o this

// cria (uma vez) a vtable para uma interface; devolve o endereco da vtable no jogo
uint32_t com_vtable(const char *iface, const ComMethod *m, int n);
// cria um objeto do jogo com essa vtable, ligado ao objeto nativo "host"
uint32_t com_new(uint32_t vtable, void *host);
void *com_host(uint32_t obj);            // objeto nativo de um objeto do jogo
uint32_t com_addref(uint32_t obj);
uint32_t com_release(uint32_t obj);      // devolve o novo contador (0 = destruido; o nativo e liberado por quem chamou)

#define S_OK_ 0u
#define E_FAIL_ 0x80004005u
#define E_NOTIMPL_ 0x80004001u
#define E_NOINTERFACE_ 0x80004002u
#define D3DERR_INVALIDCALL_ 0x8876086Cu
#define D3DERR_NOTAVAILABLE_ 0x8876086Au
