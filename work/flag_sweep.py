#!/usr/bin/env python3
"""Sweep the allowed per-file cflags over one draft and report the diff count."""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import match  # noqa: E402

FLAGS = ["-O1", "-O0", "-O3", "-fno-strength-reduce", "-fno-inline",
         "-fno-schedule-insns", "-fno-schedule-insns2", "-G0", "-G4",
         "-mno-split-addresses", "-funsigned-char", "-fsigned-char"]

name = sys.argv[1]
src = Path(sys.argv[2]).read_text()
out = ROOT / "work" / "permute-work" / name
out.mkdir(parents=True, exist_ok=True)
best = None
for flag in FLAGS:
    p = out / "flag.c"
    p.write_text(f"/* cflags: {flag} */\n" + src)
    r = match.compare(name, src=p)
    if r.error:
        print(f"{flag:24s} error")
        continue
    n = len(r.diffs)
    print(f"{flag:24s} {n:3d} words differ" + ("  MATCH" if n == 0 else ""))
    if best is None or n < best[0]:
        best = (n, flag, p.read_text())
if best and best[0] == 0:
    (out / "MATCH-flags.c").write_text(best[2])
