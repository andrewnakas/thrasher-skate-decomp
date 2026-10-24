"""Shared paths and config for every tool. Import, don't copy."""
import csv
import os
import re
import tomllib
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TOOLCHAIN = ROOT / "toolchain"
BIN = TOOLCHAIN / "bin"
ASM = ROOT / "asm"
BUILD = Path(os.environ.get("THRASHER_BUILD", ROOT / "build"))
SRC_FUNCS = ROOT / "src" / "funcs"
CONFIG = ROOT / "config"
FUNCTIONS_CSV = CONFIG / "functions.us.csv"
EXE = ROOT / "disc" / "files" / "SLUS_009.35"
EXE_SHA1 = "16829afba66533e2645bf87af2774671b06ff36b"
GP = 0x80089F18
VRAM = 0x80010000

UNIT_RE = re.compile(r"^func_([0-9A-F]{8})\.c$")
CFLAGS_RE = re.compile(r"^/\*\s*cflags:(.*?)\*/")


def tool(name):
    """A binutils tool: toolchain/bin first, then PATH."""
    p = BIN / name
    return str(p) if p.exists() else name


def compiler_config():
    return tomllib.loads((TOOLCHAIN / "compiler.toml").read_text())


def file_cflags(path):
    """Per-file flags from a first-line /* cflags: ... */ comment."""
    with open(path) as f:
        m = CFLAGS_RE.match(f.readline())
    return m.group(1).split() if m else []


def load_functions():
    """Rows of config/functions.us.csv: name, addr (int), size (int), segment, asm."""
    rows = []
    with open(FUNCTIONS_CSV) as f:
        for r in csv.DictReader(f):
            r["addr"] = int(r["addr"], 16)
            r["size"] = int(r["size"], 16)
            rows.append(r)
    return rows


def unit_path(name):
    return SRC_FUNCS / f"{name}.c"
