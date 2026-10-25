#!/usr/bin/env python3
"""The real work queue: game functions in config/functions.us.csv that have no src/funcs unit.

`asm/nonmatchings/game/*.s` is NOT that list -- those files stay in the tree after a unit
matches (1235 .s vs 477 unmatched), so using them as the queue sends a pass at units that are
already done. This is the derivation to reuse.

    python work/unmatched.py            # smallest first, with neighbour status
    python work/unmatched.py --json     # machine readable
    python work/unmatched.py --n 40     # how many to show (default 30)
    python work/unmatched.py --check    # only cross-check against tools/progress.py

Run it inside the container (work/drun.sh) like the other tools, since it imports
tools/common.py.
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import progress  # noqa: E402  (for the cross-check only)
from common import FUNCTIONS_CSV, SRC_FUNCS, load_functions  # noqa: E402

PARKED = {
    # measured and recorded in work/residue-r.md; re-attempt only with a genuinely new lever
    "func_80034B98", "func_80058448", "func_8002BCB0", "func_80011B48",
    "func_8001C4BC", "func_8001D4DC", "func_8001C2F0", "func_8001D804",
}


def queue():
    funcs = [f for f in load_functions() if f["segment"] == "game" and f["kind"] == "func"]
    done = {p.stem for p in SRC_FUNCS.glob("func_*.c")}
    by_addr = {f["addr"]: f for f in funcs}
    rows = []
    for f in funcs:
        if f["name"] in done:
            continue
        prev_f = by_addr.get(f["addr"] - 4)
        rows.append({
            "name": f["name"],
            "addr": f["addr"],
            "size": f["size"],
            "parked": f["name"] in PARKED,
            # a neighbour only counts as matched if it is a function at all and has a unit
            "left_done": bool(prev_f and prev_f["name"] in done),
            "right_done": any(g["name"] in done for g in funcs if g["addr"] == f["addr"] + f["size"]),
        })
    rows.sort(key=lambda r: (r["parked"], r["size"]))
    return funcs, done, rows


def main(argv):
    n = 30
    if "--n" in argv:
        n = int(argv[argv.index("--n") + 1])
    funcs, done, rows = queue()
    total, matched = len(funcs), len(funcs) - len(rows)

    # cross-check the derivation against tools/progress.py's own numbers
    prog = [f for f in load_functions() if f["segment"] == "game" and f["kind"] == "func"]
    prog_done = {p.stem for p in SRC_FUNCS.glob("func_*.c")}
    prog_matched = sum(1 for f in prog if f["name"] in prog_done)
    ok = (len(prog) == total and prog_matched == matched)
    if "--check" in argv:
        print(f"cross-check: progress.py {prog_matched}/{len(prog)} vs unmatched.py "
              f"{matched}/{total}: {'OK' if ok else 'MISMATCH'}")
        return 0 if ok else 1

    if "--json" in argv:
        print(json.dumps({"total": total, "matched": matched, "unmatched": len(rows), "rows": rows[:n]}))
        return 0

    live = [r for r in rows if not r["parked"]]
    print(f"queue: {len(rows)} unmatched game functions ({matched}/{total} matched); "
          f"{len(rows) - len(live)} parked by measurement")
    print(f"cross-check: {'OK' if ok else 'MISMATCH'}")
    print()
    print(f"{'size':>6}  {'addr':>8}  nb  name")
    for r in live[:n]:
        nb = ("L" if r["left_done"] else ".") + ("R" if r["right_done"] else ".")
        print(f"{r['size']:>6}  {r['addr']:>8X}  {nb}  {r['name']}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
