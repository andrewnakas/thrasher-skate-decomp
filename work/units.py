#!/usr/bin/env python3
"""Shared candidate filter: is a game unit still to be done?

The `nonmatching <name>, 0x<size>` header at the top of
asm/nonmatchings/<segment>/func_*.s is **not** a completion signal. The splitter writes
that header for every function and never rewrites it after the unit is matched, so a
candidate list built from the asm alone keeps offering finished units — that is how
func_8002EFCC (matched in 61e3096) was handed to a sweep as a fresh target.

The only reliable signal is src/funcs/<name>.c: `gate.py --cold` guarantees that every
file in there matches, so existence == done. Every screen imports `done()` from here
rather than re-deriving the rule, and reports how many candidates it skipped so the real
size of the remaining work stays visible.

    from units import done, split
"""
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SRC = ROOT / "src" / "funcs"


def done(name):
    """True when the unit already has a matching C file."""
    return (SRC / (name + ".c")).exists()


def split(names):
    """(kept, skipped) — skipped are the names that already have a src file."""
    kept, skipped = [], []
    for n in names:
        (skipped if done(n) else kept).append(n)
    return kept, skipped


def report(total, kept):
    """The one-line footer every screen prints."""
    skipped = total - len(kept)
    return f"-- {len(kept)} candidates ({skipped} skipped: already matched)"


if __name__ == "__main__":
    names = sorted(p.stem for p in SRC.glob("func_*.c"))
    print(f"matched units in src/funcs: {len(names)}")
