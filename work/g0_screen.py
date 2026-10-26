#!/usr/bin/env python3
"""List unmatched *game* units whose asm addresses globals absolutely.

A unit is a -G0 candidate when its assembly touches globals with `lui %hi` + `%lo`
and never uses `%gp_rel` — i.e. it was not compiled with the default -G8.

    python work/g0_screen.py [--all]
"""
import csv
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def main():
    rows = list(csv.DictReader(open(ROOT / "config/functions.us.csv")))
    out = []
    for r in rows:
        if r["kind"] != "func" or r["segment"] != "game":
            continue
        if (ROOT / "src/funcs" / (r["name"] + ".c")).exists():
            continue
        p = ROOT / r["asm"]
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        # -G0 shows as a %lo(sym) *memory operand* (lw/sw/... $r, %lo(sym)($r)),
        # not as `addiu $r, %hi(sym)` building an array base, which -G8 also emits.
        operand = re.findall(r"\b(?:lw|lbu|lb|lhu|lh|sw|sb|sh)\s+\$\w+,\s*%lo\(", text)
        lo = len(re.findall(r"%lo\(", text))
        gp = len(re.findall(r"%gp_rel\(", text))
        if operand and not gp:
            out.append((int(r["size"], 16), r["addr"], r["name"], lo))
    out.sort()
    for size, addr, name, lo in out:
        print(f"{size:6d} {addr} %lo={lo:2d} {name}")
    print(f"-- {len(out)} candidates")


if __name__ == "__main__":
    main()
