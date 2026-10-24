#!/usr/bin/env python3
"""Matched functions and bytes (game code only; PsyQ libraries stay asm).

    python tools/progress.py [--json]
"""
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import SRC_FUNCS, load_functions  # noqa: E402


def main():
    funcs = [f for f in load_functions() if f["segment"] == "game" and f["kind"] == "func"]
    done = {p.stem for p in SRC_FUNCS.glob("func_*.c")}
    m = [f for f in funcs if f["name"] in done]
    tb, mb = sum(f["size"] for f in funcs), sum(f["size"] for f in m)
    r = {"functions": len(funcs), "matched_functions": len(m), "bytes": tb, "matched_bytes": mb,
         "percent": round(100.0 * mb / tb, 3) if tb else 0.0}
    if "--json" in sys.argv:
        print(json.dumps(r))
    else:
        print(f"{len(m)}/{len(funcs)} functions, {mb:,}/{tb:,} bytes ({r['percent']:.3f}%)")


if __name__ == "__main__":
    main()
