#!/usr/bin/env python3
"""Forbidden-construct gate for unit files. Text only: needs no disc or toolchain.

    python tools/scan.py                 # every src/funcs/*.c
    python tools/scan.py FILE...         # just these

A matching function must be plain C that a 1999 compiler could have been fed.
Rejected (each prints "PROBLEM <file>: <why>" for Steward's report):
  - inline asm in any spelling, register pinning (register x asm("$s0")),
    .set noreorder, #pragma, INCLUDE_ASM/INCLUDE_RODATA/GLOBAL_ASM
  - __attribute__((section(...))) and other placement tricks
  - hard-coded RAM addresses (0x80010000..0x801FFFFF): use the symbol
  - #include of anything that is not a header
  - a file name that is not func_XXXXXXXX.c for a function in the table
  - per-file cflags outside toolchain/compiler.toml [per_file].allowed_cflags

Object-level rules (exactly one function, no .data/.bss of its own, rodata
only if the original function owned rodata) are checked by tools/gate.py.
"""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import CFLAGS_RE, FUNCTIONS_CSV, ROOT, SRC_FUNCS, UNIT_RE, compiler_config  # noqa: E402

RULES = [
    (re.compile(r"\b__asm__\b|\b__asm\b|\basm\s*\(|\basm\s+volatile\b|\basm\s+__volatile__\b"),
     "inline asm is not allowed: write C (register pinning and asm blocks fake a match)"),
    (re.compile(r"\bregister\b[^;]*\b(?:asm|__asm__)\b"), "register pinning is not allowed"),
    (re.compile(r"\.set\s+(?:no)?reorder|\.set\s+(?:no)?at\b"), "assembler directives are not allowed"),
    (re.compile(r"^\s*#\s*pragma\b", re.M), "#pragma is not allowed"),
    (re.compile(r"\b(?:INCLUDE_ASM|INCLUDE_RODATA|GLOBAL_ASM|NON_MATCHING)\b"),
     "asm include macros do not belong in a unit file: a unit is the finished C function"),
    (re.compile(r"__attribute__\s*\(\(\s*(?:section|aligned|used|naked|noinline)\b"),
     "placement/linkage attributes are not allowed"),
    (re.compile(r"^\s*#\s*include\s*[<\"][^>\"]*\.(?:c|s|S|inc|txt)[>\"]", re.M),
     "only headers may be included"),
]
ADDR_LIT = re.compile(r"\b0x(80[01][0-9A-Fa-f]{5})\b")


def strip_comments(src):
    """Remove comments but keep strings (string contents are checked for asm tricks too)."""
    out, i, n = [], 0, len(src)
    while i < n:
        if src.startswith("/*", i):
            j = src.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append("\n" * src.count("\n", i, j))
            i = j
        elif src.startswith("//", i):
            j = src.find("\n", i)
            i = n if j < 0 else j
        elif src[i] in "\"'":
            q, j = src[i], i + 1
            while j < n and src[j] != q:
                j += 2 if src[j] == "\\" else 1
            out.append(src[i:j + 1])
            i = j + 1
        else:
            out.append(src[i])
            i += 1
    return "".join(out)


def known_functions():
    if not FUNCTIONS_CSV.exists():
        return None
    return {line.split(",", 1)[0] for line in FUNCTIONS_CSV.read_text().splitlines()[1:]}


def scan_file(path, allowed, funcs):
    problems = []
    name = path.name
    m = UNIT_RE.match(name)
    if not m:
        return [f"file name must be func_XXXXXXXX.c (uppercase hex address), got {name}"]
    if funcs is not None and name[:-2] not in funcs:
        problems.append(f"{name[:-2]} is not a function in config/functions.us.csv")
    text = path.read_text(errors="replace")
    first = text.split("\n", 1)[0]
    cm = CFLAGS_RE.match(first)
    if cm:
        for flag in cm.group(1).split():
            if flag not in allowed:
                problems.append(f"cflag {flag} is not in toolchain/compiler.toml allowed_cflags")
    elif "cflags:" in text:
        problems.append("a /* cflags: */ comment only works on the very first line")
    code = strip_comments(text)
    for rx, why in RULES:
        if rx.search(code):
            problems.append(why)
    for lit in ADDR_LIT.findall(code):
        if 0x80010000 <= int(lit, 16) < 0x80200000:
            problems.append(f"hard-coded address 0x{lit}: reference the symbol (D_{lit.upper()}) instead")
    return problems


def main(argv):
    files = [Path(a) for a in argv] or sorted(SRC_FUNCS.glob("*"))
    allowed = set(compiler_config()["per_file"]["allowed_cflags"])
    funcs = known_functions()
    nbad = 0
    for f in files:
        if f.is_dir() or f.name.startswith("."):
            continue
        if f.suffix != ".c":
            print(f"PROBLEM {f.name}: only func_XXXXXXXX.c files belong in src/funcs")
            nbad += 1
            continue
        for p in scan_file(f, allowed, funcs):
            print(f"PROBLEM {f.name}: {p}")
            nbad += 1
    n = len([f for f in files if f.suffix == ".c"])
    print(f"scan: {n} files, {nbad} problems")
    return 1 if nbad else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
