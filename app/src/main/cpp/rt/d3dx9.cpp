// d3dx9_38.dll do Bully: matematica, ID3DXBuffer, tabela de constantes de shader (CTAB), carregamento de DDS e o
// caminho de shaders. Nao existe compilador HLSL no aparelho: D3DXCompileShader/AssembleShader procuram o bytecode ja
// compilado em <files>/shaders/<hash>.bin; se nao houver, gravam a fonte em <hash>.hlsl/.asm (com perfil e entrada no
// nome) para compilar no PC com o fxc (tools/compilar_shaders.txt) e devolvem falha.
#include "x86rt.h"
#include "d3d9_com.h"
#include "d3d9_internal.h"
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <sys/stat.h>

#define F(name) static uint32_t name(Cpu &c, const uint32_t *a)
std::string g_files_dir = ".";
static const uint32_t D3DXERR_INVALIDDATA_ = 0x88760B59u;

// ---------------------------------------------------------------- matematica (D3DXMATRIX = 16 floats, linha a linha)
static void ldm(float *m, uint32_t p) { memcpy(m, M + p, 64); }
static void stm(uint32_t p, const float *m) { memcpy(M + p, m, 64); }
F(X_MatrixMultiply) {
    float x[16], y[16], r[16]; ldm(x, a[1]); ldm(y, a[2]);
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) r[i * 4 + j] = x[i * 4] * y[j] + x[i * 4 + 1] * y[4 + j] + x[i * 4 + 2] * y[8 + j] + x[i * 4 + 3] * y[12 + j];
    stm(a[0], r); return a[0];
}
F(X_MatrixTranspose) { float m[16], r[16]; ldm(m, a[1]); for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) r[i * 4 + j] = m[j * 4 + i]; stm(a[0], r); return a[0]; }
F(X_MatrixInverse) {   // (pOut, pDeterminant, pM): NULL se singular
    float m[16], inv[16]; ldm(m, a[2]);
    inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
    inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
    inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
    inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
    inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
    inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
    inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
    inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
    inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
    inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
    inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
    inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
    inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
    inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
    inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
    inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];
    const float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    if (a[1]) memcpy(M + a[1], &det, 4);
    if (det == 0.0f) return 0;
    const float id = 1.0f / det;
    for (float &v : inv) v *= id;
    stm(a[0], inv); return a[0];
}
F(X_MatrixReflect) {   // (pOut, pPlane): plano normalizado
    float p[4]; memcpy(p, M + a[1], 16);
    const float l = sqrtf(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
    if (l > 0) for (float &v : p) v /= l;
    const float r[16] = {-2 * p[0] * p[0] + 1, -2 * p[1] * p[0], -2 * p[2] * p[0], 0,
                         -2 * p[0] * p[1], -2 * p[1] * p[1] + 1, -2 * p[2] * p[1], 0,
                         -2 * p[0] * p[2], -2 * p[1] * p[2], -2 * p[2] * p[2] + 1, 0,
                         -2 * p[0] * p[3], -2 * p[1] * p[3], -2 * p[2] * p[3], 1};
    stm(a[0], r); return a[0];
}
F(X_Vec3Normalize) {
    float v[3]; memcpy(v, M + a[1], 12);
    const float l = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (l > 0) { v[0] /= l; v[1] /= l; v[2] /= l; } else v[0] = v[1] = v[2] = 0;
    memcpy(M + a[0], v, 12); return a[0];
}
F(X_Vec4Transform) {
    float v[4], m[16], r[4]; memcpy(v, M + a[1], 16); ldm(m, a[2]);
    for (int j = 0; j < 4; ++j) r[j] = v[0] * m[j] + v[1] * m[4 + j] + v[2] * m[8 + j] + v[3] * m[12 + j];
    memcpy(M + a[0], r, 16); return a[0];
}

// ---------------------------------------------------------------- ID3DXBuffer
struct XBuf : Res { uint32_t mem = 0, size = 0; ~XBuf() override { if (mem) rt_free(mem); } };
static uint32_t Unk_QI(Cpu &, const uint32_t *a) { com_addref(a[0]); if (a[2]) wr32(a[2], a[0]); return S_OK_; }
static uint32_t Unk_AddRef(Cpu &, const uint32_t *a) { return com_addref(a[0]); }
static uint32_t Unk_Release(Cpu &, const uint32_t *a) { const uint32_t n = com_release(a[0]); if (!n) delete res_of(a[0]); return n; }
#define UNK {"QueryInterface", 2, Unk_QI}, {"AddRef", 0, Unk_AddRef}, {"Release", 0, Unk_Release}
F(XBuf_GetBufferPointer) { XBuf *b = (XBuf *)res_of(a[0]); return b ? b->mem : 0; }
F(XBuf_GetBufferSize) { XBuf *b = (XBuf *)res_of(a[0]); return b ? b->size : 0; }
static uint32_t vt_xbuf() { static uint32_t v = 0; if (!v) { static const ComMethod m[] = {UNK, {"GetBufferPointer", 0, XBuf_GetBufferPointer}, {"GetBufferSize", 0, XBuf_GetBufferSize}}; v = com_vtable("ID3DXBuffer", m, 5); } return v; }
uint32_t xbuf_new(const void *data, uint32_t size) {
    XBuf *b = new XBuf; b->type = RT_XBUF; b->size = size; b->mem = rt_alloc(size ? size : 4, true);
    if (data) memcpy(M + b->mem, data, size);
    b->obj = com_new(vt_xbuf(), b); return b->obj;
}
F(X_CreateBuffer) { wr32(a[1], xbuf_new(nullptr, a[0])); return S_OK_; }

// ---------------------------------------------------------------- shaders: versao, perfis, semanticas
F(X_GetShaderVersion) { return a[0] ? rd32(a[0]) : 0; }
F(X_GetPixelShaderProfile) { static uint32_t s = 0; if (!s) { s = rt_alloc(8, true); strcpy((char *)M + s, "ps_3_0"); } return s; }
F(X_GetVertexShaderProfile) { static uint32_t s = 0; if (!s) { s = rt_alloc(8, true); strcpy((char *)M + s, "vs_3_0"); } return s; }
F(X_GetShaderInputSemantics) {   // (pFunction, pSemantics, pCount): instrucoes dcl de registradores de entrada (v#)
    const uint32_t p = a[0]; const uint32_t ver = rd32(p); uint32_t n = 0, i = 1;
    const bool vs = (ver >> 16) == 0xFFFE;
    for (;;) {
        const uint32_t t = rd32(p + 4 * i);
        if (t == 0x0000FFFFu || i > 65536) break;
        if ((t & 0xFFFF) == 0xFFFE) { i += 1 + ((t >> 16) & 0x7FFF); continue; }
        const uint32_t len = (t >> 24) & 0xF;
        if ((t & 0xFFFF) == 0x1F) {   // dcl: token de uso, token de registrador
            const uint32_t usage = rd32(p + 4 * (i + 1)), reg = rd32(p + 4 * (i + 2));
            const uint32_t rtype = ((reg >> 28) & 7) | ((reg >> 8) & 0x18);
            if (rtype == 1 /*input*/ && (vs || true)) { if (a[1]) { wr32(a[1] + 8 * n, usage & 0x1F); wr32(a[1] + 8 * n + 4, (usage >> 16) & 0xF); } ++n; }
        }
        i += 1 + len;
    }
    if (a[2]) wr32(a[2], n);
    return S_OK_;
}

// ---------------------------------------------------------------- ID3DXConstantTable (le o comentario CTAB do bytecode)
struct XCTab : Res {
    uint32_t mem = 0, size = 0;   // copia do CTAB (a partir do cabecalho, sem o fourcc) na memoria do jogo
    uint32_t nconst = 0, info = 0;
    bool pixel = false;
    ~XCTab() override { if (mem) rt_free(mem); }
    uint32_t ci(uint32_t k) const { return mem + info + 20 * k; }          // D3DXSHADER_CONSTANTINFO k
    const char *name(uint32_t k) const { return (const char *)M + mem + rd32(ci(k)); }
    // handle -> indice: o handle e o endereco do CONSTANTINFO, ou uma string com o nome
    int find(uint32_t h) const {
        if (!h) return -1;
        if (h >= ci(0) && h < ci(nconst) && (h - ci(0)) % 20 == 0) return (int)((h - ci(0)) / 20);
        const char *s = (const char *)M + h;
        for (uint32_t k = 0; k < nconst; ++k) if (!strcmp(name(k), s)) return (int)k;
        return -1;
    }
};
// grava "regs" registradores vec4 (floats) no conjunto da constante k
static void ctab_write(XCTab *t, int k, const float *v, uint32_t regs) {
    if (k < 0 || !g_dev) return;
    const uint32_t p = t->ci((uint32_t)k);
    const uint32_t set = rd16(p + 4), idx = rd16(p + 6), cnt = rd16(p + 8);
    if (regs > cnt) regs = cnt;
    DevState &s = g_dev->st;
    for (uint32_t r = 0; r < regs; ++r) {
        const uint32_t reg = idx + r;
        switch (set) {
        case 0: if (reg < 16) (t->pixel ? s.psb : s.vsb)[reg] = v[4 * r] != 0.0f; break;                          // BOOL
        case 1: if (reg < 16) for (int j = 0; j < 4; ++j) (t->pixel ? s.psi : s.vsi)[4 * reg + j] = (int32_t)v[4 * r + j]; break;   // INT4
        case 2: if (reg < (t->pixel ? 224u : 256u)) memcpy((t->pixel ? s.psc : s.vsc) + 4 * reg, v + 4 * r, 16); break;  // FLOAT4
        default: break;
        }
    }
}
// converte dados compactos (elementos de Rows x Columns floats) para registradores, conforme a classe
static void ctab_set_packed(XCTab *t, int k, const float *d, uint32_t nfloats) {
    if (k < 0) return;
    const uint32_t p = t->ci((uint32_t)k), ti = t->mem + rd32(p + 12);
    const uint32_t cls = rd16(ti), rows = rd16(ti + 4) ? rd16(ti + 4) : 1, cols = rd16(ti + 6) ? rd16(ti + 6) : 1;
    const uint32_t cnt = rd16(p + 8);
    std::vector<float> regs(4 * cnt, 0.0f);
    const uint32_t per = rows * cols;
    uint32_t r = 0;
    for (uint32_t e = 0; e * per < nfloats && r < cnt; ++e) {
        const float *m = d + e * per;
        if (cls == 3) {          // MATRIX_COLUMNS: cada registrador e uma coluna
            for (uint32_t cc = 0; cc < cols && r < cnt; ++cc, ++r) for (uint32_t rr = 0; rr < rows; ++rr) if (e * per + rr * cols + cc < nfloats) regs[4 * r + rr] = m[rr * cols + cc];
        } else if (cls == 2) {   // MATRIX_ROWS
            for (uint32_t rr = 0; rr < rows && r < cnt; ++rr, ++r) for (uint32_t cc = 0; cc < cols; ++cc) if (e * per + rr * cols + cc < nfloats) regs[4 * r + cc] = m[rr * cols + cc];
        } else {                 // escalar / vetor: um registrador por elemento
            for (uint32_t cc = 0; cc < cols && e * per + cc < nfloats; ++cc) regs[4 * r + cc] = m[cc];
            ++r;
        }
    }
    ctab_write(t, k, regs.data(), r);
}
// matrizes 4x4 (D3DXMATRIX) -> registradores, cortando para Rows x Columns da constante
static void ctab_set_matrices(XCTab *t, int k, uint32_t pm, uint32_t n, bool transpose, bool ptr_array) {
    if (k < 0) return;
    const uint32_t p = t->ci((uint32_t)k), ti = t->mem + rd32(p + 12);
    const uint32_t rows = rd16(ti + 4), cols = rd16(ti + 6), cls = rd16(ti);
    std::vector<float> packed;
    for (uint32_t e = 0; e < n; ++e) {
        float m[16]; ldm(m, ptr_array ? rd32(pm + 4 * e) : pm + 64 * e);
        if (transpose) { float tm[16]; for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) tm[i * 4 + j] = m[j * 4 + i]; memcpy(m, tm, 64); }
        if (cls != 2 && cls != 3) { packed.insert(packed.end(), m, m + 16); continue; }
        for (uint32_t rr = 0; rr < rows; ++rr) for (uint32_t cc = 0; cc < cols; ++cc) packed.push_back(m[rr * 4 + cc]);
    }
    ctab_set_packed(t, k, packed.data(), (uint32_t)packed.size());
}
#define CT XCTab *t = (XCTab *)res_of(a[0]); if (!t) return D3DERR_INVALIDCALL_
F(CT_GetBufferPointer) { XCTab *t = (XCTab *)res_of(a[0]); return t ? t->mem : 0; }
F(CT_GetBufferSize) { XCTab *t = (XCTab *)res_of(a[0]); return t ? t->size : 0; }
F(CT_GetDesc) { CT; wr32(a[1], t->mem + rd32(t->mem + 4)); wr32(a[1] + 4, rd32(t->mem + 8)); wr32(a[1] + 8, t->nconst); return S_OK_; }
F(CT_GetConstantDesc) {   // (h, pDesc, pCount): D3DXCONSTANT_DESC = 52 bytes
    CT; const int k = t->find(a[1]); if (k < 0) return D3DERR_INVALIDCALL_;
    if (a[3]) wr32(a[3], 1);
    if (!a[2]) return S_OK_;
    const uint32_t p = t->ci((uint32_t)k), ti = t->mem + rd32(p + 12), d = a[2];
    wr32(d, t->mem + rd32(p)); wr32(d + 4, rd16(p + 4)); wr32(d + 8, rd16(p + 6)); wr32(d + 12, rd16(p + 8));
    wr32(d + 16, rd16(ti)); wr32(d + 20, rd16(ti + 2)); wr32(d + 24, rd16(ti + 4)); wr32(d + 28, rd16(ti + 6));
    wr32(d + 32, rd16(ti + 8) ? rd16(ti + 8) : 1); wr32(d + 36, rd16(ti + 10));
    const uint32_t elems = rd16(ti + 8) ? rd16(ti + 8) : 1;
    wr32(d + 40, 4 * rd16(ti + 4) * rd16(ti + 6) * elems);
    wr32(d + 44, rd32(p + 16) ? t->mem + rd32(p + 16) : 0);
    return S_OK_;
}
F(CT_GetSamplerIndex) { XCTab *t = (XCTab *)res_of(a[0]); if (!t) return 0xFFFFFFFFu; const int k = t->find(a[1]); return k < 0 ? 0xFFFFFFFFu : rd16(t->ci((uint32_t)k) + 6); }
F(CT_GetConstant) { XCTab *t = (XCTab *)res_of(a[0]); if (!t || a[1] || a[2] >= t->nconst) return 0; return t->ci(a[2]); }   // TODO: membros de struct
F(CT_GetConstantByName) { XCTab *t = (XCTab *)res_of(a[0]); if (!t || a[1]) return 0; const int k = t->find(a[2]); return k < 0 ? 0 : t->ci((uint32_t)k); }
F(CT_GetConstantElement) { XCTab *t = (XCTab *)res_of(a[0]); if (!t) return 0; const int k = t->find(a[1]); return (k >= 0 && a[2] == 0) ? t->ci((uint32_t)k) : 0; }   // TODO: elementos > 0
F(CT_SetDefaults) {
    CT;
    for (uint32_t k = 0; k < t->nconst; ++k) {
        const uint32_t p = t->ci(k), dv = rd32(p + 16);
        if (dv) ctab_write(t, (int)k, (const float *)(M + t->mem + dv), rd16(p + 8));
    }
    return S_OK_;
}
// Set*(pDevice, hConstant, ...): a[1] = device, a[2] = handle
F(CT_SetValue) { CT; ctab_set_packed(t, t->find(a[2]), (const float *)(M + a[3]), a[4] / 4); return S_OK_; }
F(CT_SetBool) { CT; const float f = a[3] ? 1.0f : 0.0f; ctab_set_packed(t, t->find(a[2]), &f, 1); return S_OK_; }
F(CT_SetBoolArray) { CT; std::vector<float> v(a[4]); for (uint32_t i = 0; i < a[4]; ++i) v[i] = rd32(a[3] + 4 * i) ? 1.0f : 0.0f; ctab_set_packed(t, t->find(a[2]), v.data(), a[4]); return S_OK_; }
F(CT_SetInt) { CT; const float f = (float)(int32_t)a[3]; ctab_set_packed(t, t->find(a[2]), &f, 1); return S_OK_; }
F(CT_SetIntArray) { CT; std::vector<float> v(a[4]); for (uint32_t i = 0; i < a[4]; ++i) v[i] = (float)(int32_t)rd32(a[3] + 4 * i); ctab_set_packed(t, t->find(a[2]), v.data(), a[4]); return S_OK_; }
F(CT_SetFloat) { CT; float f; memcpy(&f, &a[3], 4); ctab_set_packed(t, t->find(a[2]), &f, 1); return S_OK_; }
F(CT_SetFloatArray) { CT; ctab_set_packed(t, t->find(a[2]), (const float *)(M + a[3]), a[4]); return S_OK_; }
F(CT_SetVector) { CT; const int k = t->find(a[2]); ctab_write(t, k, (const float *)(M + a[3]), 1); return S_OK_; }
F(CT_SetVectorArray) { CT; const int k = t->find(a[2]); ctab_write(t, k, (const float *)(M + a[3]), a[4]); return S_OK_; }
F(CT_SetMatrix) { CT; ctab_set_matrices(t, t->find(a[2]), a[3], 1, false, false); return S_OK_; }
F(CT_SetMatrixArray) { CT; ctab_set_matrices(t, t->find(a[2]), a[3], a[4], false, false); return S_OK_; }
F(CT_SetMatrixPointerArray) { CT; ctab_set_matrices(t, t->find(a[2]), a[3], a[4], false, true); return S_OK_; }
F(CT_SetMatrixTranspose) { CT; ctab_set_matrices(t, t->find(a[2]), a[3], 1, true, false); return S_OK_; }
F(CT_SetMatrixTransposeArray) { CT; ctab_set_matrices(t, t->find(a[2]), a[3], a[4], true, false); return S_OK_; }
F(CT_SetMatrixTransposePointerArray) { CT; ctab_set_matrices(t, t->find(a[2]), a[3], a[4], true, true); return S_OK_; }
static uint32_t vt_ctab() {
    static uint32_t v = 0;
    if (!v) {
        static const ComMethod m[] = {UNK, {"GetBufferPointer", 0, CT_GetBufferPointer}, {"GetBufferSize", 0, CT_GetBufferSize},
            {"GetDesc", 1, CT_GetDesc}, {"GetConstantDesc", 3, CT_GetConstantDesc}, {"GetSamplerIndex", 1, CT_GetSamplerIndex},
            {"GetConstant", 2, CT_GetConstant}, {"GetConstantByName", 2, CT_GetConstantByName}, {"GetConstantElement", 2, CT_GetConstantElement},
            {"SetDefaults", 1, CT_SetDefaults}, {"SetValue", 4, CT_SetValue}, {"SetBool", 3, CT_SetBool}, {"SetBoolArray", 4, CT_SetBoolArray},
            {"SetInt", 3, CT_SetInt}, {"SetIntArray", 4, CT_SetIntArray}, {"SetFloat", 3, CT_SetFloat}, {"SetFloatArray", 4, CT_SetFloatArray},
            {"SetVector", 3, CT_SetVector}, {"SetVectorArray", 4, CT_SetVectorArray}, {"SetMatrix", 3, CT_SetMatrix}, {"SetMatrixArray", 4, CT_SetMatrixArray},
            {"SetMatrixPointerArray", 4, CT_SetMatrixPointerArray}, {"SetMatrixTranspose", 3, CT_SetMatrixTranspose},
            {"SetMatrixTransposeArray", 4, CT_SetMatrixTransposeArray}, {"SetMatrixTransposePointerArray", 4, CT_SetMatrixTransposePointerArray}};
        v = com_vtable("ID3DXConstantTable", m, (int)(sizeof m / sizeof m[0]));
    }
    return v;
}
// procura o comentario CTAB no bytecode (na memoria do host) e cria o objeto; 0 se nao houver
static uint32_t ctab_from_code(const uint32_t *code, uint32_t ndw) {
    const bool sm2 = ((code[0] >> 8) & 0xFF) >= 2;
    for (uint32_t i = 1; i < ndw;) {
        const uint32_t t = code[i];
        if (t == 0x0000FFFFu) break;
        if ((t & 0xFFFF) == 0xFFFE) {
            const uint32_t len = (t >> 16) & 0x7FFF;
            if (len >= 8 && i + 1 + len <= ndw && code[i + 1] == 0x42415443u /*'CTAB'*/) {
                XCTab *c = new XCTab; c->type = RT_XCTAB;
                c->size = (len - 1) * 4;
                c->mem = rt_alloc(c->size, true);
                memcpy(M + c->mem, code + i + 2, c->size);
                c->nconst = rd32(c->mem + 12); c->info = rd32(c->mem + 16);
                c->pixel = (code[0] >> 16) == 0xFFFF;
                c->obj = com_new(vt_ctab(), c);
                return c->obj;
            }
            i += 1 + len; continue;
        }
        i += sm2 ? 1 + ((t >> 24) & 0xF) : 1;
    }
    return 0;
}
F(X_GetShaderConstantTable) {
    if (!a[0]) return D3DERR_INVALIDCALL_;
    const uint32_t n = shader_len(a[0]);
    std::vector<uint32_t> code(n); memcpy(code.data(), M + a[0], 4 * n);
    const uint32_t o = ctab_from_code(code.data(), n);
    wr32(a[1], o);
    return o ? S_OK_ : D3DERR_INVALIDCALL_;
}

// ---------------------------------------------------------------- caminho dos shaders (cache de bytecode)
static uint64_t fnv64(const void *p, size_t n, uint64_t h = 1469598103934665603ull) { const uint8_t *b = (const uint8_t *)p; for (size_t i = 0; i < n; ++i) { h ^= b[i]; h *= 1099511628211ull; } return h; }
static std::string read_file(const std::string &p) { std::string s; FILE *f = fopen(p.c_str(), "rb"); if (!f) return s; char buf[65536]; size_t n; while ((n = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, n); fclose(f); return s; }
static void write_file(const std::string &p, const void *d, size_t n) { FILE *f = fopen(p.c_str(), "wb"); if (f) { fwrite(d, 1, n, f); fclose(f); } }
// defines: vetor de D3DXMACRO {Name, Definition} terminado em {NULL, NULL}
static std::string defines_str(uint32_t p) {
    std::string s;
    for (; p && rd32(p); p += 8) { s += "/D"; s += (const char *)M + rd32(p); if (rd32(p + 4)) { s += "="; s += (const char *)M + rd32(p + 4); } s += " "; }
    return s;
}
// devolve o bytecode compilado (vazio se nao houver) e grava a fonte para compilar no PC
static std::string shader_cache(const char *kind, const char *src, uint32_t len, const std::string &entry, const std::string &profile, const std::string &defs) {
    uint64_t h = fnv64(src, len);
    h = fnv64(entry.data(), entry.size(), h); h = fnv64(profile.data(), profile.size(), h); h = fnv64(defs.data(), defs.size(), h);
    char name[64]; snprintf(name, sizeof name, "%016llx", (unsigned long long)h);
    const std::string dir = g_files_dir + "/shaders";
    mkdir(dir.c_str(), 0755);
    std::string bin = read_file(dir + "/" + name + ".bin");
    if (bin.empty()) {
        const std::string srcp = dir + "/" + name + "." + kind;
        struct stat st;
        if (stat(srcp.c_str(), &st)) {
            write_file(srcp, src, len);
            const std::string meta = "entrada=" + entry + "\nperfil=" + profile + "\ndefines=" + defs + "\n";
            write_file(dir + "/" + name + ".txt", meta.data(), meta.size());
            rt_log("[d3dx] shader sem bytecode: %s.%s (%s %s)\n", name, kind, profile.c_str(), entry.c_str());
        }
    }
    return bin;
}
static uint32_t finish_shader(const std::string &bin, uint32_t ppShader, uint32_t ppErr, uint32_t ppCtab) {
    if (ppErr) wr32(ppErr, 0);
    if (ppCtab) wr32(ppCtab, 0);
    if (bin.empty()) {
        if (ppShader) wr32(ppShader, 0);
        if (ppErr) { static const char msg[] = "shader nao compilado (ver files/shaders)"; wr32(ppErr, xbuf_new(msg, sizeof msg)); }
        return E_FAIL_;
    }
    if (ppShader) wr32(ppShader, xbuf_new(bin.data(), (uint32_t)bin.size()));
    if (ppCtab) wr32(ppCtab, ctab_from_code((const uint32_t *)bin.data(), (uint32_t)bin.size() / 4));
    return S_OK_;
}
static const char *gs(uint32_t p) { return p ? (const char *)M + p : ""; }
// shaders HLSL fixos do Bully.exe montados a mao (sm2asm.py): procurados pelo hash da fonte
struct Builtin { uint64_t h; uint32_t n; uint32_t code[64]; };
static const Builtin kBuiltin[] = {
#include "d3dx9_builtin.inc"
};
static std::string builtin_shader(const char *src, uint32_t len) {
    const uint64_t h = fnv64(src, len);
    for (const Builtin &b : kBuiltin) if (b.h == h) return std::string((const char *)b.code, 4 * b.n);
    return std::string();
}
// sem bytecode: devolve um shader vazio valido para o jogo nao quebrar (o objeto nao aparece); o log avisa
static std::string dummy_shader(const std::string &profile) {
    static const uint32_t vs[] = {0xFFFE0200u, 0x0200001Fu, 0x80000000u, 0x900F0000u, 0x02000001u, 0xC00F0000u, 0x90E40000u, 0x0000FFFFu};
    static const uint32_t ps[] = {0xFFFF0200u, 0x05000051u, 0xA00F0000u, 0, 0, 0, 0, 0x02000001u, 0x800F0800u, 0xA0E40000u, 0x0000FFFFu};
    if (!profile.empty() && profile[0] == 'p') return std::string((const char *)ps, sizeof ps);
    return std::string((const char *)vs, sizeof vs);
}
static std::string compile_or_dummy(const char *kind, const char *src, uint32_t len, const std::string &entry, const std::string &profile, const std::string &defs) {
    std::string b = builtin_shader(src, len);
    if (!b.empty()) return b;
    b = shader_cache(kind, src, len, entry, profile, defs);
    if (!b.empty()) return b;
    rt_log("[d3dx] shader %s %s sem bytecode: usando substituto vazio\n", profile.c_str(), entry.c_str());
    return dummy_shader(profile);
}
F(X_CompileShader) {   // (pSrcData, SrcDataLen, pDefines, pInclude, pFunctionName, pProfile, Flags, ppShader, ppErrorMsgs, ppConstantTable)
    return finish_shader(compile_or_dummy("hlsl", gs(a[0]), a[1], gs(a[4]), gs(a[5]), defines_str(a[2])), a[7], a[8], a[9]);
}
F(X_CompileShaderFromFileA) {   // (pSrcFile, pDefines, pInclude, pFunctionName, pProfile, Flags, ppShader, ppErrorMsgs, ppConstantTable)
    const std::string src = read_file(rt_host_path(a[0]));
    if (src.empty()) { rt_log("[d3dx] CompileShaderFromFile: nao abriu %s\n", gs(a[0])); return E_FAIL_; }
    return finish_shader(compile_or_dummy("hlsl", src.data(), (uint32_t)src.size(), gs(a[3]), gs(a[4]), defines_str(a[1])), a[6], a[7], a[8]);
}
F(X_AssembleShader) {   // (pSrcData, SrcDataLen, pDefines, pInclude, Flags, ppShader, ppErrorMsgs)
    return finish_shader(shader_cache("asm", gs(a[0]), a[1], "", "asm", defines_str(a[2])), a[5], a[6], 0);
}
F(X_AssembleShaderFromFileA) {   // (pSrcFile, pDefines, pInclude, Flags, ppShader, ppErrorMsgs)
    const std::string src = read_file(rt_host_path(a[0]));
    if (src.empty()) return E_FAIL_;
    return finish_shader(shader_cache("asm", src.data(), (uint32_t)src.size(), "", "asm", defines_str(a[1])), a[4], a[5], 0);
}
// efeitos (.fx): TODO — interface ID3DXEffect inteira. Por enquanto so registra e grava a fonte.
uint32_t effect_create(const uint8_t *data, uint32_t size);
F(X_CreateEffect) {   // (pDevice, pSrcData, SrcDataLen, pDefines, pInclude, Flags, pPool, ppEffect, ppCompilationErrors)
    if (a[6]) { static bool w = false; if (!w) { w = true; rt_log("[d3dx] CreateEffect com pool de parametros (ignorado)\n"); } }
    if (const uint32_t o = effect_create(M + a[1], a[2])) { if (a[7]) wr32(a[7], o); if (a[8]) wr32(a[8], 0); return S_OK_; }
    shader_cache("fx", gs(a[1]), a[2], "", "fx_2_0", defines_str(a[3]));
    rt_log("[d3dx] D3DXCreateEffect: ainda nao implementado\n");
    if (a[7]) wr32(a[7], 0);
    if (a[8]) wr32(a[8], 0);
    return E_FAIL_;
}
F(X_CreateEffectCompiler) { rt_log("[d3dx] D3DXCreateEffectCompiler: ainda nao implementado\n"); if (a[5]) wr32(a[5], 0); if (a[6]) wr32(a[6], 0); return E_FAIL_; }

// ---------------------------------------------------------------- texturas (DDS)
struct DdsInfo { uint32_t w, h, d, levels, fmt, rtype; bool cube; const uint8_t *data; size_t size; };
static bool dds_parse(const uint8_t *p, size_t n, DdsInfo &o) {
    if (n < 128 || memcmp(p, "DDS ", 4)) return false;
    auto u = [&](size_t off) { uint32_t v; memcpy(&v, p + off, 4); return v; };
    o.h = u(12); o.w = u(16); o.d = (u(8) & 0x800000) ? u(24) : 1; o.levels = (u(8) & 0x20000) && u(28) ? u(28) : 1;
    const uint32_t pf = u(80), fcc = u(84), bits = u(88), rm = u(92), gm = u(96), bm = u(100), am = u(104), caps2 = u(112);
    o.cube = (caps2 & 0x200) != 0;
    o.rtype = o.cube ? RT_CUBE : (caps2 & 0x200000) ? RT_VOLTEX : RT_TEXTURE;
    if (!o.d) o.d = 1;
    o.fmt = 0;
    if (pf & 4) o.fmt = fcc;   // DXTn ou D3DFMT numerico
    else if (bits == 32) o.fmt = (pf & 1) && am ? (rm == 0xFF0000 ? 21 : 32) : (rm == 0xFF0000 ? 22 : 33);
    else if (bits == 16) {
        if (pf & 0x20000) o.fmt = 51;                                     // A8L8
        else if (gm == 0x7E0) o.fmt = 23;                                 // R5G6B5
        else if (am == 0x8000) o.fmt = 25; else if (gm == 0x3E0) o.fmt = 24;
        else if (am == 0xF000) o.fmt = 26;
        else if (pf & 0x80000) o.fmt = 60;                                // V8U8
    } else if (bits == 8) o.fmt = (pf & 2) && !(pf & 0x20000) ? 28 : 50;   // A8 / L8
    if (!fmt_bpp(o.fmt)) { rt_log("[d3dx] DDS formato nao suportado pf=%08X fcc=%08X bits=%u\n", pf, fcc, bits); return false; }
    o.data = p + 128; o.size = n - 128;
    if (u(84) == 0x30315844u /*'DX10'*/) return false;   // cabecalho DX10 nao existe no D3D9
    return true;
}
static void put_image_info(uint32_t p, const DdsInfo &d) {
    if (!p) return;
    wr32(p, d.w); wr32(p + 4, d.h); wr32(p + 8, d.d); wr32(p + 12, d.levels); wr32(p + 16, d.fmt); wr32(p + 20, d.rtype); wr32(p + 24, 4 /*DDS*/);
}
static const char *img_kind(const uint8_t *p, size_t n) {
    if (n >= 4 && !memcmp(p, "DDS ", 4)) return "DDS";
    if (n >= 8 && !memcmp(p, "\x89PNG", 4)) return "PNG";
    if (n >= 2 && p[0] == 0xFF && p[1] == 0xD8) return "JPG";
    if (n >= 2 && p[0] == 'B' && p[1] == 'M') return "BMP";
    return "TGA?";
}
// cria a textura a partir de um DDS; levels/usage/pool do jogo (0/FROM_FILE = do arquivo)
static uint32_t tex_from_dds(const uint8_t *p, size_t n, uint32_t want_type, uint32_t levels, uint32_t usage, uint32_t pool, uint32_t info, uint32_t pp) {
    DdsInfo d;
    if (!dds_parse(p, n, d)) { rt_log("[d3dx] textura nao carregada (%s, %zu bytes)\n", img_kind(p, n), n); if (pp) wr32(pp, 0); return D3DXERR_INVALIDDATA_; }
    if (want_type == RT_CUBE && !d.cube) { rt_log("[d3dx] DDS nao e cubemap\n"); return D3DXERR_INVALIDDATA_; }
    // TODO: gerar mipmaps quando o jogo pede mais niveis que o arquivo tem; converter formato quando pedido
    (void)levels;
    Tex *t = tex_create(d.rtype, d.w, d.h, d.d, d.levels, usage & ~3u, d.fmt, pool == 0 ? 1 : pool);
    const uint32_t faces = d.cube ? 6 : 1;
    size_t off = 0;
    for (uint32_t f = 0; f < faces; ++f)
        for (uint32_t l = 0; l < t->levels; ++l) {
            uint32_t w = d.w >> l, h = d.h >> l, dd = d.d >> l; if (!w) w = 1; if (!h) h = 1; if (!dd) dd = 1;
            const size_t sz = (size_t)fmt_size(d.fmt, w, h) * dd;
            if (off + sz > d.size) break;
            memcpy(M + tex_level_addr(t, f, l), d.data + off, sz);
            off += sz;
            tex_upload_level(t, f, l);
        }
    put_image_info(info, d);
    wr32(pp, t->obj);
    return S_OK_;
}
F(X_GetImageInfoFromFileInMemory) {
    DdsInfo d;
    if (!dds_parse(M + a[0], a[1], d)) { rt_log("[d3dx] GetImageInfo: %s nao suportado\n", img_kind(M + a[0], a[1])); return D3DXERR_INVALIDDATA_; }
    put_image_info(a[2], d); return S_OK_;
}
F(X_CreateTextureFromFileInMemory) { return tex_from_dds(M + a[1], a[2], RT_TEXTURE, 0, 0, 1, 0, a[3]); }
F(X_CreateCubeTextureFromFileInMemory) { return tex_from_dds(M + a[1], a[2], RT_CUBE, 0, 0, 1, 0, a[3]); }
F(X_CreateVolumeTextureFromFileInMemory) { return tex_from_dds(M + a[1], a[2], RT_VOLTEX, 0, 0, 1, 0, a[3]); }
static uint32_t from_file(uint32_t path, uint32_t type, uint32_t levels, uint32_t usage, uint32_t pool, uint32_t info, uint32_t pp) {
    const std::string s = read_file(rt_host_path(path));
    if (s.empty()) { rt_log("[d3dx] textura: nao abriu %s\n", gs(path)); return D3DXERR_INVALIDDATA_; }
    return tex_from_dds((const uint8_t *)s.data(), s.size(), type, levels, usage, pool, info, pp);
}
// (pDevice, pSrcFile, Width, Height, MipLevels, Usage, Format, Pool, Filter, MipFilter, ColorKey, pSrcInfo, pPalette, ppTexture)
F(X_CreateTextureFromFileExA) { return from_file(a[1], RT_TEXTURE, a[4], a[5], a[7], a[11], a[13]); }
// (pDevice, pSrcFile, Size, MipLevels, Usage, Format, Pool, Filter, MipFilter, ColorKey, pSrcInfo, pPalette, ppCubeTexture)
F(X_CreateCubeTextureFromFileExA) { return from_file(a[1], RT_CUBE, a[3], a[4], a[6], a[10], a[12]); }
// (pDevice, pSrcFile, Width, Height, Depth, MipLevels, Usage, Format, Pool, Filter, MipFilter, ColorKey, pSrcInfo, pPalette, ppVolumeTexture)
F(X_CreateVolumeTextureFromFileExA) { return from_file(a[1], RT_VOLTEX, a[5], a[6], a[8], a[12], a[14]); }
F(X_CreateTexture) {   // (pDevice, Width, Height, MipLevels, Usage, Format, Pool, ppTexture)
    if (!fmt_bpp(a[5])) return D3DERR_INVALIDCALL_;
    Tex *t = tex_create(RT_TEXTURE, a[1] ? a[1] : 256, a[2] ? a[2] : 256, 1, a[3], a[4], a[5], a[6]);
    wr32(a[7], t->obj); return S_OK_;
}
F(X_LoadSurfaceFromSurface) {   // (pDestSurface, pDestPalette, pDestRect, pSrcSurface, pSrcPalette, pSrcRect, Filter, ColorKey)
    // caso simples: mesmo tamanho e formato, sem retangulos -> copia direta. TODO: escala/conversao/alvos de desenho
    Surface *d = (Surface *)res_of(a[0]), *s = (Surface *)res_of(a[3]);
    if (!d || !s) return D3DERR_INVALIDCALL_;
    if (d->w == s->w && d->h == s->h && d->fmt == s->fmt && !a[2] && !a[5] && d->parent && s->parent) {
        memcpy(M + tex_level_addr(d->parent, d->face, d->level), M + tex_level_addr(s->parent, s->face, s->level), fmt_size(d->fmt, d->w, d->h));
        tex_upload_level(d->parent, d->face, d->level);
    } else rt_log("[d3dx] LoadSurfaceFromSurface caso nao tratado (%ux%u fmt %u -> %ux%u fmt %u)\n", s->w, s->h, s->fmt, d->w, d->h, d->fmt);
    return S_OK_;
}
F(X_SaveSurfaceToFileA) { return S_OK_; }

const RtImport g_d3dx9_imports[] = {
    {"D3DXMatrixMultiply", 3, X_MatrixMultiply}, {"D3DXMatrixInverse", 3, X_MatrixInverse}, {"D3DXMatrixTranspose", 2, X_MatrixTranspose},
    {"D3DXMatrixReflect", 2, X_MatrixReflect}, {"D3DXVec3Normalize", 2, X_Vec3Normalize}, {"D3DXVec4Transform", 3, X_Vec4Transform},
    {"D3DXCreateBuffer", 2, X_CreateBuffer}, {"D3DXGetShaderVersion", 1, X_GetShaderVersion},
    {"D3DXGetPixelShaderProfile", 1, X_GetPixelShaderProfile}, {"D3DXGetVertexShaderProfile", 1, X_GetVertexShaderProfile},
    {"D3DXGetShaderConstantTable", 2, X_GetShaderConstantTable}, {"D3DXGetShaderInputSemantics", 3, X_GetShaderInputSemantics},
    {"D3DXCompileShader", 10, X_CompileShader}, {"D3DXCompileShaderFromFileA", 9, X_CompileShaderFromFileA},
    {"D3DXAssembleShader", 7, X_AssembleShader}, {"D3DXAssembleShaderFromFileA", 6, X_AssembleShaderFromFileA},
    {"D3DXCreateEffect", 9, X_CreateEffect}, {"D3DXCreateEffectCompiler", 7, X_CreateEffectCompiler},
    {"D3DXCreateTexture", 8, X_CreateTexture}, {"D3DXCreateTextureFromFileInMemory", 4, X_CreateTextureFromFileInMemory},
    {"D3DXCreateCubeTextureFromFileInMemory", 4, X_CreateCubeTextureFromFileInMemory},
    {"D3DXCreateVolumeTextureFromFileInMemory", 4, X_CreateVolumeTextureFromFileInMemory},
    {"D3DXCreateTextureFromFileExA", 14, X_CreateTextureFromFileExA}, {"D3DXCreateCubeTextureFromFileExA", 13, X_CreateCubeTextureFromFileExA},
    {"D3DXCreateVolumeTextureFromFileExA", 15, X_CreateVolumeTextureFromFileExA},
    {"D3DXGetImageInfoFromFileInMemory", 3, X_GetImageInfoFromFileInMemory},
    {"D3DXLoadSurfaceFromSurface", 8, X_LoadSurfaceFromSurface}, {"D3DXSaveSurfaceToFileA", 5, X_SaveSurfaceToFileA},
};
const int g_d3dx9_nimports = (int)(sizeof g_d3dx9_imports / sizeof g_d3dx9_imports[0]);
