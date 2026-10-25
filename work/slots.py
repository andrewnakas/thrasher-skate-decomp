#!/usr/bin/env python3
"""Reconstruct a body's stack-slot map from its listing, and emit a declaration set.

    python work/slots.py func_80011D60          # slot map for one body
    python work/slots.py func_80011D60 --decls  # ... plus C declarations that fill the frame

Reads asm/nonmatchings/game/<name>.s, takes the frame size from the prologue and every
`<off>($sp)` operand in the body, and prints one row per slot: offset, width(s) seen, the
kinds of access, and the span. Slots whose address is taken (`addiu $x,$sp,<off>`) are
marked as arrays, because the callee writes through them.

The declaration set it emits is ordered by offset with each slot's width and padding, so a
transcription can declare exactly the frame the game uses instead of guessing. This script
measures; it owns no counts and writes no files.
"""
import argparse
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
INS = re.compile(r"\*/\s+(\S+)\s+(.*)$")
SP = re.compile(r"(-?0x[0-9A-Fa-f]+|-?\d+)\(\$sp\)")
ADDR = re.compile(r"addiu\s+\$(\w+),\s*\$sp,\s*(-?0x[0-9A-Fa-f]+|-?\d+)")
FRAME = re.compile(r"addiu\s+\$sp,\s*\$sp,\s*(-0x[0-9A-Fa-f]+|-\d+)")
WIDTH = {"lw": 4, "sw": 4, "lh": 2, "sh": 2, "lbu": 1, "sb": 1, "lhu": 2, "lb": 1, "addiu": 4, "jal": 4}


def parse(name):
    text = (ROOT / "asm" / "nonmatchings" / "game" / (name + ".s")).read_text()
    frame = 0
    hits = []
    taken = set()
    for line in text.splitlines():
        m = INS.search(line)
        if not m:
            continue
        mn, ops = m.group(1), m.group(2)
        if mn == "addiu" and "$sp, $sp, -" in ops.replace("  ", " "):
            f = FRAME.search(mn + " " + ops)
            if f:
                frame = -int(f.group(1), 16) if f.group(1).startswith("-0x") else -int(f.group(1))
        a = ADDR.search(mn + " " + ops)
        if a:
            off = a.group(2)
            taken.add(int(off, 16) if off.startswith("0x") or off.startswith("-0x") else int(off))
        for off in SP.findall(ops):
            o = int(off, 16) if "0x" in off else int(off)
            hits.append((o, mn, WIDTH.get(mn, 0)))
    return frame, hits, taken


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("body")
    ap.add_argument("--decls", action="store_true")
    args = ap.parse_args()
    name = args.body if args.body.startswith("func_") else "func_" + args.body
    frame, hits, taken = parse(name)
    print("%s: frame 0x%X" % (name, frame))
    slots = {}
    for off, mn, w in hits:
        slots.setdefault(off, []).append((mn, w))
    for off in sorted(slots):
        acc = slots[off]
        widths = sorted({w for _, w in acc if w})
        kinds = sorted({mn for mn, _ in acc})
        print("  0x%02X  width %-8s  %-22s  n=%d%s" % (
            off, "/".join(map(str, widths)) or "?", ",".join(kinds), len(acc),
            "  ADDR-TAKEN" if off in taken else ""))
    if args.decls:
        print("\n/* declarations filling the frame, in offset order */")
        end = 0
        for off in sorted(slots):
            if off < end:
                continue
            if off > end:
                print("    u8  pad%02X[0x%X];" % (end, off - end))
            widths = [w for _, w in slots[off] if w]
            w = max(widths) if widths else 4
            span = 4
            while (off + span) in slots and span < 64:
                span += 4
            size = span if span > 4 else w
            if off in taken or size > 4:
                print("    u8  slot%02X[0x%X];" % (off, size))
            elif size == 1:
                print("    u8  slot%02X;" % off)
            elif size == 2:
                print("    s16 slot%02X;" % off)
            else:
                print("    s32 slot%02X[%d];" % (off, max(1, size // 4)))
            end = off + size
        print("    /* frame 0x%X; $ra is the last saved word */" % frame)


if __name__ == "__main__":
    main()
