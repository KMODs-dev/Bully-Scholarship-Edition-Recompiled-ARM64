#!/usr/bin/env python3
# Recompilador estatico x86 (32 bits, PE do Windows) -> C. Le a desmontagem do objdump (-M intel) e o PE.
# Estado: registradores em Cpu, flags preguicosas (tipo + resultado + operandos), pilha do x87 em double com topo dinamico,
# memoria do jogo numa janela de 4 GB (M + endereco de 32 bits). Instrucao sem traducao vira chamada a x86_unimpl().
import re, struct, sys, collections, os

REG32 = ['eax', 'ecx', 'edx', 'ebx', 'esp', 'ebp', 'esi', 'edi']
REG16 = ['ax', 'cx', 'dx', 'bx', 'sp', 'bp', 'si', 'di']
REG8L = ['al', 'cl', 'dl', 'bl']
REG8H = ['ah', 'ch', 'dh', 'bh']
SIZES = {'BYTE': 1, 'WORD': 2, 'DWORD': 4, 'QWORD': 8, 'TBYTE': 10, 'XMMWORD': 16, 'FWORD': 6}
JCC = {'jo': 'O', 'jno': '!O', 'jb': 'B', 'jae': '!B', 'je': 'E', 'jne': '!E', 'jbe': 'BE', 'ja': '!BE', 'js': 'S', 'jns': '!S',
       'jp': 'P', 'jnp': '!P', 'jl': 'L', 'jge': '!L', 'jle': 'LE', 'jg': '!LE'}
SETCC = {('set' + k[1:]): v for k, v in JCC.items()}
CMOV = {('cmov' + k[1:]): v for k, v in JCC.items()}

class PE:
    def __init__(self, path):
        d = open(path, 'rb').read(); self.d = d
        pe = struct.unpack_from('<I', d, 0x3C)[0]
        nsec = struct.unpack_from('<H', d, pe + 6)[0]; optsz = struct.unpack_from('<H', d, pe + 20)[0]
        opt = pe + 24
        self.base = struct.unpack_from('<I', d, opt + 28)[0]
        self.entry = self.base + struct.unpack_from('<I', d, opt + 16)[0]
        self.secs = []
        for i in range(nsec):
            o = opt + optsz + 40 * i
            name = d[o:o + 8].rstrip(b'\0').decode()
            vsz, va, rsz, rptr = struct.unpack_from('<IIII', d, o + 8)
            self.secs.append((name, self.base + va, vsz, rptr, rsz))
        # imports: endereco da entrada da IAT -> "dll!nome"
        self.imports = {}
        idir = struct.unpack_from('<II', d, opt + 96 + 8)[0]
        o = self.rva2off(idir)
        while True:
            oft, ts, fc, nm, ft = struct.unpack_from('<IIIII', d, o)
            if nm == 0: break
            dll = d[self.rva2off(nm):].split(b'\0')[0].decode()
            t = oft or ft; k = 0
            while True:
                e = struct.unpack_from('<I', d, self.rva2off(t) + 4 * k)[0]
                if e == 0: break
                if e & 0x80000000: name = '#%d' % (e & 0xFFFF)
                else: name = d[self.rva2off(e) + 2:].split(b'\0')[0].decode()
                self.imports[self.base + ft + 4 * k] = dll + '!' + name
                k += 1
            o += 20
    def rva2off(self, rva):
        for name, va, vsz, rptr, rsz in self.secs:
            if va - self.base <= rva < va - self.base + max(vsz, rsz): return rptr + rva - (va - self.base)
        raise ValueError('rva %x' % rva)
    def u32(self, va):
        for name, sva, vsz, rptr, rsz in self.secs:
            if sva <= va < sva + rsz - 3: return struct.unpack_from('<I', self.d, rptr + va - sva)[0]
        return None
    def in_text(self, va):
        n, sva, vsz, rptr, rsz = self.secs[0]
        return sva <= va < sva + vsz

def load_dis(path):
    ins = {}
    prev = None
    rx = re.compile(r'^\s+([0-9a-f]+):\t(.*)$')
    for ln in open(path):
        m = rx.match(ln)
        if not m: continue
        a = int(m.group(1), 16); txt = m.group(2).strip()
        if prev is not None: ins[prev][2] = a - prev
        parts = txt.split(None, 1)
        mn = parts[0] if parts else ''; ops = parts[1] if len(parts) > 1 else ''
        if mn == 'data16' and ops:
            p2 = ops.split(None, 1); mn = p2[0]; ops = p2[1] if len(p2) > 1 else ''
        if mn in ('rep', 'repz', 'repnz', 'lock', 'repe', 'repne') and ops:
            p2 = ops.split(None, 1); mn = mn + ' ' + p2[0]; ops = p2[1] if len(p2) > 1 else ''
        ins[a] = [mn, ops, 0]
        prev = a
    return ins

def split_ops(ops):
    out = []; depth = 0; cur = ''
    for ch in ops:
        if ch == '[' or ch == '(': depth += 1
        if ch == ']' or ch == ')': depth -= 1
        if ch == ',' and depth == 0: out.append(cur.strip()); cur = ''
        else: cur += ch
    if cur.strip(): out.append(cur.strip())
    return out

class Opnd:
    def __init__(self, kind, **kw):
        self.kind = kind; self.__dict__.update(kw)

def parse_op(s):
    s = s.strip()
    s = re.sub(r'\s*<[^>]*>$', '', s)
    m = re.match(r'^(BYTE|WORD|DWORD|QWORD|TBYTE|XMMWORD|FWORD) PTR (.*)$', s)
    size = None
    if m: size = SIZES[m.group(1)]; s = m.group(2)
    seg = None
    m = re.match(r'^(cs|ds|es|fs|gs|ss):(.*)$', s)
    if m: seg = m.group(1); s = m.group(2)
    if s.startswith('['):
        inner = s[1:-1]
        base = idx = None; scale = 1; disp = 0
        for t in re.findall(r'[+-]?[^+-]+', inner):
            sign = -1 if t.startswith('-') else 1
            t = t.lstrip('+-')
            if '*' in t:
                r, sc = t.split('*')
                if r != 'eiz': idx = r; scale = int(sc)
            elif t == 'eiz': pass
            elif t in REG32: base = t if base is None else base
            elif t.startswith('0x'): disp += sign * int(t, 16)
            elif t.isdigit(): disp += sign * int(t)
            else: return Opnd('bad', text=s)
        return Opnd('mem', size=size, base=base, idx=idx, scale=scale, disp=disp & 0xFFFFFFFF, seg=seg)
    if seg is not None and re.match(r'^0x[0-9a-f]+$', s):
        return Opnd('mem', size=size, base=None, idx=None, scale=1, disp=int(s, 16), seg=seg)
    if s in REG32: return Opnd('reg', size=4, r=REG32.index(s), name=s)
    if s in REG16: return Opnd('reg', size=2, r=REG16.index(s), name=s)
    if s in REG8L: return Opnd('reg8', size=1, r=REG8L.index(s), hi=False, name=s)
    if s in REG8H: return Opnd('reg8', size=1, r=REG8H.index(s), hi=True, name=s)
    m = re.match(r'^st(?:\((\d)\))?$', s)
    if m: return Opnd('st', i=int(m.group(1) or 0))
    m = re.match(r'^xmm(\d)$', s)
    if m: return Opnd('xmm', i=int(m.group(1)))
    if re.match(r'^0x[0-9a-f]+$', s): return Opnd('imm', v=int(s, 16))
    if re.match(r'^-0x[0-9a-f]+$', s): return Opnd('imm', v=(-int(s[1:], 16)) & 0xFFFFFFFF)
    if re.match(r'^\d+$', s): return Opnd('imm', v=int(s))
    return Opnd('bad', text=s)

COMMENTS = False
MASK = {1: '0xFFu', 2: '0xFFFFu', 4: '0xFFFFFFFFu'}
CT = {1: 'uint8_t', 2: 'uint16_t', 4: 'uint32_t'}

class Unimpl(Exception): pass

class FuncGen:
    def __init__(self, rc, entry):
        self.rc = rc; self.entry = entry; self.L = []; self.labels = set(); self.unimpl = collections.Counter()

    def addr(self, o):
        parts = []
        if o.base: parts.append('c.r[%d]' % REG32.index(o.base))
        if o.idx: parts.append('c.r[%d]%s' % (REG32.index(o.idx), '' if o.scale == 1 else ' * %du' % o.scale))
        if o.disp or not parts: parts.append('0x%Xu' % o.disp)
        a = ' + '.join(parts)
        if o.seg == 'fs': a = 'FSBASE + (%s)' % a
        return '(uint32_t)(%s)' % a

    def rd(self, o, size=None):
        size = size or getattr(o, 'size', None) or 4
        if o.kind == 'reg':
            return 'c.r[%d]' % o.r if size == 4 else '(uint16_t)c.r[%d]' % o.r
        if o.kind == 'reg8':
            return '(uint8_t)(c.r[%d] >> 8)' % o.r if o.hi else '(uint8_t)c.r[%d]' % o.r
        if o.kind == 'imm': return '0x%Xu' % (o.v & ((1 << (8 * size)) - 1))
        if o.kind == 'mem': return 'rd%d(%s)' % (size * 8, self.addr(o))
        raise Unimpl('rd %s' % o.kind)

    def wr(self, o, val, size=None):
        size = size or getattr(o, 'size', None) or 4
        if o.kind == 'reg':
            if size == 4: return 'c.r[%d] = (uint32_t)(%s);' % (o.r, val)
            return 'c.r[%d] = (c.r[%d] & 0xFFFF0000u) | (uint16_t)(%s);' % (o.r, o.r, val)
        if o.kind == 'reg8':
            if o.hi: return 'c.r[%d] = (c.r[%d] & 0xFFFF00FFu) | ((uint32_t)(uint8_t)(%s) << 8);' % (o.r, o.r, val)
            return 'c.r[%d] = (c.r[%d] & 0xFFFFFF00u) | (uint8_t)(%s);' % (o.r, o.r, val)
        if o.kind == 'mem': return 'wr%d(%s, (%s)(%s));' % (size * 8, self.addr(o), CT[size], val)
        raise Unimpl('wr %s' % o.kind)

    def osize(self, a, b=None):
        for o in (a, b):
            if o is not None and getattr(o, 'size', None) and o.kind in ('reg', 'reg8', 'mem'): return o.size
        return 4

    def st(self, i): return 'ST(%d)' % i

    def e(self, s): self.L.append('  ' + s)

    def gen(self):
        rc = self.rc
        # descobre os enderecos alcancaveis a partir da entrada
        todo = [self.entry]; seen = set(); self.tails = set(); self.all_targets = set([self.entry])
        while todo:
            a = todo.pop()
            while a not in seen:
                if a not in rc.ins: self.tails.add(('bad', a)); break
                seen.add(a)
                mn, ops, sz = rc.ins[a]
                nxt = a + sz
                if mn in JCC or mn in ('jecxz', 'loop', 'loope', 'loopne'):
                    t = parse_op(ops)
                    if t.kind == 'imm': self.all_targets.add(t.v)
                    if t.kind == 'imm':
                        if t.v in rc.funcs and t.v != self.entry: pass
                        else: todo.append(t.v); self.labels.add(t.v)
                    a = nxt; continue
                if mn == 'jmp':
                    t = parse_op(ops)
                    if t.kind == 'imm': self.all_targets.add(t.v)
                    if t.kind == 'imm':
                        if t.v in rc.funcs and t.v != self.entry: break
                        self.labels.add(t.v); a = t.v; continue
                    tab = rc.jump_table(a, ops)
                    if tab:
                        for x in tab: todo.append(x); self.labels.add(x); self.all_targets.add(x)
                    break
                if mn in ('ret', 'retf', 'repz ret', 'int3', 'hlt') or mn == '(bad)': break
                if mn == 'call':
                    t = parse_op(ops)
                    if t.kind == 'imm' and t.v in rc.noreturn: break
                a = nxt
        self.body = sorted(seen)
        self.flags_liveness()
        self.used_labels = set([self.entry])
        out = []
        if self.body and self.body[0] != self.entry: out.append('  goto L_%X;' % self.entry)
        skip = set()
        for a in self.body:
            mn, ops, sz = rc.ins[a]
            self.L = []
            if a in skip:
                continue
            self.fuse = None; self.fuse_failed = False
            if mn in ('cmp', 'test'):
                nj = a + sz
                if nj in rc.ins and rc.ins[nj][0] in JCC and nj not in self.all_targets and nj in self.body_set() and self.flive.get(nj) == (False, False):
                    t = parse_op(rc.ins[nj][1])
                    if t.kind == 'imm': self.fuse = (JCC[rc.ins[nj][0]], t.v)
            try:
                self.ins(a, mn, ops, sz)
                if mn in ('cmp', 'test') and self.fuse is None and not self.fuse_failed and (a + sz) in rc.ins and rc.ins[a + sz][0] in JCC and (a + sz) not in self.all_targets and self.flive.get(a + sz) == (False, False) and parse_op(rc.ins[a + sz][1]).kind == 'imm':
                    skip.add(a + sz)
            except Unimpl as ex:
                self.unimpl[mn] += 1
                self.L = ['  x86_unimpl(c, 0x%Xu); /* %s %s : %s */' % (a, mn, ops.replace('*/', '* /'), ex)]
            if COMMENTS: out.append('L_%X: /* %s %s */' % (a, mn, ops.replace('*/', '* /')))
            else: out.append('L_%X:' % a)
            # flags mortas: some a gravacao preguicosa
            la, lc = self.flive.get(a, (True, True))
            for ln in self.L:
                if not la and not lc and ln.strip().startswith('FL(') and ln.strip().endswith(');'): continue
                if not la and not lc: ln = re.sub(r'\s*FL\([^;]*\); \}', ' }', ln)
                if not lc: ln = ln.replace(' c.fcin = CF(c);', '')
                out.append(ln)
            # queda para fora do corpo (proxima instrucao fora do conjunto)
            nxt = a + sz
            if nxt not in seen and not self.ends(mn, ops):
                if nxt in rc.funcs: out.append('  f_%X(c); return;' % nxt)
                else: out.append('  x86_fell(c, 0x%Xu); return;' % nxt)
        if not COMMENTS:
            out = [ln for ln in out if not (ln.startswith('L_') and ln.endswith(':') and int(ln[2:-1], 16) not in self.used_labels)]
        return out

    # vivacidade das flags (para tras): (alguma flag sem CF viva, CF viva) na saida de cada instrucao
    def flags_liveness(self):
        rc = self.rc; body = self.body; bs = set(body)
        succ = {}; info = {}
        for a in body:
            mn, ops, sz = rc.ins[a]; nxt = a + sz; ss = []
            if mn in JCC or mn in ('jecxz', 'loop', 'loope', 'loopne'):
                t = parse_op(ops)
                if t.kind == 'imm' and t.v in bs: ss.append(t.v)
                if nxt in bs: ss.append(nxt)
            elif mn == 'jmp':
                t = parse_op(ops)
                if t.kind == 'imm':
                    if t.v in bs: ss.append(t.v)
                else:
                    tab = rc.jump_table(a, ops)
                    if tab: ss.extend(x for x in tab if x in bs)
            elif not self.ends(mn, ops):
                if nxt in bs: ss.append(nxt)
            succ[a] = ss
            # (le_alguma, le_cf, mata_alguma, mata_cf)
            r_any = r_cf = False; k_any = k_cf = False
            cond = JCC.get(mn) or SETCC.get(mn) or CMOV.get(mn)
            if cond:
                cc = cond.lstrip('!')
                r_cf = cc in ('B', 'BE'); r_any = cc not in ('B',)
            elif mn in ('adc', 'sbb'): r_cf = True; k_any = k_cf = True
            elif mn in ('lahf', 'pushf', 'pushfd', 'rcl', 'rcr', 'sahf', 'rol', 'ror'): r_any = r_cf = True
            elif mn in ('add', 'sub', 'and', 'or', 'xor', 'cmp', 'test', 'neg', 'imul', 'mul', 'fcomi', 'fucomi', 'fcomip', 'fucomip'):
                k_any = k_cf = True
            elif mn in ('inc', 'dec'): k_any = True
            elif mn in ('shl', 'sal', 'shr', 'sar', 'shld', 'shrd'):
                o = split_ops(ops)
                if (len(o) == 1) or (len(o) >= 2 and parse_op(o[-1]).kind == 'imm' and (parse_op(o[-1]).v & 31)): k_any = k_cf = True
            elif mn in ('call', 'ret', 'repz ret') or mn.startswith('rep') and ('cmps' in mn or 'scas' in mn) is False and False: k_any = k_cf = True
            elif mn in ('cmps', 'scas'): k_any = k_cf = True
            if mn == 'call': k_any = k_cf = True
            # CRT em assembly (>= 0x850000) devolve resultado em flags para quem chamou (ex.: cmp; je; ret em
            # _sqrt/_sin): no ret e em saltos para fora da funcao as flags continuam vivas
            if self.entry >= 0x850000:
                if mn in ('ret', 'repz ret'): r_any = r_cf = True; k_any = k_cf = False
                elif mn == 'jmp' and not ss: r_any = r_cf = True
            info[a] = (r_any, r_cf, k_any, k_cf)
        live_in = {a: (False, False) for a in body}
        live_out = {a: (False, False) for a in body}
        changed = True
        while changed:
            changed = False
            for a in reversed(body):
                la = lc = False
                for t in succ[a]:
                    x, y = live_in[t]; la |= x; lc |= y
                r_any, r_cf, k_any, k_cf = info[a]
                ia = r_any or (la and not k_any)
                ic = r_cf or (lc and not k_cf)
                if (la, lc) != live_out[a]: live_out[a] = (la, lc)
                if (ia, ic) != live_in[a]: live_in[a] = (ia, ic); changed = True
        self.flive = live_out

    def ends(self, mn, ops):
        if mn in ('ret', 'retf', 'repz ret', 'jmp', 'int3', 'hlt', '(bad)'): return True
        if mn == 'call':
            t = parse_op(ops)
            if t.kind == 'imm' and t.v in self.rc.noreturn: return True
        return False

    def goto(self, t):
        if t in self.body_set(): self.used_labels.add(t); return 'goto L_%X;' % t
        if t in self.rc.funcs: return '{ f_%X(c); return; }' % t
        return '{ x86_jump(c, 0x%Xu); return; }' % t

    def body_set(self):
        if not hasattr(self, '_bs'): self._bs = set(self.body)
        return self._bs

    def flags(self, kind, size, res, a='0u', b='0u'):
        self.e('FL(%s, %s, %s, %s, %s);' % (kind, MASK[size], res, a, b))

    def ins(self, a, mn, ops, sz):
        rc = self.rc
        if a in IMM_PATCH: ops = ops.replace(IMM_PATCH[a][0], IMM_PATCH[a][1])
        if a in HOOKS: self.e('{ void rt_hook(Cpu &, uint32_t); rt_hook(c, 0x%Xu); }' % a)
        if a in INSN_REPLACE: self.e(INSN_REPLACE[a]); return
        SEGV = {'cs': 0x1B, 'ss': 0x23, 'ds': 0x23, 'es': 0x23, 'fs': 0x3B, 'gs': 0}
        if mn == 'mov' and ops and split_ops(ops)[-1].strip() in SEGV:   # mov r/m16, sreg: valores fixos do Windows 32 bits
            o0 = parse_op(split_ops(ops)[0]); e = self.e
            e(self.wr(o0, '0x%Xu' % SEGV[split_ops(ops)[-1].strip()], 2 if o0.kind == 'mem' else 4)); return
        if mn == 'mov' and ops and split_ops(ops)[0].strip() in SEGV: return   # mov sreg, x: ignorado
        O = [parse_op(x) for x in split_ops(ops)] if ops else []
        for o in O:
            if o.kind == 'bad': raise Unimpl('operando %s' % o.text)
        nxt = (a + sz) & 0xFFFFFFFF
        e = self.e
        if mn == 'nop' or mn == 'fwait' or mn == 'fnclex' or mn == 'cld' and False: return
        if mn == 'mov':
            s = self.osize(O[0], O[1])
            e(self.wr(O[0], self.rd(O[1], s), s)); return
        if mn in ('movzx', 'movsx'):
            ss = O[1].size; ds = O[0].size
            v = self.rd(O[1], ss)
            if mn == 'movsx': v = '(uint32_t)(int32_t)(%s)%s' % ({1: 'int8_t', 2: 'int16_t'}[ss], v)
            e(self.wr(O[0], v, ds)); return
        if mn == 'lea':
            e(self.wr(O[0], self.addr(O[1]), O[0].size)); return
        if mn == 'push':
            v = self.rd(O[0], 4) if O[0].kind != 'imm' else '0x%Xu' % O[0].v
            if O[0].kind in ('reg',) and O[0].size == 2: raise Unimpl('push16')
            e('PUSH(%s);' % v); return
        if mn == 'pop':
            if O[0].kind == 'reg' and O[0].size == 4: e('POP(c.r[%d]);' % O[0].r); return
            e('{ const uint32_t v = rd32(c.r[4]); c.r[4] += 4; %s }' % self.wr(O[0], 'v', 4)); return
        if mn in ('add', 'sub', 'and', 'or', 'xor', 'cmp', 'test', 'adc', 'sbb'):
            s = self.osize(O[0], O[1])
            A = self.rd(O[0], s); B = self.rd(O[1], s)
            la, lc = self.flive.get(a, (True, True))
            fz = getattr(self, 'fuse', None)
            if mn in ('cmp', 'test') and fz:
                # cmp/test seguido de jcc com flags mortas depois: condicao direta
                cc, tgt = fz; self.fuse = None
                sb = {1: 'int8_t', 2: 'int16_t', 4: 'int32_t'}[s]; ut = CT[s]
                if mn == 'cmp':
                    x, y = '(%s)(%s)' % (ut, A), '(%s)(%s)' % (ut, B)
                    sx, sy = '(%s)%s' % (sb, x), '(%s)%s' % (sb, y)
                    m = {'E': '%s == %s' % (x, y), 'B': '%s < %s' % (x, y), 'BE': '%s <= %s' % (x, y), 'L': '%s < %s' % (sx, sy), 'LE': '%s <= %s' % (sx, sy),
                         'S': '(%s)(%s - %s) < 0' % (sb, x, y)}
                else:
                    v = '(%s)((%s) & (%s))' % (ut, A, B); sv = '(%s)%s' % (sb, v)
                    m = {'E': '%s == 0' % v, 'S': '%s < 0' % sv, 'LE': '%s <= 0' % sv, 'L': '%s < 0' % sv, 'B': '0', 'BE': '%s == 0' % v}
                neg = cc.startswith('!'); k = cc.lstrip('!')
                if k in m:
                    e('if (%s(%s)) %s' % ('!' if neg else '', m[k], self.goto(tgt))); return
                self.fuse_failed = True
            if not la and not lc and mn not in ('cmp', 'test', 'adc', 'sbb'):
                op = {'add': '+', 'sub': '-', 'and': '&', 'or': '|', 'xor': '^'}[mn]
                if mn == 'xor' and O[0].kind == 'reg' and O[1].kind == 'reg' and O[0].r == O[1].r and s == 4: e('c.r[%d] = 0;' % O[0].r); return
                if O[0].kind == 'reg' and s == 4: e('c.r[%d] %s= %s;' % (O[0].r, op, B)); return
                e(self.wr(O[0], '(%s) %s (%s)' % (A, op, B), s)); return
            if not la and not lc and mn in ('cmp', 'test'): return
            if mn == 'xor' and O[0].kind == 'reg' and O[1].kind == 'reg' and O[0].r == O[1].r and s == 4:
                e('c.r[%d] = 0;' % O[0].r); self.flags('K_LOGIC', 4, '0u'); return
            e('{ const uint32_t a_ = %s, b_ = %s;' % (A, B))
            if mn == 'add': r = 'a_ + b_'; k = 'K_ADD'
            elif mn == 'sub' or mn == 'cmp': r = 'a_ - b_'; k = 'K_SUB'
            elif mn == 'adc': r = 'a_ + b_ + cf_'; k = 'K_ADC'
            elif mn == 'sbb': r = 'a_ - b_ - cf_'; k = 'K_SBB'
            elif mn in ('and', 'test'): r = 'a_ & b_'; k = 'K_LOGIC'
            elif mn == 'or': r = 'a_ | b_'; k = 'K_LOGIC'
            else: r = 'a_ ^ b_'; k = 'K_LOGIC'
            if mn in ('adc', 'sbb'): e('  const uint32_t cf_ = CF(c);')
            e('  const uint32_t r_ = (uint32_t)(%s);' % r)
            if mn not in ('cmp', 'test'): e('  ' + self.wr(O[0], 'r_', s))
            if mn in ('adc', 'sbb'): e('  FL(%s, %s, r_, a_, b_); c.fcin = cf_; }' % (k, MASK[s]))
            else: e('  FL(%s, %s, r_, a_, b_); }' % (k, MASK[s]))
            return
        if mn in ('inc', 'dec', 'neg', 'not'):
            s = self.osize(O[0])
            A = self.rd(O[0], s)
            if mn == 'not': e(self.wr(O[0], '~(%s)' % A, s)); return
            e('{ const uint32_t a_ = %s;' % A)
            if mn == 'inc': e('  const uint32_t r_ = a_ + 1u; c.fcin = CF(c); %s FL(K_INC, %s, r_, a_, 1u); }' % (self.wr(O[0], 'r_', s), MASK[s]))
            elif mn == 'dec': e('  const uint32_t r_ = a_ - 1u; c.fcin = CF(c); %s FL(K_DEC, %s, r_, a_, 1u); }' % (self.wr(O[0], 'r_', s), MASK[s]))
            else: e('  const uint32_t r_ = 0u - a_; %s FL(K_SUB, %s, r_, 0u, a_); }' % (self.wr(O[0], 'r_', s), MASK[s]))
            return
        if mn in ('shl', 'sal', 'shr', 'sar', 'rol', 'ror'):
            s = self.osize(O[0])
            cnt = '1u' if len(O) == 1 else ('(c.r[1] & 31u)' if O[1].kind == 'reg8' else '%du' % (O[1].v & 31))
            A = self.rd(O[0], s); bits = s * 8
            fn = {'shl': 'SHL', 'sal': 'SHL', 'shr': 'SHR', 'sar': 'SAR', 'rol': 'ROL', 'ror': 'ROR'}[mn]
            e('{ const uint32_t n_ = %s; if (n_) { const uint32_t r_ = %s%d(c, %s, n_); %s } }' % (cnt, fn, bits, A, self.wr(O[0], 'r_', s)))
            return
        if mn in ('shld', 'shrd'):
            cnt = '(c.r[1] & 31u)' if O[2].kind == 'reg8' else '%du' % (O[2].v & 31)
            e('{ const uint32_t n_ = %s; if (n_) { const uint32_t r_ = %s32(c, %s, %s, n_); %s } }' % (cnt, mn.upper(), self.rd(O[0], 4), self.rd(O[1], 4), self.wr(O[0], 'r_', 4)))
            return
        if mn == 'imul':
            if len(O) == 1:
                s = self.osize(O[0])
                if s == 1:
                    e('{ const int32_t p_ = (int32_t)(int8_t)c.r[0] * (int8_t)%s; c.r[0] = (c.r[0] & 0xFFFF0000u) | (uint16_t)p_; FLX(c, p_ != (int8_t)p_); }' % self.rd(O[0], 1)); return
                if s == 2:
                    e('{ const int32_t p_ = (int32_t)(int16_t)c.r[0] * (int16_t)%s; c.r[0] = (c.r[0] & 0xFFFF0000u) | (uint16_t)p_; c.r[2] = (c.r[2] & 0xFFFF0000u) | (uint16_t)((uint32_t)p_ >> 16); FLX(c, p_ != (int16_t)p_); }' % self.rd(O[0], 2)); return
                e('{ const int64_t p_ = (int64_t)(int32_t)c.r[0] * (int32_t)%s; c.r[0] = (uint32_t)p_; c.r[2] = (uint32_t)((uint64_t)p_ >> 32); FLX(c, p_ != (int64_t)(int32_t)p_); }' % self.rd(O[0], 4))
                return
            src = O[1] if len(O) == 2 else O[1]; imm = O[2] if len(O) == 3 else None
            s = O[0].size
            if s == 2:
                A = self.rd(O[0], 2) if len(O) == 2 else self.rd(O[1], 2)
                B = self.rd(O[1], 2) if len(O) == 2 else '0x%Xu' % (imm.v & 0xFFFF)
                e('{ const int32_t p_ = (int32_t)(int16_t)%s * (int16_t)%s; %s FLX(c, p_ != (int16_t)p_); }' % (A, B, self.wr(O[0], 'p_', 2)))
                return
            if s != 4: raise Unimpl('imul16')
            A = self.rd(O[0], 4) if len(O) == 2 else self.rd(O[1], 4)
            B = self.rd(O[1], 4) if len(O) == 2 else '0x%Xu' % imm.v
            e('{ const int64_t p_ = (int64_t)(int32_t)%s * (int32_t)%s; c.r[%d] = (uint32_t)p_; FLX(c, p_ != (int64_t)(int32_t)p_); }' % (A, B, O[0].r))
            return
        if mn == 'mul':
            s = self.osize(O[0])
            if s == 1:
                e('{ const uint32_t p_ = (uint32_t)(uint8_t)c.r[0] * %s; c.r[0] = (c.r[0] & 0xFFFF0000u) | (uint16_t)p_; FLX(c, (p_ >> 8) != 0); }' % self.rd(O[0], 1)); return
            if s == 2:
                e('{ const uint32_t p_ = (uint32_t)(uint16_t)c.r[0] * %s; c.r[0] = (c.r[0] & 0xFFFF0000u) | (uint16_t)p_; c.r[2] = (c.r[2] & 0xFFFF0000u) | (p_ >> 16); FLX(c, (p_ >> 16) != 0); }' % self.rd(O[0], 2)); return
            e('{ const uint64_t p_ = (uint64_t)c.r[0] * %s; c.r[0] = (uint32_t)p_; c.r[2] = (uint32_t)(p_ >> 32); FLX(c, (p_ >> 32) != 0); }' % self.rd(O[0], 4))
            return
        if mn in ('div', 'idiv'):
            s = self.osize(O[0])
            if s == 1:
                if mn == 'div': e('{ const uint32_t n_ = (uint16_t)c.r[0]; const uint32_t d_ = %s; if (!d_) x86_divzero(c, 0x%Xu); c.r[0] = (c.r[0] & 0xFFFF0000u) | ((n_ %% d_) << 8) | (uint8_t)(n_ / d_); }' % (self.rd(O[0], 1), a))
                else: e('{ const int32_t n_ = (int16_t)c.r[0]; const int32_t d_ = (int8_t)%s; if (!d_) x86_divzero(c, 0x%Xu); c.r[0] = (c.r[0] & 0xFFFF0000u) | ((uint32_t)(uint8_t)(n_ %% d_) << 8) | (uint8_t)(n_ / d_); }' % (self.rd(O[0], 1), a))
                return
            if s == 2:
                if mn == 'div': e('{ const uint32_t n_ = ((c.r[2] & 0xFFFFu) << 16) | (uint16_t)c.r[0]; const uint32_t d_ = %s; if (!d_) x86_divzero(c, 0x%Xu); c.r[0] = (c.r[0] & 0xFFFF0000u) | (uint16_t)(n_ / d_); c.r[2] = (c.r[2] & 0xFFFF0000u) | (uint16_t)(n_ %% d_); }' % (self.rd(O[0], 2), a))
                else: e('{ const int32_t n_ = (int32_t)(((c.r[2] & 0xFFFFu) << 16) | (uint16_t)c.r[0]); const int32_t d_ = (int16_t)%s; if (!d_) x86_divzero(c, 0x%Xu); c.r[0] = (c.r[0] & 0xFFFF0000u) | (uint16_t)(n_ / d_); c.r[2] = (c.r[2] & 0xFFFF0000u) | (uint16_t)(n_ %% d_); }' % (self.rd(O[0], 2), a))
                return
            if mn == 'div':
                e('{ const uint64_t n_ = ((uint64_t)c.r[2] << 32) | c.r[0]; const uint32_t d_ = %s; if (!d_) x86_divzero(c, 0x%Xu); c.r[0] = (uint32_t)(n_ / d_); c.r[2] = (uint32_t)(n_ %% d_); }' % (self.rd(O[0], 4), a))
            else:
                e('{ const int64_t n_ = (int64_t)(((uint64_t)c.r[2] << 32) | c.r[0]); const int32_t d_ = (int32_t)%s; if (!d_) x86_divzero(c, 0x%Xu); c.r[0] = (uint32_t)(int32_t)(n_ / d_); c.r[2] = (uint32_t)(int32_t)(n_ %% d_); }' % (self.rd(O[0], 4), a))
            return
        if mn == 'cdq': e('c.r[2] = (uint32_t)((int32_t)c.r[0] >> 31);'); return
        if mn == 'cwde': e('c.r[0] = (uint32_t)(int32_t)(int16_t)c.r[0];'); return
        if mn in ('rcr', 'rcl') and (len(O) == 1 or (O[1].kind == 'imm' and O[1].v == 1)):
            sz = self.osize(O[0]); bits = sz * 8; A = self.rd(O[0], sz)
            if mn == 'rcr': e('{ const uint32_t a_ = %s; const uint32_t r_ = (a_ >> 1) | (CF(c) << %d); %s FLX(c, a_ & 1u); }' % (A, bits - 1, self.wr(O[0], 'r_', sz)))
            else: e('{ const uint32_t a_ = %s; const uint32_t r_ = (a_ << 1) | CF(c); %s FLX(c, (a_ >> %d) & 1u); }' % (A, self.wr(O[0], 'r_', sz), bits - 1))
            return
        if mn in ('fnstenv', 'fstenv', 'fnsave', 'fsave'):
            ad = self.addr(O[0])
            e('{ const uint32_t a_ = %s; memset(M + a_, 0, 28); wr16(a_, c.fcw); wr16(a_ + 4, FSW(c)); wr16(a_ + 8, 0xFFFFu);' % ad)
            if 'save' in mn: e('  for (int i_ = 0; i_ < 8; ++i_) wrf80(a_ + 28 + 10 * i_, ST(i_)); c.top = 0; c.fcw = 0x37F; c.fsw = 0;')
            e('}'); return
        if mn in ('fldenv', 'frstor'):
            ad = self.addr(O[0])
            e('{ const uint32_t a_ = %s; c.fcw = rd16(a_); const uint16_t s_ = rd16(a_ + 4); c.top = (s_ >> 11) & 7; c.fsw = s_ & ~0x3800u;' % ad)
            if mn == 'frstor': e('  for (int i_ = 0; i_ < 8; ++i_) ST(i_) = rdf80(a_ + 28 + 10 * i_);')
            e('}'); return
        if mn == 'xlat': e('c.r[0] = (c.r[0] & ~0xFFu) | M[(uint32_t)(c.r[3] + (c.r[0] & 0xFFu))];'); return
        if mn == 'xchg':
            s = self.osize(O[0], O[1])
            e('{ const uint32_t t_ = %s; %s %s }' % (self.rd(O[0], s), self.wr(O[0], self.rd(O[1], s), s), self.wr(O[1], 't_', s))); return
        if mn == 'leave': e('c.r[4] = c.r[5]; c.r[5] = rd32(c.r[4]); c.r[4] += 4;'); return
        if mn in SETCC:
            e(self.wr(O[0], 'COND_%s(c) ? 1u : 0u' % SETCC[mn].replace('!', 'N'), 1)); return
        if mn in CMOV:
            e('if (COND_%s(c)) %s' % (CMOV[mn].replace('!', 'N'), self.wr(O[0], self.rd(O[1], 4), 4))); return
        if mn in JCC:
            t = O[0].v
            e('if (COND_%s(c)) %s' % (JCC[mn].replace('!', 'N'), self.goto(t))); return
        if mn == 'jecxz': e('if (c.r[1] == 0) %s' % self.goto(O[0].v)); return
        if mn == 'jmp':
            if O[0].kind == 'imm': e(self.goto(O[0].v)); return
            tab = rc.jump_table(a, ops)
            v = self.rd(O[0], 4)
            if tab:
                e('switch (%s) {' % v)
                for x in sorted(set(tab)): self.used_labels.add(x); e('  case 0x%Xu: goto L_%X;' % (x, x))
                e('  default: x86_jump(c, %s); return; }' % v)
                return
            if O[0].kind == 'mem' and O[0].base is None and O[0].idx is None and O[0].disp in rc.pe.imports:
                e('{ x86_import(c, %d); return; } /* %s (salto) */' % (rc.imp_id(O[0].disp), rc.pe.imports[O[0].disp])); return
            e('{ x86_jump(c, %s); return; }' % v); return
        if mn == 'call':
            e('c.r[4] -= 4; wr32(c.r[4], 0x%Xu);' % nxt)
            if O[0].kind == 'imm':
                t = O[0].v
                if t == SETJMP and t in rc.funcs:   # setjmp: o longjmp nativo volta para ca (setjmp do host neste quadro)
                    e('{ jmp_buf hb_; rt_jmp_register(rd32(c.r[4] + 4u), &hb_); if (setjmp(hb_) == 0) f_%X(c); }' % t)
                elif t in rc.funcs: e('f_%X(c);' % t)
                else: e('x86_call(c, 0x%Xu);' % t)
            elif O[0].kind == 'mem' and O[0].base is None and O[0].idx is None and O[0].disp in rc.pe.imports:
                e('x86_import(c, %d); /* %s */' % (rc.imp_id(O[0].disp), rc.pe.imports[O[0].disp]))
            else:   # no x86 o alvo e lido ANTES de empilhar o retorno: compensa o esp ja decrementado (call [esp+X])
                e('x86_call(c, %s);' % self.rd(O[0], 4).replace('c.r[4]', '(c.r[4] + 4u)'))
            return
        if mn in ('ret', 'repz ret'):
            n = O[0].v if O else 0
            e('c.r[4] += %du; return;' % (4 + n)); return
        if mn == 'int3': e('x86_int3(c, 0x%Xu); return;' % a); return
        # ---- strings
        m = re.match(r'^(rep |repz |repnz )?(movs|stos|lods|cmps|scas)$', mn)
        if m:
            rep = (m.group(1) or '').strip(); op = m.group(2)
            s = O[0].size if O and getattr(O[0], 'size', None) else 4
            e('x86_str_%s%s%d(c);' % (op, '_' + rep if rep else '', s * 8)); return
        if mn == 'sahf': e('SAHF(c);'); return
        if mn in ('pushf', 'pushfd'): e('PUSH(PUSHF(c));'); return
        if mn in ('popf', 'popfd'): e('{ uint32_t v_; POP(v_); POPF(c, v_); }'); return
        if mn == 'cpuid': e('x86_cpuid(c);'); return
        if mn == 'rdtsc': e('x86_rdtsc(c);'); return
        if mn == 'lahf': e('LAHF(c);'); return
        if mn == 'clc': e('FLX(c, 0); c.fexpl_cf = 0;'); return
        if mn == 'stc': raise Unimpl('stc')
        if mn == 'cld': e('c.df = 0;'); return
        if mn == 'std': e('c.df = 1;'); return
        if mn == 'bswap': e(self.wr(O[0], '__builtin_bswap32(%s)' % self.rd(O[0], 4), 4)); return
        if mn == 'bt':
            e('FLX(c, 0); c.fexpl_cf = (%s >> (%s & 31u)) & 1u;' % (self.rd(O[0], 4), self.rd(O[1], 4))); return
        # ---- x87
        if mn.startswith('f'):
            return self.x87(a, mn, ops, O)
        raise Unimpl('sem traducao')

    def fmem(self, o):
        return self.addr(o)

    def x87(self, a, mn, ops, O):
        e = self.e
        def src_val(o):
            if o.kind == 'st': return 'ST(%d)' % o.i
            if o.kind == 'mem':
                if o.size == 4: return '(double)rdf32(%s)' % self.addr(o)
                if o.size == 8: return 'rdf64(%s)' % self.addr(o)
                if o.size == 10: return 'rdf80(%s)' % self.addr(o)
            raise Unimpl('fsrc')
        if mn == 'fld':
            e('FPUSH(%s);' % src_val(O[0]) if O[0].kind != 'st' else '{ const double v_ = ST(%d); FPUSH(v_); }' % O[0].i); return
        if mn in ('fst', 'fstp'):
            o = O[0]
            if o.kind == 'st': e('ST(%d) = ST(0);' % o.i)
            elif o.size == 4: e('wrf32(%s, (float)ST(0));' % self.addr(o))
            elif o.size == 8: e('wrf64(%s, ST(0));' % self.addr(o))
            elif o.size == 10: e('wrf80(%s, ST(0));' % self.addr(o))
            else: raise Unimpl('fst size')
            if mn == 'fstp': e('FPOP();')
            return
        if mn == 'fild':
            o = O[0]
            t = {2: 'int16_t', 4: 'int32_t', 8: 'int64_t'}[o.size]
            e('FPUSH((double)(%s)rd%d(%s));' % (t, o.size * 8, self.addr(o))); return
        if mn in ('fist', 'fistp', 'fisttp'):
            o = O[0]
            fn = 'FIST_TRUNC' if mn == 'fisttp' else 'FIST'
            e('wr%d(%s, (uint%d_t)%s%d(c, ST(0)));' % (o.size * 8, self.addr(o), o.size * 8, fn, o.size * 8))
            if mn != 'fist': e('FPOP();')
            return
        consts = {'fldz': '0.0', 'fld1': '1.0', 'fldpi': '3.14159265358979323846', 'fldl2e': '1.44269504088896340736',
                  'fldl2t': '3.32192809488736234787', 'fldlg2': '0.30102999566398119521', 'fldln2': '0.69314718055994530942'}
        if mn in consts: e('FPUSH(%s);' % consts[mn]); return
        ar = {'fadd': '+', 'fsub': '-', 'fmul': '*', 'fdiv': '/', 'fsubr': 'r-', 'fdivr': 'r/'}
        base = mn.rstrip('p') if mn not in ('fsubrp', 'fdivrp') else mn[:-1]
        if mn in ('fsubrp', 'fdivrp'): base = mn[:-1]
        if base in ar or (mn.startswith('fi') and ('f' + mn[2:]) in ar):
            if mn.startswith('fi'):
                op = ar['f' + mn[2:]]; o = O[0]
                t = {2: 'int16_t', 4: 'int32_t'}[o.size]
                v = '(double)(%s)rd%d(%s)' % (t, o.size * 8, self.addr(o))
                e('ST(0) = %s;' % self.farith('ST(0)', v, op)); return
            op = ar[base]; pop = mn.endswith('p') and mn not in ('fsubr', 'fdivr')
            if mn in ('fsubrp', 'fdivrp', 'faddp', 'fmulp', 'fsubp', 'fdivp'): pop = True
            if not O:  # f*p sem operandos = st(1), st(0)
                O = [Opnd('st', i=1), Opnd('st', i=0)]
            if len(O) == 1:
                e('ST(0) = %s;' % self.farith('ST(0)', src_val(O[0]), op))
            else:
                d, s = O
                e('ST(%d) = %s;' % (d.i, self.farith('ST(%d)' % d.i, 'ST(%d)' % s.i, op)))
            if pop: e('FPOP();')
            return
        if mn == 'fxch':
            i = O[0].i if O else 1
            e('{ const double t_ = ST(0); ST(0) = ST(%d); ST(%d) = t_; }' % (i, i)); return
        if mn == 'fchs': e('ST(0) = -ST(0);'); return
        if mn == 'fabs': e('ST(0) = fabs(ST(0));'); return
        if mn == 'fsqrt': e('ST(0) = FPR(c, sqrt(ST(0)));'); return
        if mn == 'fsin': e('ST(0) = sin(ST(0)); c.fsw &= ~0x400u;'); return
        if mn == 'fcos': e('ST(0) = cos(ST(0)); c.fsw &= ~0x400u;'); return
        if mn == 'fsincos': e('{ const double v_ = ST(0); ST(0) = sin(v_); FPUSH(cos(v_)); c.fsw &= ~0x400u; }'); return
        if mn == 'fpatan': e('ST(1) = atan2(ST(1), ST(0)); FPOP();'); return
        if mn == 'fptan': e('ST(0) = tan(ST(0)); FPUSH(1.0); c.fsw &= ~0x400u;'); return
        if mn == 'frndint': e('ST(0) = FRND(c, ST(0));'); return
        if mn == 'fscale': e('ST(0) = ldexp(ST(0), (int)trunc(ST(1)));'); return
        if mn in ('fprem', 'fprem1'): e('ST(0) = %s(ST(0), ST(1)); c.fsw &= ~0x400u;' % ('fmod' if mn == 'fprem' else 'remainder')); return
        if mn == 'f2xm1': e('ST(0) = exp2(ST(0)) - 1.0;'); return
        if mn == 'fyl2x': e('ST(1) = ST(1) * log2(ST(0)); FPOP();'); return
        if mn in ('fcom', 'fcomp', 'fucom', 'fucomp', 'ficom', 'ficomp'):
            if mn.startswith('fi'):
                o = O[0]; t = {2: 'int16_t', 4: 'int32_t'}[o.size]
                v = '(double)(%s)rd%d(%s)' % (t, o.size * 8, self.addr(o))
            else:
                v = src_val(O[0]) if O else 'ST(1)'
            e('FCOM(c, ST(0), %s);' % v)
            if mn.endswith('p'): e('FPOP();')
            return
        if mn in ('fcompp', 'fucompp'): e('FCOM(c, ST(0), ST(1)); FPOP(); FPOP();'); return
        if mn in ('fcomi', 'fucomi', 'fcomip', 'fucomip'):
            e('FCOMI(c, ST(0), ST(%d));' % O[1].i)
            if mn.endswith('p'): e('FPOP();')
            return
        if mn == 'ftst': e('FCOM(c, ST(0), 0.0);'); return
        if mn == 'fxam': e('FXAM(c);'); return
        if mn in ('fnstsw', 'fstsw'):
            o = O[0]
            e(self.wr(o, 'FSW(c)', 2)); return
        if mn in ('fnstcw', 'fstcw'): e(self.wr(O[0], 'c.fcw', 2)); return
        if mn == 'fldcw': e('c.fcw = %s;' % self.rd(O[0], 2)); return
        if mn in ('fnclex', 'fwait', 'femms'): return
        if mn in ('ffree', 'ffreep'):
            if mn == 'ffreep': e('FPOP();')
            return
        if mn == 'fninit': e('c.top = 0; c.fcw = 0x37F; c.fsw = 0;'); return
        raise Unimpl('x87')

    def farith(self, a, b, op):   # FPR: respeita a precisao do x87 (o D3D9 poe a thread do jogo em 24 bits)
        if op == 'r-': return 'FPR(c, %s - %s)' % (b, a)
        if op == 'r/': return 'FPR(c, %s / %s)' % (b, a)
        return 'FPR(c, %s %s %s)' % (a, op, b)

class Recomp:
    def __init__(self, exe, dis):
        self.pe = PE(exe); self.ins = load_dis(dis); self.exe = exe
        self.fix_misaligned()
        self.imp_ids = {}
        self.funcs = set()
        self.noreturn = set()
        self.find_funcs()

    # o objdump desmonta em linha reta e perde o alinhamento depois de dados no meio do codigo. Para cada alvo direto
    # (call/jmp/jcc) que nao cai no inicio de uma instrucao, desmonta de novo a partir dele ate reencontrar o alinhamento.
    def fix_misaligned(self):
        import subprocess
        rx = re.compile(r'^\s+([0-9a-f]+):\t(.*)$')
        for rnd in range(6):
            miss = set(a for a in EXTRA_ENTRIES if a not in self.ins) if rnd == 0 else set()
            for a, (mn, ops, sz) in list(self.ins.items()):
                # callback guardado na memoria (mov DWORD PTR [x],0xALVO / push 0xALVO) apontando para codigo alinhado em 16
                # que ficou escondido depois de uma tabela de salto
                if mn in ('mov', 'push'):
                    mi = re.search(r'(?:^|,)0x([0-9a-f]+)$', ops.strip())
                    if mi and (mn == 'push' or ops.startswith('DWORD PTR')):
                        t = int(mi.group(1), 16)
                        if t % 16 == 0 and self.pe.in_text(t) and t not in self.ins: miss.add(t)
                if mn == 'call' or mn in JCC or mn == 'jmp':
                    m = re.match(r'^0x([0-9a-f]+)$', ops.strip())
                    if m:
                        t = int(m.group(1), 16)
                        if self.pe.in_text(t) and t not in self.ins: miss.add(t)
                    # tabelas de salto (jmp [reg*4+tab]): entradas que cairam no meio de instrucoes
                    if mn == 'jmp':
                        mt = re.match(r'^DWORD PTR \[(e[a-z]x|e[sd]i|ebp)\*4\+0x([0-9a-f]+)\]$', ops)
                        if mt:
                            tb = int(mt.group(2), 16)
                            bad = 0
                            for k in range(256):
                                v = self.pe.u32(tb + 4 * k)
                                if v is None or not self.pe.in_text(v):
                                    bad += 1   # entrada nao usada (ex.: indice 0 do memcpy do CRT): tolera 1 buraco
                                    if bad >= 2: break
                                    continue
                                bad = 0
                                if v not in self.ins: miss.add(v)
                            # indice negativo (memcpy do CRT: TrailUpVec[ecx*4+16] com ecx = -4..-1): entradas antes do deslocamento
                            fwd = [self.pe.u32(tb + 4 * k) for k in range(2)]
                            for k in (range(1, 9) if not all(x is not None and self.pe.in_text(x) for x in fwd) else []):
                                v = self.pe.u32(tb - 4 * k)
                                if v is None or not self.pe.in_text(v) or abs(v - tb) > 0x10000: break
                                if v not in self.ins: miss.add(v)
            if not miss: break
            added = 0
            for t in sorted(miss):
                if t in self.ins: continue
                out = subprocess.run(['objdump', '-d', '--no-show-raw-insn', '-M', 'intel', '--start-address=0x%x' % t,
                                      '--stop-address=0x%x' % (t + 0x3000), self.exe], capture_output=True, text=True).stdout
                prev = None
                for ln in out.split('\n'):
                    m = rx.match(ln)
                    if not m: continue
                    a = int(m.group(1), 16); txt = m.group(2).strip()
                    if prev is not None: self.ins[prev][2] = a - prev
                    if a in self.ins and prev is not None: break
                    parts = txt.split(None, 1)
                    mn = parts[0] if parts else ''; ops = parts[1] if len(parts) > 1 else ''
                    if mn == 'data16' and ops:
                        p2 = ops.split(None, 1); mn = p2[0]; ops = p2[1] if len(p2) > 1 else ''
                    if mn in ('rep', 'repz', 'repnz', 'lock', 'repe', 'repne') and ops:
                        p2 = ops.split(None, 1); mn = mn + ' ' + p2[0]; ops = p2[1] if len(p2) > 1 else ''
                    self.ins[a] = [mn, ops, 0]; prev = a; added += 1
                    if mn in ('ret', 'int3') and False: break
            print('realinhamento: rodada %d, %d alvos, %d instrucoes' % (rnd, len(miss), added), file=sys.stderr)

    def imp_id(self, va):
        if va not in self.imp_ids: self.imp_ids[va] = len(self.imp_ids)
        return self.imp_ids[va]

    def find_funcs(self):
        f = set([self.pe.entry]) | set(a for a in EXTRA_ENTRIES if a in self.ins)
        for a, (mn, ops, sz) in self.ins.items():
            if mn == 'call':
                o = parse_op(ops)
                if o.kind == 'imm' and o.v in self.ins: f.add(o.v)
        # constantes no proprio codigo que apontam para inicio de funcao (push 0x..., mov reg,0x...): construtores passados
        # como argumento, callbacks. So aceita se o alvo parece inicio de funcao (precedido de int3/ret/nop ou alinhado em 16)
        imm_rx = re.compile(r'0x([0-9a-f]{6,7})\b')
        for a, (mn, ops, sz) in self.ins.items():
            if mn in ('push', 'mov', 'lea', 'cmp') and ops:
                for h in imm_rx.findall(ops):
                    v = int(h, 16)
                    if v in self.ins and self.pe.in_text(v) and v not in f:
                        pb = self.pe.d[self.pe.rva2off(v - self.pe.base) - 1]
                        if pb in (0xCC, 0xC3, 0x90) or v % 16 == 0: f.add(v)
        # ponteiros para codigo em .rdata/.data (vtables, callbacks) que caem no inicio de uma instrucao depois de int3/ret
        for name, va, vsz, rptr, rsz in self.pe.secs[1:3]:
            data = self.pe.d[rptr:rptr + rsz]
            for i in range(0, len(data) - 3, 4):
                v = struct.unpack_from('<I', data, i)[0]
                if v in self.ins and self.pe.in_text(v):
                    pb = self.pe.d[self.pe.rva2off(v - self.pe.base) - 1]
                    f.add(v)   # qualquer ponteiro de dados que caia no inicio de uma instrucao
        # tabelas do CRT de ponto flutuante (_87except, exp/log...) guardam ponteiros DESALINHADOS em .rdata.
        # Aceita ponteiro desalinhado se cair na area do CRT (>= 0x850000) e tiver um vizinho (+-4) que tambem cai.
        for name, va, vsz, rptr, rsz in self.pe.secs[1:3]:
            data = self.pe.d[rptr:rptr + rsz]
            def okp(i):
                if i < 0 or i + 4 > len(data): return False
                v = struct.unpack_from('<I', data, i)[0]
                return v >= 0x850000 and v in self.ins and self.pe.in_text(v)
            for i in range(len(data) - 3):
                if i % 4 and okp(i) and (okp(i + 4) or okp(i - 4)): f.add(struct.unpack_from('<I', data, i)[0])
        self.funcs = f

    def jump_table(self, a, ops):
        m = re.match(r'^DWORD PTR \[(e[a-z]x|e[sd]i|ebp)\*4\+0x([0-9a-f]+)\]$', ops)
        if not m: return None
        t = int(m.group(2), 16); out = []
        bad = 0
        for k in range(1024):
            v = self.pe.u32(t + 4 * k)
            if v is None or not self.pe.in_text(v) or v not in self.ins:
                bad += 1   # tolera 1 entrada invalida (nao usada) no meio ou no inicio
                if bad >= 2: break
                continue
            bad = 0
            out.append(v)
        nf = 0
        for k in range(2):
            v = self.pe.u32(t + 4 * k)
            if v is not None and self.pe.in_text(v) and v in self.ins: nf += 1
            else: break
        for k in (range(1, 9) if nf < 2 else []):   # indice negativo (so se ha menos de 2 entradas seguidas para frente)
            v = self.pe.u32(t - 4 * k)
            if v is None or not self.pe.in_text(v) or v not in self.ins or abs(v - t) > 0x10000: break
            if v not in out: out.append(v)
        return out or None

# ajustes do jogo no proprio codigo (endereco: (texto antigo, texto novo) nos operandos)
IMM_PATCH = {
    0x44d74a: ('0xdc', '0x800'),   # pool de CPropAnim: 220 -> 2048 (enche no inicio do modo historia)
    0x44d788: ('0x8ca', '0x1194'),   # pool C0F5F8: 2250 -> 4500 (98% cheio no inicio)
    0x44d70c: ('0x12c', '0x258'),    # pool C0F600: 300 -> 600
    0x44d83e: ('0x1036', '0x206c'),  # pool C0F604: 4150 -> 8300
}
# diagnostico: chama rt_hook(c, endereco) ao executar estas instrucoes (conta chamadas e quem chamou)
# funcoes so alcancadas por vtable, escondidas depois de tabelas de salto (o objdump perde o alinhamento): 0x60F910 travou o jogo
EXTRA_ENTRIES = {0x4cb190, 0x4cf2e0, 0x50e650, 0x58f5d0, 0x5c2f30, 0x60f910, 0x67ff00, 0x6fccf0, 0x806580, 0x80d780, 0x80d9f0, 0x834290, 0x877ca0}
HOOKS = {0x7383f4}   # 0x7383f4: IsXInputDevice (WMI) -> sempre sim   # pools C0F5F8/CPropAnim (alocar/liberar), criacao de instancias, destrutores
# funcoes do CRT (MSVC, estatico) executadas como codigo nativo (rt/crt_native.cpp)
NATIVE = {0x85d080: 'n_memmove', 0x85b3b0: 'n_memset', 0x85bcfb: 'n_memcpy_s', 0x85f4d7: 'n_stricmp_ascii', 0x8619f0: 'n_strlen',
          0x8608d8: 'n_longjmp', 0x85c720: 'n_ftol2', 0x85c500: 'n_CIsqrt', 0x85aef0: 'n_CIsin', 0x85ad80: 'n_CIcos', 0x85cb70: 'n_CIpow'}
# correcoes do SilentPatchBully (build 3) refeitas em codigo nativo (rt/silentpatch.cpp). O resto das correcoes dele
# entra como bytes alterados no exe antes da desmontagem (tools/sp_patch.py)
NATIVE.update({0x435bd0: 'sp_pool_slot', 0x436b90: 'sp_pool_slot_w', 0x5ae590: 'sp_create_soundbank', 0x5ae690: 'sp_create_wavebank'})
# instrucoes trocadas por codigo do runtime: 0x40618f e o limite de FPS do jogo (mov eax,31 quando ninguem pediu outro)
INSN_REPLACE = {0x40618f: '{ uint32_t rt_fps_limit(); c.r[0] = rt_fps_limit(); }'}

# ---- pilha do x87 em variaveis: dentro de cada trecho reto (sem rotulo, desvio, chamada ou leitura do topo), a
# profundidade da pilha e conhecida na traducao; ST(i) vira uma variavel double (registrador do ARM) em vez de
# c.st[(c.top+i)&7] na memoria. No fim do trecho grava as posicoes alteradas e acerta o topo.
MEMPRE = '#include <setjmp.h>\nstatic inline uint16_t FSWT(const Cpu &c, int d) { return (uint16_t)((c.fsw & ~0x3800u) | ((((unsigned)c.top - (unsigned)d) & 7u) << 11)); }\nvoid rt_jmp_register(uint32_t, jmp_buf *);\n#define rd8(a) (Mloc[(uint32_t)(a)])\n#define wr8(a, v) (Mloc[(uint32_t)(a)] = (uint8_t)(v))\nstatic inline uint16_t g_rd16(const uint8_t *m, uint32_t a) { uint16_t v; memcpy(&v, m + a, 2); return v; }\nstatic inline uint32_t g_rd32(const uint8_t *m, uint32_t a) { uint32_t v; memcpy(&v, m + a, 4); return v; }\nstatic inline uint64_t g_rd64(const uint8_t *m, uint32_t a) { uint64_t v; memcpy(&v, m + a, 8); return v; }\nstatic inline float g_rdf32(const uint8_t *m, uint32_t a) { float v; memcpy(&v, m + a, 4); return v; }\nstatic inline double g_rdf64(const uint8_t *m, uint32_t a) { double v; memcpy(&v, m + a, 8); return v; }\nstatic inline void g_wr16(uint8_t *m, uint32_t a, uint16_t v) { memcpy(m + a, &v, 2); }\nstatic inline void g_wr32(uint8_t *m, uint32_t a, uint32_t v) { memcpy(m + a, &v, 4); }\nstatic inline void g_wr64(uint8_t *m, uint32_t a, uint64_t v) { memcpy(m + a, &v, 8); }\nstatic inline void g_wrf32(uint8_t *m, uint32_t a, float v) { memcpy(m + a, &v, 4); }\nstatic inline void g_wrf64(uint8_t *m, uint32_t a, double v) { memcpy(m + a, &v, 8); }\n#define rd16(a) g_rd16(Mloc, (a))\n#define rd32(a) g_rd32(Mloc, (a))\n#define rd64(a) g_rd64(Mloc, (a))\n#define rdf32(a) g_rdf32(Mloc, (a))\n#define rdf64(a) g_rdf64(Mloc, (a))\n#define wr16(a, v) g_wr16(Mloc, (a), (v))\n#define wr32(a, v) g_wr32(Mloc, (a), (v))\n#define wr64(a, v) g_wr64(Mloc, (a), (v))\n#define wrf32(a, v) g_wrf32(Mloc, (a), (v))\n#define wrf64(a, v) g_wrf64(Mloc, (a), (v))\n'
X87BRANCH = os.environ.get('BULLY_X87BR', '0') == '1'
# gravar a pilha do x87 so no caminho do salto: testado so no PC, desligado ate passar no aparelho
X87JUMP = os.environ.get('BULLY_X87J', '0') == '1'
X87CACHE = os.environ.get('BULLY_X87', '1') == '1'
_X87TOK = re.compile(r'\b(ST|FPUSH|FPOP)\(')
_X87BOUND = re.compile(r'^\s*L_[0-9A-F]+:|\bgoto\b|\breturn\b|\bif\b|\bswitch\b|\bcase\b|\bdefault\b|\bfor\b|\b(f_[0-9A-F]+|n_\w+|x86_\w+|rt_hook|rt_badret|FXAM)\(|\bc\.(top|st)\b')
def _split_stmts(t):
    out = []; depth = 0; cur = ''
    for ch in t:
        if ch == '(': depth += 1
        elif ch == ')': depth -= 1
        if ch == ';' and depth == 0:
            if cur.strip(): out.append(cur.strip())
            cur = ''
        else: cur += ch
    if cur.strip(): out.append(cur.strip())
    return out
def _match_paren(t, i):   # t[i] == '(' -> indice depois do ')' correspondente
    depth = 0
    for j in range(i, len(t)):
        if t[j] == '(': depth += 1
        elif t[j] == ')':
            depth -= 1
            if depth == 0: return j + 1
    raise ValueError
class _X87Abort(Exception): pass
def x87cache(body):
    out = []; st = {'d': 0, 'defd': set(), 'dirty': set()}; used = set()
    def vn(k): return 'fx%s%d' % ('m' if k < 0 else 'p', abs(k))
    def key(i):
        k = i - st['d']
        if k < -8 or k > 7: raise _X87Abort()
        ks = st['defd'] | {k}
        if max(ks) - min(ks) >= 8: raise _X87Abort()
        return k
    def flush_stmts():
        r = ['c.st[(c.top + (%d)) & 7] = %s;' % (k, vn(k)) for k in sorted(st['dirty'])]
        if st['d']: r.append('c.top = (c.top - (%d)) & 7;' % st['d'])
        return r
    def flush():
        for x in flush_stmts(): out.append('  ' + x)
        st['d'] = 0; st['defd'] = set(); st['dirty'] = set()
    def subst(t, pre):
        res = ''; i = 0
        while True:
            m = re.search(r'\bST\((\d)\)', t[i:])
            if not m: res += t[i:]; return res
            k = key(int(m.group(1)))
            if k not in st['defd']:
                pre.append('  %s = c.st[(c.top + (%d)) & 7];' % (vn(k), k)); st['defd'].add(k); used.add(k)
            res += t[i:i + m.start()] + vn(k); i += m.end()
    def stmt(sm, pre):
        if sm == 'FPOP()': st['d'] -= 1; return None
        if sm.startswith('FPUSH('):
            j = _match_paren(sm, 5)
            if sm[j:].strip(): raise _X87Abort()
            e = subst(sm[6:j - 1], pre)
            st['d'] += 1; k = key(0); st['defd'].add(k); st['dirty'].add(k); used.add(k)
            return '%s = (%s)' % (vn(k), e)
        m = re.match(r'^ST\((\d)\)\s*=\s*(.*)$', sm, re.S)
        if m:
            rhs = subst(m.group(2), pre)
            k = key(int(m.group(1))); st['defd'].add(k); st['dirty'].add(k); used.add(k)
            return '%s = %s' % (vn(k), rhs)
        if 'FPUSH(' in sm or 'FPOP(' in sm: raise _X87Abort()
        return subst(sm, pre)
    try:
        for l in body:
            if X87BRANCH and 'FSW(c)' in l: l = l.replace('FSW(c)', 'FSWT(c, %d)' % st['d'])
            if not X87JUMP and not X87BRANCH and 'FSW(c)' in l and not _X87TOK.search(l): flush(); out.append(l); continue
            # desvio condicional: grava o estado so no caminho do salto; quem segue continua com a pilha em variaveis
            mj = re.match(r'^(\s*)if \((.*)\) goto (L_[0-9A-F]+);$', l)
            if X87JUMP and mj and not _X87TOK.search(l) and not re.search(r'\b(f_[0-9A-F]+|n_\w+|x86_\w+|FXAM)\(|\bc\.(top|st)\b', mj.group(2)):
                fs = flush_stmts()
                out.append('%sif (%s) { %sgoto %s; }' % (mj.group(1), mj.group(2), ''.join(x + ' ' for x in fs), mj.group(3)) if fs else l)
                continue
            if not _X87TOK.search(l):
                if _X87BOUND.search(l): flush()
                out.append(l); continue
            if _X87BOUND.search(l): flush(); out.append(l); continue
            t = l.strip(); braced = t.startswith('{') and t.endswith('}')
            if braced: t = t[1:-1]
            if '{' in t or '}' in t: flush(); out.append(l); continue
            pre = []; res = []
            for sm in _split_stmts(t):
                r = stmt(sm, pre)
                if r is not None: res.append(r + ';')
            out.extend(pre)
            if res: out.append('  ' + ('{ ' + ' '.join(res) + ' }' if braced else ' '.join(res)))
        flush()
    except (_X87Abort, ValueError):
        return body
    if not used: return body
    return ['  double ' + ', '.join(vn(k) for k in sorted(used)) + ';'] + out

# ---- registradores locais: cada funcao trabalha numa copia local da Cpu (so os campos que usa), para o compilador
# manter registradores/flags/x87 em registradores do ARM. Sem isso, toda escrita na memoria do jogo (M, tipo char)
# obriga a recarregar c.r[...] da memoria. Sincroniza com a Cpu real (cg) so em chamadas opacas e no retorno.
LOCALIZE = os.environ.get('BULLY_LOCAL', '1') == '1'
_OPAQUE = re.compile(r'\b(f_[0-9A-F]+|n_\w+|x86_\w+|rt_hook|rt_badret|FXAM)\(c([,)])')
_INLINE = re.compile(r'^(CF|ZF|SF|OF|PF|COND_[A-Z]+|FCOM|FCOMI|FIST\w*|FLX|FL|FPR|FRND|FSW|POPF|PUSHF|LAHF|SAHF|SET_EXPL|(SHL|SHR|SAR|ROL|ROR)(8|16|32)|SHLD32|SHRD32|MSB)$')
_FLAGS = re.compile(r'\b(FL|FLX|SET_EXPL|CF|ZF|SF|OF|PF|SAHF|LAHF|PUSHF|POPF|FCOMI|(SHL|SHR|SAR|ROL|ROR)(8|16|32)|SHLD32|SHRD32|COND_[A-Z]+|x86_str_\w+)\(|\bc\.(fk|fmask|fres|fa|fb|fcin|fexpl\w*|df|eflags_hi)\b')
_FPU = re.compile(r'\b(ST|FPUSH|FPOP|FSW|FPR|FRND|FIST\w*|FCOM|FCOMI|FXAM)\(|\bc\.(st|top|fcw|fsw)\b')
_FIELDS_OK = {'r', 'fk', 'fmask', 'fres', 'fa', 'fb', 'fcin', 'fexpl_cf', 'fexpl_of', 'fexpl', 'df', 'eflags_hi', 'st', 'top', 'fcw', 'fsw'}
FLAG_FIELDS = ['fk', 'fmask', 'fres', 'fa', 'fb', 'fcin', 'fexpl_cf', 'fexpl_of', 'fexpl', 'df', 'eflags_hi']
def localize(body, fa):
    text = '\n'.join(body)
    if 'setjmp(' in text: return body   # depois do longjmp a Cpu real (c) ja tem os registradores restaurados
    for nm, _ in re.findall(r'\b(\w+)\(c([,)])', text):
        if not (_OPAQUE.match(nm + '(c,') or _OPAQUE.match(nm + '(c)') or _INLINE.match(nm)): return body
    for f in re.findall(r'\bc\.(\w+)', text):
        if f not in _FIELDS_OK: return body
    if re.search(r'[&*]\s*c\b|\bc\s*=[^=]', text): return body
    regs = sorted(set(int(n) for n in re.findall(r'\bc\.r\[(\d)\]', text)))
    if re.search(r'\b(PUSH|POP)\(', text) and 4 not in regs: regs = sorted(regs + [4])
    if re.search(r'\b(SAHF|LAHF)\(', text) and 0 not in regs: regs = sorted(regs + [0])
    fl = bool(_FLAGS.search(text)); fp = bool(_FPU.search(text))
    si = ['c.r[%d] = cg.r[%d];' % (i, i) for i in regs]; so = ['cg.r[%d] = c.r[%d];' % (i, i) for i in regs]
    # flags: o codigo do jogo (MSVC) nao le flags herdadas de quem chamou; so o CRT (>= 0x850000) devolve resultado
    # em flags. Entao: na volta de chamadas recarrega todas; antes de chamadas e no retorno grava so df (direcao),
    # exceto nas funcoes do CRT, que gravam todas.
    so_ret = list(so); so_full = list(so)
    if fl:
        so_full += ['cg.%s = c.%s;' % (f, f) for f in FLAG_FIELDS]
        si += ['c.%s = cg.%s;' % (f, f) for f in FLAG_FIELDS]
        so += ['cg.df = c.df;']
        so_ret += ['cg.%s = c.%s;' % (f, f) for f in FLAG_FIELDS] if fa >= 0x850000 else ['cg.df = c.df;']
        if fa >= 0x850000: so = list(so_ret)
    if fp:
        si += ['c.top = cg.top; c.fcw = cg.fcw; c.fsw = cg.fsw;']
        so += ['cg.top = c.top; cg.fcw = c.fcw; cg.fsw = c.fsw;']; so_ret += [so[-1]]; so_full += [so[-1]]
    SI = ' '.join(si); SO = ' '.join(so); SOR = ' '.join(so_ret); SOF = ' '.join(so_full)
    SIC = ' '.join(x for x in si if not re.match(r'c\.r\[(3|5|6|7)\] = ', x))
    out = []
    for l in body:
        # chamadas opacas: sincroniza antes/depois e passa a Cpu real
        res = []; i = 0
        for m in _OPAQUE.finditer(l):
            if m.start() < i: continue
            j = m.end() - 1; depth = 1   # posicao logo apos '(c'
            k = l.index('(', m.start()) + 1; depth = 1
            while depth and k < len(l):
                if l[k] == '(': depth += 1
                elif l[k] == ')': depth -= 1
                k += 1
            call = l[m.start():k]
            call = call.replace('(c,', '(cg,', 1).replace('(c)', '(cg)', 1)
            if l[k:].startswith('; return;'):   # salto para fora (chamada final): grava o estado e chama sem voltar aqui
                res.append(l[i:m.start()])
                if m.group(1).startswith('f_'): res.append('SR_ TAILCALL(%s); RETURN_' % call)
                else: res.append('SR_ %s; RETURN_' % call)
                i = k + len('; return;'); continue
            # instrucoes feitas por funcao do runtime (rep movs, cpuid...) nao mexem nas flags: grava todas antes
            instr = not re.match(r'(f_|n_|x86_call|x86_jump|x86_import)', m.group(1))
            nm = m.group(1)
            # item 2 (nao recarregar ebx/ebp/esi/edi) desligado: o teste mostrou funcoes que voltam com eles alterados
            keeps = KEEP_CALLEE_SAVED and (nm.startswith('n_') or nm == 'x86_import' or (nm.startswith('f_') and int(nm[2:], 16) < 0x850000))
            res.append(l[i:m.start()]); res.append('({ %s %s; %s })' % ('SF_' if instr else 'SO_', call, 'SIC_' if keeps else 'SI_')); i = k
        res.append(l[i:]); l = ''.join(res)
        l = re.sub(r'\breturn;', '{ SR_ return; }', l).replace('RETURN_', 'return;')
        out.append(l.replace('c.st[', 'cg.st['))
    return (['#undef ST\n#define ST(i) cg.st[(c.top + (i)) & 7]\n#undef FPUSH\n#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; cg.st[c.top] = v__; } while (0)\n#define SI_ ' + SI + '\n#define SO_ ' + SO + '\n#define SR_ ' + SOR + '\n#define SF_ ' + SOF + '\n#define SIC_ ' + SIC + '\nvoid f_%X(Cpu &cg) {', '  Cpu c; SI_'], out + ['#undef SI_', '#undef SO_', '#undef SR_', '#undef SF_', '#undef SIC_', '#undef ST', '#define ST(i) c.st[(c.top + (i)) & 7]', '#undef FPUSH', '#define FPUSH(v) do { const double v__ = (v); c.top = (c.top - 1) & 7; c.st[c.top] = v__; } while (0)'], [])
KEEP_CALLEE_SAVED = os.environ.get('BULLY_KEEPCS', '0') == '1'
SETJMP = 0x86098c   # _setjmp3 do CRT (usado pelo Lua: luaD_rawrunprotected)
CHUNK = int(os.environ.get("BULLY_CHUNK", "3000000"))   # tamanho de cada arquivo gerado (menor = menos RAM por arquivo)

def main():
    exe, dis, outdir = sys.argv[1:4]
    limit = int(sys.argv[4]) if len(sys.argv) > 4 else 0
    rc = Recomp(exe, dis)
    funcs = sorted(rc.funcs)
    if limit: funcs = funcs[:limit]
    print('funcoes', len(rc.funcs), 'imports', len(rc.pe.imports))
    tot = collections.Counter(); nins = 0
    chunk = []; files = 0; protos = []
    import os
    os.makedirs(outdir, exist_ok=True)
    def flush():
        nonlocal chunk, files
        if not chunk: return
        open('%s/bully_%03d.cpp' % (outdir, files), 'w').write('#include "x86rt.h"\n#ifdef __clang__\n#define TAILCALL(x) [[clang::musttail]] return x\n#else\n#define TAILCALL(x) return x\n#endif\n' + MEMPRE + '\n'.join(chunk) + '\n')
        files += 1; chunk = []
    size = 0
    for fa in funcs:
        g = FuncGen(rc, fa)
        body = g.gen()
        nins += len(g.body)
        tot.update(g.unimpl)
        hdr = ['void f_%X(Cpu &c) {']
        if X87CACHE: body = x87cache(body)
        if LOCALIZE:
            r = localize(body, fa)
            if isinstance(r, tuple): hdr, body = r[0], r[1]
        name = 'f_%X_x86' % fa if fa in NATIVE else 'f_%X' % fa
        src = [hdr[0].replace('f_%X', name), '  uint8_t *const Mloc = M;'] + hdr[1:] + body + ['}']
        if fa in NATIVE:   # funcao do CRT trocada por versao nativa (o corpo x86 fica como f_X_x86, usado como reserva)
            src += ['void %s(Cpu &c);' % NATIVE[fa], 'void f_%X(Cpu &c) { %s(c); }' % (fa, NATIVE[fa])]
            protos.append('void f_%X_x86(Cpu &c);' % fa)
        protos.append('void f_%X(Cpu &c);' % fa)
        chunk.extend(src); size += sum(len(x) for x in src)
        if size > CHUNK: flush(); size = 0
    flush()
    open('%s/funcs.h' % outdir, 'w').write('#pragma once\n#include <stdint.h>\nstruct Cpu;\nvoid rt_badret(Cpu &, uint32_t);\n' + '\n'.join(protos) + '\n')
    tab = ['#include "x86rt.h"', 'extern const FuncEnt g_funcs[];', 'extern const ImportEnt g_imports[];', 'extern const unsigned g_nfuncs;', 'const FuncEnt g_funcs[] = {'] + ['  {0x%Xu, f_%X},' % (fa, fa) for fa in funcs] + ['  {0, 0}};', 'const unsigned g_nfuncs = %d;' % len(funcs), 'const ImportEnt g_imports[] = {']
    for va in sorted(rc.pe.imports): rc.imp_id(va)   # todas as entradas da IAT (inclusive as lidas com mov reg,[IAT])
    for va, i in sorted(rc.imp_ids.items(), key=lambda x: x[1]): tab.append('  {%d, 0x%Xu, "%s"},' % (i, va, rc.pe.imports[va]))
    tab.append('  {-1, 0, 0}};')
    open('%s/tables.cpp' % outdir, 'w').write('\n'.join(tab) + '\n')
    print('instrucoes traduzidas', nins, 'arquivos', files)
    print('sem traducao:', sum(tot.values()), tot.most_common(25))

if __name__ == '__main__':
    main()
