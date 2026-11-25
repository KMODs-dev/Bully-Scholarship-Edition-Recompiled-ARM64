// Teste de boot no PC: carrega o Bully.exe na janela de 4 GB e chama o ponto de entrada recompilado.
#include "x86rt.h"
#include "rt.h"
#include <stdio.h>
#include <atomic>

int main(int argc, char **argv) {
    const char *exe = argc > 1 ? argv[1] : "Bully.exe";
    const char *dir = argc > 2 ? argv[2] : ".";
    if (!rt_mem_init()) { fprintf(stderr, "sem janela de 4 GB\n"); return 1; }
    if (!rt_load_pe(exe)) { fprintf(stderr, "nao abriu %s\n", exe); return 1; }
    rt_win32_init(dir);
    static Cpu c; memset(&c, 0, sizeof c);
    c.r[4] = STACK_TOP - 64; c.fcw = 0x27F;
    c.r[4] -= 4; wr32(c.r[4], 0xDEAD0000u);   // retorno do ponto de entrada
    rt_log("[bully] entrada %08X\n", rt_entry());
    x86_call(c, rt_entry());
    rt_log("[bully] ponto de entrada retornou eax=%08X\n", c.r[0]);
    return 0;
}
