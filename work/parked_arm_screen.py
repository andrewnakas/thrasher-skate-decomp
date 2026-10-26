#!/usr/bin/env python3
"""Find unmatched game units whose only oddity may be a parked `beq` arm.

The else-side recipe produces `beq rs,rt,<arm>` where the arm sits after a jump,
i.e. a forward `beq` whose target label is preceded by a `j`. Units whose
assembly has such a pattern are candidates for that recipe.

    python work/parked_arm_screen.py [--min-words N]
"""
import re
import sys
from pathlib import Path

import units

ROOT = Path(__file__).resolve().parent.parent
ASM = ROOT / "asm" / "nonmatchings" / "game"
SRC = ROOT / "src" / "funcs"

LABEL = re.compile(r"^(\.L[0-9A-F]+):")
INS = re.compile(r"/\* [0-9A-F]+ [0-9A-F]+ [0-9A-F]+ \*/")
BEQ = re.compile(r"\bbeq\s+\$\w+,\s*\$\w+,\s*(\.L[0-9A-F]+)")
JMP = re.compile(r"\bj\s+(\.L[0-9A-F]+)")
WORDS = re.compile(r"nonmatching (\w+), 0x([0-9A-F]+)")


def scan(path):
    lines = path.read_text().splitlines()
    m = WORDS.search(lines[0]) if lines else None
    if not m:
        return None
    words = int(m.group(2), 16) // 4
    idx = {}
    for i, line in enumerate(lines):
        mo = LABEL.match(line.strip())
        if mo:
            idx.setdefault(mo.group(1), i)
    hits = 0
    for i, line in enumerate(lines):
        mo = BEQ.search(line)
        if not mo:
            continue
        tgt = idx.get(mo.group(1))
        if tgt is None or tgt <= i:
            continue
        if any(JMP.search(l) for l in lines[i:tgt]):
            hits += 1
    return words, hits


def main():
    min_words = 40
    if "--min-words" in sys.argv:
        min_words = int(sys.argv[sys.argv.index("--min-words") + 1])
    rows = []
    names = [p.stem for p in sorted(ASM.glob("func_*.s"))]
    todo, already = units.split(names)
    for name in todo:
        path = ASM / (name + ".s")
        r = scan(path)
        if not r:
            continue
        words, hits = r
        if hits and words >= min_words:
            rows.append((words, hits, name))
    rows.sort()
    print(f"{len(rows)} parked-arm candidates at >= {min_words} words")
    print(units.report(len(names), todo, already))
    for words, hits, name in rows:
        print(f"  {words:4d}w beq={hits} {name}")


if __name__ == "__main__":
    main()
