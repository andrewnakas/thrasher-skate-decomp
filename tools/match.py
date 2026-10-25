#!/usr/bin/env python3
"""Compile one function and compare it with the original, instruction by instruction.

    python tools/match.py func_80012345            # MATCH / N words differ
    python tools/match.py func_80012345 --show     # side-by-side diff, !! on differences
    python tools/match.py func_80012345 --src draft.c   # try a file outside src/funcs

Relocations are not masked away: every relocated field is resolved to the
original address it points at (named symbol, the function's own rodata, or a
local label) and those addresses must be equal. A jump to the wrong label or a
load from the wrong table is a mismatch. (thps64 once masked local jumps and
merged a non-match; never again.)

Library use: compare(name, src=None, **pipeline_overrides) -> Result
"""
import argparse
import csv
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import cc  # noqa: E402
from common import ASM, BUILD, CONFIG, ROOT, compiler_config, load_functions, unit_path  # noqa: E402

from elftools.elf.elffile import ELFFile  # noqa: E402
from elftools.elf.relocation import RelocationSection  # noqa: E402

R_MIPS_32, R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16, R_MIPS_GPREL16, R_MIPS_PC16 = 2, 4, 5, 6, 7, 10
RTYPE = {2: "32", 4: "26", 5: "hi", 6: "lo", 7: "gprel", 10: "pc16"}
NAMED_ADDR = re.compile(r"^(?:\.L|[A-Za-z]+_)([0-9A-F]{8})$")
LABEL_DEF = re.compile(r"^\s*(?:glabel|dlabel|jlabel|alabel|ehlabel)\s+(\S+)")
OFF_ADDR = re.compile(r"/\*\s*[0-9A-F]+\s+([0-9A-F]{8})\s")
SYMFILE = re.compile(r"^\s*(\S+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")

_symbols = None


def symbols():
    """name -> original address, from config symbol files and every asm label."""
    global _symbols
    if _symbols is not None:
        return _symbols
    syms = {}
    for f in CONFIG.glob("*.txt"):
        for line in f.read_text().splitlines():
            m = SYMFILE.match(line)
            if m:
                syms[m.group(1)] = int(m.group(2), 16)
    for s in ASM.rglob("*.s"):
        pending = None
        for line in s.read_text().splitlines():
            m = LABEL_DEF.match(line)
            if m:
                pending = m.group(1)
                continue
            if pending:
                m = OFF_ADDR.search(line)
                if m:
                    syms.setdefault(pending, int(m.group(1), 16))
                    pending = None
    _symbols = syms
    return syms


def sym_addr(name):
    a = symbols().get(name)
    if a is None:
        m = NAMED_ADDR.match(name)
        if m:
            a = int(m.group(1), 16)
    return a


def sext16(v):
    return v - 0x10000 if v & 0x8000 else v


@dataclass
class Obj:
    words: list
    relocs: dict          # word index -> (type, resolved target address or None, symbol)
    size: int
    defined: list = field(default_factory=list)   # global function symbols in .text
    sections: dict = field(default_factory=dict)  # name -> size


def read_obj(path, func_name, func_addr, rodata_base):
    with open(path, "rb") as fh:
        elf = ELFFile(fh)
        text = elf.get_section_by_name(".text")
        symtab = elf.get_section_by_name(".symtab")
        sections = {s.name: s.data_size for s in elf.iter_sections() if s.name.startswith(".")}
        start = None
        size = None
        defined = []
        for s in symtab.iter_symbols():
            if s["st_info"]["type"] == "STT_FUNC" and s["st_shndx"] != "SHN_UNDEF":
                if elf.get_section(s["st_shndx"]).name == ".text":
                    defined.append(s.name)
                    if s.name == func_name:
                        start, size = s["st_value"], s["st_size"]
        if start is None:
            raise ValueError(f"{path}: {func_name} not defined in .text")
        if not size:
            size = text.data_size - start
        data = text.data()[start:start + size]
        words = [int.from_bytes(data[i:i + 4], "little") for i in range(0, len(data) - 3, 4)]

        relocs = {}
        rel = elf.get_section_by_name(".rel.text")
        last_hi = {}
        if isinstance(rel, RelocationSection):
            entries = sorted(rel.iter_relocations(), key=lambda r: r["r_offset"])
            for r in entries:
                off = r["r_offset"] - start
                if off < 0 or off >= size:
                    continue
                i = off // 4
                t = r["r_info_type"]
                sym = symtab.get_symbol(r["r_info_sym"])
                if sym["st_info"]["type"] == "STT_SECTION":
                    sec = elf.get_section(sym["st_shndx"]).name
                    base = {".text": func_addr - start}.get(sec)
                    if sec in (".rodata", ".rdata"):
                        base = rodata_base
                    name = sec
                else:
                    name = sym.name
                    base = sym_addr(name) if sym["st_shndx"] == "SHN_UNDEF" or not name.startswith(".") else None
                    if sym["st_shndx"] != "SHN_UNDEF" and elf.get_section(sym["st_shndx"]).name == ".text":
                        base = func_addr - start + sym["st_value"]
                w = words[i]
                if t == R_MIPS_26:
                    addend = (w & 0x3FFFFFF) << 2
                    if sym["st_info"]["type"] != "STT_SECTION" and sym["st_shndx"] == "SHN_UNDEF":
                        addend = 0 if (w & 0x3FFFFFF) == 0 else addend
                elif t == R_MIPS_HI16:
                    lo = next((x for x in entries if x["r_offset"] > r["r_offset"]
                               and x["r_info_type"] == R_MIPS_LO16
                               and x["r_info_sym"] == r["r_info_sym"]), None)
                    lo_v = sext16(int.from_bytes(text.data()[lo["r_offset"]:lo["r_offset"] + 2], "little")) if lo else 0
                    addend = ((w & 0xFFFF) << 16) + lo_v
                    last_hi[r["r_info_sym"]] = w & 0xFFFF
                elif t == R_MIPS_LO16:
                    addend = (last_hi.get(r["r_info_sym"], 0) << 16) + sext16(w & 0xFFFF)
                elif t == R_MIPS_PC16:
                    # A branch to a jlabel: the assembler leaves -1 in the field as a
                    # placeholder and the linker writes (S - P - 4) >> 2, so the target
                    # is the symbol itself (cross-checked against branch_target below).
                    addend = 0
                else:
                    addend = sext16(w & 0xFFFF)
                target = base + addend if base is not None else None
                relocs[i] = (t, target, name)
        return Obj(words, relocs, size, defined, sections)


def mask(t, w):
    return w & {R_MIPS_26: 0xFC000000}.get(t, 0xFFFF0000)


def branch_target(w, addr):
    """Where a resolved branch word goes: the branch to an external/global label keeps a
    PC16 relocation, a branch to a local one is already folded into the offset."""
    return addr + 4 + sext16(w & 0xFFFF) * 4


@dataclass
class Result:
    name: str
    ok: bool
    diffs: list
    target: Obj = None
    ours: Obj = None
    error: str = ""


def func_row(name):
    for f in load_functions():
        if f["name"] == name:
            return f
    raise KeyError(f"{name} is not in config/functions.us.csv")


def rodata_base(row):
    addrs = []
    if row["rodata_addr"]:
        addrs.append(int(row["rodata_addr"], 16))
    owned = row["owned_rodata"].split()
    if owned:
        with open(CONFIG / "rodata.us.csv") as fh:
            addrs += [int(r["addr"], 16) for r in csv.DictReader(fh) if r["name"] in owned]
    return min(addrs) if addrs else None


def compare(name, src=None, cc1=None, cflags=None, maspsx_args=None, as_flags=None, outdir=None):
    row = func_row(name)
    addr = row["addr"]
    src = Path(src) if src else unit_path(name)
    outdir = Path(outdir) if outdir else BUILD / "match"
    cfg = compiler_config()
    ours_o = outdir / f"{name}.o"
    target_o = outdir / "target" / f"{name}.o"
    try:
        cc.assemble(cc.asm_wrapper(ROOT / row["asm"]), target_o, cfg)
        asm = cc.c_to_asm(src, cfg, cc1, cflags, maspsx_args)
        cc.assemble(asm, ours_o, cfg, as_flags)
    except cc.StageError as e:
        return Result(name, False, [], error=str(e))
    base = rodata_base(row)
    try:
        t = read_obj(target_o, name, row["addr"], base)
        o = read_obj(ours_o, name, row["addr"], base)
    except ValueError as e:
        return Result(name, False, [], error=str(e))
    diffs = []
    for i in range(max(len(t.words), len(o.words))):
        tw = t.words[i] if i < len(t.words) else None
        ow = o.words[i] if i < len(o.words) else None
        tr, orr = t.relocs.get(i), o.relocs.get(i)
        if tw is None or ow is None:
            diffs.append(i)
        elif tr or orr:
            mt = mask(tr[0], tw) if tr else tw & 0xFFFF0000
            mo = mask(orr[0], ow) if orr else ow & 0xFFFF0000
            ok = (tr and orr and tr[0] == orr[0] and tr[1] is not None and tr[1] == orr[1]
                  and mt == mo)
            if not ok and mt == mo:
                # A jlabel target: the original object keeps a PC16 relocation, our compile
                # folds the same branch to the label. Compare resolved target addresses.
                here = addr + i * 4
                if tr and not orr and tr[0] == R_MIPS_PC16:
                    ok = tr[1] is not None and tr[1] == branch_target(ow, here)
                elif orr and not tr and orr[0] == R_MIPS_PC16:
                    ok = orr[1] is not None and orr[1] == branch_target(tw, here)
            if not ok:
                diffs.append(i)
        elif tw != ow:
            diffs.append(i)
    return Result(name, not diffs, diffs, t, o)


def disasm(word, addr, reloc):
    from rabbitizer import Instruction
    s = Instruction(word, vram=addr).disassemble()
    if reloc:
        t, target, sym = reloc
        tgt = f"0x{target:08X}" if target is not None else "?"
        s = f"{s:<34} [{RTYPE.get(t, t)} {sym if not sym.startswith('.') else ''} -> {tgt}]"
    return s


def show(res, addr):
    t, o = res.target, res.ours
    print(f"{'game':<62} | yours")
    for i in range(max(len(t.words), len(o.words))):
        a = addr + i * 4
        l = disasm(t.words[i], a, t.relocs.get(i)) if i < len(t.words) else ""
        r = disasm(o.words[i], a, o.relocs.get(i)) if i < len(o.words) else ""
        mark = "!!" if i in res.diffs else "  "
        print(f"{mark} {a:08X} {l:<50} | {r}")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("name")
    ap.add_argument("--src")
    ap.add_argument("--show", action="store_true")
    a = ap.parse_args()
    res = compare(a.name, a.src)
    if res.error:
        print(f"{a.name}: ERROR {res.error}")
        sys.exit(2)
    if a.show:
        show(res, func_row(a.name)["addr"])
    if res.ok:
        print(f"{a.name}: MATCH")
    else:
        print(f"{a.name}: {len(res.diffs)} of {len(res.target.words)} words differ"
              + ("" if len(res.target.words) == len(res.ours.words)
                 else f" (size {len(res.ours.words) * 4:#x}, want {len(res.target.words) * 4:#x})"))
        sys.exit(1)


if __name__ == "__main__":
    main()
