// Tradutor D3D9 SM2/SM3 -> GLSL ES 3.00 (ver sm_translate.h).
#include "sm_translate.h"
#include <stdio.h>
#include <string.h>
#include <map>
#include <set>

enum { RT_TEMP = 0, RT_INPUT = 1, RT_CONST = 2, RT_ADDR = 3, RT_TEXTURE = 3, RT_RASTOUT = 4, RT_ATTROUT = 5, RT_TEXCRDOUT = 6, RT_OUTPUT = 6,
       RT_CONSTINT = 7, RT_COLOROUT = 8, RT_DEPTHOUT = 9, RT_SAMPLER = 10, RT_CONSTBOOL = 14, RT_LOOP = 15, RT_MISCTYPE = 17, RT_LABEL = 18,
       RT_PREDICATE = 19 };
static const char *kUsage[] = {"POSITION", "BLENDWEIGHT", "BLENDINDICES", "NORMAL", "PSIZE", "TEXCOORD", "TANGENT", "BINORMAL",
                               "TESSFACTOR", "POSITIONT", "COLOR", "FOG", "DEPTH", "SAMPLE"};
const char *sm_usage_name(uint32_t u) { return u < 14 ? kUsage[u] : "UNKNOWN"; }
static std::string sem(uint32_t u, uint32_t i) { char b[32]; snprintf(b, sizeof b, "%s%u", sm_usage_name(u), i); return b; }
static std::string fstr(float f) {
    char b[48];
    if (f != f) return "(0.0/0.0)";
    if (f > 3.4e38f) return "1e38"; if (f < -3.4e38f) return "-1e38";
    snprintf(b, sizeof b, "%.9g", f);
    std::string s = b; if (s.find_first_of(".e") == std::string::npos) s += ".0";
    return s;
}

struct Param { uint32_t tok = 0, rel = 0; bool has_rel = false; };
static uint32_t ptype(uint32_t t) { return ((t >> 28) & 7) | ((t >> 8) & 0x18); }
static uint32_t pnum(uint32_t t) { return t & 0x7FF; }

struct Tr {
    SmShader &o;
    const uint32_t *w; uint32_t n, i = 1;
    bool vs = false;
    std::string *cur;                    // body ou funcao atual
    int depth = 1;                       // indentacao
    std::map<uint32_t, std::string> in_sem, out_sem;   // registrador -> semantica (SM3 / SM2 fixos)
    std::map<uint32_t, uint32_t> in_usage;             // VS: registrador de entrada -> (usage<<16|index)
    std::set<uint32_t> temps, defc, defi, defb, outs_used, labels;
    std::vector<std::string> loopvars;
    int loopn = 0;
    bool in_func = false;
    std::string funcs_cur;
    std::set<std::string> ps_in;
    bool fail = false; std::string why;

    explicit Tr(SmShader &s) : o(s) {}
    void line(const std::string &s) { cur->append(std::string(depth * 2, ' ')).append(s).append("\n"); }
    void err(const std::string &s) { if (!fail) { fail = true; why = s; } }

    std::string aL() { return loopvars.empty() ? std::string("0") : loopvars.back(); }
    // nome do registrador (sem swizzle)
    std::string reg(uint32_t t, const Param *p, bool is_dst) {
        const uint32_t ty = ptype(t), nm = pnum(t);
        char b[64];
        switch (ty) {
        case RT_TEMP: temps.insert(nm); snprintf(b, sizeof b, "r%u", nm); return b;
        case RT_INPUT:
            if (vs) { snprintf(b, sizeof b, "a%u", nm); return b; }
            if (o.major < 3) { const std::string s = sem(10, nm); ps_in.insert(s); return "V_" + s; }   // ps_2: v0/v1 = COLOR0/1
            { auto it = in_sem.find(nm); std::string s = it != in_sem.end() ? it->second : sem(5, nm); ps_in.insert(s);
              if (p && p->has_rel) err("entrada com endereco relativo"); return "V_" + s; }
        case RT_CONST:
            if (p && p->has_rel) {
                const uint32_t rt = ptype(p->rel); const char comp = "xyzw"[(p->rel >> 16) & 3];
                std::string idx = rt == RT_LOOP ? aL() : std::string("A0.") + comp;
                snprintf(b, sizeof b, "%s[clamp(%s + %u, 0, %d)]", vs ? "vc" : "pc", idx.c_str(), nm, vs ? 255 : 223); return b;
            }
            if (defc.count(nm)) { snprintf(b, sizeof b, "K%u", nm); return b; }
            snprintf(b, sizeof b, "%s[%u]", vs ? "vc" : "pc", nm); return b;
        case 3:
            if (vs) return "vec4(A0)";   // a0 como fonte (raro)
            { const std::string s = sem(5, nm); ps_in.insert(s); return "V_" + s; }   // ps_2: t# = TEXCOORD#
        case RT_RASTOUT:
            if (nm == 0) { outs_used.insert(0x100); return "oPos"; }
            if (nm == 1) { outs_used.insert(0x101); return "oFog"; }
            outs_used.insert(0x102); return "oPts";
        case RT_ATTROUT: outs_used.insert(0x200 + nm); snprintf(b, sizeof b, "oD%u", nm); return b;
        case RT_OUTPUT:
            if (vs && o.major >= 3) { outs_used.insert(0x400 + nm); snprintf(b, sizeof b, "o%u", nm); return b; }
            outs_used.insert(0x300 + nm); snprintf(b, sizeof b, "oT%u", nm); return b;
        case RT_CONSTINT: if (defi.count(nm)) { snprintf(b, sizeof b, "vec4(I%u)", nm); return b; } snprintf(b, sizeof b, "vec4(%s[%u])", vs ? "vci" : "pci", nm); return b;
        case RT_COLOROUT: if ((int)nm + 1 > o.ncolor_out) o.ncolor_out = nm + 1; snprintf(b, sizeof b, "oC%u", nm); return b;
        case RT_DEPTHOUT: o.depth_out = true; return "oDepth";
        case RT_CONSTBOOL: if (defb.count(nm)) { snprintf(b, sizeof b, "B%u", nm); return b; } snprintf(b, sizeof b, "%s[%u]", vs ? "vcb" : "pcb", nm); return b;
        case RT_LOOP: return "vec4(float(" + aL() + "))";
        case RT_MISCTYPE: if (nm == 0) return "vPos"; return "vFace";
        case RT_PREDICATE: return "P0";
        case RT_SAMPLER: snprintf(b, sizeof b, vs ? "vs_s%u" : "s%u", nm); return b;
        }
        (void)is_dst;
        err("registrador tipo " + std::to_string(ty));
        return "vec4(0)";
    }
    static std::string swz(uint32_t t) {
        const uint32_t s = (t >> 16) & 0xFF;
        if (s == 0xE4) return "";
        std::string r = ".";
        for (int k = 0; k < 4; ++k) r += "xyzw"[(s >> (2 * k)) & 3];
        return r;
    }
    // fonte como vec4 (com swizzle e modificador)
    std::string src(const Param &p) {
        const uint32_t ty = ptype(p.tok);
        std::string r = reg(p.tok, &p, false);
        if (ty == RT_CONSTBOOL || ty == RT_PREDICATE) return r;   // tratados pelo chamador
        std::string v = r + swz(p.tok);
        if (ty == RT_MISCTYPE && pnum(p.tok) == 1) v = "vec4(vFace)" + swz(p.tok);
        switch ((p.tok >> 24) & 0xF) {
        case 0: return v;
        case 1: return "(-" + v + ")";
        case 2: return "(" + v + " - 0.5)";
        case 3: return "(0.5 - " + v + ")";
        case 4: return "(" + v + " * 2.0 - 1.0)";
        case 5: return "(1.0 - " + v + " * 2.0)";
        case 6: return "(1.0 - " + v + ")";
        case 7: return "(" + v + " * 2.0)";
        case 8: return "(" + v + " * -2.0)";
        case 11: return "abs(" + v + ")";
        case 12: return "(-abs(" + v + "))";
        default: err("modificador de fonte"); return v;
        }
    }
    std::string sx(const Param &p) { return src(p) + ".x"; }   // escalar (componente ja escolhido pelo swizzle)
    std::string mask(uint32_t t) {
        const uint32_t m = (t >> 16) & 0xF;
        if (m == 0xF) return "";
        std::string r = ".";
        for (int k = 0; k < 4; ++k) if (m & (1 << k)) r += "xyzw"[k];
        return r;
    }
    // grava E (expressao vec4) no destino com mascara e saturacao; predicado opcional
    void write(const Param &d, const std::string &E, const Param *pred) {
        const std::string r = reg(d.tok, &d, true);
        const uint32_t ty = ptype(d.tok);
        const std::string m = mask(d.tok);
        std::string e = "(" + E + ")";
        if ((d.tok >> 20) & 1) e = "clamp(" + e + ", 0.0, 1.0)";
        if (ty == RT_ADDR && vs) { line("A0" + m + " = ivec4(floor(" + e + " + 0.5))" + m + ";"); return; }
        if (ty == RT_PREDICATE) { line("P0" + m + " = bvec4(" + e + ")" + m + ";"); return; }
        if (ty == RT_DEPTHOUT) { line("oDepth = " + e + ".x;"); return; }
        if (!pred) { line(r + m + " = " + e + (m.empty() ? "" : m) + ";"); return; }
        // predicado por componente
        const uint32_t mm = (d.tok >> 16) & 0xF; const uint32_t ps = (pred->tok >> 16) & 0xFF; const bool nt = ((pred->tok >> 24) & 0xF) == 13;
        line("{ vec4 t_ = " + e + ";");
        for (int k = 0; k < 4; ++k) if (mm & (1 << k)) {
            const char pc = "xyzw"[(ps >> (2 * k)) & 3], dc = "xyzw"[k];
            line(std::string("  if (") + (nt ? "!" : "") + "P0." + pc + ") " + r + "." + dc + " = t_." + dc + ";");
        }
        line("}");
    }
    Param rd_param() {
        Param p; p.tok = w[i++];
        if ((p.tok & 0x2000) && o.major >= 2) { p.has_rel = true; p.rel = w[i++]; }
        else if (p.tok & 0x2000) { p.has_rel = true; p.rel = 0x80000000u | (RT_ADDR << 28); }   // vs_1_1: a0.x implicito
        return p;
    }
    static const char *cmpop(uint32_t c) { switch (c) { case 1: return ">"; case 2: return "=="; case 3: return ">="; case 4: return "<"; case 5: return "!="; case 6: return "<="; } return "=="; }
    std::string boolsrc(const Param &p) {   // if b# / if p0.c
        const uint32_t ty = ptype(p.tok);
        if (ty == RT_CONSTBOOL) return reg(p.tok, &p, false);
        if (ty == RT_PREDICATE) { const bool nt = ((p.tok >> 24) & 0xF) == 13; return std::string(nt ? "!" : "") + "P0." + "xyzw"[(p.tok >> 16) & 3]; }
        return "(" + sx(p) + " != 0.0)";
    }
    std::string ireg(const Param &p) {   // registrador inteiro (loop/rep)
        const uint32_t nm = pnum(p.tok); char b[32];
        if (defi.count(nm)) snprintf(b, sizeof b, "I%u", nm); else snprintf(b, sizeof b, "%s[%u]", vs ? "vci" : "pci", nm);
        return b;
    }
    std::string texfn(uint32_t samp, const std::string &coord, const char *mode, const std::string &extra = "") {
        const int st = o.sampler_type[(vs ? 16 : 0) + (samp & 15)] ? o.sampler_type[(vs ? 16 : 0) + (samp & 15)] : 2;
        const char *cs = st == 2 ? ".xy" : ".xyz";
        char sn[16]; snprintf(sn, sizeof sn, vs ? "vs_s%u" : "s%u", samp);
        if (!vs && st == 2) {   // 2D no pixel shader: funcao auxiliar (o link escolhe sampler2D ou sampler2DShadow para mapas de sombra)
            char fn[24]; const unsigned k = samp & 15;
            if (!strcmp(mode, "proj")) snprintf(fn, sizeof fn, "t2dp_%u", k);
            else if (!strcmp(mode, "bias")) snprintf(fn, sizeof fn, "t2db_%u", k);
            else if (!strcmp(mode, "lod")) snprintf(fn, sizeof fn, "t2dl_%u", k);
            else if (!strcmp(mode, "grad")) snprintf(fn, sizeof fn, "t2dg_%u", k);
            else snprintf(fn, sizeof fn, "t2d_%u", k);
            return std::string(fn) + "(vec4(" + coord + ")" + (extra.empty() ? "" : ", " + extra) + ")";
        }
        if (!strcmp(mode, "proj")) return st == 2 ? std::string("textureProj(") + sn + ", " + coord + ".xyw)" : std::string("texture(") + sn + ", " + coord + ".xyz / " + coord + ".w)";
        if (!strcmp(mode, "bias")) return std::string("texture(") + sn + ", " + coord + cs + ", " + coord + ".w)";
        if (!strcmp(mode, "lod")) return std::string("textureLod(") + sn + ", " + coord + cs + ", " + coord + ".w)";
        if (!strcmp(mode, "grad")) return std::string("textureGrad(") + sn + ", " + coord + cs + ", " + extra + ")";
        return std::string("texture(") + sn + ", " + coord + cs + ")";
    }
    void run();
};

void Tr::run() {
    const uint32_t ver = w[0];
    o.pixel = (ver >> 16) == 0xFFFF; vs = !o.pixel;
    o.major = (ver >> 8) & 0xFF; o.minor = ver & 0xFF;
    if (o.major < 2) { err("shader model 1.x nao suportado"); return; }
    std::string body;
    cur = &body;
    while (i < n && !fail) {
        const uint32_t tok = w[i];
        if (tok == 0x0000FFFFu) break;
        const uint32_t op = tok & 0xFFFF;
        if (op == 0xFFFE) { i += 1 + ((tok >> 16) & 0x7FFF); continue; }
        const uint32_t len = (tok >> 24) & 0xF, ctl = (tok >> 16) & 0xFF;
        const uint32_t start = i + 1, next = start + len;
        const bool predicated = (tok & 0x10000000u) != 0;
        i = start;
        auto D = [&]() { return rd_param(); };
        if (op == 31) {   // dcl
            const uint32_t u = w[i], d = w[i + 1]; i = next;
            const uint32_t ty = ptype(d), nm = pnum(d);
            if (ty == RT_SAMPLER) { const uint32_t st = (u >> 27) & 0xF; o.sampler_type[(vs ? 16 : 0) + (nm & 15)] = st ? (int)st : 2; continue; }
            if (vs && ty == RT_INPUT) { in_usage[nm] = ((u & 0x1F) << 16) | ((u >> 16) & 0xF); o.inputs.push_back({u & 0x1F, (u >> 16) & 0xF, nm}); continue; }
            if (vs && ty == RT_OUTPUT) { out_sem[nm] = sem(u & 0x1F, (u >> 16) & 0xF); continue; }
            if (!vs && ty == RT_INPUT && o.major >= 3) { in_sem[nm] = sem(u & 0x1F, (u >> 16) & 0xF); continue; }
            continue;
        }
        if (op == 81) {   // def
            const uint32_t nm = pnum(w[i]); float f[4]; memcpy(f, w + i + 1, 16); i = next;
            defc.insert(nm);
            char b[256]; snprintf(b, sizeof b, "const vec4 K%u = vec4(%s, %s, %s, %s);\n", nm, fstr(f[0]).c_str(), fstr(f[1]).c_str(), fstr(f[2]).c_str(), fstr(f[3]).c_str());
            o.globals += b; continue;
        }
        if (op == 48) {   // defi
            const uint32_t nm = pnum(w[i]); int32_t v[4]; memcpy(v, w + i + 1, 16); i = next; defi.insert(nm);
            char b[160]; snprintf(b, sizeof b, "const ivec4 I%u = ivec4(%d, %d, %d, %d);\n", nm, v[0], v[1], v[2], v[3]); o.globals += b; continue;
        }
        if (op == 47) {   // defb
            const uint32_t nm = pnum(w[i]); const uint32_t v = w[i + 1]; i = next; defb.insert(nm);
            char b[96]; snprintf(b, sizeof b, "const bool B%u = %s;\n", nm, v ? "true" : "false"); o.globals += b; continue;
        }
        if (op == 0) { i = next; continue; }
        // controle de fluxo
        if (op == 30) {   // label
            const uint32_t l = pnum(w[i]); i = next;
            in_func = true; funcs_cur.clear(); cur = &funcs_cur; depth = 1;
            char b[48]; snprintf(b, sizeof b, "void L%u() {\n", l); funcs_cur = b; labels.insert(l);
            continue;
        }
        if (op == 28) {   // ret
            i = next;
            if (in_func && depth == 1) { funcs_cur += "}\n"; o.funcs += funcs_cur; funcs_cur.clear(); cur = &body; in_func = false; }
            else if (!in_func && depth == 1) { /* fim do main */ }
            else line("return;");
            continue;
        }
        if (op == 25 || op == 26) {   // call / callnz
            const uint32_t l = pnum(w[i]); char b[64];
            if (op == 25) { i = next; snprintf(b, sizeof b, "L%u();", l); line(b); }
            else { i++; Param p = D(); i = next; snprintf(b, sizeof b, "if (%s) L%u();", boolsrc(p).c_str(), l); line(b); }
            continue;
        }
        if (op == 27) {   // loop aL, i#
            i++; Param ip = D(); i = next;
            const std::string I = ireg(ip); char b[256]; const int k = loopn++;
            snprintf(b, sizeof b, "{ int lc%d = 0; for (int aL%d = %s.y; lc%d < %s.x && lc%d < 255; ++lc%d, aL%d += %s.z) {", k, k, I.c_str(), k, I.c_str(), k, k, k, I.c_str());
            line(b); depth++; loopvars.push_back("aL" + std::to_string(k)); continue;
        }
        if (op == 29) { i = next; depth--; line("} }"); if (!loopvars.empty()) loopvars.pop_back(); continue; }   // endloop
        if (op == 38) {   // rep i#
            Param ip = D(); i = next; const int k = loopn++; char b[160];
            snprintf(b, sizeof b, "for (int rp%d = 0; rp%d < %s.x && rp%d < 255; ++rp%d) {", k, k, ireg(ip).c_str(), k, k);
            line(b); depth++; continue;
        }
        if (op == 39) { i = next; depth--; line("}"); continue; }   // endrep
        if (op == 40) { Param p = D(); i = next; line("if (" + boolsrc(p) + ") {"); depth++; continue; }
        if (op == 41) { Param a = D(), b2 = D(); i = next; line("if (" + sx(a) + " " + cmpop(ctl) + " " + sx(b2) + ") {"); depth++; continue; }
        if (op == 42) { i = next; depth--; line("} else {"); depth++; continue; }
        if (op == 43) { i = next; depth--; line("}"); continue; }
        if (op == 44) { i = next; line("break;"); continue; }
        if (op == 45) { Param a = D(), b2 = D(); i = next; line("if (" + sx(a) + " " + cmpop(ctl) + " " + sx(b2) + ") break;"); continue; }
        if (op == 96) { Param p = D(); i = next; line("if (" + boolsrc(p) + ") break;"); continue; }
        if (op == 65) {   // texkill: o operando e um destino com mascara
            Param d = D(); i = next;
            const std::string r = reg(d.tok, &d, false); const uint32_t m = (d.tok >> 16) & 0xF;
            std::string c;
            for (int k = 0; k < 4; ++k) if (m & (1 << k)) { if (!c.empty()) c += " || "; c += r + "." + "xyzw"[k] + " < 0.0"; }
            if (o.major < 2 || m == 0xF) { c = r + ".x < 0.0 || " + r + ".y < 0.0 || " + r + ".z < 0.0"; if (m == 0xF && o.major >= 2) c += " || " + r + ".w < 0.0"; }
            line("if (" + c + ") discard;"); continue;
        }
        // instrucoes aritmeticas: destino, [predicado], fontes
        Param d = D();
        Param pred; bool has_pred = false;
        if (predicated) { pred = D(); has_pred = true; }
        std::vector<Param> s;
        while (i < next) s.push_back(D());
        i = next;
        auto S = [&](int k) { return k < (int)s.size() ? src(s[k]) : std::string("vec4(0.0)"); };
        auto X = [&](int k) { return k < (int)s.size() ? sx(s[k]) : std::string("0.0"); };
        const Param *P = has_pred ? &pred : nullptr;
        std::string E;
        switch (op) {
        case 1: E = S(0); break;
        case 2: E = S(0) + " + " + S(1); break;
        case 3: E = S(0) + " - " + S(1); break;
        // vertex shader: multiplicacao "do D3D9" (0 * inf/NaN = 0). Ossos sem uso com peso 0 e matrizes nao preenchidas
        // davam NaN no GLES e o vertice sumia (braços/roupa dos personagens), como o d3d9.floatEmulation do DXVK
        case 4: E = vs ? "smul(" + S(0) + ", " + S(1) + ") + " + S(2) : S(0) + " * " + S(1) + " + " + S(2); break;
        case 5: E = vs ? "smul(" + S(0) + ", " + S(1) + ")" : S(0) + " * " + S(1); break;
        case 6: E = "vec4(1.0 / " + X(0) + ")"; break;
        case 7: E = "vec4(inversesqrt(abs(" + X(0) + ")))"; break;
        case 8: E = vs ? "vec4(sdot3(" + S(0) + ", " + S(1) + "))" : "vec4(dot(" + S(0) + ".xyz, " + S(1) + ".xyz))"; break;
        case 9: E = vs ? "vec4(sdot4(" + S(0) + ", " + S(1) + "))" : "vec4(dot(" + S(0) + ", " + S(1) + "))"; break;
        case 10: E = "min(" + S(0) + ", " + S(1) + ")"; break;
        case 11: E = "max(" + S(0) + ", " + S(1) + ")"; break;
        case 12: E = "vec4(lessThan(" + S(0) + ", " + S(1) + "))"; break;
        case 13: E = "vec4(greaterThanEqual(" + S(0) + ", " + S(1) + "))"; break;
        case 14: case 78: E = "vec4(exp2(" + X(0) + "))"; break;
        case 15: case 79: E = "vec4(log2(abs(" + X(0) + ")))"; break;
        case 16: E = "sm_lit(" + S(0) + ")"; break;
        case 17: E = "vec4(1.0, " + S(0) + ".y * " + S(1) + ".y, " + S(0) + ".z, " + S(1) + ".w)"; break;
        case 18: E = "mix(" + S(2) + ", " + S(1) + ", " + S(0) + ")"; break;
        case 19: E = "fract(" + S(0) + ")"; break;
        case 20: case 21: case 22: case 23: case 24: {   // m4x4 m4x3 m3x4 m3x3 m3x2
            const int rows = op == 20 ? 4 : op == 21 ? 3 : op == 22 ? 4 : op == 23 ? 3 : 2;
            const bool v3 = op >= 22;
            std::string a = S(0); std::string parts;
            for (int k = 0; k < 4; ++k) {
                if (k) parts += ", ";
                if (k < rows) {
                    Param pk = s[1]; pk.tok = (pk.tok & ~0x7FFu) | ((pnum(pk.tok) + k) & 0x7FF);
                    if (vs) parts += v3 ? "sdot3(" + a + ", " + src(pk) + ")" : "sdot4(" + a + ", " + src(pk) + ")";
                    else parts += v3 ? "dot(" + a + ".xyz, " + src(pk) + ".xyz)" : "dot(" + a + ", " + src(pk) + ")";
                } else parts += "0.0";
            }
            E = "vec4(" + parts + ")"; break;
        }
        case 32: E = "vec4(pow(abs(" + X(0) + "), " + X(1) + "))"; break;
        case 33: E = "vec4(cross(" + S(0) + ".xyz, " + S(1) + ".xyz), 0.0)"; break;
        case 34: E = "sign(" + S(0) + ")"; break;
        case 35: E = "abs(" + S(0) + ")"; break;
        case 36: E = "(" + S(0) + " * inversesqrt(max(dot(" + S(0) + ".xyz, " + S(0) + ".xyz), 1e-30)))"; break;
        case 37: E = "vec4(cos(" + X(0) + "), sin(" + X(0) + "), 0.0, 0.0)"; break;
        case 46: E = S(0); break;   // mova (o write converte para inteiro)
        case 66: {   // texld / texldp / texldb
            const uint32_t sn = pnum(s[1].tok);
            E = texfn(sn, S(0), ctl == 1 ? "proj" : ctl == 2 ? "bias" : "") + swz(s[1].tok); break;
        }
        case 95: E = texfn(pnum(s[1].tok), S(0), "lod") + swz(s[1].tok); break;
        case 93: E = texfn(pnum(s[1].tok), S(0), "grad", S(2) + ".xy, " + S(3) + ".xy") + swz(s[1].tok); break;
        case 88: E = "mix(" + S(2) + ", " + S(1) + ", greaterThanEqual(" + S(0) + ", vec4(0.0)))"; break;
        case 80: E = "mix(" + S(2) + ", " + S(1) + ", greaterThan(" + S(0) + ", vec4(0.5)))"; break;
        case 90: E = "vec4(dot(" + S(0) + ".xy, " + S(1) + ".xy) + " + X(2) + ")"; break;
        case 91: E = "dFdx(" + S(0) + ")"; break;
        case 92: E = "(-dFdy(" + S(0) + "))"; break;
        case 94: {   // setp
            const char *f = ctl == 1 ? "greaterThan" : ctl == 2 ? "equal" : ctl == 3 ? "greaterThanEqual" : ctl == 4 ? "lessThan" : ctl == 5 ? "notEqual" : "lessThanEqual";
            E = std::string("vec4(") + f + "(" + S(0) + ", " + S(1) + "))"; break;
        }
        default: { char b[48]; snprintf(b, sizeof b, "instrucao %u", op); err(b); continue; }
        }
        write(d, E, P);
    }
    if (fail) return;
    // declaracoes globais: registradores
    std::string g;
    for (uint32_t t : temps) { char b[48]; snprintf(b, sizeof b, "vec4 r%u = vec4(0.0);\n", t); g += b; }
    g += "ivec4 A0 = ivec4(0);\nbvec4 P0 = bvec4(false);\n";
    if (vs) {
        for (uint32_t u : outs_used) {
            char b[48];
            if (u == 0x100) g += "vec4 oPos = vec4(0.0, 0.0, 0.0, 1.0);\n";
            else if (u == 0x101) g += "vec4 oFog = vec4(0.0);\n";
            else if (u == 0x102) g += "vec4 oPts = vec4(1.0);\n";
            else if (u >= 0x400) { snprintf(b, sizeof b, "vec4 o%u = vec4(0.0, 0.0, 0.0, 1.0);\n", u - 0x400); g += b; }
            else if (u >= 0x300) { snprintf(b, sizeof b, "vec4 oT%u = vec4(0.0, 0.0, 0.0, 1.0);\n", u - 0x300); g += b; }
            else { snprintf(b, sizeof b, "vec4 oD%u = vec4(1.0);\n", u - 0x200); g += b; }
        }
        // saidas: semantica -> variavel
        for (uint32_t u : outs_used) {
            char v[16];
            if (u == 0x100) o.outputs.push_back({"POSITION0", "oPos"});
            else if (u == 0x101) o.outputs.push_back({"FOG0", "oFog"});
            else if (u == 0x102) o.outputs.push_back({"PSIZE0", "oPts"});
            else if (u >= 0x400) { snprintf(v, sizeof v, "o%u", u - 0x400); auto it = out_sem.find(u - 0x400); o.outputs.push_back({it != out_sem.end() ? it->second : sem(5, u - 0x400), v}); }
            else if (u >= 0x300) { snprintf(v, sizeof v, "oT%u", u - 0x300); o.outputs.push_back({sem(5, u - 0x300), v}); }
            else { snprintf(v, sizeof v, "oD%u", u - 0x200); o.outputs.push_back({sem(10, u - 0x200), v}); }
        }
    } else {
        for (int k = 0; k < (o.ncolor_out ? o.ncolor_out : 1); ++k) { char b[48]; snprintf(b, sizeof b, "vec4 oC%d = vec4(0.0);\n", k); g += b; }
        if (o.depth_out) g += "float oDepth = 0.0;\n";
        o.ps_inputs.assign(ps_in.begin(), ps_in.end());
    }
    o.globals = g + o.globals;
    for (uint32_t l : labels) { char b[32]; snprintf(b, sizeof b, "void L%u();\n", l); o.protos += b; }
    o.body = body;
    o.ok = true;
}

bool sm_translate(const uint32_t *code, uint32_t ndw, SmShader &out) {
    out = SmShader();
    if (ndw < 2) { out.err = "vazio"; return false; }
    Tr t(out); t.w = code; t.n = ndw;
    t.run();
    if (t.fail) { out.ok = false; out.err = t.why; }
    return out.ok;
}

static const char *kPrelude =
    "vec4 smul(vec4 a, vec4 b) { return mix(a * b, vec4(0.0), bvec4(vec4(equal(a, vec4(0.0))) + vec4(equal(b, vec4(0.0))))); }\n"
    "float sdot4(vec4 a, vec4 b) { vec4 p = smul(a, b); return (p.x + p.y) + (p.z + p.w); }\n"
    "float sdot3(vec4 a, vec4 b) { vec4 p = smul(a, b); return p.x + p.y + p.z; }\n"
    "vec4 sm_lit(vec4 s) { vec4 r = vec4(1.0, 0.0, 0.0, 1.0); if (s.x > 0.0) { r.y = s.x; if (s.y > 0.0) r.z = pow(s.y, clamp(s.w, -127.9961, 127.9961)); } return r; }\n";

std::string sm_link_vs(const SmShader &v, const std::vector<std::string> &ps_inputs, uint32_t color_bgra) {
    std::string s = "#version 300 es\nprecision highp float;\nprecision highp int;\n";
    s += "uniform vec4 vc[256];\nuniform ivec4 vci[16];\nuniform bool vcb[16];\nuniform vec4 u_fix;\n";
    for (int k = 0; k < 4; ++k) if (v.sampler_type[16 + k]) {
        char b[64]; snprintf(b, sizeof b, "uniform highp %s vs_s%d;\n", v.sampler_type[16 + k] == 3 ? "samplerCube" : v.sampler_type[16 + k] == 4 ? "sampler3D" : "sampler2D", k); s += b;
    }
    std::set<uint32_t> regs;
    for (const SmIO &io : v.inputs) regs.insert(io.reg);
    for (uint32_t r : regs) { char b[64]; snprintf(b, sizeof b, "layout(location = %u) in vec4 in%u;\n", r, r); s += b; }
    for (const std::string &p : ps_inputs) s += "out vec4 V_" + p + ";\n";
    for (uint32_t r : regs) { char b[64]; snprintf(b, sizeof b, "vec4 a%u;\n", r); s += b; }
    s += kPrelude;
    s += v.globals + v.protos + v.funcs;
    s += "void main() {\n";
    for (uint32_t r : regs) { char b[64]; snprintf(b, sizeof b, (color_bgra >> r) & 1 ? "  a%u = in%u.zyxw;\n" : "  a%u = in%u;\n", r, r); s += b; }
    s += v.body;
    std::string pos = "vec4(0.0, 0.0, 0.0, 1.0)";
    for (auto &o : v.outputs) if (o.first == "POSITION0") pos = o.second;
    // D3D -> GL: meio pixel (u_fix.zw), Y invertido (u_fix.x) e z de [0,1] para [-1,1]
    s += "  vec4 p_ = " + pos + ";\n  p_.xy += u_fix.zw * p_.w;\n  p_.y *= u_fix.x;\n  p_.z = p_.z * 2.0 - p_.w;\n  gl_Position = p_;\n";
    for (auto &o : v.outputs) if (o.first == "PSIZE0") s += "  gl_PointSize = max(" + o.second + ".x, 1.0);\n";
    for (const std::string &p : ps_inputs) {
        std::string val = p.compare(0, 5, "COLOR") == 0 ? "vec4(1.0)" : "vec4(0.0, 0.0, 0.0, 1.0)";
        for (auto &o : v.outputs) if (o.first == p) val = o.second;
        s += "  V_" + p + " = " + val + ";\n";
    }
    s += "}\n";
    return s;
}

std::string sm_link_ps(const SmShader &p, uint32_t shadow) {
    std::string s = "#version 300 es\nprecision highp float;\nprecision highp int;\n";
    s += "uniform vec4 pc[224];\nuniform ivec4 pci[16];\nuniform bool pcb[16];\nuniform vec4 u_at;\n";
    for (int k = 0; k < 16; ++k) if (p.sampler_type[k]) {
        const bool sh = p.sampler_type[k] == 2 && ((shadow >> k) & 1);
        char b[64]; snprintf(b, sizeof b, "uniform highp %s s%d;\n", p.sampler_type[k] == 3 ? "samplerCube" : p.sampler_type[k] == 4 ? "sampler3D" : sh ? "sampler2DShadow" : "sampler2D", k); s += b;
        if (p.sampler_type[k] != 2) continue;
        char f[1024];
        if (sh)   // mapa de sombra (textura de profundidade): como no D3D9, a amostra devolve a comparacao com z (PCF com filtro linear)
            snprintf(f, sizeof f,
                "vec4 t2d_%d(vec4 c) { return vec4(texture(s%d, vec3(c.xy, c.z))); }\n"
                "vec4 t2dp_%d(vec4 c) { return vec4(textureProj(s%d, c)); }\n"
                "vec4 t2db_%d(vec4 c) { return vec4(texture(s%d, vec3(c.xy, c.z), c.w)); }\n"
                "vec4 t2dl_%d(vec4 c) { return vec4(textureLod(s%d, vec3(c.xy, c.z), c.w)); }\n"
                "vec4 t2dg_%d(vec4 c, vec2 dx, vec2 dy) { return vec4(textureGrad(s%d, vec3(c.xy, c.z), dx, dy)); }\n", k, k, k, k, k, k, k, k, k, k);
        else
            snprintf(f, sizeof f,
                "vec4 t2d_%d(vec4 c) { return texture(s%d, c.xy); }\n"
                "vec4 t2dp_%d(vec4 c) { return textureProj(s%d, c.xyw); }\n"
                "vec4 t2db_%d(vec4 c) { return texture(s%d, c.xy, c.w); }\n"
                "vec4 t2dl_%d(vec4 c) { return textureLod(s%d, c.xy, c.w); }\n"
                "vec4 t2dg_%d(vec4 c, vec2 dx, vec2 dy) { return textureGrad(s%d, c.xy, dx, dy); }\n", k, k, k, k, k, k, k, k, k, k);
        s += f;
    }
    for (const std::string &x : p.ps_inputs) s += "in vec4 V_" + x + ";\n";
    const int nc = p.ncolor_out ? p.ncolor_out : 1;
    for (int k = 0; k < nc; ++k) { char b[64]; snprintf(b, sizeof b, "layout(location = %d) out vec4 Frag%d;\n", k, k); s += b; }
    s += "vec4 vPos;\nfloat vFace;\n";
    s += kPrelude;
    s += p.globals + p.protos + p.funcs;
    s += "void main() {\n  vPos = vec4(gl_FragCoord.xy - 0.5, 0.0, 0.0);\n  vFace = gl_FrontFacing ? 1.0 : -1.0;\n";
    s += p.body;
    // alpha test (o GLES nao tem): u_at.x = funcao D3DCMP (0 = desligado), u_at.y = referencia
    s += "  int at_ = int(u_at.x); float a_ = oC0.a;\n"
         "  if (at_ != 0 && at_ != 8) { bool ok_ = at_ == 2 ? a_ < u_at.y : at_ == 3 ? a_ == u_at.y : at_ == 4 ? a_ <= u_at.y : at_ == 5 ? a_ > u_at.y : at_ == 6 ? a_ != u_at.y : at_ == 7 ? a_ >= u_at.y : false; if (!ok_) discard; }\n";
    for (int k = 0; k < nc; ++k) { char b[48]; snprintf(b, sizeof b, "  Frag%d = oC%d;\n", k, k); s += b; }
    if (p.depth_out) s += "  gl_FragDepth = oDepth;\n";
    s += "}\n";
    return s;
}
