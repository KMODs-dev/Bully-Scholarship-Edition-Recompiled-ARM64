// Threads do jogo: cada CreateThread ganha um Cpu e uma pilha propria na janela de 4 GB.
#include "x86rt.h"
#include "rt.h"
#include <string.h>
#include <atomic>

static std::atomic<uint32_t> g_stack_next{STACK_TOP - STACK_SIZE};
uint32_t rt_new_thread_stack() { return g_stack_next.fetch_sub(0x100000) ; }
void rt_thread_main(uint32_t start, uint32_t param, uint32_t h) {
    static Cpu cs[64]; static std::atomic<int> n{0};
    Cpu &c = cs[n++ % 64]; memset(&c, 0, sizeof c);
    c.r[4] = rt_new_thread_stack() - 16; c.fcw = 0x27F;
    c.r[4] -= 4; wr32(c.r[4], param);
    c.r[4] -= 4; wr32(c.r[4], 0);
    x86_call(c, start);
    rt_log("[bully] thread %08X terminou\n", start);
}

