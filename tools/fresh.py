#!/usr/bin/env python3
"""Re-split automatically when splat's inputs changed since the last split.

    python tools/fresh.py        # (also called by gate.py and build.py)

The stamp (build/split.stamp) is a sha256 of the yaml, symbol files, pinned
requirements and split.py itself. A stale asm/ tree was a recurring source of
phantom mismatches in thps64; this makes it impossible to judge against one.
After a re-split, the committed tables (config/functions.us.csv,
config/rodata.us.csv, config/undefined_*) must be unchanged, or whoever changed
the split inputs forgot to re-run split.py and commit the result.
"""
import hashlib
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ASM, BUILD, CONFIG, EXE, ROOT  # noqa: E402

TABLES = ["functions.us.csv", "rodata.us.csv", "undefined_funcs_auto.us.txt",
          "undefined_syms_auto.us.txt"]


def digest(paths):
    return {p: hashlib.sha256((CONFIG / p).read_bytes()).hexdigest()
            for p in paths if (CONFIG / p).exists()}


def ensure():
    import split
    stamp = BUILD / "split.stamp"
    if ASM.exists() and stamp.exists() and stamp.read_text().strip() == split.inputs_hash():
        return False
    if not EXE.exists():
        sys.exit("disc/files/SLUS_009.35 missing: python tools/extract_disc.py")
    before = digest(TABLES)
    print("fresh: split inputs changed (or no asm/): re-splitting", flush=True)
    r = subprocess.run([sys.executable, str(ROOT / "tools" / "split.py")], cwd=ROOT)
    if r.returncode != 0:
        sys.exit("fresh: split failed")
    after = digest(TABLES)
    changed = [p for p in TABLES if before.get(p) != after.get(p)]
    if before and changed:
        sys.exit("fresh: re-split changed committed tables (" + ", ".join(changed) +
                 "): run python tools/split.py and commit config/")
    return True


if __name__ == "__main__":
    print("re-split" if ensure() else "split is fresh")
