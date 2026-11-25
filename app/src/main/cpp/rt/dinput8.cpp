// DirectInput 8 do Bully: teclado e mouse existem mas nunca tem teclas apertadas (no Android a entrada vem do
// controle via XInput). Joysticks nao sao enumerados.
// TODO: mapear toque/teclado do SDL para o estado de teclado (256 bytes, DIK_*) e mouse (DIMOUSESTATE) se precisar.
#include "x86rt.h"
#include "d3d9_com.h"
#include "d3d9_internal.h"
#include "input.h"
#include <mutex>
#include <time.h>

#define F(name) static uint32_t name(Cpu &c, const uint32_t *a)
struct DIDev : Res { bool mouse = false; };

static uint32_t Unk_QI(Cpu &, const uint32_t *a) { com_addref(a[0]); if (a[2]) wr32(a[2], a[0]); return S_OK_; }
static uint32_t Unk_AddRef(Cpu &, const uint32_t *a) { return com_addref(a[0]); }
static uint32_t Unk_Release(Cpu &, const uint32_t *a) { return com_release(a[0]); }   // objetos vivem para sempre
#define UNK {"QueryInterface", 2, Unk_QI}, {"AddRef", 0, Unk_AddRef}, {"Release", 0, Unk_Release}

F(Dev_Ok) { return S_OK_; }
F(Dev_GetCapabilities) {   // DIDEVCAPS: dwSize, dwFlags, dwDevType, dwAxes, dwButtons, dwPOVs...
    DIDev *d = (DIDev *)res_of(a[0]); const uint32_t p = a[1];
    wr32(p + 4, 1 /*ATTACHED*/); wr32(p + 8, d && d->mouse ? 0x12 : 0x13); wr32(p + 12, d && d->mouse ? 3 : 0); wr32(p + 16, d && d->mouse ? 3 : 128); wr32(p + 20, 0);
    return S_OK_;
}
// teclado: os controles (toque/controle fisico) tambem viram teclas, porque o menu do Bully le o teclado
// setas = direcional/analogico esquerdo; A = Enter + Alt esquerdo ("Choose"); B = Esc; Start = Enter; Back = Esc
static void kbd_state(uint8_t k[256]) {
    memset(k, 0, 256);
    uint8_t st[16]; input_get_xinput(st);
    uint16_t b; memcpy(&b, st + 4, 2); int16_t lx, ly; memcpy(&lx, st + 8, 2); memcpy(&ly, st + 10, 2);
    if ((b & 0x1) || ly > 16000) k[0xC8] = 0x80;
    if ((b & 0x2) || ly < -16000) k[0xD0] = 0x80;
    if ((b & 0x4) || lx < -16000) k[0xCB] = 0x80;
    if ((b & 0x8) || lx > 16000) k[0xCD] = 0x80;
    if (b & 0x1000) { k[0x1C] = 0x80; k[0x38] = 0x80; }
    if (b & 0x2000) k[0x01] = 0x80;
    if (b & 0x10) k[0x1C] = 0x80;
    if (b & 0x20) k[0x01] = 0x80;
}
static std::mutex g_kmtx; static uint8_t g_kprev[256]; static uint32_t g_kseq = 0;
F(Dev_GetDeviceState) {   // (cbData, lpvData)
    DIDev *d = (DIDev *)res_of(a[0]);
    memset(M + a[2], 0, a[1]);
    if (d && !d->mouse && a[1] >= 256) kbd_state(M + a[2]);
    static bool logged = false; if (!logged) { logged = true; rt_log("[dinput] GetDeviceState(%u bytes, %s)\n", a[1], d && d->mouse ? "mouse" : "teclado"); }
    return S_OK_;
}
F(Dev_GetDeviceData) {   // (cbObjectData, rgdod, pdwInOut, dwFlags): modo com fila de eventos
    DIDev *d = (DIDev *)res_of(a[0]);
    static bool logged = false; if (!logged) { logged = true; rt_log("[dinput] GetDeviceData (fila de eventos, %s)\n", d && d->mouse ? "mouse" : "teclado"); }
    if (!a[3]) return S_OK_;
    const uint32_t max = rd32(a[3]); uint32_t n = 0;
    if (d && !d->mouse) {
        std::lock_guard<std::mutex> lk(g_kmtx);
        uint8_t k[256]; kbd_state(k);
        for (int i = 0; i < 256 && n < max; ++i) if (k[i] != g_kprev[i]) {
            if (a[2]) { const uint32_t p = a[2] + n * a[1]; memset(M + p, 0, a[1]); wr32(p, (uint32_t)i); wr32(p + 4, k[i]); wr32(p + 8, (uint32_t)(clock() / (CLOCKS_PER_SEC / 1000))); wr32(p + 12, ++g_kseq); }
            if (!(a[4] & 1)) g_kprev[i] = k[i];   // DIGDD_PEEK nao consome
            ++n;
        }
    }
    wr32(a[3], n);
    return S_OK_;
}
F(Dev_GetProperty) { return S_OK_; }
static uint32_t vt_didev() {
    static uint32_t v = 0;
    if (!v) {
        static const ComMethod m[] = {UNK, {"GetCapabilities", 1, Dev_GetCapabilities}, {"EnumObjects", 3, Dev_Ok}, {"GetProperty", 2, Dev_GetProperty},
            {"SetProperty", 2, Dev_Ok}, {"Acquire", 0, Dev_Ok}, {"Unacquire", 0, Dev_Ok}, {"GetDeviceState", 2, Dev_GetDeviceState},
            {"GetDeviceData", 4, Dev_GetDeviceData}, {"SetDataFormat", 1, Dev_Ok}, {"SetEventNotification", 1, Dev_Ok},
            {"SetCooperativeLevel", 2, Dev_Ok}, {"GetObjectInfo", 3, nullptr}, {"GetDeviceInfo", 1, nullptr}, {"RunControlPanel", 2, Dev_Ok},
            {"Initialize", 3, Dev_Ok}, {"CreateEffect", 4, nullptr}, {"EnumEffects", 3, Dev_Ok}, {"GetEffectInfo", 2, nullptr},
            {"GetForceFeedbackState", 1, nullptr}, {"SendForceFeedbackCommand", 1, Dev_Ok}, {"EnumCreatedEffectObjects", 3, Dev_Ok},
            {"Escape", 1, nullptr}, {"Poll", 0, Dev_Ok}, {"SendDeviceData", 4, Dev_Ok}, {"EnumEffectsInFile", 4, Dev_Ok},
            {"WriteEffectToFile", 4, nullptr}, {"BuildActionMap", 3, nullptr}, {"SetActionMap", 3, nullptr}, {"GetImageInfo", 1, nullptr}};
        v = com_vtable("IDirectInputDevice8A", m, (int)(sizeof m / sizeof m[0]));
    }
    return v;
}
// GUID_SysMouse = {6F1D2B60-D5A0-11CF-BFC7-444553540000}; GUID_SysKeyboard = {6F1D2B61-...}
F(DI_CreateDevice) {   // (rguid, lplpDirectInputDevice, pUnkOuter)
    const uint32_t g0 = rd32(a[1]);
    DIDev *d = new DIDev; d->type = 200; d->mouse = (g0 == 0x6F1D2B60u);
    if (g0 != 0x6F1D2B60u && g0 != 0x6F1D2B61u) rt_log("[dinput] CreateDevice de dispositivo %08X (tratado como teclado)\n", g0);
    d->obj = com_new(vt_didev(), d);
    wr32(a[2], d->obj);
    return S_OK_;
}
// (dwDevType, lpCallback, pvRef, dwFlags): anuncia um controle de Xbox 360 (o Bully so usa XInput para controles que
// aparecem aqui; os controles na tela e o controle fisico chegam como XInput)
F(DI_EnumDevices) {
    const uint32_t cls = a[1] & 0xFF;
    if (!(a[1] == 0 || cls == 4 || cls == 0x14 || cls == 0x15) || !a[2]) return S_OK_;
    static uint32_t ddi = 0; if (!ddi) ddi = rt_alloc(600, true);
    memset(M + ddi, 0, 584);
    wr32(ddi, 584);
    wr32(ddi + 4, 0x12345678u); wr32(ddi + 8, 0x11D0ABCDu); memcpy(M + ddi + 12, "BULLYPAD", 8);                 // guidInstance
    wr32(ddi + 20, 0x028E045Eu); wr32(ddi + 24, 0x00000000u); memcpy(M + ddi + 28, "\x00\x00PIDVID", 8);        // guidProduct (VID 045E PID 028E)
    wr32(ddi + 36, 0x00010215u);                                                                                    // gamepad HID
    strcpy((char *)M + ddi + 40, "Controller (XBOX 360 For Windows)"); strcpy((char *)M + ddi + 300, "Controller (XBOX 360 For Windows)");
    wr16(ddi + 576, 1); wr16(ddi + 578, 5);
    const uint32_t save = c.r[4];
    c.r[4] -= 4; wr32(c.r[4], a[3]); c.r[4] -= 4; wr32(c.r[4], ddi); c.r[4] -= 4; wr32(c.r[4], 0xDEAD0003u);
    x86_call(c, a[2]);
    c.r[4] = save;
    rt_log("[dinput] EnumDevices: controle de Xbox 360 anunciado (callback devolveu %u)\n", c.r[0]);
    return S_OK_;
}
F(DI_GetDeviceStatus) { return S_OK_; }
static uint32_t vt_di() {
    static uint32_t v = 0;
    if (!v) {
        static const ComMethod m[] = {UNK, {"CreateDevice", 3, DI_CreateDevice}, {"EnumDevices", 4, DI_EnumDevices}, {"GetDeviceStatus", 1, DI_GetDeviceStatus},
            {"RunControlPanel", 2, nullptr}, {"Initialize", 2, nullptr}, {"FindDevice", 3, nullptr}, {"EnumDevicesBySemantics", 5, nullptr},
            {"ConfigureDevices", 4, nullptr}};
        v = com_vtable("IDirectInput8A", m, (int)(sizeof m / sizeof m[0]));
    }
    return v;
}
F(DirectInput8Create) {   // (hinst, dwVersion, riidltf, ppvOut, punkOuter)
    static uint32_t di = 0;
    if (!di) { Res *r = new Res; r->type = 201; di = com_new(vt_di(), r); }
    else com_addref(di);
    rt_log("[dinput] DirectInput8Create(%08X)\n", a[1]);
    wr32(a[3], di);
    return S_OK_;
}

const RtImport g_dinput8_imports[] = {{"DirectInput8Create", 5, DirectInput8Create}};
const int g_dinput8_nimports = 1;
