#!/usr/bin/env python3
"""Find listings where an argument register is loaded, tested by a guard, and
still live at a later call. That is the tell for a missing call parameter:
the loaded value is the callee's argument and only looks like a register-home
residue because the draft does not declare the parameter.
"""
import os
import re
import sys
import glob

INSN = re.compile(r'/\* [0-9A-F]+ [0-9A-F]+ [0-9A-F]+ \*/\s+(\w+)\s*(.*)$')
CALL = {'jal', 'jalr'}
STORES = {'sw', 'sb', 'sh', 'swl', 'swr', 'lwl', 'lwr'}
BRANCHES = {'beq', 'bne', 'beqz', 'bnez', 'bgez', 'bltz', 'blez', 'bgtz', 'bgezal', 'bltzal'}
NO_DEST = CALL | STORES | BRANCHES | {'nop', 'break', 'jr', 'j', 'b', 'mult', 'multu', 'div',
                                      'divu', 'mtlo', 'mthi', 'syscall', 'sb', 'sh'}
LOADS = {'lw', 'lh', 'lhu', 'lb', 'lbu'}
ARGS = ('a1', 'a2', 'a3')


def parse(path):
    out = []
    for line in open(path):
        m = INSN.search(line)
        if m:
            ops = [o.strip() for o in m.group(2).split(',') if o.strip()]
            out.append((m.group(1), ops))
    return out


def dest(insn):
    mnem, ops = insn
    if mnem in NO_DEST or not ops:
        return None
    d = ops[0]
    if mnem in ('jal', 'jalr', 'lui'):
        return None if mnem != 'lui' else d
    return d if d.startswith('$') else None


def scan(path):
    insns = parse(path)
    hits = []
    for i, (mnem, ops) in enumerate(insns):
        if mnem not in LOADS or not ops:
            continue
        reg = ops[0]
        if reg not in ('$' + a for a in ARGS):
            continue
        # guard on this register within the next few instructions
        for j in range(i + 1, min(i + 5, len(insns))):
            bmnem, bops = insns[j]
            if bmnem in ('beqz', 'bnez') and bops and bops[0] == reg:
                pass
            elif bmnem in ('beq', 'bne') and bops and reg in bops[:2]:
                pass
            else:
                continue
            # walk forward: is the register redefined before a call?
            for k in range(j + 1, min(j + 25, len(insns))):
                kmnem, kops = insns[k]
                if kmnem in CALL:
                    hits.append((i, insns[i], j, k, kmnem))
                    break
                if dest(insns[k]) == reg:
                    break
            break
    return insns, hits


def main():
    merged = set(open('/tmp/merged2.txt').read().split())
    rows = []
    for p in sorted(glob.glob('asm/nonmatchings/game/func_*.s')):
        name = os.path.basename(p)[:-2]
        if name in merged:
            continue
        insns, hits = scan(p)
        for (li, load, gi, ci, cmnem) in hits:
            # only interesting when the register is NOT set just before the call
            prev = insns[ci - 1] if ci else ('', [])
            if prev[0] in ('addu', 'addiu', 'lui', 'lw', 'lhu', 'lh', 'lbu', 'or', 'andi') and \
                    '$' + 'a1' in prev[1] + prev[1]:
                pass
            rows.append((name, len(insns), load[0], load[1][-1] if load[1] else '', ci - gi))
    for r in sorted(rows, key=lambda x: x[1]):
        print(f"{r[0]}  words={r[1]:3d}  guard={r[2]} {r[3]:12s} gap={r[4]}")
    print(len(rows), 'candidate guards')


if __name__ == '__main__':
    main()
