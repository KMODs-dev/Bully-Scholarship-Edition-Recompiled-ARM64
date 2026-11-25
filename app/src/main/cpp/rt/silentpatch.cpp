// Correcoes do SilentPatchBully (build 3, CookiePLMonster, codigo aberto) refeitas para o port. O SilentPatch e uma
// DLL x86 que reescreve o Bully.exe 1.200 na memoria; aqui as correcoes que sao so bytes entram no exe antes da
// recompilacao (tools/sp_patch.py) e as que precisam de codigo novo estao neste arquivo:
//  - pools (CBasePool::GetSlotWithLinked): o original lia a lista de livres fora do limite e podia devolver um
//    objeto ja liberado (crash ao andar pela cidade);
//  - bancos de som SEA: o buffer era alocado e nunca liberado (vazamento que acaba em falta de memoria em sessoes
//    longas). Agora vai para o XACT com MANAGEDATA e rt/xact3.cpp o libera quando o banco e destruido;
//  - limite de FPS configuravel (30 ou 60, opcao do launcher).
// Ficaram de fora: correcoes de saida do jogo (o Android mata o processo), o laco de espera ocupada do limitador
// (o Sleep daqui ja e preciso e o laco gastaria bateria) e as que tratam leitura assincrona (aqui ela e sincrona).
#include "x86rt.h"
#include <initializer_list>

uint32_t rt_alloc(uint32_t n, bool zero);
void rt_free(uint32_t a);
void rt_override(uint32_t va, Fn fn);

static inline uint32_t arg(Cpu &c, int i) { return rd32(c.r[4] + 4 + 4 * i); }

// chama uma funcao do jogo a partir do codigo nativo (cdecl, stdcall ou thiscall: a pilha volta ao que era)
static uint32_t gcall(Cpu &c, uint32_t fn, uint32_t ecx, std::initializer_list<uint32_t> args) {
    const uint32_t sp = c.r[4];
    const uint32_t *v = args.begin();
    for (size_t i = args.size(); i-- > 0;) { c.r[4] -= 4; wr32(c.r[4], v[i]); }
    c.r[4] -= 4; wr32(c.r[4], 0x5AE590u);
    c.r[1] = ecx;
    x86_call(c, fn);
    const uint32_t r = c.r[0];
    c.r[4] = sp;
    return r;
}

// ---------------- limite de FPS
static uint32_t g_fps_limit = 30;   // o jogo usa 31 (o Sleep do Windows atrasava); o SilentPatch usa 30
uint32_t rt_fps_limit() { return g_fps_limit; }
void rt_set_fps_limit(uint32_t fps) { g_fps_limit = fps ? fps : 30; }

// ---------------- pools
static uint32_t pool_slot(uint32_t pool, int32_t idx, bool chk) {
    for (int depth = 0; pool && depth < 32; ++depth) {
        const int32_t n = (int32_t)rd32(pool + 8);
        if (idx < n) {
            uint32_t slot = rd32(pool) + (uint32_t)idx * rd32(pool + 0xC);
            if (chk && (rd8(rd32(pool + 4) + (uint32_t)idx) & 0x80)) slot = 0;   // so olha a lista dentro do limite
            return slot;
        }
        idx -= n; chk = true; pool = rd32(pool + 0x10);   // pool ligada
    }
    return 0;
}
void sp_pool_slot(Cpu &c) {     // 0x435BD0 thiscall (indice, checar livre), ret 8
    c.r[0] = pool_slot(c.r[1], (int32_t)arg(c, 0), (arg(c, 1) & 0xFF) != 0);
    c.r[4] += 12;
}
void sp_pool_slot_w(Cpu &c) {   // 0x436B90 thiscall (indice), ret 4; tambem chamada pelos 29 trechos trocados
    c.r[0] = pool_slot(c.r[1], (int32_t)arg(c, 0), true);
    c.r[4] += 8;
}

// ---------------- bancos de som SEA
static void sp_alloc(Cpu &c) { c.r[0] = rt_alloc(arg(c, 0), false); c.r[4] += 4; }   // cdecl (tamanho)
static void sp_free(Cpu &c) { rt_free(arg(c, 0)); c.r[4] += 4; }                    // cdecl (ptr)
static void sp_sbcmd(Cpu &c) {   // MDXactCreateSoundBankCommand(buffer, tamanho, flags, attr): flags = MANAGEDATA
    wr32(c.r[4] + 12, 1);
    x86_call(c, 0x5AF150);
}
// MDXact_Manager_Internal_CreateSoundBank / CreateInMemoryWaveBank (id, buffer, tamanho, flags, attr), cdecl.
// O original ignorava as flags do banco de som e, na falha, liberava com o free do jogo um buffer que agora e do runtime.
static void create_bank(Cpu &c, bool wave) {
    const uint32_t id = arg(c, 0), buf = arg(c, 1), size = arg(c, 2), flags = arg(c, 3), attr = arg(c, 4);
    const uint32_t eng = rd32(0xCFACE0);
    if (eng) {
        const uint32_t save = c.r[4];
        c.r[4] -= 4; const uint32_t out = c.r[4]; wr32(out, 0);
        const uint32_t fn = rd32(rd32(eng) + (wave ? 0x28 : 0x24));
        const uint32_t hr = gcall(c, fn, c.r[1], {eng, buf, size, flags, attr, out});
        if ((int32_t)hr >= 0) {
            const uint32_t bank = rd32(out);
            gcall(c, wave ? 0x5AD810 : 0x5AD8E0, 0, {bank});   // registra o banco (contagem de referencias)
            gcall(c, wave ? 0x5AD4D0 : 0x5AD530, 0, {id});
            uint32_t obj = gcall(c, 0x5EEAA0, 0, {wave ? 12u : 24u});
            if (obj) {
                if (wave) gcall(c, 0x5B0660, obj, {bank, 0, id});   // MDXact_WaveBank(banco, false, id)
                else gcall(c, 0x5B04E0, obj, {bank, id});           // MDXact_SoundBank(banco, id)
            }
            gcall(c, 0x8A5140, rd32(wave ? 0xCFACE4 : 0xCFACE8), {id, obj});   // NiTMap<int, banco>::SetAt
        } else {
            if (buf) { if (flags & 1) rt_free(buf); else gcall(c, 0x5EEAB0, 0, {buf}); }
            gcall(c, wave ? 0x5AD5F0 : 0x5AD660, 0, {id});
        }
        c.r[4] = save;
    }
    c.r[4] += 4;
}
void sp_create_soundbank(Cpu &c) { create_bank(c, false); }
void sp_create_wavebank(Cpu &c) { create_bank(c, true); }

void rt_silentpatch_init() {
    rt_override(0xFE000000u, sp_alloc);
    rt_override(0xFE000010u, sp_free);
    rt_override(0xFE000020u, sp_sbcmd);
}
