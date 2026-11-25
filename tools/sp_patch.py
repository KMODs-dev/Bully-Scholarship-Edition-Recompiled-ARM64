#!/usr/bin/env python3
# Aplica no Bully.exe 1.200 as correcoes de codigo do SilentPatchBully (build 3, CookiePLMonster) que sao bytes
# alterados, e grava um exe novo para o x86rc. As que precisam de codigo novo estao em rt/silentpatch.cpp
# (NATIVE e INSN_REPLACE no x86rc). Uso: sp_patch.py Bully.exe Bully_sp.exe dis.txt
# O dis.txt (desmontagem do exe ORIGINAL) serve para conferir que nenhum desvio do jogo cai no codigo que sobra
# depois dos saltos novos; se cair, aquele trecho fica com os bytes originais (como no SilentPatch).
import re, struct, sys

exe, out, dis = sys.argv[1:4]
d = bytearray(open(exe, 'rb').read())
pe = struct.unpack_from('<I', d, 0x3C)[0]
nsec = struct.unpack_from('<H', d, pe + 6)[0]
optsz = struct.unpack_from('<H', d, pe + 20)[0]
base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
secs = []
for i in range(nsec):
    o = pe + 24 + optsz + 40 * i
    vsz, va, rsz, rptr = struct.unpack_from('<IIII', d, o + 8)
    secs.append((base + va, max(vsz, rsz), rptr))
def off(v):
    for va, sz, rp in secs:
        if va <= v < va + sz: return rp + v - va
    raise ValueError('%X fora do exe' % v)

# conferencia da versao: 1.200 tem este texto de versao na tela de menu
assert d[off(0x6A69EA)] == 0x68, 'exe nao e o 1.200'

def patch(va, bs):
    for i, b in enumerate(bs): d[off(va + i)] = b
def nop(va, n): patch(va, [0x90] * n)
def rel(va, op, tgt): patch(va, [op] + list(struct.pack('<I', (tgt - (va + 5)) & 0xFFFFFFFF)))
def readcall(va):
    assert d[off(va)] == 0xE8, 'nao e call em %X' % va
    return va + 5 + struct.unpack_from('<i', d, off(va) + 1)[0]

# alvos de desvio no exe original (para nao apagar codigo que alguem ainda alcanca)
targets = set()
rx = re.compile(r'^\s*([0-9a-f]+):\s+(call|j[a-z]+)\s+0x([0-9a-f]+)\s*$')
for ln in open(dis):
    m = rx.match(ln)
    if m: targets.add(int(m.group(3), 16))

# enderecos falsos tratados pelo runtime (rt_override em rt/silentpatch.cpp)
SP_ALLOC, SP_FREE, SP_SBCMD = 0xFE000000, 0xFE000010, 0xFE000020

# CFileLoader::LoadCollisionModel: carga dos vertices da colisao (travava ao carregar o jogo)
patch(0x42BE80 + 2, [16])

# Nutcrackin': trata a contagem de jogadores sempre como indice (estourava a lista)
for a, n in ((0x6FB302, 6), (0x6FB3EB, 6), (0x6FC920, 2), (0x6FC945, 2), (0x6FC94F, 2), (0x6FC97C, 2), (0x6FCE91, 2)):
    nop(a, n)

# CameraDestroy nao chama RwFrameDestroy (travava)
patch(0x5EF954, [0xEB])

# Pools (CBasePool): codigo copiado (inline) do GetSlotWithLinked lia a lista de livres fora do limite. Cada trecho
# vira: push indice; mov ecx, pool; call GetSlotWithLinkedWrapper (nativo); [mov reg, eax]; jmp fim
PUSH = {'eax': 0x50, 'ebx': 0x53, 'esi': 0x56, 'edi': 0x57}
MOVECX = {'ebx': [0x8B, 0xCB], 'ebp': [0x8B, 0xCD], 'esi': [0x8B, 0xCE], 'edi': [0x8B, 0xCF]}
MOVEAX = {'esi': [0x8B, 0xF0], 'edi': [0x8B, 0xF8], None: []}
POOL = [
    (0x4378D0, 'edi', 'ebx', 'esi', 0x437901), (0x437A18, 'edi', 'ebx', 'esi', 0x437A59), (0x437AA4, 'esi', 'edi', None, 0x437AD3),
    (0x44A4F6, 'edi', 'ebx', 'esi', 0x44A527), (0x450A99, 'esi', 'ebx', None, 0x450AC5), (0x45E72B, 'esi', 'edi', None, 0x45E757),
    (0x49E0D4, 'edi', 'ebx', 'esi', 0x49E109), (0x49E489, 'ebx', 'edi', 'esi', 0x49E4B8), (0x4CFE11, 'edi', 'ebp', 'esi', 0x4CFE43),
    (0x4CFE91, 'edi', 'ebp', 'esi', 0x4CFEC3), (0x4CFF24, 'ebx', 'edi', 'esi', 0x4CFF59), (0x4D0138, 'edi', 'ebx', 'esi', 0x4D0169),
    (0x4D01A0, 'edi', 'ebx', 'esi', 0x4D01D1), (0x4D0211, 'edi', 'ebp', 'esi', 0x4D0243), (0x4D02B0, 'edi', 'ebp', 'esi', 0x4D02E2),
    (0x4D0350, 'esi', 'edi', None, 0x4D037F), (0x5309A6, 'edi', 'ebp', 'esi', 0x5309D5), (0x532446, 'esi', 'edi', None, 0x532472),
    (0x5332DA, 'ebx', 'edi', 'esi', 0x53330C), (0x5BCE62, 'edi', 'ebx', 'esi', 0x5BCE97), (0x5C2642, 'ebx', 'ebp', 'edi', 0x5C2679),
    (0x5C2770, 'ebx', 'ebp', 'edi', 0x5C27A7), (0x5C2FC6, 'edi', 'esi', None, 0x5C2FF3), (0x5C31F0, 'edi', 'esi', None, 0x5C3220),
    (0x5C3280, 'esi', 'edi', None, 0x5C32AF), (0x5C33D6, 'edi', 'ebx', 'esi', 0x5C3407), (0x5C4D91, 'edi', 'ebp', 'esi', 0x5C4DC3),
    (0x677206, 'edi', 'ebx', None, 0x67722E), (0x67C1AD, 'edi', 'ebx', 'esi', 0x67C1F2),
]
WRAPPER = 0x436B90
kept = 0
for a, idx, pool, res, end in POOL:
    p = a
    patch(p, [PUSH[idx]]); p += 1
    patch(p, MOVECX[pool]); p += 2
    rel(p, 0xE8, WRAPPER); p += 5
    patch(p, MOVEAX[res]); p += len(MOVEAX[res])
    o = end - (p + 2)
    if -128 <= o <= 127: patch(p, [0xEB, o & 0xFF]); p += 2
    else: rel(p, 0xE9, end); p += 5
    # resto do trecho antigo: nop (desmontagem limpa), a nao ser que algum desvio do jogo caia ali dentro
    if any(p <= t < end for t in targets): kept += 1
    else: nop(p, end - p)

# Vazamento de memoria nos bancos de som SEA: o buffer vai para o XACT com XACT_FLAG_ENGINE_CREATE_MANAGEDATA e o
# XACT (rt/xact3.cpp) o libera quando o banco e destruido. Alocacao e liberacao passam a ser do runtime.
assert readcall(0x5A990D) == 0x5EEAA0 and readcall(0x5A99FB) == 0x5EEAA0 and readcall(0x5A9B32) == 0x5EEAB0
rel(0x5A990D, 0xE8, SP_ALLOC)
rel(0x5A99FB, 0xE8, SP_ALLOC)
rel(0x5A9B32, 0xE8, SP_FREE)
assert d[off(0x5A99AE)] == 0x6A and d[off(0x5A99AF)] == 0
patch(0x5A99AF, [1])   # banco de ondas em memoria: flags = MANAGEDATA
assert readcall(0x5A9A1F) == 0x5AF150
rel(0x5A9A1F, 0xE8, SP_SBCMD)   # banco de som: o comando passa MANAGEDATA

open(out, 'wb').write(d)
print('SilentPatch aplicado: %d trechos de pool (%d com codigo antigo mantido) -> %s' % (len(POOL), kept, out))
