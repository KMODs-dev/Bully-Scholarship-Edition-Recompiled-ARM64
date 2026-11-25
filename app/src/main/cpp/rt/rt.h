// Interface interna do runtime do Bully PC
#pragma once
#include <stdint.h>
#include <stdarg.h>
#include <string>

// mapa da janela de 4 GB (enderecos do jogo)
#define IMAGE_BASE      0x00400000u
#define STACK_TOP       0x3F000000u   // pilha da thread principal (cresce para baixo)
#define STACK_SIZE      0x01000000u
#define HEAP_BASE       0x40000000u
#define HEAP_END        0xE0000000u
#define MISC_BASE       0xE0000000u   // estruturas do "sistema" (PEB, ambiente, linha de comando...)
#define THUNK_BASE      0xFF000000u   // enderecos falsos dos imports (16 bytes cada)
#define DYN_THUNK_BASE  0xFF080000u   // funcoes criadas em tempo de execucao (GetProcAddress, vtables de COM)

struct Cpu;
void rt_log(const char *fmt, ...);
[[noreturn]] void rt_fatal(const char *fmt, ...);
bool rt_mem_init();
bool rt_load_pe(const char *path);
uint32_t rt_entry();
uint32_t rt_alloc(uint32_t n, bool zero);
void rt_free(uint32_t a);
uint32_t rt_size(uint32_t a);
uint32_t rt_realloc(uint32_t a, uint32_t n);

// imports
void rt_call_import(Cpu &c, int id, const char *name);
void rt_dyn_thunk(Cpu &c, uint32_t idx);
// cria um thunk dinamico: fn recebe (c, args) e devolve eax; nargs = argumentos stdcall (o thunk tira da pilha)
typedef uint32_t (*NativeFn)(Cpu &c, const uint32_t *a);
uint32_t rt_make_thunk(const char *name, int nargs, NativeFn fn);
// tabelas de importacao de outros arquivos (d3d9.cpp, d3dx9.cpp): nome sem DLL ou "dll!nome"
struct RtImport { const char *name; int nargs; NativeFn fn; };
extern const RtImport g_d3d9_imports[]; extern const int g_d3d9_nimports;
extern const RtImport g_d3dx9_imports[]; extern const int g_d3dx9_nimports;
extern const RtImport g_dinput8_imports[]; extern const int g_dinput8_nimports;
extern std::string g_files_dir;   // pasta de dados do app (shaders compilados etc.)
void rt_win32_init(const char *game_dir);
std::string rt_host_path(uint32_t guest_str);   // caminho do Windows -> caminho no aparelho
