#!/usr/bin/env python3
"""The one compile driver. Every C file and every asm file is built through here.

    python tools/cc.py c   src/funcs/func_80012345.c  build/x.o
    python tools/cc.py asm asm/nonmatchings/game/func_80012345.s build/y.o
    python tools/cc.py c   in.c out.o --print-asm     # stop after maspsx, print asm

C pipeline:  cpp | cc1 | maspsx | mipsel-linux-gnu-as   (flags: toolchain/compiler.toml)

Each stage runs as its own subprocess and its exit status is checked, and an
empty or missing object is an error. A shell pipe would hide a missing tool
and leave an empty .o that ninja happily links (sotn-decomp lesson).

Experiments (compiler identification) may override the pipeline with
--cc1, --cflags, --maspsx-args, --as-flags; gates never pass these.
"""
import argparse
import os
import shlex
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, compiler_config, file_cflags, tool  # noqa: E402

PY = sys.executable


class StageError(Exception):
    pass


def run(stage, argv, data):
    try:
        p = subprocess.run(argv, input=data, capture_output=True, cwd=ROOT)
    except FileNotFoundError:
        raise StageError(f"{stage}: tool not found: {argv[0]} (run python toolchain/setup.py)")
    if p.returncode != 0:
        raise StageError(f"{stage} failed ({p.returncode}):\n{p.stderr.decode(errors='replace')}")
    return p.stdout


def c_to_asm(src, cfg, cc1=None, cflags=None, maspsx_args=None, extra_cpp=(), depfile=None, target=None):
    c = cfg["compiler"]
    flags = list(cflags if cflags is not None else c["cflags"])
    for f in file_cflags(src):  # later flags win in gcc
        flags.append(f)
    dep = ["-MMD", "-MF", str(depfile), "-MT", str(target)] if depfile else []
    pre = run("cpp", ["cpp", *c["cppflags"], *dep, *extra_cpp, str(src)], b"")
    cc1 = cc1 or str(ROOT / c["cc1"])
    s = run("cc1", [cc1, *flags], pre)
    if not s.strip():
        raise StageError("cc1 produced no output")
    margs = maspsx_args if maspsx_args is not None else cfg["maspsx"]["args"]
    return run("maspsx", [PY, str(ROOT / "toolchain/maspsx/maspsx.py"), *margs], s)


def assemble(asm_text, out, cfg, as_flags=None):
    flags = as_flags if as_flags is not None else cfg["as"]["flags"]
    out = Path(out)
    out.parent.mkdir(parents=True, exist_ok=True)
    tmp = out.with_suffix(out.suffix + ".tmp")
    run("as", [tool("mipsel-linux-gnu-as"), *flags, "-o", str(tmp), "--"], asm_text)
    if not tmp.exists() or tmp.stat().st_size == 0:
        raise StageError("as produced an empty object")
    os.replace(tmp, out)


def asm_wrapper(path):
    """splat's per-function .s files are made for INCLUDE_ASM; give them a preamble."""
    rel = os.path.relpath(path, ROOT)
    return (f'.include "macro.inc"\n.set noat\n.set noreorder\n.section .text\n'
            f'.include "{rel}"\n').encode()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("kind", choices=["c", "asm"])
    ap.add_argument("src")
    ap.add_argument("out", nargs="?")
    ap.add_argument("--print-asm", action="store_true")
    ap.add_argument("--cc1")
    ap.add_argument("--cflags")
    ap.add_argument("--maspsx-args")
    ap.add_argument("--as-flags")
    ap.add_argument("-D", action="append", default=[])
    ap.add_argument("--depfile")
    a = ap.parse_args()
    cfg = compiler_config()
    split = lambda s: shlex.split(s) if s is not None else None  # noqa: E731
    try:
        if a.kind == "c":
            text = c_to_asm(a.src, cfg, a.cc1, split(a.cflags), split(a.maspsx_args),
                            [f"-D{d}" for d in a.D], a.depfile, a.out)
            if a.print_asm:
                sys.stdout.write(text.decode())
                return
        else:
            text = asm_wrapper(a.src)
        if not a.out:
            sys.exit("output path required")
        assemble(text, a.out, cfg, split(a.as_flags))
    except StageError as e:
        sys.exit(f"{a.src}: {e}")


if __name__ == "__main__":
    main()
