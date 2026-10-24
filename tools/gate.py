#!/usr/bin/env python3
"""The match gate: every unit file must match, alone, with no side effects.

    python tools/gate.py              # all of src/funcs (cached per input hash)
    python tools/gate.py --cold       # ignore the cache
    python tools/gate.py FILE...      # just these (still a full check of each)

For each src/funcs/func_X.c:
  - it compiles through the pinned pipeline and MATCHes the original
    instruction for instruction, relocations resolved (tools/match.py)
  - its object defines exactly one function, func_X, and nothing else in .text
  - it has no .data/.sdata/.bss/.sbss of its own (data stays in the asm until
    it is migrated deliberately as a tooling change)
  - it has .rodata only if the original function owned rodata, and then the
    same amount (jump tables, strings and float literals it emits itself)

Because every merged unit is re-checked whenever a shared input changes
(tools/, include/, config/, toolchain/), a change that breaks an earlier match
fails here: zero regressions by construction.

Output for Steward: "PROBLEM <file>: <why>" and "DIFFLINE <file>: yours | game".
Exit 0 only if everything passes.
"""
import argparse
import hashlib
import json
import os
import sys
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import match  # noqa: E402
from common import BUILD, ROOT, SRC_FUNCS, UNIT_RE  # noqa: E402

SHARED = ["tools", "include", "config", "toolchain/compiler.toml", "toolchain/checksums.sha256",
          "requirements.txt"]
CACHE = BUILD / "gate_cache.json"
DATA_SECTIONS = (".data", ".sdata", ".bss", ".sbss")
MAX_DIFFLINES = 6


def shared_hash():
    h = hashlib.sha256()
    for s in SHARED:
        p = ROOT / s
        files = sorted(p.rglob("*")) if p.is_dir() else [p]
        for f in files:
            if f.is_file() and "__pycache__" not in f.parts:
                h.update(str(f.relative_to(ROOT)).encode() + b"\0" + f.read_bytes())
    return h.hexdigest()


def check(path):
    """Return (file name, list of problems, list of difflines)."""
    path = Path(path)
    name = path.stem
    if not UNIT_RE.match(path.name):
        return path.name, ["not a unit file name (func_XXXXXXXX.c)"], []
    try:
        row = match.func_row(name)
    except KeyError as e:
        return path.name, [str(e)], []
    res = match.compare(name, path, outdir=BUILD / "gate" / str(os.getpid()))
    if res.error:
        return path.name, [res.error.strip().splitlines()[-1][:300]], []
    problems, lines = [], []
    o = res.ours
    extra = [d for d in o.defined if d != name]
    if extra:
        problems.append(f"defines other functions too ({', '.join(extra)}): one function per file")
    for s in DATA_SECTIONS:
        if o.sections.get(s, 0):
            problems.append(f"has its own {s} ({o.sections[s]} bytes): reference data by extern symbol")
    ro = o.sections.get(".rodata", 0) + o.sections.get(".rdata", 0)
    owns = match.rodata_base(row) is not None
    if ro and not owns:
        problems.append(f"emits {ro} bytes of .rodata but the original function owns none "
                        "(a literal or table that lives elsewhere: use its D_ symbol)")
    if not res.ok:
        n = len(res.target.words)
        problems.append(f"does not match: {len(res.diffs)} instruction(s) differ ({n} in the original)"
                        + ("" if n == len(o.words) else f" (size {len(o.words) * 4:#x}, game {n * 4:#x})"))
        for i in res.diffs[:MAX_DIFFLINES]:
            a = row["addr"] + i * 4
            yours = match.disasm(o.words[i], a, o.relocs.get(i)) if i < len(o.words) else "-"
            game = match.disasm(res.target.words[i], a, res.target.relocs.get(i)) if i < n else "-"
            lines.append(f"{a:08X} {yours} | {game}")
    return path.name, problems, lines


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("files", nargs="*")
    ap.add_argument("--cold", action="store_true")
    ap.add_argument("-j", type=int, default=os.cpu_count())
    a = ap.parse_args()

    import fresh
    fresh.ensure()

    files = [Path(f) for f in a.files] or sorted(SRC_FUNCS.glob("*.c"))
    stray = [f for f in SRC_FUNCS.glob("*") if f.suffix != ".c" and f.is_file()]
    sh = shared_hash()
    cache = {}
    if CACHE.exists() and not a.cold:
        c = json.loads(CACHE.read_text())
        if c.get("shared") == sh:
            cache = c.get("ok", {})
    todo, passed = [], []
    for f in files:
        key = hashlib.sha256(f.read_bytes()).hexdigest() if f.exists() else None
        if key and cache.get(f.name) == key:
            passed.append(f.name)
        else:
            todo.append(f)

    bad = 0
    for f in stray:
        print(f"PROBLEM {f.name}: only func_XXXXXXXX.c files belong in src/funcs")
        bad += 1
    with ProcessPoolExecutor(max_workers=max(1, a.j)) as ex:
        for f, (fname, problems, lines) in zip(todo, ex.map(check, todo)):
            if problems:
                bad += 1
                for p in problems:
                    print(f"PROBLEM {fname}: {p}")
                for l in lines:
                    print(f"DIFFLINE {fname}: {l}")
            else:
                passed.append(fname)
                if f.resolve().parent == SRC_FUNCS.resolve():
                    cache[fname] = hashlib.sha256(f.read_bytes()).hexdigest()

    CACHE.parent.mkdir(parents=True, exist_ok=True)
    CACHE.write_text(json.dumps({"shared": sh, "ok": {k: v for k, v in cache.items() if v}}, indent=0))
    total = len(files)
    print(f"gate: {len(passed)}/{total} unit files match ({len(todo)} checked, "
          f"{total - len(todo)} cached)" + (f", {bad} failing" if bad else ""))
    if bad:
        print("GATE FAIL")
        sys.exit(1)
    print("GATE PASS")


if __name__ == "__main__":
    main()
