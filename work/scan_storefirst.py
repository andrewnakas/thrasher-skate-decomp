"""Mechanical selection: listings that store a call result and then branch on the same register.

Signature (from func_80047B28): `jal T` ... `sw $r, off($base)` where $r is a result register
written by the call, followed within a few instructions by `beqz/bnez $r` with no intervening
write to $r.
"""
import re, sys, pathlib

ASM = pathlib.Path("asm/nonmatchings/game")
INSN = re.compile(r"/\* [0-9A-F]+ [0-9A-F]{8} (?P<w>[0-9A-F]{8}) \*/\s+(?P<op>\S+)\s*(?P<args>.*)")
RES = ("$v0", "$v1")

def parse(p):
    out = []
    for line in p.read_text().splitlines():
        m = INSN.search(line)
        if m:
            out.append((m.group("op"), m.group("args").strip()))
    return out

def candidates(ins):
    hits = []
    for i, (op, args) in enumerate(ins):
        if op != "jal":
            continue
        # find the store within the next 5 instructions
        for j in range(i + 1, min(i + 6, len(ins))):
            op2, a2 = ins[j]
            if op2 == "sw":
                m = re.match(r"(\$\w+),\s*(.*)", a2)
                if not m:
                    continue
                reg, addr = m.group(1), m.group(2)
                if reg not in RES:
                    continue
                for k in range(j + 1, min(j + 8, len(ins))):
                    op3, a3 = ins[k]
                    if op3 in ("beqz", "bnez") and a3.split(",")[0].strip() == reg:
                        hits.append((i, j, k, reg, addr))
                        break
                    if op3 == "sw" and a3.startswith(reg + ","):
                        break
                break
    return hits

for p in sorted(ASM.glob("func_*.s")):
    ins = parse(p)
    h = candidates(ins)
    if h:
        print(p.stem, len(h), " ".join(sorted({x[3] for x in h})))
