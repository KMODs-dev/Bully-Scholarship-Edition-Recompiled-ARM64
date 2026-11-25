// XACT3 (audio do Bully) sobre o FACT do FAudio (reimplementacao aberta do XACT, zlib): os .sea do Bully sao
// cabecalho + banco de som (.xsb) + banco de ondas (.xwb, MS-ADPCM); musica/ambiente/falas vem de bancos de onda
// em streaming (Audio\PLAYLIST\*.bin). Aqui so traduzimos as chamadas do jogo (ponteiros de 32 bits, structs do XACT)
// para o FACT; a mixagem roda na thread de audio do SDL (outro nucleo).
// Bancos de som, de onda, cues e ondas do XACT3 NAO sao COM (sem QueryInterface/AddRef/Release): so a vtable.
#include "x86rt.h"
#include "d3d9_com.h"
#include "d3d9_internal.h"
#include "FACT.h"
#include <stdlib.h>
#include <string.h>
#include <mutex>
#include <vector>

#define F(name) static uint32_t name(Cpu &c, const uint32_t *a)
static uint32_t Unk_QI(Cpu &, const uint32_t *a) { com_addref(a[0]); if (a[2]) wr32(a[2], a[0]); return S_OK_; }
static uint32_t Unk_AddRef(Cpu &, const uint32_t *a) { return com_addref(a[0]); }
static uint32_t Unk_Release(Cpu &, const uint32_t *a) { return com_release(a[0]); }
F(X_Ok) { return S_OK_; }
F(X_Zero) { return 0; }

static int g_xl = 0;   // diagnostico do audio (limite de linhas)
#define XL(...) do { } while (0)   // diagnostico do audio (desligado)
static FACTAudioEngine *g_eng = nullptr;   // nulo = sem audio (comportamento mudo antigo)
static inline float fl(uint32_t v) { float f; memcpy(&f, &v, 4); return f; }
static inline const char *gs(uint32_t p) { return p ? (const char *)(M + p) : nullptr; }

// objeto do jogo -> objeto do FACT; state guarda o estado quando nao ha FACT (modo mudo)
struct XObj : Res { void *p = nullptr; uint32_t state = 4; void *owner = nullptr; uint32_t mbuf = 0; };   // mbuf: buffer do jogo que o banco libera (MANAGEDATA)
// cues e ondas pertencem a um banco: ao destruir o banco o FACT libera todos eles. Sem isso o jogo podia chamar um metodo
// num cue ja liberado (uso depois de liberar: travou em IXACT3Cue::GetVariableIndex, igual ao bug que o SilentPatch corrige no PC)
static std::mutex g_child_m; static std::vector<XObj *> g_child;
static void own(uint32_t obj, void *owner) { XObj *x = obj ? (XObj *)res_of(obj) : nullptr; if (!x || !owner) return; x->owner = owner; std::lock_guard<std::mutex> lk(g_child_m); g_child.push_back(x); }
static void orphan(void *owner) { std::lock_guard<std::mutex> lk(g_child_m); size_t j = 0; for (XObj *x : g_child) { if (x->owner == owner) { x->p = nullptr; x->owner = nullptr; x->state = 0x20; } else if (x->p) g_child[j++] = x; } g_child.resize(j); }
static uint32_t new_xobj(uint32_t vt, void *p, uint32_t st = 4) { XObj *r = new XObj; r->type = 300; r->p = p; r->state = st; return com_new(vt, r); }
static XObj *xo(uint32_t o) { return (XObj *)res_of(o); }
template <class T> static T *fp(uint32_t o) { XObj *x = xo(o); return x ? (T *)x->p : nullptr; }

static uint32_t vt_cue(); static uint32_t vt_wave(); static uint32_t vt_soundbank(); static uint32_t vt_wavebank();

// ---- E/S dos bancos em streaming: o "arquivo" e o handle do Windows do jogo (lido pelo nosso runtime)
bool rt_file_pread(uint32_t h, uint64_t off, void *dst, uint32_t n, uint32_t *got);
static int32_t FACTCALL io_read(void *hFile, void *buffer, uint32_t n, uint32_t *got, FACTOverlapped *ov) {
    uint32_t r = 0;
    const uint64_t off = ((uint64_t)ov->OffsetHigh << 32) | ov->Offset;
    rt_file_pread((uint32_t)(uintptr_t)hFile, off, buffer, n, &r);
    ov->InternalHigh = (void *)(uintptr_t)r; ov->Internal = 0;
    if (got) *got = r;
    return 1;
}
static int32_t FACTCALL io_result(void *, FACTOverlapped *ov, uint32_t *n, int32_t) { *n = (uint32_t)(uintptr_t)ov->InternalHigh; return 1; }

// ---- cue
F(Cue_Play) { if (FACTCue *q = fp<FACTCue>(a[0])) { const uint32_t r = FACTCue_Play(q); XL("[xact] cue %08X Play -> %08X\n", a[0], r); return r; } if (XObj *x = xo(a[0])) x->state = 8; return S_OK_; }
F(Cue_Stop) { XL("[xact] cue %08X Stop(%X)\n", a[0], a[1]); if (FACTCue *q = fp<FACTCue>(a[0])) return FACTCue_Stop(q, a[1]); if (XObj *x = xo(a[0])) x->state = 0x20; return S_OK_; }
F(Cue_GetState) {
    uint32_t v = 0x20;
    if (FACTCue *q = fp<FACTCue>(a[0])) { FACTCue_GetState(q, &v); XObj *x = xo(a[0]); if (x && x->state != v) { XL("[xact] cue %08X estado %X -> %X\n", a[0], x->state, v); x->state = v; } }
    else if (XObj *x = xo(a[0])) { v = x->state; if (v == 8) x->state = 0x20; }
    if (a[1]) wr32(a[1], v); return S_OK_;
}
F(Cue_Destroy) { XObj *x = xo(a[0]); if (x && x->p) { std::lock_guard<std::mutex> lk(g_child_m); FACTCue_Destroy((FACTCue *)x->p); x->p = nullptr; x->owner = nullptr; } return S_OK_; }
F(Cue_SetMatrix) { if (FACTCue *q = fp<FACTCue>(a[0])) return FACTCue_SetMatrixCoefficients(q, a[1], a[2], a[3] ? (float *)(M + a[3]) : nullptr); return S_OK_; }
F(Cue_GetVarIdx) { XL("[xact] cue %08X GetVariableIndex(%s)\n", a[0], a[1] ? gs(a[1]) : "?"); if (FACTCue *q = fp<FACTCue>(a[0])) return FACTCue_GetVariableIndex(q, gs(a[1])); return 0xFFFF; }
F(Cue_SetVar) { if (FACTCue *q = fp<FACTCue>(a[0])) return FACTCue_SetVariable(q, (uint16_t)a[1], fl(a[2])); return S_OK_; }
F(Cue_GetVar) { float v = 0; if (FACTCue *q = fp<FACTCue>(a[0])) FACTCue_GetVariable(q, (uint16_t)a[1], &v); if (a[2]) wrf32(a[2], v); return S_OK_; }
F(Cue_Pause) { if (FACTCue *q = fp<FACTCue>(a[0])) return FACTCue_Pause(q, (int32_t)a[1]); return S_OK_; }
F(Cue_GetProperties) { XL("[xact] cue %08X GetProperties (devolve falha)\n", a[0]); if (a[1]) wr32(a[1], 0); return E_FAIL_; }   // o jogo funciona sem (aloca struct com ponteiros)
static uint32_t vt_cue() {
    static uint32_t v = 0;
    if (!v) { static const ComMethod m[] = {{"Play", 0, Cue_Play}, {"Stop", 1, Cue_Stop}, {"GetState", 1, Cue_GetState}, {"Destroy", 0, Cue_Destroy},
        {"SetMatrixCoefficients", 3, Cue_SetMatrix}, {"GetVariableIndex", 1, Cue_GetVarIdx}, {"SetVariable", 2, Cue_SetVar}, {"GetVariable", 2, Cue_GetVar},
        {"Pause", 1, Cue_Pause}, {"GetProperties", 1, Cue_GetProperties}, {"SetOutputVoices", 1, X_Ok}, {"SetOutputVoiceMatrix", 4, X_Ok}};
        v = com_vtable("IXACT3Cue", m, (int)(sizeof m / sizeof m[0])); }
    return v;
}
// ---- onda
F(Wave_Destroy) { XObj *x = xo(a[0]); if (x) { std::lock_guard<std::mutex> lk(g_child_m); if (x->p) FACTWave_Destroy((FACTWave *)x->p); x->p = nullptr; x->owner = nullptr; } return S_OK_; }
F(Wave_Play) { if (FACTWave *w = fp<FACTWave>(a[0])) { const uint32_t r = FACTWave_Play(w); XL("[xact] onda %08X Play -> %08X\n", a[0], r); return r; } if (XObj *x = xo(a[0])) x->state = 8; return S_OK_; }
F(Wave_Stop) { if (FACTWave *w = fp<FACTWave>(a[0])) return FACTWave_Stop(w, a[1]); if (XObj *x = xo(a[0])) x->state = 0x20; return S_OK_; }
F(Wave_Pause) { if (FACTWave *w = fp<FACTWave>(a[0])) return FACTWave_Pause(w, (int32_t)a[1]); return S_OK_; }
F(Wave_GetState) {
    uint32_t v = 0x20;
    if (FACTWave *w = fp<FACTWave>(a[0])) { FACTWave_GetState(w, &v); XObj *x = xo(a[0]); if (x && x->state != v) { XL("[xact] onda %08X estado %X -> %X\n", a[0], x->state, v); x->state = v; } }
    else if (XObj *x = xo(a[0])) { v = x->state; if (v == 8) x->state = 0x20; }
    if (a[1]) wr32(a[1], v); return S_OK_;
}
F(Wave_SetPitch) { if (FACTWave *w = fp<FACTWave>(a[0])) return FACTWave_SetPitch(w, (int16_t)a[1]); return S_OK_; }
F(Wave_SetVolume) { if (FACTWave *w = fp<FACTWave>(a[0])) return FACTWave_SetVolume(w, fl(a[1])); return S_OK_; }
F(Wave_SetMatrix) { if (FACTWave *w = fp<FACTWave>(a[0])) return FACTWave_SetMatrixCoefficients(w, a[1], a[2], a[3] ? (float *)(M + a[3]) : nullptr); return S_OK_; }
F(Wave_GetProperties) {   // XACT_WAVE_INSTANCE_PROPERTIES: mesmo layout (sem ponteiros), 88 bytes
    if (!a[1]) return E_FAIL_;
    memset(M + a[1], 0, 88);
    if (FACTWave *w = fp<FACTWave>(a[0])) { FACTWaveInstanceProperties p; memset(&p, 0, sizeof p); FACTWave_GetProperties(w, &p); memcpy(M + a[1], &p, 88); }
    return S_OK_;
}
static uint32_t vt_wave() {
    static uint32_t v = 0;
    if (!v) { static const ComMethod m[] = {{"Destroy", 0, Wave_Destroy}, {"Play", 0, Wave_Play}, {"Stop", 1, Wave_Stop}, {"Pause", 1, Wave_Pause}, {"GetState", 1, Wave_GetState},
        {"SetPitch", 1, Wave_SetPitch}, {"SetVolume", 1, Wave_SetVolume}, {"SetMatrixCoefficients", 3, Wave_SetMatrix}, {"GetProperties", 1, Wave_GetProperties}};
        v = com_vtable("IXACT3Wave", m, (int)(sizeof m / sizeof m[0])); }
    return v;
}
// ---- banco de som
F(SB_GetCueIndex) { if (FACTSoundBank *s = fp<FACTSoundBank>(a[0])) return FACTSoundBank_GetCueIndex(s, gs(a[1])); return 0; }
F(SB_GetNumCues) { uint16_t n = 1; if (FACTSoundBank *s = fp<FACTSoundBank>(a[0])) FACTSoundBank_GetNumCues(s, &n); if (a[1]) wr16(a[1], n); return S_OK_; }
F(SB_GetCueProperties) {   // XACT_CUE_PROPERTIES (empacotada): nome[255], interactive, iaVariableIndex, numVariations, maxInstances, currentInstances
    if (!a[2]) return E_FAIL_;
    memset(M + a[2], 0, 265);
    if (FACTSoundBank *s = fp<FACTSoundBank>(a[0])) {
        FACTCueProperties p; memset(&p, 0, sizeof p);
        if (FACTSoundBank_GetCueProperties(s, (uint16_t)a[1], &p) != 0) return E_FAIL_;
        memcpy(M + a[2], p.friendlyName, 255); wr32(a[2] + 255, (uint32_t)p.interactive); wr16(a[2] + 259, p.iaVariableIndex);
        wr16(a[2] + 261, p.numVariations); M[a[2] + 263] = p.maxInstances; M[a[2] + 264] = p.currentInstances;
    }
    return S_OK_;
}
F(SB_Prepare) {   // (nCueIndex, dwFlags, timeOffset, ppCue)
    FACTSoundBank *s = fp<FACTSoundBank>(a[0]);
    if (!s) { if (a[4]) wr32(a[4], new_xobj(vt_cue(), nullptr, 4)); return S_OK_; }
    FACTCue *q = nullptr; const uint32_t r = FACTSoundBank_Prepare(s, (uint16_t)a[1], a[2], (int32_t)a[3], &q);
    if (a[4]) { wr32(a[4], q ? new_xobj(vt_cue(), q) : 0); if (q) own(rd32(a[4]), s); }
    XL("[xact] SoundBank %08X Prepare(cue %u, inicio %u) -> %08X cue %08X\n", a[0], a[1], a[3], r, a[4] ? rd32(a[4]) : 0);
    return r;
}
F(SB_Play) {
    FACTSoundBank *s = fp<FACTSoundBank>(a[0]);
    if (!s) { if (a[4]) wr32(a[4], new_xobj(vt_cue(), nullptr, 8)); return S_OK_; }
    FACTCue *q = nullptr; const uint32_t r = FACTSoundBank_Play(s, (uint16_t)a[1], a[2], (int32_t)a[3], a[4] ? &q : nullptr);
    XL("[xact] SoundBank %08X Play(cue %u) -> %08X\n", a[0], a[1], r);
    if (a[4]) { wr32(a[4], q ? new_xobj(vt_cue(), q) : 0); if (q) own(rd32(a[4]), s); }
    return r;
}
F(SB_Stop) { if (FACTSoundBank *s = fp<FACTSoundBank>(a[0])) return FACTSoundBank_Stop(s, (uint16_t)a[1], a[2]); return S_OK_; }
F(SB_Destroy) { XObj *x = xo(a[0]); if (x && x->p) { void *p = x->p; FACTSoundBank_Destroy((FACTSoundBank *)p); x->p = nullptr; orphan(p); } if (x && x->mbuf) { rt_free(x->mbuf); x->mbuf = 0; } return S_OK_; }
F(SB_GetState) { uint32_t v = 4; if (FACTSoundBank *s = fp<FACTSoundBank>(a[0])) FACTSoundBank_GetState(s, &v); if (a[1]) wr32(a[1], v); return S_OK_; }
static uint32_t vt_soundbank() {
    static uint32_t v = 0;
    if (!v) { static const ComMethod m[] = {{"GetCueIndex", 1, SB_GetCueIndex}, {"GetNumCues", 1, SB_GetNumCues}, {"GetCueProperties", 2, SB_GetCueProperties},
        {"Prepare", 4, SB_Prepare}, {"Play", 4, SB_Play}, {"Stop", 2, SB_Stop}, {"Destroy", 0, SB_Destroy}, {"GetState", 1, SB_GetState}};
        v = com_vtable("IXACT3SoundBank", m, (int)(sizeof m / sizeof m[0])); }
    return v;
}
// ---- banco de ondas
F(WB_Destroy) { XObj *x = xo(a[0]); if (x && x->p) { void *p = x->p; FACTWaveBank_Destroy((FACTWaveBank *)p); x->p = nullptr; orphan(p); } if (x && x->mbuf) { rt_free(x->mbuf); x->mbuf = 0; } return S_OK_; }
F(WB_GetNum) { uint16_t n = 1; if (FACTWaveBank *w = fp<FACTWaveBank>(a[0])) FACTWaveBank_GetNumWaves(w, &n); if (a[1]) wr16(a[1], n); return S_OK_; }
F(WB_GetWaveIndex) { if (FACTWaveBank *w = fp<FACTWaveBank>(a[0])) return FACTWaveBank_GetWaveIndex(w, gs(a[1])); return 0; }
F(WB_GetWaveProperties) {   // XACT_WAVE_PROPERTIES: mesmo layout, 84 bytes
    if (!a[2]) return E_FAIL_;
    memset(M + a[2], 0, 84);
    if (FACTWaveBank *w = fp<FACTWaveBank>(a[0])) { FACTWaveProperties p; memset(&p, 0, sizeof p); FACTWaveBank_GetWaveProperties(w, (uint16_t)a[1], &p); memcpy(M + a[2], &p, 84); }
    return S_OK_;
}
F(WB_Prepare) {   // (idx, flags, playOffset, loopCount, ppWave)
    FACTWaveBank *w = fp<FACTWaveBank>(a[0]);
    if (!w) { if (a[5]) wr32(a[5], new_xobj(vt_wave(), nullptr, 4)); return S_OK_; }
    FACTWave *v = nullptr; const uint32_t r = FACTWaveBank_Prepare(w, (uint16_t)a[1], a[2], a[3], (uint8_t)a[4], &v);
    if (a[5]) { wr32(a[5], v ? new_xobj(vt_wave(), v) : 0); if (v) own(rd32(a[5]), w); }
    XL("[xact] WaveBank %08X Prepare(onda %u, flags %X, inicio %u, loops %u) -> %08X onda %08X\n", a[0], a[1], a[2], a[3], a[4], r, a[5] ? rd32(a[5]) : 0);
    return r;
}
F(WB_Play) {
    FACTWaveBank *w = fp<FACTWaveBank>(a[0]);
    if (!w) { if (a[5]) wr32(a[5], new_xobj(vt_wave(), nullptr, 8)); return S_OK_; }
    FACTWave *v = nullptr; const uint32_t r = FACTWaveBank_Play(w, (uint16_t)a[1], a[2], a[3], (uint8_t)a[4], a[5] ? &v : nullptr);
    XL("[xact] WaveBank %08X Play(onda %u) -> %08X\n", a[0], a[1], r);
    if (a[5]) { wr32(a[5], v ? new_xobj(vt_wave(), v) : 0); if (v) own(rd32(a[5]), w); }
    return r;
}
F(WB_Stop) { if (FACTWaveBank *w = fp<FACTWaveBank>(a[0])) return FACTWaveBank_Stop(w, (uint16_t)a[1], a[2]); return S_OK_; }
F(WB_GetState) {
    uint32_t v = 4;
    if (FACTWaveBank *w = fp<FACTWaveBank>(a[0])) { FACTWaveBank_GetState(w, &v); XObj *x = xo(a[0]); if (x && x->state != v) { XL("[xact] WaveBank %08X estado %X -> %X\n", a[0], x->state, v); x->state = v; } }
    if (a[1]) wr32(a[1], v); return S_OK_;
}
static uint32_t vt_wavebank() {
    static uint32_t v = 0;
    if (!v) { static const ComMethod m[] = {{"Destroy", 0, WB_Destroy}, {"GetNumWaves", 1, WB_GetNum}, {"GetWaveIndex", 1, WB_GetWaveIndex},
        {"GetWaveProperties", 2, WB_GetWaveProperties}, {"Prepare", 5, WB_Prepare}, {"Play", 5, WB_Play}, {"Stop", 2, WB_Stop}, {"GetState", 1, WB_GetState}};
        v = com_vtable("IXACT3WaveBank", m, (int)(sizeof m / sizeof m[0])); }
    return v;
}

// ---- motor
F(E_GetRendererCount) { if (a[1]) wr16(a[1], 1); return S_OK_; }
F(E_GetRendererDetails) {   // XACT_RENDERER_DETAILS: rendererID[255], displayName[255] (WCHAR), defaultDevice
    if (!a[2]) return E_FAIL_;
    memset(M + a[2], 0, 1024);
    const char *n = "Android";
    for (int i = 0; n[i]; ++i) { M[a[2] + 2 * i] = (uint8_t)n[i]; M[a[2] + 510 + 2 * i] = (uint8_t)n[i]; }
    wr32(a[2] + 1020, 1);
    return S_OK_;
}
F(E_GetFinalMixFormat) {   // WAVEFORMATEXTENSIBLE: PCM 16 bits, 2 canais, 44100 Hz
    if (!a[1]) return E_FAIL_;
    const uint32_t p = a[1]; memset(M + p, 0, 40);
    wr16(p, 1); wr16(p + 2, 2); wr32(p + 4, 44100); wr32(p + 8, 44100 * 4); wr16(p + 12, 4); wr16(p + 14, 16);
    return S_OK_;
}
F(E_Initialize) {   // XACT_RUNTIME_PARAMETERS (32 bits): lookAhead, pGlobalSettings, tamanho, flags, allocAttr, callbacks E/S, notificacao...
    if (g_eng || !a[1]) return S_OK_;
    const uint32_t p = a[1];
    if (!rd32(p + 4) || !rd32(p + 8)) { rt_log("[xact] jogo nao passou configuracao global (.xgs): fica mudo\n"); return S_OK_; }   // o FACT quebra sem ela
    FACTAudioEngine *e = nullptr;
    if (FACTCreateEngine(0, &e) != 0 || !e) { rt_log("[xact] FACT: falhou criar o motor (fica mudo)\n"); return S_OK_; }
    FACTRuntimeParameters rp; memset(&rp, 0, sizeof rp);
    rp.lookAheadTime = rd32(p);
    const uint32_t gsb = rd32(p + 4), gsz = rd32(p + 8);
    if (gsb && gsz) {   // copia: o FACT pode liberar o buffer (flag MANAGEDATA) com o free dele
        void *cp = malloc(gsz); memcpy(cp, M + gsb, gsz);
        rp.pGlobalSettingsBuffer = cp; rp.globalSettingsBufferSize = gsz; rp.globalSettingsFlags = rd32(p + 12) | 1u /*MANAGEDATA*/;
    }
    rp.fileIOCallbacks.readFileCallback = io_read;
    rp.fileIOCallbacks.getOverlappedResultCallback = io_result;
    const uint32_t r = FACTAudioEngine_Initialize(e, &rp);
    if (r != 0) { rt_log("[xact] FACT: Initialize falhou (%08X), fica mudo\n", r); FACTAudioEngine_Release(e); return S_OK_; }
    g_eng = e;
    rt_log("[xact] audio ligado (FACT/FAudio, configuracao global de %u bytes) | callback de notificacao do jogo: %08X\n", gsz, rd32(p + 28));
    return S_OK_;
}
F(E_ShutDown) { if (g_eng) { FACTAudioEngine_ShutDown(g_eng); g_eng = nullptr; } return S_OK_; }
F(E_DoWork) { if (g_eng) FACTAudioEngine_DoWork(g_eng); return S_OK_; }
// XACT_FLAG_ENGINE_CREATE_MANAGEDATA: o banco fica dono do buffer do jogo (correcao de vazamento do SilentPatch).
// O FACT nao recebe a flag (liberaria com o free do host um ponteiro do jogo): o buffer vai para o rt_free no Destroy
static void managed(const uint32_t *a, bool ok) {
    if (!(a[3] & 1u) || !a[1]) return;
    if (ok) { XObj *x = xo(rd32(a[5])); if (x) x->mbuf = a[1]; } else rt_free(a[1]);
}
F(E_CreateSoundBank) {   // (buffer, tamanho, flags, allocAttr, ppSoundBank)
    if (!a[5]) return E_FAIL_;
    FACTSoundBank *s = nullptr;
    if (g_eng && a[1]) {
        const uint32_t r = FACTAudioEngine_CreateSoundBank(g_eng, M + a[1], a[2], a[3] & ~1u, a[4], &s);
        if (r != 0) { rt_log("[xact] banco de som rejeitado (%08X)\n", r); s = nullptr; }
    }
    wr32(a[5], new_xobj(vt_soundbank(), s));
    managed(a, s != nullptr);
    return S_OK_;
}
F(E_CreateInMemoryWaveBank) {   // (buffer, tamanho, flags, allocAttr, ppWaveBank): o FACT usa o buffer do jogo direto
    if (!a[5]) return E_FAIL_;
    FACTWaveBank *w = nullptr;
    if (g_eng && a[1]) {
        const uint32_t r = FACTAudioEngine_CreateInMemoryWaveBank(g_eng, M + a[1], a[2], a[3] & ~1u, a[4], &w);
        if (r != 0) { rt_log("[xact] banco de ondas rejeitado (%08X)\n", r); w = nullptr; }
    }
    wr32(a[5], new_xobj(vt_wavebank(), w));
    managed(a, w != nullptr);
    return S_OK_;
}
F(E_CreateStreamingWaveBank) {   // XACT_WAVEBANK_STREAMING_PARAMETERS (empacotada): file, offset, flags, packetSize
    if (!a[2]) return E_FAIL_;
    FACTWaveBank *w = nullptr;
    if (g_eng && a[1]) {
        FACTStreamingParameters sp; memset(&sp, 0, sizeof sp);
        sp.file = (void *)(uintptr_t)rd32(a[1]); sp.offset = rd32(a[1] + 4); sp.flags = rd32(a[1] + 8); sp.packetSize = rd16(a[1] + 12);
        const uint32_t r = FACTAudioEngine_CreateStreamingWaveBank(g_eng, &sp, &w);
        if (r != 0) { rt_log("[xact] banco em streaming rejeitado (%08X)\n", r); w = nullptr; }
        uint16_t nw = 0; if (w) FACTWaveBank_GetNumWaves(w, &nw);
        XL("[xact] CreateStreamingWaveBank(arquivo %08X, offset %u, flags %X, pacote %u) -> %08X, %u ondas\n", rd32(a[1]), rd32(a[1] + 4), rd32(a[1] + 8), rd16(a[1] + 12), r, nw);
    }
    wr32(a[2], new_xobj(vt_wavebank(), w));
    { XObj *x = xo(rd32(a[2])); if (x) x->state = 0xFFFF; }
    return S_OK_;
}
F(E_RegisterNotification) { XL("[xact] RegisterNotification(tipo %u, flags %X)\n", M[a[1]], M[a[1] + 1]); return S_OK_; }
F(E_PrepareWave) { XL("[xact] PrepareWave (sem implementacao)\n"); if (a[7]) wr32(a[7], new_xobj(vt_wave(), nullptr)); return S_OK_; }
F(E_PrepareInMem) { XL("[xact] PrepareInMemoryWave (sem implementacao)\n"); if (a[12]) wr32(a[12], new_xobj(vt_wave(), nullptr)); return S_OK_; }
F(E_PrepareStream) { XL("[xact] PrepareStreamingWave (sem implementacao)\n"); if (a[13]) wr32(a[13], new_xobj(vt_wave(), nullptr)); return S_OK_; }
F(E_GetCategory) { return g_eng ? FACTAudioEngine_GetCategory(g_eng, gs(a[1])) : 0; }
F(E_Stop) { return g_eng ? FACTAudioEngine_Stop(g_eng, (uint16_t)a[1], a[2]) : S_OK_; }
F(E_SetVolume) { return g_eng ? FACTAudioEngine_SetVolume(g_eng, (uint16_t)a[1], fl(a[2])) : S_OK_; }
F(E_Pause) { return g_eng ? FACTAudioEngine_Pause(g_eng, (uint16_t)a[1], (int32_t)a[2]) : S_OK_; }
F(E_GetGlobalVarIdx) { return g_eng ? FACTAudioEngine_GetGlobalVariableIndex(g_eng, gs(a[1])) : 0; }
F(E_SetGlobalVar) { return g_eng ? FACTAudioEngine_SetGlobalVariable(g_eng, (uint16_t)a[1], fl(a[2])) : S_OK_; }
F(E_GetGlobalVariable) { float v = 0; if (g_eng) FACTAudioEngine_GetGlobalVariable(g_eng, (uint16_t)a[1], &v); if (a[2]) wrf32(a[2], v); return S_OK_; }
static uint32_t vt_engine() {
    static uint32_t v = 0;
    if (!v) { static const ComMethod m[] = {{"QueryInterface", 2, Unk_QI}, {"AddRef", 0, Unk_AddRef}, {"Release", 0, Unk_Release},
        {"GetRendererCount", 1, E_GetRendererCount}, {"GetRendererDetails", 2, E_GetRendererDetails}, {"GetFinalMixFormat", 1, E_GetFinalMixFormat},
        {"Initialize", 1, E_Initialize}, {"ShutDown", 0, E_ShutDown}, {"DoWork", 0, E_DoWork},
        {"CreateSoundBank", 5, E_CreateSoundBank}, {"CreateInMemoryWaveBank", 5, E_CreateInMemoryWaveBank}, {"CreateStreamingWaveBank", 2, E_CreateStreamingWaveBank},
        {"PrepareWave", 7, E_PrepareWave}, {"PrepareInMemoryWave", 12, E_PrepareInMem}, {"PrepareStreamingWave", 13, E_PrepareStream},
        {"RegisterNotification", 1, E_RegisterNotification}, {"UnRegisterNotification", 1, X_Ok}, {"GetCategory", 1, E_GetCategory},
        {"Stop", 2, E_Stop}, {"SetVolume", 2, E_SetVolume}, {"Pause", 2, E_Pause}, {"GetGlobalVariableIndex", 1, E_GetGlobalVarIdx},
        {"SetGlobalVariable", 2, E_SetGlobalVar}, {"GetGlobalVariable", 2, E_GetGlobalVariable}};
        v = com_vtable("IXACT3Engine", m, (int)(sizeof m / sizeof m[0])); }
    return v;
}
// chamado pelo CoCreateInstance: devolve o objeto do jogo (0 = classe desconhecida)
uint32_t xact_create(uint32_t clsid) {
    const uint32_t d1 = rd32(clsid);
    // XACT 3.x: CLSID_XACTEngine / versao de auditoria / depuracao (varias versoes do SDK)
    if (d1 == 0x962F5027u || d1 == 0x3B80EE2Au || d1 == 0xCD0D66ECu || d1 == 0x3A2495CEu || d1 == 0x248D8A3Bu || d1 == 0xBCC782BCu || d1 == 0x074B110Fu) {
        rt_log("[xact] motor de audio XACT3 criado\n");
        return new_xobj(vt_engine(), nullptr);
    }
    return 0;
}
