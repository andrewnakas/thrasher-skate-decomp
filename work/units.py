#!/usr/bin/env python3
"""Shared candidate filter: can this game unit still become a `src/funcs` file?

Two filters, both learned the hard way:

1. **Done.** The `nonmatching <name>, 0x<size>` header at the top of
   asm/nonmatchings/<segment>/func_*.s is **not** a completion signal. The splitter writes
   that header for every function and never rewrites it after the unit is matched, so a
   candidate list built from the asm alone keeps offering finished units — that is how
   func_8002EFCC (matched in 61e3096) was handed to a sweep as a fresh target. The only
   reliable signal is src/funcs/<name>.c: `gate.py --cold` guarantees that every file in
   there matches, so existence == done.

2. **Writable in C.** Some functions are not compiler output at all: they hold
   hand-assembled GTE code (`cfc2`/`mtc2`/`ctc2`/`swc2`/`rtps`/`rtpt`/`nccs`, …) or the
   3000's `sub`/`div`/`break` forms. `include/gte_macros.inc` is assembler-only and
   `tools/scan.py` forbids inline asm, so no C spelling can ever match them. Handing them to
   a sweep costs a pass its shapes (25 of the 193 live 40+ word candidates were this class),
   so every screen filters them out and reports how many it dropped.

Screens import `split` / `report` from here rather than re-deriving either rule.

    from units import split, report
"""
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SRC = ROOT / "src" / "funcs"
ASM = ROOT / "asm" / "nonmatchings"

# spimdisasm marks every hand-assembled instruction it cannot decode inline, and the cop2 /
# GTE forms it does decode carry these mnemonics. Either means "not compiler output". Note
# `divu`/`break` are deliberately absent: gcc emits them for ordinary C division.
HANDWRITTEN = re.compile(
    r"handwritten instruction|/\*[^*]*\*/\s+("
    r"cfc2|ctc2|mfc2|mtc2|lwc2|swc2|rtps|rtpt|nclip|nccs|nct|cdp|dpcl|dpcs|dpct|"
    r"intpl|mvmva|sqr|gpf|gpl|srt|ldr|stp|avsz3|avsz4"
    r")\b",
    re.M,
)


def done(name):
    """True when the unit already has a matching C file."""
    return (SRC / (name + ".c")).exists()


def handwritten(name):
    """True when the unit's asm holds instructions a C compiler cannot emit."""
    path = ASM / "game" / (name + ".s")
    try:
        text = path.read_text(errors="replace")
    except FileNotFoundError:
        return False
    return bool(HANDWRITTEN.search(text))


def split(names):
    """(kept, skipped) — skipped are done already, or are hand-written asm, not C."""
    kept, skipped = [], []
    for n in names:
        (kept if not done(n) and not handwritten(n) else skipped).append(n)
    return kept, skipped


def report(total, kept, skipped=()):
    """The one-line footer every screen prints, with both skip reasons broken out."""
    skipped = list(skipped)
    was_done = sum(1 for n in skipped if done(n))
    was_asm = len(skipped) - was_done
    return (f"-- {len(kept)} candidates ({was_done} skipped: already matched, "
            f"{was_asm} skipped: not C / hand-written asm)")


if __name__ == "__main__":
    names = sorted(p.stem for p in SRC.glob("func_*.c"))
    print(f"matched units in src/funcs: {len(names)}")
