#!/usr/bin/env python3
"""Link build/link.ld into the PS-X EXE, or verify it.

    python tools/link.py build/SLUS_009.35            # ld + objcopy
    python tools/link.py --verify build/SLUS_009.35 build/SLUS_009.35.ok

--verify writes the stamp only when the sha1 matches, so a mismatching build
never looks up to date to ninja.
"""
import hashlib
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, EXE_SHA1, ROOT, tool  # noqa: E402


def link(out):
    out = Path(out)
    elf = BUILD / "slus_009.35.elf"
    r = subprocess.run([tool("mipsel-linux-gnu-ld"), "-nostdlib", "--no-check-sections",
                        "-T", str(BUILD / "link.ld"), "-Map", str(BUILD / "slus_009.35.map"),
                        "-o", str(elf)], cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit("ld failed:\n" + r.stderr)
    r = subprocess.run([tool("mipsel-linux-gnu-objcopy"), "-O", "binary",
                        "-j", ".header", "-j", ".main", str(elf), str(out)],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit("objcopy failed:\n" + r.stderr)


def verify(exe, stamp):
    h = hashlib.sha1(Path(exe).read_bytes()).hexdigest()
    Path(stamp).unlink(missing_ok=True)
    if h != EXE_SHA1:
        print(f"SLUS_009.35: MISMATCH (sha1 {h}, want {EXE_SHA1})")
        print("run: python tools/first_diff.py")
        sys.exit(1)
    Path(stamp).write_text(h + "\n")
    print(f"SLUS_009.35: OK ({h})")


if __name__ == "__main__":
    if sys.argv[1] == "--verify":
        verify(sys.argv[2], sys.argv[3])
    else:
        link(sys.argv[1])
