// Funcoes do CRT do Bully (MSVC 2005, ligado estatico) executadas como codigo nativo.
// O x86rc gera f_X(c) { n_xxx(c); } para os enderecos em NATIVE; o corpo x86 original fica como f_X_x86.
// Convencao: cdecl (o chamador limpa os argumentos); args em [esp+4...]; retorno em eax (edx:eax para 64 bits);
// as funcoes _CI* recebem e devolvem o valor na pilha do x87.
#include "x86rt.h"
#include <math.h>
#include <string.h>
#include <strings.h>

static inline uint32_t arg(Cpu &c, int i) { return rd32(c.r[4] + 4 + 4 * i); }
static inline void ret_(Cpu &c) { c.r[4] += 4; }

void n_memmove(Cpu &c) {   // memcpy/memmove (o memcpy do MSVC trata sobreposicao)
    const uint32_t d = arg(c, 0), s = arg(c, 1), n = arg(c, 2);
    if (n) memmove(M + d, M + s, n);
    c.r[0] = d; ret_(c);
}
void n_memset(Cpu &c) {
    const uint32_t d = arg(c, 0), v = arg(c, 1), n = arg(c, 2);
    if (n) memset(M + d, (int)(v & 0xFF), n);
    c.r[0] = d; ret_(c);
}
void f_85BCFB_x86(Cpu &c);
void n_memcpy_s(Cpu &c) {  // memcpy_s(dst, tamanho, src, n): erros vao para o codigo original
    const uint32_t d = arg(c, 0), sz = arg(c, 1), s = arg(c, 2), n = arg(c, 3);
    if (n == 0) { c.r[0] = 0; ret_(c); return; }
    if (!d || !s || sz < n) { f_85BCFB_x86(c); return; }
    memmove(M + d, M + s, n);
    c.r[0] = 0; ret_(c);
}
void n_stricmp_ascii(Cpu &c) {   // compara sem maiusculas (so A-Z), devolve a diferenca do primeiro caractere diferente
    const uint8_t *a = M + arg(c, 0), *b = M + arg(c, 1);
    int x, y;
    do { x = *a++; y = *b++; if (x - 'A' <= 25u) x += 32; if (y - 'A' <= 25u) y += 32; } while (x && x == y);
    c.r[0] = (uint32_t)(x - y); ret_(c);
}
void n_strlen(Cpu &c) { c.r[0] = (uint32_t)strlen((const char *)M + arg(c, 0)); ret_(c); }
void n_ftol2(Cpu &c) {     // _ftol2: ST(0) -> edx:eax truncado, desempilha
    const double v = ST(0); FPOP();
    const int64_t r = (v >= -9223372036854775808.0 && v < 9223372036854775808.0) ? (int64_t)v : INT64_MIN;
    c.r[0] = (uint32_t)r; c.r[2] = (uint32_t)((uint64_t)r >> 32); ret_(c);
}
void n_CIsqrt(Cpu &c) { ST(0) = FPR(c, sqrt(ST(0))); ret_(c); }
void n_CIsin(Cpu &c) { ST(0) = sin(ST(0)); ret_(c); }
void n_CIcos(Cpu &c) { ST(0) = cos(ST(0)); ret_(c); }
void n_CIpow(Cpu &c) { const double y = ST(0), x = ST(1); FPOP(); ST(0) = pow(x, y); ret_(c); }

// ---- setjmp/longjmp (Lua: erros de script). No ponto do setjmp o codigo gerado faz um setjmp do host e registra
// o jmp_buf do jogo; o longjmp do jogo (nativo) restaura os registradores salvos pelo _setjmp3 e volta para la.
#include <setjmp.h>
#include <unordered_map>
void rt_fatal(const char *fmt, ...);
static thread_local std::unordered_map<uint32_t, jmp_buf *> t_jb;
void rt_jmp_register(uint32_t gbuf, jmp_buf *h) { t_jb[gbuf] = h; }
void n_longjmp(Cpu &c) {   // longjmp(jmp_buf, valor): layout do _setjmp3 do MSVC: ebp, ebx, edi, esi, esp, eip, registro SEH...
    const uint32_t b = arg(c, 0), v = arg(c, 1);
    auto it = t_jb.find(b);
    if (it == t_jb.end()) rt_fatal("longjmp para jmp_buf desconhecido %08X\n", b);
    c.r[5] = rd32(b); c.r[3] = rd32(b + 4); c.r[7] = rd32(b + 8); c.r[6] = rd32(b + 12);
    c.r[4] = rd32(b + 16) + 4; c.r[0] = v ? v : 1;
    wr32(FSBASE, rd32(b + 0x18));   // cadeia de excecoes (SEH) como estava no setjmp
    longjmp(*it->second, 1);
}
