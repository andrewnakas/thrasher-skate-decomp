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
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
PAT = re.compile(r"/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+(\S+)")
GTE = re.compile(r"\b(mtc2|mfc2|ctc2|cfc2|lwc2|swc2|gpf|gpl)\b")
SCALED = re.compile(r"\bsll\s+\$[a-z0-9]+,\s*\$[a-z0-9]+,\s*[1234]\b")
BODY = re.compile(r"func_([0-9A-Fa-f]{8})")


def bodies():
    """(insn count, name, asm text) for every unmatched, clean game body."""
    merged = {p.stem for p in (ROOT / "src" / "funcs").glob("func_*.c")}
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
        if "glabel" not in text or "Handwritten" in text or GTE.search(text):
            continue
        yield len(PAT.findall(text)), name, text


def drafted():
    out = set()
    for d in (ROOT / "work" / "near-miss", ROOT / "work" / "best"):
        for f in d.glob("*.c"):
            hit = BODY.search(f.name)
            if hit:
                out.add("func_" + hit.group(1).upper())
    return out


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
