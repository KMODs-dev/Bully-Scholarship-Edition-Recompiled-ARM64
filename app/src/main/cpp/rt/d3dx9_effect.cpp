// ID3DXEffect sobre efeitos JA COMPILADOS (binario fx_2_0, assinatura 0xFEFF0901) — e o que o Bully usa (846 arquivos).
// Nao ha compilador: efeitos em texto falham (o log avisa).
//
// Formato (validado nos 846 efeitos do Bully): [FEFF0901][offset] e a partir do byte 8 a "area de dados"; em 8+offset:
//   nparams, ntechs, ?, nobjects; parametros (tipo, valor, flags, anotacoes); tecnicas -> passadas -> estados;
//   strings (id do objeto + texto); recursos (bytecode de shader ou nome de parametro ligado a um estado).
// Shaders podem ter "preshader" (comentario PRES: CTAB de entradas, CLIT literais em double, FXLC codigo) que calcula
// constantes na CPU a partir dos parametros.
#include "x86rt.h"
#include "d3d9_com.h"
#include "d3d9_internal.h"
#include <math.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <strings.h>
#include <initializer_list>

#define F(name) static uint32_t name(Cpu &c, const uint32_t *a)

void d3d_set_render_state(uint32_t rs, uint32_t v);
void d3d_set_sampler_state(uint32_t s, uint32_t t, uint32_t v);
void d3d_set_texture(uint32_t s, uint32_t tex);
void d3d_set_vs(uint32_t obj);
void d3d_set_ps(uint32_t obj);
void d3d_shader_const_f(bool pixel, uint32_t reg, const float *v, uint32_t n);
void d3d_shader_const_i(bool pixel, uint32_t reg, const int32_t *v, uint32_t n);
void d3d_shader_const_b(bool pixel, uint32_t reg, const uint32_t *v, uint32_t n);
uint32_t d3d_create_shader(bool pixel, const uint32_t *code, uint32_t ndw);
void *d3d_state_save();
void d3d_state_restore(void *p);
uint32_t d3d_device_obj();
float *d3d_shader_consts(bool pixel);

enum { PT_VOID, PT_BOOL, PT_INT, PT_FLOAT, PT_STRING, PT_TEXTURE, PT_TEXTURE1D, PT_TEXTURE2D, PT_TEXTURE3D, PT_TEXTURECUBE,
       PT_SAMPLER, PT_SAMPLER1D, PT_SAMPLER2D, PT_SAMPLER3D, PT_SAMPLERCUBE, PT_PIXELSHADER, PT_VERTEXSHADER };
enum { PC_SCALAR, PC_VECTOR, PC_MROWS, PC_MCOLS, PC_OBJECT, PC_STRUCT };
static bool is_sampler(uint32_t t) { return t >= PT_SAMPLER && t <= PT_SAMPLERCUBE; }

// operacao de estado do efeito -> render state do D3D9 (operacoes 0..102 na ordem da tabela do D3DX)
static const uint16_t kRS[103] = {
    7, 8, 9, 14, 15, 16, 19, 20, 22, 23, 24, 25, 26, 27, 28, 29, 34, 35, 36, 37, 38, 48, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    128, 129, 130, 131, 132, 133, 134, 135, 198, 199, 200, 201, 202, 203, 204, 205,
    136, 137, 139, 140, 141, 142, 143, 145, 146, 147, 148, 151, 152, 154, 155, 166, 156, 157, 158, 159, 160, 161, 162, 163,
    165, 167, 168, 170, 171, 172, 173, 174, 175, 176, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189,
    190, 191, 192, 193, 194, 195, 206, 207, 208, 209};
// render states cujo valor e float (o valor do efeito vai em bits)
static bool rs_is_float(uint32_t rs) {
    switch (rs) { case 36: case 37: case 38: case 154: case 155: case 158: case 159: case 160: case 166: case 170: case 175:
                  case 178: case 179: case 180: case 181: case 182: case 183: case 195: return true; }
    return false;
}

struct ShaderInfo;
struct FxState { uint32_t op = 0, idx = 0; int par = -1; int ref = -1; std::string refname; ShaderInfo *expr = nullptr; };
struct FxParam {
    uint32_t type = 0, cls = 0, rows = 0, cols = 0, elems = 0, nmembers = 0, bytes = 0, flags = 0;
    uint32_t name_g = 0, sem_g = 0; std::string name, sem;
    std::vector<int> members, annots;
    uint32_t off = 0;             // deslocamento no buffer de valores (numericos: dados; objetos: 4 bytes com o ponteiro do jogo)
    std::vector<FxState> states;  // samplers
    uint32_t oid = 0xFFFFFFFFu;
    uint32_t handle = 0;
};
struct ShConst { int param; uint32_t set, reg, count; uint32_t cls = 0; std::vector<float> last; uint32_t b0 = 0, b1 = 0, seen = 0; };   // b0..b1: blocos de 16 bytes de val que o parametro usa; seen: geracao do ultimo empacotamento   // last: ultimo envio (CommitChanges so reenvia o que mudou)
struct PresIns { uint32_t op, comp, nin; uint32_t tab[4], off[4]; };
struct ShaderInfo {
    bool pixel = false;
    uint32_t obj = 0, code_g = 0;
    std::vector<ShConst> consts;
    std::vector<std::pair<int, uint32_t>> samplers;   // (parametro sampler, unidade)
    std::vector<uint32_t> smp_last;                   // ultimo valor enviado de cada estado de sampler (16 por sampler)
    std::vector<float> pres_last; uint32_t pres_seen = 0;                     // ultima saida do preshader enviada
    bool pres = false;
    std::vector<ShConst> pin;                         // entradas do preshader (registradores float4)
    uint32_t pin_regs = 0, ntemp = 0;
    std::vector<float> lit;
    std::vector<PresIns> code;
};
struct FxPass { std::string name; uint32_t name_g = 0, handle = 0; std::vector<int> annots; std::vector<FxState> states; ShaderInfo *vs = nullptr, *ps = nullptr; };
struct FxTech { std::string name; uint32_t name_g = 0, handle = 0; std::vector<int> annots; std::vector<FxPass> passes; };

struct Effect : Res {
    std::vector<uint8_t> blob; uint32_t gb = 0;   // copia do arquivo (host e jogo)
    std::vector<FxParam> P;                       // todos os parametros (topo, membros, anotacoes, parametros de estado)
    std::vector<int> top;
    std::vector<FxTech> T;
    std::vector<uint8_t> val;
    uint32_t wgen = 1; std::vector<uint32_t> bgen;   // geracao da ultima escrita em cada bloco de 16 bytes de val
    std::map<uint32_t, int> objects;              // id do objeto -> parametro
    std::map<uint32_t, ShaderInfo *> shaders;     // id do objeto -> shader
    uint32_t hbase = 0, nh = 0;
    std::vector<std::pair<int, int>> hnode;       // handle -> (tipo 0 param / 1 tecnica / 2 passada, indice; passada = tec<<16|p)
    int cur_tech = 0, cur_pass = -1;
    void *saved = nullptr;
    uint32_t state_mgr = 0;
    // ---- leitura
    const uint8_t *B() const { return blob.data(); }
    uint32_t u32(size_t p) const { uint32_t v; memcpy(&v, B() + p, 4); return v; }
};

static bool g_fx_log_unk = true;

// ================================================================ leitura do binario
struct Reader {
    Effect *e; size_t base; bool ok = true;
    uint32_t at(size_t p) { if (p + 4 > e->blob.size()) { ok = false; return 0; } return e->u32(p); }
    void name(uint32_t off, std::string &s, uint32_t &g) {
        const size_t p = base + off; const uint32_t n = at(p);
        if (!n || p + 4 + n > e->blob.size()) { s.clear(); g = 0; return; }
        s.assign((const char *)e->B() + p + 4, strnlen((const char *)e->B() + p + 4, n));
        g = e->gb + (uint32_t)p + 4;
    }
    // tipo do parametro a partir de q (absoluto); com pai = copia do pai (elemento de array)
    int typedef_(size_t &q, int parent) {
        const int idx = (int)e->P.size(); e->P.emplace_back();
        if (parent < 0) {
            FxParam t;
            t.type = at(q); t.cls = at(q + 4);
            name(at(q + 8), t.name, t.name_g); name(at(q + 12), t.sem, t.sem_g);
            t.elems = at(q + 16); q += 20;
            if (t.cls == PC_VECTOR) { t.cols = at(q); t.rows = at(q + 4); q += 8; }
            else if (t.cls == PC_SCALAR || t.cls == PC_MROWS || t.cls == PC_MCOLS) { t.rows = at(q); t.cols = at(q + 4); q += 8; }   // matriz: linhas, colunas (mBone float4x3 = 4x3)
            else if (t.cls == PC_STRUCT) { t.nmembers = at(q); q += 4; }
            t.bytes = (t.cls <= PC_MCOLS) ? 4 * t.rows * t.cols : (t.cls == PC_OBJECT ? 4 : 0);
            e->P[idx] = t;
        } else {
            FxParam t = e->P[parent];
            t.elems = 0; t.members.clear(); t.annots.clear(); t.states.clear(); t.handle = 0;
            t.bytes = (t.cls <= PC_MCOLS) ? 4 * t.rows * t.cols : (t.cls == PC_OBJECT ? 4 : 0);
            e->P[idx] = t;
        }
        if (e->P[idx].elems) {
            const size_t save = q; uint32_t tot = 0; std::vector<int> mem;
            for (uint32_t i = 0; i < e->P[idx].elems && ok; ++i) { q = save; const int m = typedef_(q, idx); mem.push_back(m); tot += e->P[m].bytes; }
            e->P[idx].members = mem; e->P[idx].bytes = tot;
            e->P[idx].off = mem.empty() ? 0 : e->P[mem[0]].off;
        } else if (e->P[idx].nmembers) {
            uint32_t tot = 0; std::vector<int> mem;
            for (uint32_t i = 0; i < e->P[idx].nmembers && ok; ++i) { const int m = typedef_(q, -1); mem.push_back(m); tot += e->P[m].bytes; }
            e->P[idx].members = mem; e->P[idx].bytes = tot;
            e->P[idx].off = mem.empty() ? 0 : e->P[mem[0]].off;
        } else {
            e->P[idx].off = (uint32_t)e->val.size();
            e->val.resize(e->val.size() + ((e->P[idx].bytes + 3) & ~3u), 0);
        }
        return idx;
    }
    void value(int pi, size_t &q) {
        FxParam &t = e->P[pi];
        if (!t.members.empty()) { std::vector<int> m = t.members; for (int x : m) value(x, q); return; }
        if (t.cls <= PC_MCOLS) {
            if (q + t.bytes <= e->blob.size()) memcpy(e->val.data() + t.off, e->B() + q, t.bytes); else ok = false;
            q += t.bytes; return;
        }
        if (t.cls == PC_OBJECT) {
            if (is_sampler(t.type)) {
                const uint32_t n = at(q); q += 4;
                for (uint32_t i = 0; i < n && ok; ++i) { FxState s = state(q); e->P[pi].states.push_back(s); }
                return;
            }
            const uint32_t oid = at(q); q += 4;
            e->P[pi].oid = oid; e->objects[oid] = pi;
        }
    }
    FxState state(size_t &q) {
        FxState s; s.op = at(q); s.idx = at(q + 4);
        size_t tq = base + at(q + 8), vq = base + at(q + 12); q += 16;
        s.par = typedef_(tq, -1); value(s.par, vq);
        return s;
    }
    int annot(size_t &q) {
        size_t tq = base + at(q), vq = base + at(q + 4); q += 8;
        const int p = typedef_(tq, -1); value(p, vq); return p;
    }
};

// ---- CTAB (host): chama f(nome, regset, reg, count) para cada constante
static uint32_t g_ct_cls = 0;
template <class Fn> static void ctab_each(const uint32_t *ct, uint32_t ndw, Fn f) {
    const uint8_t *b = (const uint8_t *)ct; const uint32_t sz = 4 * ndw;
    if (sz < 28) return;
    uint32_t n, info; memcpy(&n, b + 12, 4); memcpy(&info, b + 16, 4);
    for (uint32_t k = 0; k < n && info + 20 * (k + 1) <= sz; ++k) {
        const uint8_t *ci = b + info + 20 * k; uint32_t no, ti; uint16_t set, reg, cnt;
        memcpy(&no, ci, 4); memcpy(&set, ci + 4, 2); memcpy(&reg, ci + 6, 2); memcpy(&cnt, ci + 8, 2); memcpy(&ti, ci + 12, 4);
        g_ct_cls = 0; if (ti + 2 <= sz) { uint16_t c; memcpy(&c, b + ti, 2); g_ct_cls = c; }   // classe no shader (linhas/colunas)
        if (no < sz) f((const char *)b + no, set, reg, cnt);
    }
}
// comentarios de um bytecode (a partir de i): devolve ponteiro para o conteudo depois do fourcc
static const uint32_t *find_comment(const uint32_t *w, uint32_t n, uint32_t i, uint32_t tag, uint32_t &len) {
    while (i < n) {
        const uint32_t t = w[i];
        if ((t & 0xFFFF) != 0xFFFE) break;
        const uint32_t l = (t >> 16) & 0x7FFF;
        if (l >= 1 && i + 1 < n && w[i + 1] == tag) { len = l - 1; return w + i + 2; }
        i += 1 + l;
    }
    len = 0; return nullptr;
}
#define TAG(a, b, c, d) ((uint32_t)(a) | ((uint32_t)(b) << 8) | ((uint32_t)(c) << 16) | ((uint32_t)(d) << 24))

static int find_top(Effect *e, const char *name) {
    for (int i : e->top) if (e->P[i].name == name) return i;
    return -1;
}

static void parse_pres(Effect *e, ShaderInfo *s, const uint32_t *pr, uint32_t pn);
static ShaderInfo *make_shader_info(Effect *e, const uint32_t *w, uint32_t n, uint32_t code_g) {
    ShaderInfo *s = new ShaderInfo;
    s->pixel = (w[0] >> 16) == 0xFFFF;
    s->code_g = code_g;
    s->obj = d3d_create_shader(s->pixel, w, n);
    uint32_t len;
    if (const uint32_t *ct = find_comment(w, n, 1, TAG('C', 'T', 'A', 'B'), len)) {
        ctab_each(ct, len, [&](const char *nm, uint32_t set, uint32_t reg, uint32_t cnt) {
            const int p = find_top(e, nm);
            if (p < 0) { rt_log("[fx] constante %s sem parametro\n", nm); return; }
            if (set == 3) s->samplers.push_back({p, s->pixel ? reg : 257 + reg});
            else s->consts.push_back({p, set, reg, cnt, g_ct_cls});
        });
    }
    const uint32_t *pr = find_comment(w, n, 1, TAG('P', 'R', 'E', 'S'), len);
    if (pr && len >= 2) parse_pres(e, s, pr, len);
    return s;
}
// preshader / expressao: versao (FX) + comentarios CTAB (entradas), CLIT (literais) e FXLC (codigo)
static void parse_pres(Effect *e, ShaderInfo *s, const uint32_t *pr, uint32_t pn) {
    {   uint32_t l2;
        if (const uint32_t *ct = find_comment(pr, pn, 1, TAG('C', 'T', 'A', 'B'), l2))
            ctab_each(ct, l2, [&](const char *nm, uint32_t set, uint32_t reg, uint32_t cnt) {
                const int p = find_top(e, nm);
                if (p < 0) { rt_log("[fx] entrada de preshader %s sem parametro\n", nm); return; }
                s->pin.push_back({p, set, reg, cnt, g_ct_cls});
                if (reg + cnt > s->pin_regs) s->pin_regs = reg + cnt;
            });
        if (const uint32_t *cl = find_comment(pr, pn, 1, TAG('C', 'L', 'I', 'T'), l2)) {
            const uint32_t cnt = l2 ? cl[0] : 0;
            for (uint32_t i = 0; i < cnt && 1 + 2 * i + 1 < l2 + 1; ++i) { double d; memcpy(&d, cl + 1 + 2 * i, 8); s->lit.push_back((float)d); }
        }
        if (const uint32_t *fx = find_comment(pr, pn, 1, TAG('F', 'X', 'L', 'C'), l2)) {
            const uint32_t ni = l2 ? fx[0] : 0; uint32_t i = 1; bool ok = true;
            for (uint32_t k = 0; k < ni && ok; ++k) {
                if (i + 2 > l2) { ok = false; break; }
                PresIns in{}; in.op = fx[i] >> 16; in.comp = fx[i] & 0xFFFF; in.nin = fx[i + 1]; i += 2;
                if (in.nin > 3) { ok = false; break; }
                for (uint32_t j = 0; j <= in.nin; ++j) {
                    if (i + 3 > l2) { ok = false; break; }
                    if (fx[i]) { rt_log("[fx] preshader com enderecamento relativo (nao suportado)\n"); ok = false; break; }
                    in.tab[j] = fx[i + 1]; in.off[j] = fx[i + 2]; i += 3;
                    if (in.tab[j] == 7 && in.off[j] + in.comp > s->ntemp) s->ntemp = in.off[j] + in.comp;
                }
                s->code.push_back(in);
            }
            s->pres = ok && !s->code.empty();
            if (!ok) rt_log("[fx] preshader nao lido\n");
        }
    }
}

static Effect *effect_parse(const uint8_t *data, uint32_t size) {
    Effect *e = new Effect; e->type = RT_XEFFECT;
    e->blob.assign(data, data + size);
    e->gb = rt_alloc(size, false); memcpy(M + e->gb, data, size);
    Reader r{e, 8};
    size_t q = 8 + r.at(4);
    const uint32_t np = r.at(q), nt = r.at(q + 4); q += 16;
    for (uint32_t i = 0; i < np && r.ok; ++i) {
        size_t tq = 8 + r.at(q), vq = 8 + r.at(q + 4); const uint32_t flags = r.at(q + 8), na = r.at(q + 12); q += 16;
        const int p = r.typedef_(tq, -1); r.value(p, vq);
        e->P[p].flags = flags; e->top.push_back(p);
        for (uint32_t k = 0; k < na && r.ok; ++k) { const int an = r.annot(q); e->P[p].annots.push_back(an); }
    }
    for (uint32_t i = 0; i < nt && r.ok; ++i) {
        FxTech t; r.name(r.at(q), t.name, t.name_g); const uint32_t na = r.at(q + 4), npass = r.at(q + 8); q += 12;
        for (uint32_t k = 0; k < na && r.ok; ++k) t.annots.push_back(r.annot(q));
        for (uint32_t j = 0; j < npass && r.ok; ++j) {
            FxPass ps; r.name(r.at(q), ps.name, ps.name_g); const uint32_t pa = r.at(q + 4), ns = r.at(q + 8); q += 12;
            for (uint32_t k = 0; k < pa && r.ok; ++k) ps.annots.push_back(r.annot(q));
            for (uint32_t k = 0; k < ns && r.ok; ++k) ps.states.push_back(r.state(q));
            t.passes.push_back(ps);
        }
        e->T.push_back(t);
    }
    const uint32_t nstr = r.at(q), nres = r.at(q + 4); q += 8;
    for (uint32_t i = 0; i < nstr && r.ok; ++i) {
        const uint32_t oid = r.at(q), n = r.at(q + 4);
        auto it = e->objects.find(oid);
        if (it != e->objects.end()) { const uint32_t g = e->gb + (uint32_t)q + 8; memcpy(e->val.data() + e->P[it->second].off, &g, 4); }
        q += 8 + ((n + 3) & ~3u);
    }
    for (uint32_t i = 0; i < nres && r.ok; ++i) {
        const uint32_t ti = r.at(q), idx = r.at(q + 4), ei = r.at(q + 8), si = r.at(q + 12), usage = r.at(q + 16); q += 20;
        FxState *st = nullptr;
        if (ti == 0xFFFFFFFFu) {
            if (idx < e->top.size()) {
                int p = e->top[idx];
                if (ei != 0xFFFFFFFFu && ei < e->P[p].members.size()) p = e->P[p].members[ei];
                if (si < e->P[p].states.size()) st = &e->P[p].states[si];
            }
        } else if (ti < e->T.size() && idx < e->T[ti].passes.size() && si < e->T[ti].passes[idx].states.size()) st = &e->T[ti].passes[idx].states[si];
        const uint32_t n = r.at(q);
        const size_t dp = q + 4; q += 4 + ((n + 3) & ~3u);
        if (!st) { rt_log("[fx] recurso sem estado (t=%u i=%u)\n", ti, idx); continue; }
        if (usage == 0) {   // bytecode de shader para o objeto do parametro do estado
            const FxParam &sp = e->P[st->par];
            if ((sp.type == PT_VERTEXSHADER || sp.type == PT_PIXELSHADER) && n >= 8)
                e->shaders[sp.oid] = make_shader_info(e, (const uint32_t *)(e->B() + dp), n / 4, e->gb + (uint32_t)dp);
            else if (n >= 8) {   // expressao (ex.: ColorWriteEnable = iColorWriteEnable * 15): avaliada a cada passada
                ShaderInfo *x = new ShaderInfo;
                parse_pres(e, x, (const uint32_t *)(e->B() + dp), n / 4);
                if (x->pres) st->expr = x; else { delete x; rt_log("[fx] expressao de estado nao lida\n"); }
            }
        } else if (usage == 1) {   // estado ligado a um parametro pelo nome
            st->refname.assign((const char *)e->B() + dp, strnlen((const char *)e->B() + dp, n));
            st->ref = find_top(e, st->refname.c_str());
            if (st->ref < 0) rt_log("[fx] estado ligado a parametro desconhecido %s\n", st->refname.c_str());
        } else rt_log("[fx] recurso de uso %u (expressao) ainda nao suportado\n", usage);
    }
    if (!r.ok) { rt_log("[fx] efeito truncado/invalido\n"); return nullptr; }
    // shaders de cada passada
    for (FxTech &t : e->T) for (FxPass &p : t.passes) for (FxState &s : p.states)
        if (s.op == 146 || s.op == 147) {
            auto it = e->shaders.find(e->P[s.par].oid);
            if (it != e->shaders.end()) (s.op == 146 ? p.vs : p.ps) = it->second;
        }
    // handles: um por parametro, tecnica e passada
    e->nh = (uint32_t)e->P.size();
    for (FxTech &t : e->T) e->nh += 1 + (uint32_t)t.passes.size();
    e->hbase = rt_alloc(4 * e->nh + 4, true);
    uint32_t k = 0;
    for (size_t i = 0; i < e->P.size(); ++i) { e->P[i].handle = e->hbase + 4 * k++; e->hnode.push_back({0, (int)i}); }
    for (size_t i = 0; i < e->T.size(); ++i) {
        e->T[i].handle = e->hbase + 4 * k++; e->hnode.push_back({1, (int)i});
        for (size_t j = 0; j < e->T[i].passes.size(); ++j) { e->T[i].passes[j].handle = e->hbase + 4 * k++; e->hnode.push_back({2, (int)((i << 16) | j)}); }
    }
    return e;
}

// ================================================================ handles
static const char *gs(uint32_t p) { return p ? (const char *)M + p : ""; }
static bool is_handle(Effect *e, uint32_t h) { return h >= e->hbase && h < e->hbase + 4 * e->nh; }
static int param_by_path(Effect *e, const char *s) {
    // "nome", "nome.membro", "nome[3]"
    std::string str(s); int cur = -1; size_t i = 0;
    while (i <= str.size()) {
        size_t j = str.find_first_of(".[", i); if (j == std::string::npos) j = str.size();
        const std::string part = str.substr(i, j - i);
        if (!part.empty()) {
            if (cur < 0) cur = find_top(e, part.c_str());
            else { int f = -1; for (int m : e->P[cur].members) if (e->P[m].name == part) { f = m; break; } cur = f; }
            if (cur < 0) return -1;
        }
        if (j < str.size() && str[j] == '[') {
            const size_t k = str.find(']', j); const uint32_t n = (uint32_t)atoi(str.c_str() + j + 1);
            if (cur < 0 || n >= e->P[cur].members.size() || !e->P[cur].elems) return -1;
            cur = e->P[cur].members[n]; i = (k == std::string::npos ? str.size() : k + 1);
            if (i < str.size() && str[i] == '.') ++i;
            continue;
        }
        i = j + 1;
    }
    return cur;
}
static int param_of(Effect *e, uint32_t h) {
    if (!h) return -1;
    if (is_handle(e, h)) { auto &n = e->hnode[(h - e->hbase) / 4]; return n.first == 0 ? n.second : -1; }
    return param_by_path(e, gs(h));
}
static int tech_of(Effect *e, uint32_t h) {
    if (!h) return -1;
    if (is_handle(e, h)) { auto &n = e->hnode[(h - e->hbase) / 4]; return n.first == 1 ? n.second : -1; }
    for (size_t i = 0; i < e->T.size(); ++i) if (e->T[i].name == gs(h)) return (int)i;
    return -1;
}
static FxPass *pass_of(Effect *e, uint32_t h) {
    if (!is_handle(e, h)) return nullptr;
    auto &n = e->hnode[(h - e->hbase) / 4]; if (n.first != 2) return nullptr;
    return &e->T[n.second >> 16].passes[n.second & 0xFFFF];
}
static std::vector<int> *annots_of(Effect *e, uint32_t h) {
    if (!is_handle(e, h)) { const int p = param_of(e, h); if (p >= 0) return &e->P[p].annots; const int t = tech_of(e, h); return t >= 0 ? &e->T[t].annots : nullptr; }
    auto &n = e->hnode[(h - e->hbase) / 4];
    if (n.first == 0) return &e->P[n.second].annots;
    if (n.first == 1) return &e->T[n.second].annots;
    return &e->T[n.second >> 16].passes[n.second & 0xFFFF].annots;
}

// ================================================================ valores
// le/grava o componente i (em floats/ints) de um parametro numerico, convertendo pelo tipo
static float getf(Effect *e, const FxParam &p, uint32_t i) {
    uint32_t v; memcpy(&v, e->val.data() + p.off + 4 * i, 4);
    if (p.type == PT_FLOAT) { float f; memcpy(&f, &v, 4); return f; }
    if (p.type == PT_INT) return (float)(int32_t)v;
    return v ? 1.0f : 0.0f;
}
// marca os bytes [off, off+len) de val como alterados (CommitChanges so reempacota parametros com blocos mais novos)
static void mark(Effect *e, uint32_t off, uint32_t len) {
    if (e->bgen.size() != e->val.size() / 16 + 1) e->bgen.assign(e->val.size() / 16 + 1, 0);
    if (!len) return;
    const uint32_t g = ++e->wgen;
    for (uint32_t b = off / 16, b1 = (off + len - 1) / 16; b <= b1 && b < e->bgen.size(); ++b) e->bgen[b] = g;
}
static void param_range(Effect *e, int pi, uint32_t &lo, uint32_t &hi) {
    const FxParam &p = e->P[pi];
    if (p.bytes) { lo = std::min(lo, p.off); hi = std::max(hi, p.off + p.bytes); }
    for (int m : p.members) param_range(e, m, lo, hi);
}
// maior geracao de escrita nos blocos do parametro (calcula a faixa na primeira vez)
static uint32_t const_gen(Effect *e, ShConst &k) {
    if (!k.b1) { uint32_t lo = 0xFFFFFFFFu, hi = 0; param_range(e, k.param, lo, hi); if (hi > lo) { k.b0 = lo / 16; k.b1 = (hi - 1) / 16 + 1; } else { k.b0 = 0; k.b1 = 1; } }
    if (e->bgen.size() != e->val.size() / 16 + 1) e->bgen.assign(e->val.size() / 16 + 1, 0);
    uint32_t g = 0; for (uint32_t b = k.b0; b < k.b1 && b < e->bgen.size(); ++b) if (e->bgen[b] > g) g = e->bgen[b];
    return g;
}
static void setf(Effect *e, const FxParam &p, uint32_t i, float f) {
    mark(e, p.off + 4 * i, 4);
    uint32_t v;
    if (p.type == PT_FLOAT) memcpy(&v, &f, 4); else if (p.type == PT_INT) v = (uint32_t)(int32_t)lrintf(f); else v = f != 0.0f;
    memcpy(e->val.data() + p.off + 4 * i, &v, 4);
}
static uint32_t ncomp(const FxParam &p) { return p.bytes / 4; }
static const FxParam &leaf(Effect *e, int p, uint32_t elem = 0) {
    const FxParam &x = e->P[p];
    if (x.elems && elem < x.members.size()) return e->P[x.members[elem]];
    return x;
}
// matriz logica (linha r, coluna c) <-> armazenamento (MCOLS guarda coluna a coluna, como nos registradores)
static uint32_t midx(const FxParam &p, uint32_t r, uint32_t c) { return p.cls == PC_MCOLS ? c * p.rows + r : r * p.cols + c; }


// ---- gerenciador de estados do jogo (ID3DXEffectStateManager): o Gamebryo guarda os estados no proprio cache; se o
// efeito escrevesse direto no dispositivo, o cache do jogo ficaria errado. Com gerenciador, chama os metodos dele.
static Cpu *g_fx_cpu = nullptr;          // Cpu da thread que chamou o metodo do efeito
static uint32_t g_fx_mgr = 0, g_fx_scratch = 0;
static uint32_t mgr_call(int idx, std::initializer_list<uint32_t> args) {
    Cpu &c = *g_fx_cpu;
    const uint32_t fn = rd32(rd32(g_fx_mgr) + 4 * idx);
    const uint32_t save_esp = c.r[4];
    c.r[4] -= 4u * (uint32_t)args.size();   // argumentos direto na pilha do jogo (antes: std::vector alocado a cada chamada)
    uint32_t sp = c.r[4]; for (uint32_t v : args) { wr32(sp, v); sp += 4; }
    c.r[4] -= 4; wr32(c.r[4], g_fx_mgr);
    c.r[4] -= 4; wr32(c.r[4], 0xDEAD0002u);
    x86_call(c, fn);
    c.r[4] = save_esp;
    return c.r[0];
}
static bool use_mgr() { return g_fx_mgr && g_fx_cpu; }
static void st_rs(uint32_t rs, uint32_t v) { if (use_mgr()) mgr_call(7, {rs, v}); else d3d_set_render_state(rs, v); }
static void st_tex(uint32_t unit, uint32_t t) { if (use_mgr()) mgr_call(8, {unit, t}); else d3d_set_texture(unit, t); }
static void st_ss(uint32_t unit, uint32_t k, uint32_t v) { if (use_mgr()) mgr_call(10, {unit, k, v}); else d3d_set_sampler_state(unit, k, v); }
static void st_vs(uint32_t o) { if (use_mgr()) mgr_call(13, {o}); else d3d_set_vs(o); }
static void st_ps(uint32_t o) { if (use_mgr()) mgr_call(17, {o}); else d3d_set_ps(o); }
static void st_cf(bool pixel, uint32_t reg, const float *v, uint32_t n) {
    if (!use_mgr()) { d3d_shader_const_f(pixel, reg, v, n); return; }
    if (n > 256) n = 256; memcpy(M + g_fx_scratch, v, 16 * n); mgr_call(pixel ? 18 : 14, {reg, g_fx_scratch, n});
}
static void st_ci(bool pixel, uint32_t reg, const int32_t *v, uint32_t n) {
    if (!use_mgr()) { d3d_shader_const_i(pixel, reg, v, n); return; }
    memcpy(M + g_fx_scratch, v, 16 * n); mgr_call(pixel ? 19 : 15, {reg, g_fx_scratch, n});
}
static void st_cb(bool pixel, uint32_t reg, const uint32_t *v, uint32_t n) {
    if (!use_mgr()) { d3d_shader_const_b(pixel, reg, v, n); return; }
    memcpy(M + g_fx_scratch, v, 4 * n); mgr_call(pixel ? 20 : 16, {reg, g_fx_scratch, n});
}

// empacota um parametro em registradores (float4) para o conjunto de constantes; devolve quantos registradores
// cls_sh: classe da constante no shader (CTAB). O D3DX transpoe quando o parametro e row_major e o shader espera
// colunas (ou o contrario): o registrador i e a linha i (MROWS) ou a coluna i (MCOLS) da matriz logica
static uint32_t pack_regs(Effect *e, int pi, float *out, uint32_t maxregs, uint32_t cls_sh = 0) {
    const FxParam &p = e->P[pi];
    uint32_t r = 0;
    auto one = [&](const FxParam &l) {
        const bool mat = l.cls == PC_MROWS || l.cls == PC_MCOLS;
        const uint32_t pk = (mat && (cls_sh == PC_MROWS || cls_sh == PC_MCOLS)) ? cls_sh : l.cls;
        auto get = [&](uint32_t rr, uint32_t cc) { return getf(e, l, midx(l, rr, cc)); };
        if (mat && pk == PC_MROWS) { for (uint32_t i = 0; i < l.rows && r < maxregs; ++i, ++r) for (uint32_t j = 0; j < 4; ++j) out[4 * r + j] = j < l.cols ? get(i, j) : 0.0f; }
        else if (mat) { for (uint32_t i = 0; i < l.cols && r < maxregs; ++i, ++r) for (uint32_t j = 0; j < 4; ++j) out[4 * r + j] = j < l.rows ? get(j, i) : 0.0f; }
        else if (l.cls <= PC_VECTOR) { if (r < maxregs) { const uint32_t n = ncomp(l); for (uint32_t j = 0; j < 4; ++j) out[4 * r + j] = j < n ? getf(e, l, j) : 0.0f; ++r; } }
    };
    std::vector<int> stack;
    if (!p.members.empty()) { for (int m : p.members) { const FxParam &l = e->P[m]; if (l.members.empty()) one(l); else { r += pack_regs(e, m, out + 4 * r, maxregs - r, cls_sh); } } }
    else one(p);
    return r;
}

static void run_pres(Effect *e, ShaderInfo *s, float *outv, uint32_t lim, uint32_t &lo, uint32_t &hi);
static void upload_consts(Effect *e, ShaderInfo *s, bool force) {
    float buf[4 * 256];
    for (ShConst &k : s->consts) {
        const uint32_t cnt = k.count > 256 ? 256 : k.count;
        uint32_t n;
        const uint32_t g = const_gen(e, k);
        if (!k.last.empty() && g <= k.seen) {   // parametro sem escrita desde o ultimo empacotamento
            if (!force) continue;
            n = (uint32_t)(k.last.size() / 4); memcpy(buf, k.last.data(), 16 * n);   // BeginPass: reenvia sem reempacotar
        } else {
            k.seen = e->wgen;
            memset(buf, 0, 16 * cnt);
            n = pack_regs(e, k.param, buf, cnt, k.cls);
            if (!n) { k.last.clear(); continue; }
            if (!force && k.last.size() == 4 * n && !memcmp(k.last.data(), buf, 16 * n)) continue;   // nao mudou desde o ultimo envio
            k.last.assign(buf, buf + 4 * n);
        }
        if (k.set == 2) st_cf(s->pixel, k.reg, buf, n);
        else if (k.set == 1) { int32_t iv[4 * 16]; const uint32_t m = n > 16 ? 16 : n; for (uint32_t i = 0; i < 4 * m; ++i) iv[i] = (int32_t)lrintf(buf[i]); st_ci(s->pixel, k.reg, iv, m); }
        else if (k.set == 0) { uint32_t bv[16]; const uint32_t m = n > 16 ? 16 : n; for (uint32_t i = 0; i < m; ++i) bv[i] = buf[4 * i] != 0.0f; st_cb(s->pixel, k.reg, bv, m); }
    }
    if (!s->pres) return;
    {   // entradas do preshader sem escrita desde a ultima execucao: a saida e a mesma
        bool same = !s->pres_last.empty();
        for (ShConst &k : s->pin) if (!same || const_gen(e, k) > s->pres_seen) { same = false; break; }
        if (same) {
            if (force) { const uint32_t lo = (uint32_t)s->pres_last[0], n = (uint32_t)((s->pres_last.size() - 1) / 4); st_cf(s->pixel, lo, s->pres_last.data() + 1, n); }
            return;
        }
        s->pres_seen = e->wgen;
    }
    float outv[4 * 256]; uint32_t touched_lo = 256, touched_hi = 0;
    const uint32_t lim = s->pixel ? 224u : 256u;
    memcpy(outv, d3d_shader_consts(s->pixel), 16 * lim);
    run_pres(e, s, outv, lim, touched_lo, touched_hi);
    if (touched_hi > touched_lo) {
        const uint32_t n = touched_hi - touched_lo; const float *v = outv + 4 * touched_lo;
        if (!force && s->pres_last.size() == 4 * n + 1 && s->pres_last[0] == (float)touched_lo && !memcmp(s->pres_last.data() + 1, v, 16 * n)) return;
        s->pres_last.resize(4 * n + 1); s->pres_last[0] = (float)touched_lo; memcpy(s->pres_last.data() + 1, v, 16 * n);
        st_cf(s->pixel, touched_lo, v, n);
    }
}
static void run_pres(Effect *e, ShaderInfo *s, float *outv, uint32_t lim, uint32_t &touched_lo, uint32_t &touched_hi) {
    static thread_local std::vector<float> in, tmp;
    in.assign(4 * s->pin_regs + 4, 0.0f); tmp.assign(s->ntemp + 4, 0.0f);
    for (const ShConst &k : s->pin) pack_regs(e, k.param, in.data() + 4 * k.reg, k.count, k.cls);
    auto rd = [&](uint32_t tab, uint32_t off) -> float {
        switch (tab) {
        case 1: return off < s->lit.size() ? s->lit[off] : 0.0f;
        case 2: return off < in.size() ? in[off] : 0.0f;
        case 4: return off < 4 * 256 ? outv[off] : 0.0f;
        case 7: return off < tmp.size() ? tmp[off] : 0.0f;
        }
        return 0.0f;
    };
    auto wr = [&](uint32_t tab, uint32_t off, float v) {
        if (tab == 7) { if (off < tmp.size()) tmp[off] = v; }
        else if (tab == 4 && off < 4 * lim) { outv[off] = v; const uint32_t rg = off / 4; if (rg < touched_lo) touched_lo = rg; if (rg + 1 > touched_hi) touched_hi = rg + 1; }
    };
    for (const PresIns &ins : s->code) {
        const bool scalar = (ins.op & 0xF000) == 0xA000;
        const uint32_t op = scalar ? (ins.op & 0x0FFF) | 0x2000 : ins.op;
        if (op == 0x5000) {   // dot: todos os componentes -> 1
            float acc = 0; for (uint32_t i = 0; i < ins.comp; ++i) acc += rd(ins.tab[0], ins.off[0] + i) * rd(ins.tab[1], ins.off[1] + i);
            wr(ins.tab[ins.nin], ins.off[ins.nin], acc); continue;
        }
        for (uint32_t i = 0; i < ins.comp; ++i) {
            const float x = rd(ins.tab[0], ins.off[0] + (scalar ? 0 : i));
            const float y = ins.nin > 1 ? rd(ins.tab[1], ins.off[1] + i) : 0.0f;
            const float z = ins.nin > 2 ? rd(ins.tab[2], ins.off[2] + i) : 0.0f;
            float v;
            switch (op) {
            case 0x1000: v = x; break;
            case 0x1010: v = -x; break;
            case 0x1030: v = x == 0.0f ? INFINITY : 1.0f / x; break;
            case 0x1040: v = x - floorf(x); break;
            case 0x1050: v = exp2f(x); break;
            case 0x1060: v = x == 0.0f ? -INFINITY : log2f(fabsf(x)); break;
            case 0x1070: v = x == 0.0f ? INFINITY : 1.0f / sqrtf(fabsf(x)); break;
            case 0x1080: v = sinf(x); break;
            case 0x1090: v = cosf(x); break;
            case 0x2000: v = x < y ? x : y; break;
            case 0x2010: v = x > y ? x : y; break;
            case 0x2020: v = x < y ? 1.0f : 0.0f; break;
            case 0x2030: v = x >= y ? 1.0f : 0.0f; break;
            case 0x2040: v = x + y; break;
            case 0x2050: v = x * y; break;
            case 0x2060: v = atan2f(x, y); break;
            case 0x2080: v = x / y; break;
            case 0x3000: v = x >= 0.0f ? y : z; break;
            case 0x3010: v = x != 0.0f ? y : z; break;
            default: { static bool w = false; if (!w) { w = true; rt_log("[fx] operacao de preshader %04X nao suportada\n", ins.op); } v = 0; }
            }
            wr(ins.tab[ins.nin], ins.off[ins.nin] + i, v);
        }
    }
}

static uint32_t obj_val(Effect *e, int p) { uint32_t v; memcpy(&v, e->val.data() + e->P[p].off, 4); return v; }
static uint32_t state_dword(Effect *e, const FxState &s) {
    if (s.expr) {   // resultado da expressao em c0.x (float) convertido para o tipo do parametro do estado
        static thread_local float outv[4 * 256]; memset(outv, 0, 64 * sizeof(float)); uint32_t lo = 4, hi = 0;
        run_pres(e, s.expr, outv, 4, lo, hi);
        const uint32_t t = e->P[s.par].type; uint32_t v;
        if (t == PT_FLOAT) memcpy(&v, &outv[0], 4); else if (t == PT_BOOL) v = outv[0] != 0.0f; else v = (uint32_t)(int32_t)lrintf(outv[0]);
        return v;
    }
    const FxParam &p = e->P[s.ref >= 0 ? s.ref : s.par];   // estado ligado a parametro ("ColorWriteEnable = iColorWriteEnable")
    uint32_t v; memcpy(&v, e->val.data() + p.off, 4);
    return v;
}
static void apply_sampler(Effect *e, int sp, uint32_t unit, uint32_t *last, bool force) {
    for (const FxState &s : e->P[sp].states) {
        if (s.op == 164) { const int tp = s.ref >= 0 ? s.ref : -1; const uint32_t v = tp >= 0 ? obj_val(e, tp) : obj_val(e, s.par);
            if (force || last[0] != v) { last[0] = v; st_tex(unit, v); } }
        else if (s.op >= 165 && s.op <= 177) { const uint32_t k = s.op - 164, v = state_dword(e, s);
            if (force || last[k] != v) { last[k] = v; st_ss(unit, k, v); } }
    }
}
// force: BeginPass (envia tudo); sem force: CommitChanges (so o que mudou desde o ultimo envio, como o D3DX)
static void commit(Effect *e, bool force) {
    if (e->cur_pass < 0 || e->cur_tech < 0 || e->cur_tech >= (int)e->T.size()) return;
    FxPass &p = e->T[e->cur_tech].passes[e->cur_pass];
    for (ShaderInfo *s : {p.vs, p.ps}) {
        if (!s) continue;
        upload_consts(e, s, force);
        if (s->smp_last.size() != 16 * s->samplers.size()) { s->smp_last.assign(16 * s->samplers.size(), 0); force = true; }
        for (size_t i = 0; i < s->samplers.size(); ++i) apply_sampler(e, s->samplers[i].first, s->samplers[i].second, &s->smp_last[16 * i], force);
    }
}
// diagnostico (1 vez por tecnica): texturas nulas e constantes zeradas na primeira vez que a passada e usada
static void fx_audit(Effect *e, FxPass &p) {
    static std::set<std::string> seen; static int ntech = 0;
    const std::string key = e->T[e->cur_tech].name + "/" + p.name;
    if (ntech >= 150 || !seen.insert(key).second) return;
    ++ntech;
    std::string out;
    for (ShaderInfo *sh : {p.vs, p.ps}) {
        if (!sh) continue;
        for (auto &sm : sh->samplers) {
            uint32_t tv = 0;
            for (const FxState &st : e->P[sm.first].states) if (st.op == 164) tv = st.ref >= 0 ? obj_val(e, st.ref) : obj_val(e, st.par);
            Res *r = tv ? res_of(tv) : nullptr;
            char b[160]; snprintf(b, sizeof b, " | s%u %s=%s", sm.second, e->P[sm.first].name.c_str(), !tv ? "NULA" : !r ? "?" : r->type == RT_CUBE ? "cubo" : r->type == RT_VOLTEX ? "volume" : "2D");
            out += b;
        }
        for (ShConst &k : sh->consts) {
            if (k.set != 2) continue;
            float buf[4 * 64]; const uint32_t cnt = k.count > 64 ? 64 : k.count; memset(buf, 0, 16 * cnt);
            const uint32_t n = pack_regs(e, k.param, buf, cnt, k.cls);
            bool zero = true; for (uint32_t i = 0; i < 4 * n; ++i) if (buf[i] != 0.0f) { zero = false; break; }
            if (zero) { out += sh->pixel ? " | ps zero " : " | vs zero "; out += e->P[k.param].name; }
        }
    }
    rt_log("[fx-audit] %s%s\n", key.c_str(), out.c_str());
}
static void apply_pass(Effect *e) {
    FxPass &p = e->T[e->cur_tech].passes[e->cur_pass];
    for (const FxState &s : p.states) {
        if (s.op < 103) {
            const uint32_t rs = kRS[s.op]; const FxParam &sp = e->P[s.ref >= 0 ? s.ref : s.par];
            uint32_t v = state_dword(e, s);
            if (sp.type == PT_FLOAT && !rs_is_float(rs)) { float f; memcpy(&f, &v, 4); v = (uint32_t)(int32_t)f; }
            if (rs == 168) { static int n = 0; if (n < 30) { ++n; rt_log("[fx] passada %s: ColorWriteEnable = %X (parametro '%s' tipo %u%s%s)\n",
                e->T[e->cur_tech].name.c_str(), v, sp.name.c_str(), sp.type, s.ref >= 0 ? ", ligado a " : "", s.refname.c_str()); } }
            st_rs(rs, v);
        } else if (s.op == 146) st_vs(p.vs ? p.vs->obj : 0);
        else if (s.op == 147) st_ps(p.ps ? p.ps->obj : 0);
        else if (g_fx_log_unk) { rt_log("[fx] estado de passada %u nao suportado (ignorado)\n", s.op); }
    }
    commit(e, true);
}

// ================================================================ metodos
#define FX_ Effect *e = (Effect *)res_of(a[0]); if (!e) return D3DERR_INVALIDCALL_
#define PAR(h) const int pi = param_of(e, h); if (pi < 0) return D3DERR_INVALIDCALL_; FxParam &P_ = e->P[pi]; (void)P_
static uint32_t Unk_QI(Cpu &, const uint32_t *a) { com_addref(a[0]); if (a[2]) wr32(a[2], a[0]); return S_OK_; }
static uint32_t Unk_AddRef(Cpu &, const uint32_t *a) { return com_addref(a[0]); }
static uint32_t Unk_Release(Cpu &, const uint32_t *a) { return com_release(a[0]); }   // TODO: liberar o efeito

F(E_GetDesc) {
    FX_; static uint32_t creator = 0; if (!creator) { creator = rt_alloc(40, true); strcpy((char *)M + creator, "Microsoft (R) D3DX9 Shader Compiler"); }
    wr32(a[1], creator); wr32(a[1] + 4, (uint32_t)e->top.size()); wr32(a[1] + 8, (uint32_t)e->T.size()); wr32(a[1] + 12, 0);
    return S_OK_;
}
F(E_GetParameterDesc) {
    FX_; PAR(a[1]); const uint32_t d = a[2];
    wr32(d, P_.name_g); wr32(d + 4, P_.sem_g); wr32(d + 8, P_.cls); wr32(d + 12, P_.type); wr32(d + 16, P_.rows); wr32(d + 20, P_.cols);
    wr32(d + 24, P_.elems); wr32(d + 28, (uint32_t)P_.annots.size()); wr32(d + 32, P_.nmembers); wr32(d + 36, P_.flags); wr32(d + 40, P_.bytes);
    return S_OK_;
}
F(E_GetTechniqueDesc) {
    FX_; const int t = tech_of(e, a[1]); if (t < 0) return D3DERR_INVALIDCALL_;
    wr32(a[2], e->T[t].name_g); wr32(a[2] + 4, (uint32_t)e->T[t].passes.size()); wr32(a[2] + 8, (uint32_t)e->T[t].annots.size()); return S_OK_;
}
F(E_GetPassDesc) {
    FX_; FxPass *p = pass_of(e, a[1]); if (!p) return D3DERR_INVALIDCALL_;
    wr32(a[2], p->name_g); wr32(a[2] + 4, (uint32_t)p->annots.size()); wr32(a[2] + 8, p->vs ? p->vs->code_g : 0); wr32(a[2] + 12, p->ps ? p->ps->code_g : 0);
    return S_OK_;
}
F(E_GetParameter) {   // (hParent, index)
    FX_;
    if (!a[1]) return a[2] < e->top.size() ? e->P[e->top[a[2]]].handle : 0;
    const int p = param_of(e, a[1]); if (p < 0 || e->P[p].elems) return 0;
    return a[2] < e->P[p].members.size() ? e->P[e->P[p].members[a[2]]].handle : 0;
}
F(E_GetParameterByName) {   // (hParent, name)
    FX_;
    if (!a[1]) { const int p = param_by_path(e, gs(a[2])); return p >= 0 ? e->P[p].handle : 0; }
    const int p = param_of(e, a[1]); if (p < 0) return 0;
    for (int m : e->P[p].members) if (e->P[m].name == gs(a[2])) return e->P[m].handle;
    return 0;
}
F(E_GetParameterBySemantic) {
    FX_;
    const std::vector<int> &lst = a[1] ? e->P[param_of(e, a[1]) < 0 ? 0 : param_of(e, a[1])].members : e->top;
    for (int m : lst) if (!strcasecmp(e->P[m].sem.c_str(), gs(a[2]))) return e->P[m].handle;
    return 0;
}
F(E_GetParameterElement) { FX_; const int p = param_of(e, a[1]); if (p < 0 || !e->P[p].elems || a[2] >= e->P[p].members.size()) return 0; return e->P[e->P[p].members[a[2]]].handle; }
F(E_GetTechnique) { FX_; return a[1] < e->T.size() ? e->T[a[1]].handle : 0; }
F(E_GetTechniqueByName) { FX_; const int t = tech_of(e, a[1]); return t >= 0 ? e->T[t].handle : 0; }
F(E_GetPass) { FX_; const int t = tech_of(e, a[1]); if (t < 0 || a[2] >= e->T[t].passes.size()) return 0; return e->T[t].passes[a[2]].handle; }
F(E_GetPassByName) { FX_; const int t = tech_of(e, a[1]); if (t < 0) return 0; for (FxPass &p : e->T[t].passes) if (p.name == gs(a[2])) return p.handle; return 0; }
F(E_GetFunction) { return 0; }
F(E_GetAnnotation) { FX_; std::vector<int> *l = annots_of(e, a[1]); return (l && a[2] < l->size()) ? e->P[(*l)[a[2]]].handle : 0; }
F(E_GetAnnotationByName) { FX_; std::vector<int> *l = annots_of(e, a[1]); if (!l) return 0; for (int x : *l) if (e->P[x].name == gs(a[2])) return e->P[x].handle; return 0; }
// SetValue/GetValue: os dados do jogo vem na ordem logica do D3DX (matrizes linha a linha, int/bool como inteiros);
// aqui as matrizes "por coluna" (float4x3 dos ossos etc.) sao guardadas coluna a coluna, entao nao da para copiar cru
static uint32_t raw_io(Effect *e, int pi, uint8_t *data, uint32_t bytes, bool set) {
    const FxParam &p = e->P[pi];
    if (!p.members.empty()) { uint32_t k = 0; for (int m : p.members) { if (k >= bytes) break; k += raw_io(e, m, data + k, bytes - k, set); } return k; }
    const bool mat = p.cls == PC_MROWS || p.cls == PC_MCOLS;
    const uint32_t n = mat ? p.rows * p.cols : ncomp(p);
    uint32_t i = 0;
    for (; i < n && 4 * i + 4 <= bytes; ++i) {
        const uint32_t idx = mat ? midx(p, i / p.cols, i % p.cols) : i;
        if (set) {
            uint32_t raw; memcpy(&raw, data + 4 * i, 4); float f;
            if (p.type == PT_FLOAT) memcpy(&f, &raw, 4); else if (p.type == PT_BOOL) f = raw ? 1.0f : 0.0f; else f = (float)(int32_t)raw;
            setf(e, p, idx, f);
        } else {
            const float f = getf(e, p, idx); uint32_t raw;
            if (p.type == PT_FLOAT) memcpy(&raw, &f, 4); else if (p.type == PT_BOOL) raw = f != 0.0f; else raw = (uint32_t)(int32_t)lrintf(f);
            memcpy(data + 4 * i, &raw, 4);
        }
    }
    return 4 * i;
}
F(E_SetValue) {   // (h, pData, Bytes)
    FX_; PAR(a[1]);
    if (0) { static std::set<std::string> vist; if (vist.size() < 40 && vist.insert(P_.name).second) rt_log("[fx] SetValue %s (%u bytes, classe %u, tipo %u, %u linhas x %u colunas, %u elementos)\n", P_.name.c_str(), a[3], P_.cls, P_.type, P_.rows, P_.cols, P_.elems); }
    if (P_.cls == PC_OBJECT) { if (P_.type >= PT_TEXTURE && P_.type <= PT_TEXTURECUBE && a[3] >= 4) { mark(e, P_.off, 4); memcpy(e->val.data() + P_.off, M + a[2], 4); } return S_OK_; }
    if (P_.cls == PC_STRUCT || !P_.members.empty() || P_.cls == PC_MROWS || P_.cls == PC_MCOLS || P_.type != PT_FLOAT) { raw_io(e, pi, M + a[2], a[3], true); return S_OK_; }
    mark(e, P_.off, a[3] < P_.bytes ? a[3] : P_.bytes); memcpy(e->val.data() + P_.off, M + a[2], a[3] < P_.bytes ? a[3] : P_.bytes); return S_OK_;
}
F(E_GetValue) {
    FX_; PAR(a[1]);
    if (P_.cls != PC_OBJECT && (P_.cls == PC_STRUCT || !P_.members.empty() || P_.cls == PC_MROWS || P_.cls == PC_MCOLS || P_.type != PT_FLOAT)) { raw_io(e, pi, M + a[2], a[3], false); return S_OK_; }
    memcpy(M + a[2], e->val.data() + P_.off, a[3] < P_.bytes ? a[3] : P_.bytes); return S_OK_;
}
F(E_SetRawValue) { FX_; PAR(a[1]); if (a[3] < P_.bytes) mark(e, P_.off + a[3], (a[4] < P_.bytes - a[3]) ? a[4] : P_.bytes - a[3]); if (a[3] < P_.bytes) memcpy(e->val.data() + P_.off + a[3], M + a[2], (a[4] < P_.bytes - a[3]) ? a[4] : P_.bytes - a[3]); return S_OK_; }
// escalares e vetores planos
static void set_flat(Effect *e, int pi, const float *v, uint32_t n) {
    const FxParam &p = e->P[pi];
    if (p.members.empty()) { const uint32_t m = n < ncomp(p) ? n : ncomp(p); for (uint32_t i = 0; i < m; ++i) setf(e, p, i, v[i]); return; }
    uint32_t k = 0; for (int x : p.members) { if (k >= n) break; const uint32_t c = ncomp(e->P[x]); set_flat(e, x, v + k, n - k); k += c; }
}
static void get_flat(Effect *e, int pi, float *v, uint32_t n) {
    const FxParam &p = e->P[pi];
    if (p.members.empty()) { const uint32_t m = n < ncomp(p) ? n : ncomp(p); for (uint32_t i = 0; i < m; ++i) v[i] = getf(e, p, i); return; }
    uint32_t k = 0; for (int x : p.members) { if (k >= n) break; get_flat(e, x, v + k, n - k); k += ncomp(e->P[x]); }
}
F(E_SetBool) { FX_; PAR(a[1]); const float f = a[2] ? 1.0f : 0.0f; set_flat(e, pi, &f, 1); return S_OK_; }
F(E_GetBool) { FX_; PAR(a[1]); float f = 0; get_flat(e, pi, &f, 1); wr32(a[2], f != 0.0f); return S_OK_; }
F(E_SetInt) { FX_; PAR(a[1]); const float f = (float)(int32_t)a[2]; set_flat(e, pi, &f, 1); return S_OK_; }
F(E_GetInt) { FX_; PAR(a[1]); float f = 0; get_flat(e, pi, &f, 1); wr32(a[2], (uint32_t)(int32_t)lrintf(f)); return S_OK_; }
F(E_SetFloat) { FX_; PAR(a[1]); float f; memcpy(&f, &a[2], 4); set_flat(e, pi, &f, 1); return S_OK_; }
F(E_GetFloat) { FX_; PAR(a[1]); float f = 0; get_flat(e, pi, &f, 1); memcpy(M + a[2], &f, 4); return S_OK_; }
F(E_SetBoolArray) { FX_; PAR(a[1]); std::vector<float> v(a[3]); for (uint32_t i = 0; i < a[3]; ++i) v[i] = rd32(a[2] + 4 * i) ? 1.0f : 0.0f; set_flat(e, pi, v.data(), a[3]); return S_OK_; }
F(E_GetBoolArray) { FX_; PAR(a[1]); std::vector<float> v(a[3]); get_flat(e, pi, v.data(), a[3]); for (uint32_t i = 0; i < a[3]; ++i) wr32(a[2] + 4 * i, v[i] != 0.0f); return S_OK_; }
F(E_SetIntArray) { FX_; PAR(a[1]); std::vector<float> v(a[3]); for (uint32_t i = 0; i < a[3]; ++i) v[i] = (float)(int32_t)rd32(a[2] + 4 * i); set_flat(e, pi, v.data(), a[3]); return S_OK_; }
F(E_GetIntArray) { FX_; PAR(a[1]); std::vector<float> v(a[3]); get_flat(e, pi, v.data(), a[3]); for (uint32_t i = 0; i < a[3]; ++i) wr32(a[2] + 4 * i, (uint32_t)(int32_t)lrintf(v[i])); return S_OK_; }
F(E_SetFloatArray) { FX_; PAR(a[1]); set_flat(e, pi, (const float *)(M + a[2]), a[3]); return S_OK_; }
F(E_GetFloatArray) { FX_; PAR(a[1]); get_flat(e, pi, (float *)(M + a[2]), a[3]); return S_OK_; }
static void set_vec(Effect *e, const FxParam &l, const float *v) { const uint32_t n = ncomp(l) < 4 ? ncomp(l) : 4; for (uint32_t i = 0; i < n; ++i) setf(e, l, i, v[i]); }
static void get_vec(Effect *e, const FxParam &l, float *v) { const uint32_t n = ncomp(l) < 4 ? ncomp(l) : 4; for (uint32_t i = 0; i < 4; ++i) v[i] = i < n ? getf(e, l, i) : 0.0f; }
F(E_SetVector) { FX_; PAR(a[1]); set_vec(e, leaf(e, pi), (const float *)(M + a[2])); return S_OK_; }
F(E_GetVector) { FX_; PAR(a[1]); get_vec(e, leaf(e, pi), (float *)(M + a[2])); return S_OK_; }
F(E_SetVectorArray) { FX_; PAR(a[1]); if (0) { static std::set<std::string> vist; if (vist.size() < 20 && vist.insert(P_.name).second) rt_log("[fx] SetVectorArray %s (%u itens, classe %u, %u x %u)\n", P_.name.c_str(), a[3], P_.cls, P_.rows, P_.cols); } const uint32_t n = P_.elems ? (a[3] < P_.elems ? a[3] : P_.elems) : 1; for (uint32_t i = 0; i < n; ++i) set_vec(e, leaf(e, pi, i), (const float *)(M + a[2] + 16 * i)); return S_OK_; }
F(E_GetVectorArray) { FX_; PAR(a[1]); const uint32_t n = P_.elems ? (a[3] < P_.elems ? a[3] : P_.elems) : 1; for (uint32_t i = 0; i < n; ++i) get_vec(e, leaf(e, pi, i), (float *)(M + a[2] + 16 * i)); return S_OK_; }
static void set_mat(Effect *e, const FxParam &l, const float *m, bool tr) {
    if (l.cls != PC_MROWS && l.cls != PC_MCOLS) { set_vec(e, l, m); return; }
    for (uint32_t r = 0; r < l.rows && r < 4; ++r) for (uint32_t c = 0; c < l.cols && c < 4; ++c) setf(e, l, midx(l, r, c), tr ? m[c * 4 + r] : m[r * 4 + c]);
}
static void get_mat(Effect *e, const FxParam &l, float *m, bool tr) {
    float o[16] = {0};
    if (l.cls == PC_MROWS || l.cls == PC_MCOLS)
        for (uint32_t r = 0; r < l.rows && r < 4; ++r) for (uint32_t c = 0; c < l.cols && c < 4; ++c) (tr ? o[c * 4 + r] : o[r * 4 + c]) = getf(e, l, midx(l, r, c));
    memcpy(m, o, 64);
}
static uint32_t mat_n(const FxParam &p, uint32_t n) { return p.elems ? (n < p.elems ? n : p.elems) : 1; }
F(E_SetMatrix) { FX_; PAR(a[1]); set_mat(e, leaf(e, pi), (const float *)(M + a[2]), false); return S_OK_; }
F(E_GetMatrix) { FX_; PAR(a[1]); get_mat(e, leaf(e, pi), (float *)(M + a[2]), false); return S_OK_; }
F(E_SetMatrixTranspose) { FX_; PAR(a[1]); set_mat(e, leaf(e, pi), (const float *)(M + a[2]), true); return S_OK_; }
F(E_GetMatrixTranspose) { FX_; PAR(a[1]); get_mat(e, leaf(e, pi), (float *)(M + a[2]), true); return S_OK_; }
F(E_SetMatrixArray) { FX_; PAR(a[1]); if (0) { static std::set<std::string> vist; if (vist.size() < 20 && vist.insert(P_.name).second) rt_log("[fx] SetMatrixArray %s (%u itens, classe %u, %u x %u)\n", P_.name.c_str(), a[3], P_.cls, P_.rows, P_.cols); } for (uint32_t i = 0; i < mat_n(P_, a[3]); ++i) set_mat(e, leaf(e, pi, i), (const float *)(M + a[2] + 64 * i), false); return S_OK_; }
F(E_GetMatrixArray) { FX_; PAR(a[1]); for (uint32_t i = 0; i < mat_n(P_, a[3]); ++i) get_mat(e, leaf(e, pi, i), (float *)(M + a[2] + 64 * i), false); return S_OK_; }
void rt_watch_writes(uint32_t addr, uint32_t len);
uint32_t rt_heap_top();
F(E_SetMatrixTransposeArray) { FX_; PAR(a[1]);
    if (0 && a[3] > 8) {   // diagnostico: o buffer enviado e so uma copia; acha a ORIGEM (mesmos 48 bytes na memoria) e vigia quem a calcula
        static int nl = 0;
        if (false && nl < 6) {
            ++nl;
            uint32_t src = 0;
            const uint8_t *pat = M + a[2];
            auto scan = [&](uint32_t lo, uint32_t hi) {
                for (uint32_t p = lo; p + 48 <= hi && !src; p += 4) if (p != a[2] && !memcmp(M + p, pat, 48)) src = p;
            };
            uint32_t ht = rt_heap_top();
            scan(0x00900000u, 0x02200000u); if (!src) scan(0x40000000u, ht);
            rt_log("[ossos] copia em %08X, origem %08X\n", a[2], src);
            if (src) rt_watch_writes(src, 48);
        }
    }   // diagnostico: quem calcula os ossos do pedaco grande (tronco do Jimmy na cutscene)
    if (0) {   // diagnostico dos ossos: quem envia (endereco de retorno) e a translacao do 1o osso, por (chamador, quantidade)
        static std::set<uint64_t> vist; static int ncall = 0; const uint32_t ret = rd32(c.r[4]); const uint64_t key = ((uint64_t)ret << 16) | (a[3] > 8 ? 9 : a[3]);
        if ((vist.size() < 30 && vist.insert(key).second) || (a[3] > 8 && ++ncall % 90 == 0 && ncall <= 450)) { const float *m = (const float *)(M + a[2]);
            rt_log("[ossos] %s: %u matrizes, chamado de %08X | 1a: linha0 %.3f %.3f %.3f %.3f | col3 %.2f %.2f %.2f | linha3 %.2f %.2f %.2f %.2f\n", P_.name.c_str(), a[3], ret,
                   m[0], m[1], m[2], m[3], m[3], m[7], m[11], m[12], m[13], m[14], m[15]); }
    } if (0) { static std::set<std::string> vist; if (vist.size() < 20 && vist.insert(P_.name).second) rt_log("[fx] SetMatrixTransposeArray %s (%u itens, classe %u, %u x %u)\n", P_.name.c_str(), a[3], P_.cls, P_.rows, P_.cols); } for (uint32_t i = 0; i < mat_n(P_, a[3]); ++i) set_mat(e, leaf(e, pi, i), (const float *)(M + a[2] + 64 * i), true); return S_OK_; }
F(E_GetMatrixTransposeArray) { FX_; PAR(a[1]); for (uint32_t i = 0; i < mat_n(P_, a[3]); ++i) get_mat(e, leaf(e, pi, i), (float *)(M + a[2] + 64 * i), true); return S_OK_; }
F(E_SetMatrixPointerArray) { FX_; PAR(a[1]); if (0) { static std::set<std::string> vist; if (vist.size() < 20 && vist.insert(P_.name).second) rt_log("[fx] SetMatrixPointerArray %s (%u itens, classe %u, %u x %u)\n", P_.name.c_str(), a[3], P_.cls, P_.rows, P_.cols); } for (uint32_t i = 0; i < mat_n(P_, a[3]); ++i) set_mat(e, leaf(e, pi, i), (const float *)(M + rd32(a[2] + 4 * i)), false); return S_OK_; }
F(E_GetMatrixPointerArray) { FX_; PAR(a[1]); for (uint32_t i = 0; i < mat_n(P_, a[3]); ++i) get_mat(e, leaf(e, pi, i), (float *)(M + rd32(a[2] + 4 * i)), false); return S_OK_; }
F(E_SetMatrixTransposePointerArray) { FX_; PAR(a[1]); for (uint32_t i = 0; i < mat_n(P_, a[3]); ++i) set_mat(e, leaf(e, pi, i), (const float *)(M + rd32(a[2] + 4 * i)), true); return S_OK_; }
F(E_GetMatrixTransposePointerArray) { FX_; PAR(a[1]); for (uint32_t i = 0; i < mat_n(P_, a[3]); ++i) get_mat(e, leaf(e, pi, i), (float *)(M + rd32(a[2] + 4 * i)), true); return S_OK_; }
F(E_SetString) { return S_OK_; }
F(E_GetString) { FX_; PAR(a[1]); if (P_.type != PT_STRING) return D3DERR_INVALIDCALL_; wr32(a[2], obj_val(e, pi)); return S_OK_; }
F(E_SetTexture) { FX_; PAR(a[1]); if (P_.type < PT_TEXTURE || P_.type > PT_TEXTURECUBE) return D3DERR_INVALIDCALL_; mark(e, P_.off, 4); memcpy(e->val.data() + P_.off, &a[2], 4); return S_OK_; }
F(E_GetTexture) { FX_; PAR(a[1]); const uint32_t t = obj_val(e, pi); if (t) com_addref(t); wr32(a[2], t); return S_OK_; }
F(E_GetShader) { FX_; PAR(a[1]); auto it = e->shaders.find(P_.oid); const uint32_t o = it != e->shaders.end() ? it->second->obj : 0; if (o) com_addref(o); wr32(a[2], o); return S_OK_; }
F(E_SetArrayRange) { return S_OK_; }
F(E_GetPool) { wr32(a[1], 0); return S_OK_; }
F(E_SetTechnique) { FX_; const int t = tech_of(e, a[1]); if (t < 0) return D3DERR_INVALIDCALL_; e->cur_tech = t; return S_OK_; }
F(E_GetCurrentTechnique) { FX_; return e->cur_tech < (int)e->T.size() ? e->T[e->cur_tech].handle : 0; }
F(E_ValidateTechnique) { return S_OK_; }
F(E_FindNextValidTechnique) {   // (hTechnique, pTechnique)
    FX_; int t = a[1] ? tech_of(e, a[1]) + 1 : 0;
    if (t >= 0 && t < (int)e->T.size()) { wr32(a[2], e->T[t].handle); return S_OK_; }
    wr32(a[2], 0); return 1;   // S_FALSE
}
F(E_IsParameterUsed) { return 1; }
F(E_Begin) {   // (pPasses, Flags)
    FX_;
    if (e->cur_tech >= (int)e->T.size()) return D3DERR_INVALIDCALL_;
    if (a[1]) wr32(a[1], (uint32_t)e->T[e->cur_tech].passes.size());
    if (!(a[2] & 1)) e->saved = d3d_state_save();
    return S_OK_;
}
const char *g_fx_tech = nullptr;   // tecnica atual (diagnostico no d3d9)
F(E_BeginPass) { FX_; g_fx_tech = e->T[e->cur_tech].name.c_str(); g_fx_cpu = &c; g_fx_mgr = e->state_mgr; if (a[1] >= e->T[e->cur_tech].passes.size()) return D3DERR_INVALIDCALL_; e->cur_pass = (int)a[1]; apply_pass(e); return S_OK_; }
F(E_CommitChanges) { FX_; g_fx_cpu = &c; g_fx_mgr = e->state_mgr; commit(e, false); return S_OK_; }
F(E_EndPass) { FX_; e->cur_pass = -1; return S_OK_; }
F(E_End) { FX_; if (e->saved) { d3d_state_restore(e->saved); e->saved = nullptr; } return S_OK_; }
F(E_GetDevice) { const uint32_t d = d3d_device_obj(); if (d) com_addref(d); wr32(a[1], d); return S_OK_; }
F(E_Ok) { return S_OK_; }
F(E_SetStateManager) { FX_; e->state_mgr = a[1]; if (!g_fx_scratch) g_fx_scratch = rt_alloc(4096, true); return S_OK_; }
F(E_GetStateManager) { FX_; if (e->state_mgr) com_addref(e->state_mgr); wr32(a[1], e->state_mgr); return S_OK_; }
F(E_EndParameterBlock) { return 0; }

static uint32_t vt_effect() {
    static uint32_t v = 0;
    if (!v) {
        static const ComMethod m[] = {
            {"QueryInterface", 2, Unk_QI}, {"AddRef", 0, Unk_AddRef}, {"Release", 0, Unk_Release},
            {"GetDesc", 1, E_GetDesc}, {"GetParameterDesc", 2, E_GetParameterDesc}, {"GetTechniqueDesc", 2, E_GetTechniqueDesc},
            {"GetPassDesc", 2, E_GetPassDesc}, {"GetFunctionDesc", 2, nullptr}, {"GetParameter", 2, E_GetParameter},
            {"GetParameterByName", 2, E_GetParameterByName}, {"GetParameterBySemantic", 2, E_GetParameterBySemantic},
            {"GetParameterElement", 2, E_GetParameterElement}, {"GetTechnique", 1, E_GetTechnique}, {"GetTechniqueByName", 1, E_GetTechniqueByName},
            {"GetPass", 2, E_GetPass}, {"GetPassByName", 2, E_GetPassByName}, {"GetFunction", 1, E_GetFunction}, {"GetFunctionByName", 1, E_GetFunction},
            {"GetAnnotation", 2, E_GetAnnotation}, {"GetAnnotationByName", 2, E_GetAnnotationByName},
            {"SetValue", 3, E_SetValue}, {"GetValue", 3, E_GetValue},
            {"SetBool", 2, E_SetBool}, {"GetBool", 2, E_GetBool}, {"SetBoolArray", 3, E_SetBoolArray}, {"GetBoolArray", 3, E_GetBoolArray},
            {"SetInt", 2, E_SetInt}, {"GetInt", 2, E_GetInt}, {"SetIntArray", 3, E_SetIntArray}, {"GetIntArray", 3, E_GetIntArray},
            {"SetFloat", 2, E_SetFloat}, {"GetFloat", 2, E_GetFloat}, {"SetFloatArray", 3, E_SetFloatArray}, {"GetFloatArray", 3, E_GetFloatArray},
            {"SetVector", 2, E_SetVector}, {"GetVector", 2, E_GetVector}, {"SetVectorArray", 3, E_SetVectorArray}, {"GetVectorArray", 3, E_GetVectorArray},
            {"SetMatrix", 2, E_SetMatrix}, {"GetMatrix", 2, E_GetMatrix}, {"SetMatrixArray", 3, E_SetMatrixArray}, {"GetMatrixArray", 3, E_GetMatrixArray},
            {"SetMatrixPointerArray", 3, E_SetMatrixPointerArray}, {"GetMatrixPointerArray", 3, E_GetMatrixPointerArray},
            {"SetMatrixTranspose", 2, E_SetMatrixTranspose}, {"GetMatrixTranspose", 2, E_GetMatrixTranspose},
            {"SetMatrixTransposeArray", 3, E_SetMatrixTransposeArray}, {"GetMatrixTransposeArray", 3, E_GetMatrixTransposeArray},
            {"SetMatrixTransposePointerArray", 3, E_SetMatrixTransposePointerArray}, {"GetMatrixTransposePointerArray", 3, E_GetMatrixTransposePointerArray},
            {"SetString", 2, E_SetString}, {"GetString", 2, E_GetString}, {"SetTexture", 2, E_SetTexture}, {"GetTexture", 2, E_GetTexture},
            {"GetPixelShader", 2, E_GetShader}, {"GetVertexShader", 2, E_GetShader}, {"SetArrayRange", 3, E_SetArrayRange},
            {"GetPool", 1, E_GetPool}, {"SetTechnique", 1, E_SetTechnique}, {"GetCurrentTechnique", 0, E_GetCurrentTechnique},
            {"ValidateTechnique", 1, E_ValidateTechnique}, {"FindNextValidTechnique", 2, E_FindNextValidTechnique},
            {"IsParameterUsed", 2, E_IsParameterUsed}, {"Begin", 2, E_Begin}, {"BeginPass", 1, E_BeginPass}, {"CommitChanges", 0, E_CommitChanges},
            {"EndPass", 0, E_EndPass}, {"End", 0, E_End}, {"GetDevice", 1, E_GetDevice}, {"OnLostDevice", 0, E_Ok}, {"OnResetDevice", 0, E_Ok},
            {"SetStateManager", 1, E_SetStateManager}, {"GetStateManager", 1, E_GetStateManager},
            {"BeginParameterBlock", 0, E_Ok}, {"EndParameterBlock", 0, E_EndParameterBlock}, {"ApplyParameterBlock", 1, E_Ok},
            {"DeleteParameterBlock", 1, E_Ok}, {"CloneEffect", 2, nullptr}, {"SetRawValue", 4, E_SetRawValue}};
        v = com_vtable("ID3DXEffect", m, (int)(sizeof m / sizeof m[0]));
    }
    return v;
}

// chamado pelo D3DXCreateEffect: devolve o objeto do jogo ou 0
uint32_t effect_create(const uint8_t *data, uint32_t size) {
    uint32_t tag = 0; if (size >= 4) memcpy(&tag, data, 4);
    if (tag != 0xFEFF0901u) { rt_log("[fx] efeito em texto (nao compilado): nao suportado\n"); return 0; }
    Effect *e = effect_parse(data, size);
    if (!e) return 0;
    e->obj = com_new(vt_effect(), e);
    return e->obj;
}
