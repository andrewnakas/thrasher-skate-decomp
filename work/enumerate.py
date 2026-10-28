#!/usr/bin/env python3
"""List unmatched game bodies, smallest first. The one queue enumerator.

    python work/enumerate.py                 # every unopened body, by instruction count
    python work/enumerate.py --band 16 30    # only bodies in that window
    python work/enumerate.py --fresh         # drop bodies the census already mentions
    python work/enumerate.py --scaled        # only bodies that scale an index into a base
    python work/enumerate.py --windows       # count bodies per 4K window instead of listing
    python work/enumerate.py --limit 40

Supersedes enum_fresh.py, enum_small.py, enum_band.py, unopened.py and unopened2.py, which each
re-implemented the same corpus filter with a different print. This script *finds* work and owns no
numbers; work/verify.py owns every measurement.
"""
import argparse
import csv
import re
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "work"))

import drafts  # noqa: E402  the one owner of which bodies have drafts, in every directory
PAT = re.compile(r"/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+(\S+)")
GTE = re.compile(r"\b(mtc2|mfc2|ctc2|cfc2|lwc2|swc2|gpf|gpl)\b")
# $sp switched onto the scratchpad stack (`addu $sp, $t0, $zero` / `lw $sp, 0x10($sp)`): gcc never
# assigns $sp in a function body, so the class cannot be written in C. func_80023B1C, func_800262E8,
# func_80027538 and func_8003B068 are the four bodies; their twins own the same trampoline.
SP_SWAP = re.compile(r"\*/\s+(addu|lw|or)\s+\$sp,")
# the function itself writes `$gp` (a gp-reload trampoline: `lw $gp, D_8008B398` / `sw $gp, D_8008B398`
# and a bare `jr $ra`, the pair at func_80045828/func_80045838).  gcc never assigns $gp in a body, so
# the class cannot be written in C; only these two bodies carry it.
GP_SWAP = re.compile(r"\*/\s+(lw|sw|addu|or)\s+\$gp,")
# no frame at all and `$ra` parked in `$t7` across the calls (`addu $t7, $ra, $zero` ... `addu $ra, $t7`):
# gcc always spills $ra to its own frame, so the pair (func_80032E94, func_80033268) is hand-written and
# func_80032E94 also keeps the return address in D_80032C20.  Both are outside the C class.
RA_T7 = re.compile(r"\*/\s+addu\s+\$t7,\s+\$ra,")
# `$at` as a data temporary (`slt $at, ...`, `addu $at, ...`): the assembler only produces that from
# its own hand-written macros never from gcc, and none of the 653 merged units contains it, so the
# body is hand-written asm and not a C target.  The *other* `$at` form -- `lui $at, %hi(sym)` plus a
# `mem ... %lo(sym)($at)` -- is compiler output under the allowed `-mno-split-addresses` flag
# (func_80011BD4, func_80011C40, func_8003ED28 and two more merged units carry it), so it must NOT
# be filtered: those bodies are C work with a per-file cflag.
AT_VALUE = re.compile(r"\*/\s+(slt|sltu|slti|sltiu|addu|or|and|xor|subu|negu)\s+\$at,")
# `mult` followed by two or more `nop`s: manual HI/LO hazard padding. gcc emits `mult` immediately
# before `mflo` (see func_800331FC); func_80032C28 hand-schedules the delay.
MULT_NOPS = re.compile(r"\*/\s+mult\s+[^\n]*\n(?:\s*/\*[^\n]*\*/\s+nop\n){2,}")
# ordered `lw $t0` ... `lw $t1` ... `lw $t2` ... `lw $t3` in one listing: the hand-written register
# walk (t0-t9, then v0/v1) that the 0x80033xxx copy/vector bodies use. gcc fills low registers first
# -- a C 12-word copy compiles to `$2,$3,$6..$14,$5` (proved with a synthetic through tools/cc.py) --
# and none of the 653 merged units contains this chain, so the body is not a C target.
LW_CHAIN = re.compile(r"\*/\s+lw\s+\$(t\d|v0|v1|a\d)\b")


def hand_written_chain(text):
    regs = [m.group(1) for m in LW_CHAIN.finditer(text)]
    if not all(r in regs for r in ("t0", "t1", "t2", "t3")):
        return False
    return regs.index("t0") < regs.index("t1") < regs.index("t2") < regs.index("t3")
SCALED = re.compile(r"\bsll\s+\$[a-z0-9]+,\s*\$[a-z0-9]+,\s*[1234]\b")
BODY = re.compile(r"func_([0-9A-Fa-f]{8})")


def bodies():
    """(insn count, name, asm text) for every unmatched, clean game body."""
    merged = drafts.merged_bodies()  # committed units only: a scratch copy in src/funcs is not a unit
    for row in csv.DictReader(open(ROOT / "config" / "functions.us.csv")):
        addr = int(row["addr"], 16)
        if addr > 0x80058633:
            continue
        name = "func_%08X" % addr
        if name in merged:
            continue
        asm = ROOT / "asm" / "nonmatchings" / "game" / (name + ".s")
        if not asm.exists():
            continue
        text = asm.read_text()
        if ("glabel" not in text or "Handwritten" in text or GTE.search(text)
                or SP_SWAP.search(text) or GP_SWAP.search(text) or RA_T7.search(text)
                or AT_VALUE.search(text) or MULT_NOPS.search(text) or hand_written_chain(text)):
            continue
        yield len(PAT.findall(text)), name, text


def drafted():
    """Bodies that already have a draft somewhere, from the one owner of that fact."""
    return set(drafts.by_body())


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--band", nargs=2, type=int, metavar=("MIN", "MAX"))
    ap.add_argument("--fresh", action="store_true", help="skip bodies the census mentions")
    ap.add_argument("--scaled", action="store_true", help="only scaled-index bodies")
    ap.add_argument("--windows", action="store_true")
    ap.add_argument("--limit", type=int, default=40)
    args = ap.parse_args()

    have = drafted()
    census = (ROOT / "work" / "census-corrected.md").read_text() if args.fresh else ""
    rows = []
    for n, name, text in sorted(bodies()):
        if args.band and not (args.band[0] <= n <= args.band[1]):
            continue
        if args.fresh and (("%08X" % int(name[5:], 16)) in census):
            continue
        if args.scaled and not SCALED.search(text):
            continue
        rows.append((n, name, name in have))

    if args.windows:
        for win, count in Counter(int(name[5:], 16) & ~0xFFF for _, name, _ in rows).most_common(16):
            print("%08X %d" % (win, count))
        return 0

    print("%d bodies%s" % (len(rows), " (drafted marked *)" if rows else ""))
    for n, name, is_drafted in rows[:args.limit]:
        print("%3d %s%s" % (n, name, " *" if is_drafted else ""))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
