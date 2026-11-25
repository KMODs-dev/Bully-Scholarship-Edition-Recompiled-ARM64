# Mini-montador de shaders D3D9 SM2 (so o necessario) -> bytecode, para os shaders HLSL fixos do Bully.exe.
# Gera rt/d3dx9_builtin.inc com tabela (hash FNV-64 da fonte -> bytecode).
import struct, re, sys

OP = {'nop': 0, 'mov': 1, 'add': 2, 'sub': 3, 'mad': 4, 'mul': 5, 'rcp': 6, 'rsq': 7, 'dp3': 8, 'dp4': 9, 'min': 10, 'max': 11,
      'dcl': 31, 'def': 81, 'texld': 66}
RT = {'r': 0, 'v': 1, 'c': 2, 't': 3, 'oPos': 4, 'oD': 5, 'oT': 6, 'oC': 8, 's': 10}
USAGE = {'position': 0, 'normal': 3, 'texcoord': 5, 'color': 10}

def regbits(name):
    m = re.match(r'^(oPos|oD|oT|oC|r|v|c|t|s)(\d*)$', name)
    t = RT[m.group(1)]; n = int(m.group(2) or 0)
    return 0x80000000 | n | ((t & 7) << 28) | ((t & 0x18) << 8)

def dst(s):
    s = s.strip(); reg, _, mask = s.partition('.')
    wm = 0
    for ch in (mask or 'xyzw'): wm |= {'x': 1, 'y': 2, 'z': 4, 'w': 8}[ch]
    return regbits(reg) | (wm << 16)

def src(s):
    s = s.strip(); neg = s.startswith('-'); s = s.lstrip('-')
    reg, _, sw = s.partition('.')
    sw = sw or 'xyzw'
    if len(sw) == 1: sw = sw * 4
    while len(sw) < 4: sw += sw[-1]
    swz = 0
    for i, ch in enumerate(sw): swz |= 'xyzw'.index(ch) << (2 * i)
    return regbits(reg) | (swz << 16) | ((1 << 24) if neg else 0)

def asm(text):
    out = []
    for ln in text.strip().split('\n'):
        ln = ln.split('//')[0].strip()
        if not ln: continue
        if ln.startswith('vs_') or ln.startswith('ps_'):
            maj, mn = int(ln[3]), int(ln[5]); out.append((0xFFFE0000 if ln[0] == 'v' else 0xFFFF0000) | (maj << 8) | mn); continue
        op, _, rest = ln.partition(' '); args = [a for a in rest.split(',')] if rest else []
        if op.startswith('dcl'):
            kind = op[4:] if '_' in op else ''
            if kind in USAGE: ut = 0x80000000 | USAGE[kind]
            elif kind == '2d': ut = 0x80000000 | (2 << 27)
            else: ut = 0x80000000
            out += [OP['dcl'] | (2 << 24), ut, dst(args[0])]; continue
        if op == 'def':
            out += [OP['def'] | (5 << 24), dst(args[0])] + [struct.unpack('<I', struct.pack('<f', float(x)))[0] for x in args[1:5]]; continue
        toks = [dst(args[0])] + [src(a) for a in args[1:]]
        out += [OP[op] | (len(toks) << 24)] + toks
    out.append(0x0000FFFF)
    return out

def fnv64(b, h=1469598103934665603):
    for x in b: h ^= x; h = (h * 1099511628211) & 0xFFFFFFFFFFFFFFFF
    return h

EXE = sys.argv[1]
d = open(EXE, 'rb').read()
def cstr(va): o = va - 0x8fc000 + 0x4fc000; return d[o:d.index(b'\0', o)]

VS_COLOR_TEX = '''vs_2_0
dcl_position v0
dcl_texcoord v1
dcl_color v2
def c4, 0.0039215686, 1, 2, 0
mov r0.xyz, v0
mov r0.w, c4.y
dp4 oPos.x, r0, c0
dp4 oPos.y, r0, c1
dp4 oPos.z, r0, c2
dp4 oPos.w, r0, c3
mov oT0.xy, v1
mul oD0, v2.zyxw, c4.x'''
VS_COLOR = '''vs_2_0
dcl_position v0
dcl_color v1
def c4, 0.0039215686, 1, 2, 0
mov r0.xyz, v0
mov r0.w, c4.y
dp4 oPos.x, r0, c0
dp4 oPos.y, r0, c1
dp4 oPos.z, r0, c2
dp4 oPos.w, r0, c3
mul oD0, v1.zyxw, c4.x'''
VS_SCREEN = '''vs_2_0
dcl_position v0
dcl_texcoord v1
dcl_color v2
def c4, 0.0039215686, 1, 2, 0
mov r0.xyz, v0
mov r0.w, c4.y
dp4 r1.z, r0, c2
dp4 r1.w, r0, c3
rcp r2.x, r1.w
mul oPos.z, r1.z, r2.x
mov r3.x, v0.x
add r3.y, c4.y, -v0.y
mad oPos.xy, r3, c4.z, -c4.y
mov oPos.w, c4.y
mov oT0.xy, v1
mul oD0, v2.zyxw, c4.x'''
PS_COLOR = '''ps_2_0
dcl v0
mov oC0, v0'''
PS_TEX = '''ps_2_0
dcl t0.xy
dcl v0
dcl_2d s0
texld r0, t0, s0
mul r0, r0, v0
mov oC0, r0'''

table = [(0x94ea80, VS_COLOR_TEX), (0x94de10, VS_COLOR), (0x94e380, VS_SCREEN), (0x94d798, PS_COLOR), (0x94da60, PS_TEX)]
lines = ['// gerado por sm2asm.py: shaders HLSL fixos do Bully.exe montados a mao (hash FNV-64 da fonte -> bytecode)']
for va, text in table:
    code = asm(text); h = fnv64(cstr(va))
    lines.append('{0x%016xull, %d, {%s}},' % (h, len(code), ', '.join('0x%08x' % x for x in code)))
open(sys.argv[2], 'w').write('\n'.join(lines) + '\n')
print('\n'.join(lines))
