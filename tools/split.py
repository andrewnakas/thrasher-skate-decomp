#!/usr/bin/env python3
"""Clean re-split of the executable, then derive the function table.

    python tools/split.py

1. Wipes asm/ and build/splat_src (splat leaves stale .s files behind; never
   split over an old tree).
2. Runs splat on config/splat.us.yaml.
3. Writes config/functions.us.csv (the Steward unit table and the progress
   denominator) and config/rodata.us.csv (every standalone rodata piece, with
   the single function that references it, if any: its "owner").

When a function is decompiled to C, the compiler emits that function's jump
tables, strings and float literals itself, so configure.py drops the rodata
pieces that function owns and places the C object's .rodata where they were.
"""
import csv
import hashlib
import re
import shutil
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ASM, BUILD, CONFIG, FUNCTIONS_CSV, ROOT  # noqa: E402

YAML = CONFIG / "splat.us.yaml"
RODATA_CSV = CONFIG / "rodata.us.csv"
STAMP = BUILD / "split.stamp"
SEGMENTS = ["game", "psyq"]

ADDR = re.compile(r"/\*\s*[0-9A-F]+\s+([0-9A-F]{8})\s")
SECTION = re.compile(r"^\s*\.section\s+(\.\w+)")
NONMATCH = re.compile(r"^nonmatching\s+(\w+)(?:,\s*(0x[0-9A-Fa-f]+))?")
GLABEL = re.compile(r"^\s*glabel\s+(\w+)")
DLABEL = re.compile(r"^\s*dlabel\s+(\w+)")
SYMREF = re.compile(r"\b((?:D|jtbl|jpt|str|flt|dbl)_[0-9A-F]{8}\w*)\b")


def split_inputs():
    """Files whose change requires a re-split (tools/fresh.py stamps these)."""
    files = [YAML, CONFIG / "symbol_addrs.us.txt", CONFIG / "psyq_syms.us.txt",
             CONFIG / "reloc_addrs.us.txt", ROOT / "requirements.txt", Path(__file__)]
    return [f for f in files if f.exists()]


def inputs_hash():
    h = hashlib.sha256()
    for f in split_inputs():
        h.update(f.name.encode() + b"\0" + f.read_bytes())
    return h.hexdigest()


def parse(path):
    """Return dict: kind (func|rodata), name, size, text_addr, rodata (list of addr), refs."""
    sect = ".text"
    info = {"name": None, "func": None, "size": 0, "text_addr": None,
            "rodata_addrs": [], "refs": set(), "labels": set()}
    for line in path.read_text().splitlines():
        m = SECTION.match(line)
        if m:
            sect = m.group(1)
            continue
        m = NONMATCH.match(line)
        if m and info["name"] is None:
            info["name"] = m.group(1)
            if m.group(2):
                info["size"] = int(m.group(2), 16)
        m = GLABEL.match(line)
        if m and sect == ".text" and info["func"] is None:
            info["func"] = m.group(1)
        m = DLABEL.match(line)
        if m:
            info["labels"].add(m.group(1))
        m = ADDR.search(line)
        if m:
            a = int(m.group(1), 16)
            if sect == ".text" and info["text_addr"] is None:
                info["text_addr"] = a
            elif sect == ".rodata":
                info["rodata_addrs"].append(a)
        if sect == ".text":
            info["refs"].update(SYMREF.findall(line))
    return info


def main():
    for d in (ASM, BUILD / "splat_src"):
        shutil.rmtree(d, ignore_errors=True)
    r = subprocess.run([sys.executable, "-m", "splat", "split", str(YAML)], cwd=ROOT,
                       capture_output=True, text=True)
    if r.returncode != 0:
        sys.stdout.write(r.stdout[-4000:] + r.stderr[-4000:])
        sys.exit("splat failed")

    funcs, pieces = [], []
    for seg in SEGMENTS:
        for p in sorted((ASM / "nonmatchings" / seg).glob("*.s")):
            info = parse(p)
            rel = p.relative_to(ROOT).as_posix()
            if info["func"] or info["text_addr"] is not None:  # dlabel'd data in .text counts too
                kind = "func" if info["func"] else "data"
                info["func"] = info["func"] or info["name"]
                ro = info["rodata_addrs"]
                funcs.append({"name": info["func"], "addr": info["text_addr"], "size": info["size"],
                              "segment": seg, "asm": rel, "kind": kind,
                              "rodata_addr": min(ro) if ro else None, "refs": info["refs"]})
            elif info["rodata_addrs"]:
                pieces.append({"name": info["name"], "addr": min(info["rodata_addrs"]),
                               "segment": seg, "asm": rel, "labels": info["labels"]})
            else:
                sys.exit(f"{rel}: neither a function nor rodata")

    funcs.sort(key=lambda f: f["addr"])
    for a, b in zip(funcs, funcs[1:]):  # data-in-text pieces carry no size
        if not a["size"]:
            a["size"] = b["addr"] - a["addr"]
    pieces.sort(key=lambda p: p["addr"])
    for a, b in zip(funcs, funcs[1:]):
        if a["addr"] + a["size"] > b["addr"]:
            sys.exit(f"overlap: {a['name']} runs into {b['name']}")

    # rodata ownership: a piece is owned by the one function that references it
    by_label = {}
    for p in pieces:
        p["users"] = set()
        for lab in p["labels"] | {p["name"]}:
            by_label[lab] = p
    for f in funcs:
        for ref in f["refs"]:
            if ref in by_label:
                by_label[ref]["users"].add(f["name"])
    for p in pieces:
        p["owner"] = next(iter(p["users"])) if len(p["users"]) == 1 else ""

    owned = {}
    for p in pieces:
        if p["owner"]:
            owned.setdefault(p["owner"], []).append(p["name"])

    with open(FUNCTIONS_CSV, "w", newline="") as fh:
        w = csv.writer(fh, lineterminator="\n")
        w.writerow(["name", "addr", "size", "segment", "kind", "asm", "rodata_addr", "owned_rodata"])
        for f in funcs:
            w.writerow([f["name"], f"{f['addr']:08X}", f"0x{f['size']:X}", f["segment"], f["kind"], f["asm"],
                        f"{f['rodata_addr']:08X}" if f["rodata_addr"] else "",
                        " ".join(owned.get(f["name"], []))])
    with open(RODATA_CSV, "w", newline="") as fh:
        w = csv.writer(fh, lineterminator="\n")
        w.writerow(["name", "addr", "segment", "asm", "owner"])
        for p in pieces:
            w.writerow([p["name"], f"{p['addr']:08X}", p["segment"], p["asm"], p["owner"]])

    BUILD.mkdir(exist_ok=True)
    STAMP.write_text(inputs_hash() + "\n")
    game = [f for f in funcs if f["segment"] == "game" and f["kind"] == "func"]
    print(f"split: {len(game)} game functions ({sum(f['size'] for f in game):,} bytes), "
          f"{len(funcs) - len(game)} PsyQ functions, {len(pieces)} rodata pieces "
          f"({sum(1 for p in pieces if p['owner'])} owned by one function)")


if __name__ == "__main__":
    main()
