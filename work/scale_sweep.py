#!/usr/bin/env python3
"""Sweep parked drafts for equivalence-spelling wins.

For every draft in work/near-miss/ the body is re-matched with each applicable
constant-only rewrite:

    shift2mul   x << N        -> x * (1 << N)
    mul2shift   x * 16        -> x << 4          (also x * (1 << N))
    div2shift   x / 4         -> x >> 2
    mod2mask    x % 8         -> x & 7
    mask2mod    x & 7         -> x % 8
    add2mul     x + x         -> x * 2
    mul2add     x * 2         -> x + x

The best spelling per body is kept; winners that MATCH are left in
src/funcs/. Output: work/scale-sweep/table.tsv (also printed as a summary).

    .venv/bin/python work/scale_sweep.py [-j4] [--limit N]
"""
import argparse
import os
import re
import sys
from multiprocessing import Pool
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import match  # noqa: E402
from common import BUILD  # noqa: E402

DRAFTS = ROOT / "work/near-miss"
OUT = ROOT / "work/scale-sweep"

SIMPLE = r"(?:[A-Za-z_]\w*(?:\s*\[[^\[\]]*\])?|\([^()]*\))"
SHIFT = re.compile(rf"(?P<lhs>{SIMPLE})\s*<<\s*(?P<n>\d+)")
MULPOW = re.compile(rf"(?P<lhs>{SIMPLE})\s*\*\s*(?:\(\s*1\s*<<\s*(?P<n1>\d+)\s*\)|(?P<lit>\d+))")
DIV = re.compile(rf"(?P<lhs>{SIMPLE})\s*/\s*(?P<k>\d+)")
MOD = re.compile(rf"(?P<lhs>{SIMPLE})\s*%\s*(?P<k>\d+)")
MASK = re.compile(rf"(?P<lhs>{SIMPLE})\s*&\s*(?P<k>\d+)")
ADD = re.compile(r"(?P<x>[A-Za-z_]\w*)\s*\+\s*(?P=x)\b")
MUL2 = re.compile(rf"(?P<lhs>{SIMPLE})\s*\*\s*2\b")

POW2 = {2: 1, 4: 2, 8: 3, 16: 4, 32: 5, 64: 6, 128: 7, 256: 8, 512: 9, 1024: 10}


def _mul2shift_sub(m):
    if m.group("n1"):
        return "(%s << %s)" % (m.group("lhs"), m.group("n1"))
    lit = int(m.group("lit"))
    if lit in POW2:
        return "(%s << %d)" % (m.group("lhs"), POW2[lit])
    return m.group(0)


def variants(text):
    out = {}
    if SHIFT.search(text):
        out["shift2mul"] = SHIFT.sub(lambda m: "(%s * (1 << %s))" % (m.group("lhs"), m.group("n")), text)
        # NOTE: x << N is x * 2**N. There is deliberately no "shift2div" cell:
        # rewriting a left shift as a division computes the right shift instead,
        # so it is not an equivalence and its diffs measure a different expression.
    if MULPOW.search(text):
        new = MULPOW.sub(_mul2shift_sub, text)
        if new != text:
            out["mul2shift"] = new
    if DIV.search(text):
        new = DIV.sub(lambda m: "(%s >> %d)" % (m.group("lhs"), POW2[int(m.group("k"))])
                      if int(m.group("k")) in POW2 else m.group(0), text)
        if new != text:
            out["div2shift"] = new
    if MOD.search(text):
        new = MOD.sub(lambda m: "(%s & %d)" % (m.group("lhs"), int(m.group("k")) - 1)
                      if int(m.group("k")) in POW2 else m.group(0), text)
        if new != text:
            out["mod2mask"] = new
    if MASK.search(text):
        new = MASK.sub(lambda m: "(%s %% %d)" % (m.group("lhs"), int(m.group("k")) + 1)
                       if (int(m.group("k")) + 1) in POW2 else m.group(0), text)
        if new != text:
            out["mask2mod"] = new
    if ADD.search(text):
        out["add2mul"] = ADD.sub(lambda m: "(%s * 2)" % m.group("x"), text)
    if MUL2.search(text):
        new = MUL2.sub(lambda m: "(%s + %s)" % (m.group("lhs"), m.group("lhs")), text)
        if new != text:
            out["mul2add"] = new
    return out


def score(res):
    if res.ok:
        return (0, 0)
    return (len(res.diffs), len(getattr(res.ours, "words", []) or []) - len(getattr(res.target, "words", []) or []))


def run_body(args):
    name, draft_text = args
    outdir = BUILD / ("sweep-" + name)
    tag = name
    results = []

    def attempt(kind, text):
        src = OUT / ("%s__%s.c" % (name, kind))
        src.write_text(text)
        try:
            res = match.compare(name, src=src, outdir=outdir)
        except Exception as e:  # noqa: BLE001 - a broken variant is data, not a crash
            results.append((kind, None, None, str(e)))
            return None
        words = len(getattr(res.ours, "words", []) or [])
        sc = None if res.error else (len(res.diffs), words)
        results.append((kind, res.ok and not res.error, sc, res.error))
        return res

    base = attempt("base", draft_text)
    if base is None or not base.ok or base.error:
        for kind, text in variants(draft_text).items():
            attempt(kind, text)
        best = None
        for kind, ok, sc, err in results:
            if ok:
                best = (kind, sc)
                break
        if best is None:
            cand = [(sc, kind) for kind, ok, sc, err in results if sc is not None]
            if cand:
                sc, kind = min(cand)
                if kind != "base" and sc[0] < score(base)[0]:
                    best = (kind, sc)
        return (name, score(base), best)

    # already matching: stale draft of a shipped body
    return (name, score(base), ("already", score(base)))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("-j", "--jobs", type=int, default=4)
    ap.add_argument("--limit", type=int, default=0)
    a = ap.parse_args()
    OUT.mkdir(parents=True, exist_ok=True)

    by_body = {}
    for p in sorted(DRAFTS.glob("*.c")):
        m = re.search(r"func_([0-9A-Fa-f]{8})", p.name)
        if not m:
            continue
        name = "func_" + m.group(1).upper()
        # prefer the plain recording of the best draft
        prio = 0 if p.name == "%s-near-miss.c" % name else 1
        cur = by_body.get(name)
        if cur is None or prio < cur[0]:
            by_body[name] = (prio, p)

    todo = []
    for name, (_, p) in sorted(by_body.items()):
        if (ROOT / "src/funcs" / (name + ".c")).exists():
            continue
        todo.append((name, p.read_text()))
    if a.limit:
        todo = todo[: a.limit]
    print("bodies: %d" % len(todo), flush=True)

    with Pool(a.jobs) as pool:
        rows = pool.map(run_body, todo, chunksize=1)

    lines = ["body\tbefore_diffs\tbefore_words\tbest\tmatched\tafter_diffs\tafter_words"]
    wins = []
    for name, before, best in rows:
        if best and best[0] != "already":
            kind, sc = best
            if not (kind == "base"):
                wins.append((name, before, kind, sc))
            lines.append("%s\t%d\t%d\t%s\t%s\t%d\t%d" % (name, before[0], before[1], kind,
                                                         "YES" if sc[0] == 0 else "no", sc[0], sc[1]))
        elif best and best[0] == "already":
            lines.append("%s\t%d\t%d\talready-matching\t(prune)\t-\t-" % (name, before[0], before[1]))
        else:
            lines.append("%s\t%d\t%d\tnone\tno\t%d\t%d" % (name, before[0], before[1], before[0], before[1]))
    (OUT / "table.tsv").write_text("\n".join(lines) + "\n")
    print("conversions: %d" % sum(1 for _, _, _, sc in wins if sc[0] == 0))
    for name, before, kind, sc in sorted(wins, key=lambda w: w[3][0])[:40]:
        print("  %s %d/%d -> %s %d/%d" % (name, before[0], before[1], kind, sc[0], sc[1]))


if __name__ == "__main__":
    main()
