import struct, sys, glob, collections
# leitor do formato binario fx_2_0 (efeitos compilados do D3DX9) para validar a estrutura
CL = {0:'SCALAR',1:'VECTOR',2:'MROWS',3:'MCOLS',4:'OBJECT',5:'STRUCT'}
OBJ_TYPES = set(range(4, 20))  # string(4), texture..(5-9), sampler..(10-14), pixelshader(15), vertexshader(16)

class P: pass

class FX:
    def __init__(s, b):
        s.b = b; assert struct.unpack_from('<I', b, 0)[0] == 0xFEFF0901
        off = struct.unpack_from('<I', b, 4)[0]
        s.base = 8; s.p = 8 + off
        s.objects = {}
        s.stats = collections.Counter()
    def d(s):
        v = struct.unpack_from('<I', s.b, s.p)[0]; s.p += 4; return v
    def dat(s, off):
        return struct.unpack_from('<I', s.b, s.base + off)[0]
    def name(s, off):
        n = s.dat(off)
        return s.b[s.base + off + 4: s.base + off + 4 + n].rstrip(b'\0').decode('latin1') if n else None
    def typedef(s, q, parent=None):
        # q = posicao absoluta; devolve (param, nova posicao)
        t = P()
        def rd():
            nonlocal q
            v = struct.unpack_from('<I', s.b, q)[0]; q += 4; return v
        if parent is None:
            t.type = rd(); t.cls = rd(); t.name = s.name(rd()); t.sem = s.name(rd()); t.elems = rd()
            t.rows = t.cols = t.members_n = 0
            if t.cls == 1: t.cols = rd(); t.rows = rd()
            elif t.cls in (0, 2, 3): t.rows = rd(); t.cols = rd()
            elif t.cls == 5: t.members_n = rd()
            t.bytes = 4 * t.rows * t.cols if t.cls in (0, 1, 2, 3) else (4 if t.cls == 4 else 0)
        else:
            t.type, t.cls, t.name, t.sem = parent.type, parent.cls, parent.name, parent.sem
            t.elems = 0; t.rows, t.cols, t.members_n, t.bytes = parent.rows, parent.cols, parent.members_n, parent.bytes
        t.members = []
        if t.elems:
            save = q; tot = 0
            for i in range(t.elems):
                m, q = s.typedef(save, t); t.members.append(m); tot += m.bytes
            t.bytes = tot
        elif t.members_n:
            tot = 0
            for i in range(t.members_n):
                m, q = s.typedef(q, None); t.members.append(m); tot += m.bytes
            t.bytes = tot
        return t, q
    def value(s, t, q):
        def rd():
            nonlocal q
            v = struct.unpack_from('<I', s.b, q)[0]; q += 4; return v
        if t.elems or t.cls == 5:
            for m in t.members: q = s.value(m, q)
            return q
        if t.cls in (0, 1, 2, 3):
            t.val = s.b[q:q + t.bytes]; return q + t.bytes
        if t.cls == 4:
            if t.type in (10, 11, 12, 13, 14):   # samplers: lista de estados
                n = rd(); t.states = []
                for i in range(n):
                    st, q = s.state_at(q); t.states.append(st)
                s.stats['sampler_states'] += n
                return q
            oid = rd(); t.oid = oid; s.objects[oid] = t; return q
        raise Exception('classe %d' % t.cls)
    def state_at(s, q):
        op, idx, toff, voff = struct.unpack_from('<4I', s.b, q); q += 16
        st = P(); st.op = op; st.idx = idx
        st.par, _ = s.typedef(s.base + toff)
        s.value(st.par, s.base + voff)
        s.stats['op_%d' % op] += 1
        return st, q
    def annot(s):
        toff = s.d(); voff = s.d()
        t, _ = s.typedef(s.base + toff); s.value(t, s.base + voff); return t
    def parse(s):
        np_ = s.d(); nt = s.d(); s.d(); nobj = s.d()
        s.params = []
        for i in range(np_):
            toff = s.d(); voff = s.d(); flags = s.d(); na = s.d()
            t, _ = s.typedef(s.base + toff); s.value(t, s.base + voff)
            t.annots = [s.annot() for _ in range(na)]
            s.params.append(t)
        s.techs = []
        for i in range(nt):
            tn = s.name(s.d()); na = s.d(); npass = s.d()
            ann = [s.annot() for _ in range(na)]
            passes = []
            for j in range(npass):
                pn = s.name(s.d()); pa = s.d(); ns = s.d()
                pann = [s.annot() for _ in range(pa)]
                sts = []
                for k in range(ns):
                    st, s.p = s.state_at(s.p); sts.append(st)
                passes.append((pn, sts))
            s.techs.append((tn, passes))
        nstr = s.d(); nres = s.d()
        for i in range(nstr):
            oid = s.d(); n = s.d(); s.p += (n + 3) & ~3
        s.res = []; s.blobs = []
        for i in range(nres):
            ti, idx, ei, si, usage = [s.d() for _ in range(5)]
            s.stats['usage_%d' % usage] += 1
            if usage == 0 or usage == 1:
                n = s.d(); blob = s.b[s.p:s.p + n]; s.p += (n + 3) & ~3
                s.blobs.append((usage, ti, idx, ei, si, blob))
                if usage == 0 and blob[:4] in (b'\x00\x03\xfe\xff', b'\x00\x03\xff\xff', b'\x00\x02\xfe\xff', b'\x00\x02\xff\xff', b'\x01\x01\xfe\xff'):
                    s.stats['shader_' + blob[2:4].hex() + '_' + blob[1:2].hex()] += 1
                    if b'PRES' in blob: s.stats['shader_com_preshader'] += 1
                if usage == 1: s.stats['fxlc'] += 1
            elif usage == 2:
                n = s.d(); nm = s.b[s.p:s.p + n]; s.p += (n + 3) & ~3
                if b'[' in nm:
                    n2 = s.d(); s.p += (n2 + 3) & ~3; s.stats['array_selector'] += 1
            else:
                raise Exception('usage %d' % usage)
            s.res.append((ti, idx, ei, si, usage))
        return s.p

if __name__ == '__main__':
    tot = collections.Counter(); bad = 0
    files = sorted(glob.glob(sys.argv[1] + '/*.fx'))
    for f in files:
        b = open(f, 'rb').read()
        fx = FX(b)
        try:
            end = fx.parse()
            if end != len(b): bad += 1; print('sobra', f, end, len(b))
            tot.update(fx.stats)
            tot['techs'] += len(fx.techs); tot['params'] += len(fx.params)
            tot['passes'] += sum(len(p) for _, p in fx.techs)
        except Exception as e:
            bad += 1; print('erro', f, e)
    print('arquivos', len(files), 'ruins', bad)
    for k, v in sorted(tot.items()): print(k, v)
    