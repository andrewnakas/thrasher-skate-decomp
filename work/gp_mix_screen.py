#!/usr/bin/env python3
"""List unmatched *game* units that address some globals absolutely and others through $gp.

`work/g0_screen.py` finds units with no `%gp_rel` at all — the `-G0` units. But a unit can
address globals both ways: `%gp_rel` for the small ones and `lui %hi` + `%lo` memory operands
for the ones that are not in the small-data area. No compiler flag produces that mix, so
those units were invisible to the -G0 screen; the spelling that reproduces them is a
*declaration* choice — an absolutely-addressed symbol declared as an array leaves the
small-data path while a scalar beside it stays `%gp_rel` (see func_80034A78).

    python work/gp_mix_screen.py [--all]

Prints, smallest first: size, address, how many `%lo` memory operands, how many `%gp_rel`
references, and the function name.
"""
import csv
import re
import sys
from pathlib import Path

import units

ROOT = Path(__file__).resolve().parent.parent

LO_OPERAND = re.compile(r"\b(?:lw|lbu|lb|lhu|lh|sw|sb|sh)\s+\$\w+,\s*%lo\(")
LO = re.compile(r"%lo\(")
GP = re.compile(r"%gp_rel\(")


def main():
    want_all = "--all" in sys.argv
    rows = list(csv.DictReader(open(ROOT / "config/functions.us.csv")))
    out = []
    skipped = 0
    for r in rows:
        if r["kind"] != "func" or r["segment"] != "game":
            continue
        if units.done(r["name"]):
            skipped += 1
            continue
        p = ROOT / r["asm"]
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        operand = len(LO_OPERAND.findall(text))
        gp = len(GP.findall(text))
        if operand and gp:
            out.append((int(r["size"], 16), r["addr"], r["name"], operand, gp))
    out.sort()
    for i, (size, addr, name, operand, gp) in enumerate(out):
        if not want_all and i >= 40:
            break
        print(f"{size:6d} {size // 4:3d}w {addr} %lo-mem={operand:2d} gp={gp:2d} {name}")
    print(f"-- {len(out)} mixed-global candidates ({skipped} skipped: already matched)")


if __name__ == "__main__":
    main()
