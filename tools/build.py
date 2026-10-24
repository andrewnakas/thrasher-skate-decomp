#!/usr/bin/env python3
"""The build gate: link everything and require a byte-identical SLUS_009.35.

    python tools/build.py

Runs fresh (re-split if stale), configure.py, then ninja. On a mismatch it
runs first_diff.py so the report names the function that broke the image.
"""
import json
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import fresh  # noqa: E402
from common import ROOT, tool  # noqa: E402


def main():
    fresh.ensure()
    py = sys.executable
    subprocess.run([py, "configure.py"], cwd=ROOT, check=True)
    r = subprocess.run([py, "-m", "ninja", "-k", "0"], cwd=ROOT, capture_output=True, text=True)
    out = r.stdout + r.stderr
    if r.returncode != 0:
        tail = "\n".join(l for l in out.splitlines() if not l.startswith("[")) or out
        print(tail[-3000:], flush=True)
        if "MISMATCH" in out:
            subprocess.run([py, "tools/first_diff.py"], cwd=ROOT)
            print("PROBLEM SLUS_009.35: linked image differs from the original (see first_diff above)")
        else:
            print("PROBLEM SLUS_009.35: build failed before the sha1 check (compile or link error above)")
        print("BUILD FAIL")
        sys.exit(1)
    print(next((l for l in out.splitlines() if "SLUS_009.35:" in l), "SLUS_009.35: OK"))
    if not objdiff_agrees():
        print("BUILD FAIL")
        sys.exit(1)
    print("BUILD PASS")


def objdiff_agrees():
    """Second opinion: objdiff must also see every unit file as a 100% match."""
    py = sys.executable
    r = subprocess.run([py, "-m", "ninja", "objdiff"], cwd=ROOT, capture_output=True, text=True)
    out = ROOT / "build" / "report" / "objdiff_check.json"
    out.parent.mkdir(parents=True, exist_ok=True)
    r2 = subprocess.run([tool("objdiff-cli"), "report", "generate", "-o", str(out)], cwd=ROOT,
                        capture_output=True, text=True)
    if r.returncode or r2.returncode:
        print("PROBLEM objdiff: could not build or run the objdiff check:\n" + (r.stdout + r2.stderr)[-1500:])
        return False
    ok = True
    for u in json.loads(out.read_text())["units"]:
        if u.get("metadata", {}).get("complete"):
            for f in u.get("functions", []):
                if f.get("fuzzy_match_percent", 0) < 100.0:
                    print(f"PROBLEM {f['name']}.c: objdiff scores it {f.get('fuzzy_match_percent', 0):.2f}%")
                    ok = False
    if ok:
        print("objdiff: every unit file is a 100% match")
    return ok


if __name__ == "__main__":
    main()
