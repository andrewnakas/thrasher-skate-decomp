#!/usr/bin/env python3
"""Sibling-adjacency ranking + honest triage of the unmatched game units.

Ranking idea: this session's cheapest matches came from a unit whose immediate
sibling was already matched (func_800122A0 mirrors func_80012274). So score an
unmatched unit by the matched unit it most resembles:

  * address adjacency (same window, close by),
  * shared callees (`jal` targets),
  * similar size in words,
  * same segment-level neighbours.

Triage: classify every unmatched unit as data (dlabel), handwritten, gp plumbing
or plain C, so later passes stop spending attempts on classes C cannot reach.
"""
import csv
import re
import subprocess
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ASM = ROOT / "asm" / "nonmatchings" / "game"


def matched_names():
    out = subprocess.run(["git", "ls-tree", "--name-only", "origin/main", "src/funcs/"],
                         capture_output=True, text=True, cwd=ROOT, check=True).stdout
    return {Path(p).stem for p in out.split() if p.endswith(".c")}


def parse(path):
    text = path.read_text(errors="replace")
    words = len(re.findall(r"/\*[0-9A-F]{4} [0-9A-F]{8} ", text))
    callees = set(re.findall(r"jal\s+(\w+)", text))
    return {
        "is_func": re.search(r"^glabel ", text, re.M) is not None,
        "data": re.search(r"^dlabel ", text, re.M) is not None,
        "handwritten": "handwritten instruction" in text,
        "gp_plumb": bool(re.search(r"(lw|sw)\s+\$gp,", text)) and words <= 8,
        "words": words,
        "callees": callees,
    }


def main():
    rows = [r for r in csv.DictReader(open(ROOT / "config/functions.us.csv"))
            if r["segment"] == "game"]
    matched = matched_names()
    info = {r["name"]: (int(r["addr"], 16), int(r["size"], 16) // 4) for r in rows}
    parsed = {}
    for name in info:
        p = ASM / f"{name}.s"
        if p.exists():
            parsed[name] = parse(p)

    unmatched = [n for n in info if n not in matched]
    classes = Counter()
    detail = defaultdict(list)
    for n in unmatched:
        p = parsed.get(n)
        if p is None:
            cls = "no-asm"
        elif p["data"]:
            cls = "data/dlabel"
        elif p["handwritten"]:
            cls = "handwritten-asm"
        elif p["gp_plumb"]:
            cls = "gp-plumbing"
        else:
            cls = "candidate"
        classes[cls] += 1
        detail[cls].append(n)
    print(f"matched {len(matched)} / {len(rows)}  unmatched {len(unmatched)}")
    for c, k in classes.most_common():
        print(f"  {c:16s} {k}")
    print("  handwritten+data overlap:", len(set(detail['handwritten-asm']) & set(detail['data/dlabel'])))

    # --- sibling ranking over the plain-C candidates
    maddr = {n: info[n][0] for n in matched if n in info}
    msort = sorted(maddr.values())

    def nearest(a):
        lo, hi = 0, len(msort)
        while lo < hi:
            mid = (lo + hi) // 2
            if msort[mid] < a:
                lo = mid + 1
            else:
                hi = mid
        best = None
        for i in (lo - 1, lo):
            if 0 <= i < len(msort):
                d = abs(msort[i] - a)
                if best is None or d < best:
                    best = d
        return best if best is not None else 1 << 30

    scored = []
    for n in detail["candidate"]:
        a, w = info[n]
        dist = nearest(a)
        mine = parsed[n]["callees"]
        shared = 0
        for m in matched:
            if m not in parsed:
                continue
            ov = len(mine & parsed[m]["callees"])
            if not ov:
                continue
            mw = info[m][1] if m in info else 0
            if w and 0.5 <= (mw / w) <= 2.0:
                shared = max(shared, ov)
        score = shared * 6 - (dist / 0x40) - abs(w - 10) * 0.05
        scored.append((score, n, w, dist, shared))
    scored.sort(reverse=True)
    print("\ntop sibling-ranked candidates (score, unit, words, addr-gap, shared callees):")
    for s, n, w, d, sh in scored[:20]:
        print(f"  {s:7.2f} {n} {w:4d}w gap=0x{d:x} shared={sh}")

    out = ROOT / "work/sibling-ranking.txt"
    with open(out, "w") as fh:
        fh.write(f"matched {len(matched)} / {len(rows)}  unmatched {len(unmatched)}\n")
        for c, k in classes.most_common():
            fh.write(f"{c}\t{k}\n")
        for cls, names in detail.items():
            fh.write(f"\n[{cls}]\n")
            for n in sorted(names):
                fh.write(n + "\n")
        fh.write("\n[ranking]\n")
        for s, n, w, d, sh in scored:
            fh.write(f"{s:.2f}\t{n}\t{w}\t0x{d:x}\t{sh}\n")
    print(f"\nwrote {out.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
