#!/usr/bin/env python3
"""Where does the built executable first differ from the original, and in what?

    python tools/first_diff.py [--all]

Maps differing bytes back to the function or rodata piece that owns them, via
config/functions.us.csv and config/rodata.us.csv. Because configure.py pins
every object to its original address, a bad function does not shift the rest;
the list is the set of guilty objects, not a cascade.
"""
import bisect
import csv
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, CONFIG, EXE, VRAM, load_functions  # noqa: E402

HEADER = 0x800


def owners():
    spans = [(f["addr"], f["name"]) for f in load_functions()]
    with open(CONFIG / "rodata.us.csv") as fh:
        spans += [(int(r["addr"], 16), r["name"]) for r in csv.DictReader(fh)]
    spans.sort()
    return [a for a, _ in spans], [n for _, n in spans]


def main():
    built = (BUILD / "SLUS_009.35").read_bytes()
    orig = EXE.read_bytes()
    if built == orig:
        print("first_diff: identical")
        return
    if len(built) != len(orig):
        print(f"first_diff: size {len(built):#x}, original {len(orig):#x}")
    addrs, names = owners()
    guilty = {}
    for off in range(min(len(built), len(orig))):
        if built[off] != orig[off]:
            if off < HEADER:
                guilty.setdefault("PS-X EXE header", []).append(off)
                continue
            va = VRAM + off - HEADER
            i = bisect.bisect_right(addrs, va) - 1
            who = names[i] if i >= 0 else "?"
            guilty.setdefault(who, []).append(va)
    first = min(min(v) for v in guilty.values())
    print(f"first_diff: first difference at 0x{first:08X}; {len(guilty)} object(s) differ")
    for who, vas in sorted(guilty.items(), key=lambda kv: kv[1][0])[: None if "--all" in sys.argv else 15]:
        print(f"  {who}: {len(vas)} byte(s), first at 0x{vas[0]:08X}")


if __name__ == "__main__":
    main()
