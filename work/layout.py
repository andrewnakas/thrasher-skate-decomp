#!/usr/bin/env python3
"""Read a body's operand pattern off its listing, so a draft starts from what the compiler emitted.

The expensive parks in this lane were drafts shaped on assumed record strides, offsets and mask
widths.  This script owns that reading: it parses `asm/nonmatchings/game/<body>.s` and prints

  - the frame size and which registers the prologue saves, in save order
  - every memory access with its base register, displacement and width
  - the strides it can derive, from the emitted shift/add chain rather than from any C type
  - every mask (`andi`) and every constant, in materialisation order
  - how each symbol is reached: direct pair (`lui $r,%hi(S)` + `addiu $r,$r,%lo(S)`), symbolic load
    (`lui $r,%hi(S)` + `lw $d,%lo(S)($r)`), folded displacement (`%lo(S+N)`), `$at` round-trip, or
    gp-relative
  - every register copy (`addu $d,$s,$zero`) — the tell for a value kept alive across a rewrite

    python work/layout.py func_8002DE18         # operand pattern for one body
    python work/layout.py --scan --limit 40     # rank undrafted bodies that show the two proved levers

It measures nothing and decides nothing: verify.py still owns every number, enumerate.py still owns
which bodies are open.
"""
import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "work"))
import drafts  # noqa: E402  the one owner of which bodies are merged

LINE = re.compile(r"/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*)")
SYM = re.compile(r"%(hi|lo|gp_rel)\(([A-Za-z0-9_]+?)(?:\+0x([0-9A-Fa-f]+))?\)")
LOAD = {"lw", "lh", "lhu", "lb", "lbu", "sw", "sh", "sb", "lwc1", "swc1"}
WIDTH = {"lw": 4, "sw": 4, "lh": 2, "lhu": 2, "sh": 2, "lb": 1, "lbu": 1, "sb": 1,
         "lwc1": 4, "swc1": 4}


def instructions(text):
    out = []
    for line in text.splitlines():
        m = LINE.search(line)
        if m:
            out.append((m.group(2), m.group(3).strip()))
    return out


def parse(text):
    ins = instructions(text)
    info = {"frame": 0, "saves": [], "access": [], "masks": [], "consts": [], "copies": [],
            "syms": {}, "strides": []}
    ins = [(op, re.sub(r",\s+", ",", rest)) for op, rest in ins]
    for i, (op, rest) in enumerate(ins):
        ops = [o.strip() for o in rest.split(",")] if rest else []
        if op == "addiu" and len(ops) == 3 and ops[0] == "$sp" and ops[1] == "$sp":
            info["frame"] = -int(ops[2], 0) if ops[2].startswith("-") else int(ops[2], 0)
        if op == "sw" and len(ops) == 2 and ops[0].startswith("$") and "($sp)" in ops[1]:
            info["saves"].append(ops[0])
        if op in LOAD:
            m = re.match(r"(-?0x[0-9A-Fa-f]+|-?\d+)?\((\$\w+)\)", ops[-1])
            sym = SYM.search(rest)
            info["access"].append({
                "op": op, "dst": ops[0], "base": m.group(2) if m else "?",
                "off": m.group(1) if m and m.group(1) else "0", "width": WIDTH.get(op, 0),
                "sym": ("%s%s(%s)" % (sym.group(1), "+0x" + sym.group(3) if sym.group(3) else "",
                                      sym.group(2))) if sym else "",
            })
            if sym:
                info["syms"].setdefault(sym.group(2), set()).add(
                    "%s%s+%s" % (sym.group(1), "+0x" + sym.group(3) if sym.group(3) else "", op))
        if op == "andi" and len(ops) == 3:
            info["masks"].append(int(ops[2], 0))
        if op in ("addiu", "ori") and len(ops) == 3 and ops[1] == "$zero":
            info["consts"].append(int(ops[2], 0))
        if op == "lui" and len(ops) == 2 and "%hi" not in rest:
            try:
                info["consts"].append(int(ops[1], 0) << 16)
            except ValueError:
                pass
        if op == "addu" and len(ops) == 3 and ops[2] == "$zero":
            info["copies"].append((ops[0], ops[1], i))
    # symbol materialisation: lui $r,%hi(S) then addiu $r,$r,%lo(S) (same register) is the direct
    # pair; lui $r,%hi(S) then a load through %lo(S)($r) is the symbolic load.  Both are the tell
    # the incomplete-array spelling reproduces; $at and %lo(S+N) are the forms it removes.
    for i in range(len(ins)):
        m1 = re.match(r"\$(\w+),%hi\(([A-Za-z0-9_]+)\)", ins[i][1])
        if ins[i][0] != "lui" or not m1:
            continue
        reg, sym = m1.group(1), m1.group(2)
        # the low half is not always the next instruction: look ahead for this register
        for j in range(i + 1, min(i + 21, len(ins))):
            op2, r2 = ins[j]
            m2 = re.match(r"\$(\w+),\$(\w+),%lo\(([A-Za-z0-9_]+)\)", r2)
            if m2 and op2 == "addiu" and m2.group(1) == m2.group(2) == reg and m2.group(3) == sym:
                info["syms"].setdefault(sym, set()).add("direct-pair")
                break
            m4 = SYM.search(r2)
            if m4 and m4.group(1) == "lo" and m4.group(2) == sym and ("(%s)" % reg) in r2:
                info["syms"].setdefault(sym, set()).add("symbolic-load")
                if m4.group(3):
                    info["syms"][sym].add("folded+0x" + m4.group(3))
                break
    # strides: sll x,b,N ; addu x,x,b ; sll x,x,M  =>  (2^N + 1) * 2^M
    seq = [(op, [o.strip() for o in rest.split(",")] if rest else []) for op, rest in ins]
    for i in range(len(seq) - 2):
        (o1, a1), (o2, a2), (o3, a3) = seq[i], seq[i + 1], seq[i + 2]
        if (o1 == "sll" and o2 == "addu" and o3 == "sll" and len(a1) == 3 and len(a2) == 3
                and len(a3) == 3 and a1[0] == a1[1] and a2[0] == a3[0] == a2[1]
                and a2[2] == a1[1] and a3[1] == a2[0]):
            n, m = int(a1[2], 0), int(a3[2], 0)
            info["strides"].append(((1 << n) + 1) << m)
    return info


def format_body(name, path):
    info = parse(path.read_text())
    lines = ["%s  frame=0x%X  saves=%s" % (name, info["frame"], " ".join(info["saves"]) or "-")]
    for s in info["strides"]:
        lines.append("  stride   0x%-4X  (from sll/addu/sll chain)" % s)
    for sym, uses in sorted(info["syms"].items()):
        lines.append("  symbol   %-14s %s" % (sym, ", ".join(sorted(uses))))
    for a in info["access"]:
        if a["sym"]:
            continue
        lines.append("  %-4s %-4s +%-6s base=%-4s w=%d" %
                     (a["op"], a["dst"], a["off"], a["base"], a["width"]))
    if info["masks"]:
        lines.append("  masks    %s" % " ".join("0x%X" % m for m in info["masks"]))
    if info["consts"]:
        lines.append("  consts   %s" % " ".join("0x%X" % c for c in info["consts"]))
    for dst, src, at in info["copies"]:
        lines.append("  copy     addu %s,%s,$zero   (insn %d)" % (dst, src, at))
    return "\n".join(lines)


def scan(limit):
    merged = drafts.merged_bodies()
    drafted = set(drafts.by_body())
    found = []
    for path in sorted((ROOT / "asm/nonmatchings/game").glob("func_*.s")):
        name = path.stem
        if name in merged or name in drafted:
            continue
        text = path.read_text()
        if "glabel" not in text or "Handwritten" in text:
            continue
        info = parse(text)
        pair = sorted(sym for sym, how in info["syms"].items() if "direct-pair" in how)
        copies = [c for c in info["copies"] if c[1] != "$zero"]
        if pair:
            found.append((len(pair), -len(instructions(text)), name, pair[:2], len(copies)))
    found.sort(reverse=True)
    print("%d unmerged, undrafted bodies materialise a symbol as a direct pair (lever A)" % len(found))
    for npair, negn, name, syms, ncopy in found[:limit]:
        print("%-14s words=%-3d pairs=%d copies=%-2d %s" % (name, -negn, npair, ncopy, ",".join(syms)))


RF = re.compile(r"%hi\(([A-Za-z0-9_]+)\)")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("body", nargs="?")
    ap.add_argument("--scan", action="store_true")
    ap.add_argument("--limit", type=int, default=40)
    args = ap.parse_args()
    if args.scan:
        return scan(args.limit)
    if not args.body:
        ap.error("give a body name or --scan")
    path = ROOT / "asm/nonmatchings/game" / (args.body + ".s")
    print(format_body(args.body, path))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
