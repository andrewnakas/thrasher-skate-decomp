#!/usr/bin/env python3
"""Batch-test C shape variants for one function against tools/match.py.

This is the loop every matching pass in this repo re-implements by hand: write a draft,
run match.py, read the diff count, tweak one thing, repeat. Doing it in a shell keeps the
results in scrollback; doing it here leaves a ranked table and the best variant on disk.

Usage:
    python work/shape_search.py func_80056A3C work/shapes/func_80056A3C.py

The shape file must define VARIANTS = {name: source_text}. Each variant is written to
src/funcs/<func>.c in turn, matched, and removed again, so a failed search leaves no draft
behind. The best variant is copied to work/near-miss/<func>-best.c and every result is
printed as `diff_words name`, smallest first.
"""
import os
import re
import subprocess
import sys

SRC = os.path.join("src", "funcs")
NEAR = os.path.join("work", "near-miss")
MATCH = [os.path.join(".venv", "bin", "python"), "tools/match.py"]


def diff_count(out):
    """Words differing, parsed from the last line match.py prints."""
    lines = [l for l in out.strip().splitlines() if l.strip()]
    if not lines:
        return 9999, "no output"
    last = lines[-1]
    m = re.search(r": (\d+) of \d+ words differ", last)
    if m:
        return int(m.group(1)), last
    if "MATCH" in last:
        return 0, last
    return 9999, last


def run_variants(func, variants):
    path = os.path.join(SRC, func + ".c")
    results = []
    for name, text in variants.items():
        with open(path, "w") as fh:
            fh.write(text)
        try:
            out = subprocess.run(MATCH + [func, "--show"], capture_output=True, text=True).stdout
        finally:
            if os.path.exists(path):
                os.remove(path)
        n, last = diff_count(out)
        results.append((n, name, last, text))
        print("%4d  %s" % (n, name))
    results.sort(key=lambda r: (r[0], r[1]))
    best = results[0]
    os.makedirs(NEAR, exist_ok=True)
    with open(os.path.join(NEAR, func + "-best.c"), "w") as fh:
        fh.write(best[3])
    print("\nbest: %s (%d)  %s" % (best[1], best[0], best[2]))
    print("written: %s" % os.path.join(NEAR, func + "-best.c"))
    return best


def main(argv):
    if len(argv) != 3:
        print(__doc__)
        return 2
    func, shapes = argv[1], argv[2]
    ns = {}
    with open(shapes) as fh:
        exec(compile(fh.read(), shapes, "exec"), ns)
    if "VARIANTS" not in ns:
        print("%s does not define VARIANTS" % shapes)
        return 2
    best = run_variants(func, ns["VARIANTS"])
    return 0 if best[0] == 0 else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv))
