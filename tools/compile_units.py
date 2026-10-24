#!/usr/bin/env python3
"""Compile every unit file and check the object rules that need no disc.

    python tools/compile_units.py [FILE...]

Public CI runs this (GitHub has no disc): every src/funcs file must compile
through the pinned pipeline, define exactly its own function and carry no
.data/.sdata/.bss/.sbss. Whether it MATCHES is decided on the judge box
(tools/gate.py), because that needs the original executable.
"""
import sys
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import cc  # noqa: E402
from common import BUILD, SRC_FUNCS, compiler_config  # noqa: E402

from elftools.elf.elffile import ELFFile  # noqa: E402

DATA = (".data", ".sdata", ".bss", ".sbss")


def one(path):
    path = Path(path)
    out = BUILD / "ci" / f"{path.stem}.o"
    cfg = compiler_config()
    try:
        cc.assemble(cc.c_to_asm(path, cfg), out, cfg)
    except cc.StageError as e:
        return path.name, [str(e).strip().splitlines()[-1][:300]]
    probs = []
    with open(out, "rb") as f:
        elf = ELFFile(f)
        for s in DATA:
            sec = elf.get_section_by_name(s)
            if sec is not None and sec.data_size:
                probs.append(f"has its own {s} ({sec.data_size} bytes)")
        funcs = [s.name for s in elf.get_section_by_name(".symtab").iter_symbols()
                 if s["st_info"]["type"] == "STT_FUNC" and s["st_shndx"] != "SHN_UNDEF"]
        if funcs != [path.stem]:
            probs.append(f"defines {funcs or 'no function'}; must define exactly {path.stem}")
    return path.name, probs


def main():
    files = [Path(a) for a in sys.argv[1:]] or sorted(SRC_FUNCS.glob("*.c"))
    bad = 0
    with ProcessPoolExecutor() as ex:
        for name, probs in ex.map(one, files):
            for p in probs:
                print(f"PROBLEM {name}: {p}")
            bad += bool(probs)
    print(f"compile_units: {len(files) - bad}/{len(files)} ok")
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
