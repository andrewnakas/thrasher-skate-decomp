#!/usr/bin/env python3
"""Start a function: write an m2c draft to src/funcs/<name>.c and try it.

    python tools/new_func.py func_80012345            # draft + match
    python tools/new_func.py func_80012345 --stdout   # just print the draft
    python tools/new_func.py --next                   # suggest small unclaimed-looking work

The draft is a starting point, never a finished match: m2c output usually needs
types, struct definitions and loop shapes fixed by hand. Context comes from
include/common.h plus every header under include/game/.
"""
import argparse
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import match  # noqa: E402
from common import BUILD, ROOT, load_functions, unit_path  # noqa: E402
import csv  # noqa: E402

M2C = ROOT / "toolchain" / "m2c" / "m2c.py"


def context():
    headers = ["common.h"] + sorted(str(p.relative_to(ROOT / "include"))
                                    for p in (ROOT / "include" / "game").rglob("*.h"))
    src = "".join(f'#include "{h}"\n' for h in headers)
    out = BUILD / "m2c_ctx.c"
    out.parent.mkdir(parents=True, exist_ok=True)
    r = subprocess.run(["cpp", "-undef", "-nostdinc", "-P", "-Iinclude", "-DM2CTX", "-"],
                       input=src, capture_output=True, text=True, cwd=ROOT)
    if r.returncode != 0:
        sys.exit("context preprocessing failed:\n" + r.stderr)
    out.write_text(r.stdout)
    return out


def draft(name):
    row = match.func_row(name)
    files = [ROOT / row["asm"]]
    owned = row["owned_rodata"].split()
    if owned:
        with open(ROOT / "config" / "rodata.us.csv") as fh:
            files += [ROOT / r["asm"] for r in csv.DictReader(fh) if r["name"] in owned]
    r = subprocess.run([sys.executable, str(M2C), "-t", "mipsel-gcc-c", "--context", str(context()),
                        *map(str, files), "-f", name], capture_output=True, text=True, cwd=ROOT)
    if r.returncode != 0:
        sys.exit("m2c failed:\n" + r.stderr[-2000:])
    return '#include "common.h"\n\n' + r.stdout


def suggest(n=20):
    done = {p.stem for p in (ROOT / "src" / "funcs").glob("*.c")}
    todo = [f for f in load_functions() if f["segment"] == "game" and f["kind"] == "func" and f["name"] not in done and f["size"] > 8]
    todo.sort(key=lambda f: f["size"])
    for f in todo[:n]:
        print(f"{f['name']}  {f['size']:#6x} bytes")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("name", nargs="?")
    ap.add_argument("--stdout", action="store_true")
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--next", action="store_true")
    a = ap.parse_args()
    if a.next or not a.name:
        suggest()
        return
    text = draft(a.name)
    if a.stdout:
        sys.stdout.write(text)
        return
    dest = unit_path(a.name)
    if dest.exists() and not a.force:
        sys.exit(f"{dest.relative_to(ROOT)} exists (use --force to overwrite your work)")
    dest.parent.mkdir(parents=True, exist_ok=True)
    dest.write_text(text)
    print(f"wrote {dest.relative_to(ROOT)}")
    res = match.compare(a.name)
    if res.error:
        print(f"draft does not compile yet: {res.error.strip().splitlines()[-1][:200]}")
    elif res.ok:
        print(f"{a.name}: MATCH straight from m2c (check it reads like real code)")
    else:
        print(f"{a.name}: {len(res.diffs)} instruction(s) differ: python tools/match.py {a.name} --show")


if __name__ == "__main__":
    main()
