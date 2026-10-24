#!/usr/bin/env python3
"""The split gate: is the split sound and reproducible?

    python tools/check_split.py            # all checks, including a re-split
    python tools/check_split.py --quick    # skip the determinism re-split

Checks:
  1. the executable on disk is the one splat.us.yaml expects (sha1)
  2. functions tile .text: each starts where the previous ended, no overlaps
     or gaps, and the PsyQ segment follows the game segment
  3. every function ends in a jump (jr/j + delay slot); a function that falls
     off its end means a bad split (a missed boundary: thps64's biggest churn).
     Known exceptions go in config/split_exceptions.us.txt with a reason.
  4. every src/funcs unit still names a function in the table (re-splits
     orphan merged files otherwise)
  5. determinism: splitting again yields a byte-identical asm/ tree and the
     same committed tables
"""
import hashlib
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import fresh  # noqa: E402
from common import ASM, CONFIG, EXE, EXE_SHA1, ROOT, SRC_FUNCS, load_functions  # noqa: E402

INSN = re.compile(r"/\*\s*[0-9A-F]+\s+[0-9A-F]{8}\s+[0-9A-F]{8}\s*\*/\s+(\S+)\s*(.*)")
EXCEPTIONS = CONFIG / "split_exceptions.us.txt"


def tree_hash():
    h = hashlib.sha256()
    for p in sorted(ASM.rglob("*.s")):
        h.update(str(p.relative_to(ASM)).encode() + b"\0" + p.read_bytes())
    for t in fresh.TABLES:
        h.update((CONFIG / t).read_bytes())
    return h.hexdigest()


def exceptions():
    if not EXCEPTIONS.exists():
        return set()
    return {l.split()[0] for l in EXCEPTIONS.read_text().splitlines() if l.strip() and not l.startswith("#")}


def ends_in_jump(path):
    insns = []
    for line in path.read_text().splitlines():
        if line.lstrip().startswith("endlabel"):
            break
        m = INSN.search(line)
        if m:
            insns.append(m.group(1))
    while insns and insns[-1] == "nop" and len(insns) > 2 and insns[-2] == "nop":
        insns.pop()  # alignment padding
    if len(insns) < 2:
        return None  # data in .text (dlabel'd), not code
    return insns[-2] in ("jr", "j", "jalr") or insns[-1] in ("jr", "j")


ANY_ADDR = re.compile(r"/\*\s*[0-9A-F]+\s+([0-9A-F]{8})\s")


def extent_end(path):
    """One past the last byte the asm file emits (functions carry padding/alt-entry data)."""
    last = None
    sect = ".text"
    for line in path.read_text().splitlines():
        if line.startswith(".section"):
            sect = line.split()[1]
        m = ANY_ADDR.search(line)
        if m and sect == ".text":
            last = int(m.group(1), 16)
    return last + 4 if last is not None else None


def main():
    problems = []
    if not EXE.exists():
        sys.exit("disc/files/SLUS_009.35 missing: python tools/extract_disc.py")
    if hashlib.sha1(EXE.read_bytes()).hexdigest() != EXE_SHA1:
        problems.append("disc/files/SLUS_009.35 is not the USA executable (sha1)")
    fresh.ensure()

    funcs = load_functions()
    for a, b in zip(funcs, funcs[1:]):
        end = extent_end(ROOT / a["asm"]) or a["addr"] + a["size"]
        if end != b["addr"]:
            kind = "overlaps" if end > b["addr"] else f"leaves a {b['addr'] - end:#x}-byte gap before"
            problems.append(f"{a['name']} {kind} {b['name']}")
    seg_order = [f["segment"] for f in funcs]
    if "psyq" in seg_order and "game" in seg_order[seg_order.index("psyq"):]:
        problems.append("game functions appear after the PsyQ segment starts")

    allowed = exceptions()
    for f in funcs:
        if f["name"] in allowed:
            continue
        r = ends_in_jump(ROOT / f["asm"])
        if r is False:
            problems.append(f"{f['name']} does not end in a jump: likely a missed function boundary "
                            "(fix symbol_addrs, or add to config/split_exceptions.us.txt with a reason)")

    names = {f["name"] for f in funcs}
    for u in sorted(SRC_FUNCS.glob("*.c")):
        if u.stem not in names:
            problems.append(f"src/funcs/{u.name} no longer names a function (orphaned by a re-split)")

    if "--quick" not in sys.argv:
        before = tree_hash()
        r = subprocess.run([sys.executable, str(ROOT / "tools" / "split.py")], cwd=ROOT,
                           capture_output=True, text=True)
        if r.returncode != 0:
            problems.append("re-split failed: " + (r.stdout + r.stderr)[-300:])
        elif tree_hash() != before:
            problems.append("splitting twice gives different asm/ or tables: the split is not deterministic")

    for p in problems:
        print(f"PROBLEM split: {p}")
    game = [f for f in funcs if f["segment"] == "game"]
    print(f"check_split: {len(game)} game + {len(funcs) - len(game)} PsyQ functions, "
          f"{len(problems)} problems")
    if problems:
        print("SPLIT FAIL")
        sys.exit(1)
    print("SPLIT PASS")


if __name__ == "__main__":
    main()
