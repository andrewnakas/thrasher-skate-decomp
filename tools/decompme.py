#!/usr/bin/env python3
"""Everything needed to open a decomp.me scratch for one function.

    python tools/decompme.py func_80012345 [--out work/scratch]

Writes <out>/<name>.s (target asm, with its owned rodata) and <out>/ctx.c (the
preprocessed headers), and prints the compiler settings to choose. On
decomp.me pick platform "PlayStation" and the gcc 2.8.1 PSX compiler with
maspsx, then paste the flags below. Put the scratch link in a comment above the
function when you merge it.
"""
import argparse
import csv
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import match  # noqa: E402
import new_func  # noqa: E402
from common import ROOT, compiler_config, file_cflags, unit_path  # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("name")
    ap.add_argument("--out", default=str(ROOT / "work" / "scratch"))
    a = ap.parse_args()
    row = match.func_row(a.name)
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    parts = [(ROOT / row["asm"]).read_text()]
    owned = row["owned_rodata"].split()
    if owned:
        with open(ROOT / "config" / "rodata.us.csv") as fh:
            parts += [(ROOT / r["asm"]).read_text() for r in csv.DictReader(fh) if r["name"] in owned]
    (out / f"{a.name}.s").write_text("\n".join(parts))
    (out / "ctx.c").write_text(new_func.context().read_text())
    cfg = compiler_config()
    flags = cfg["compiler"]["cflags"] + (file_cflags(unit_path(a.name)) if unit_path(a.name).exists() else [])
    print(f"asm:      {out / (a.name + '.s')}")
    print(f"context:  {out / 'ctx.c'}")
    print(f"compiler: {cfg['compiler']['name']} + maspsx {' '.join(cfg['maspsx']['args'])}")
    print(f"flags:    {' '.join(f for f in flags if f not in ('-quiet', '-w'))}")


if __name__ == "__main__":
    main()
