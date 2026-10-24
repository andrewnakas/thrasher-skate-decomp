#!/usr/bin/env python3
"""Write an objdiff report.json (report version 2) without the disc, for ByteMatch.

    python tools/objdiff_report.py [-o build/report/SLUS_009.35/report.json]

Inputs are only committed files: config/functions.us.csv and src/funcs/.
Every merged unit passed tools/gate.py and tools/build.py on the judge box, so
each counts as a 100% match. Each function is its own unit with a source_path,
so ByteMatch can link to the C. Only game code is counted: the PsyQ libraries
are Sony's prebuilt objects and stay asm. Adapted from thps64's tool.
"""
import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, SRC_FUNCS, load_functions  # noqa: E402

REPORT_VERSION = 2
VERSION = "SLUS_009.35"


def pct(a, b):
    return 100.0 * a / b if b else 0.0


def measures(funcs, matched, units, complete_units=0):
    total = sum(f["size"] for f in funcs)
    done = sum(f["size"] for f in funcs if f["name"] in matched)
    mf = sum(1 for f in funcs if f["name"] in matched)
    return {
        "fuzzy_match_percent": pct(done, total), "total_code": str(total),
        "matched_code": str(done), "matched_code_percent": pct(done, total),
        "total_data": "0", "matched_data": "0", "matched_data_percent": 0.0,
        "total_functions": len(funcs), "matched_functions": mf,
        "matched_functions_percent": pct(mf, len(funcs)),
        "complete_code": str(done), "complete_code_percent": pct(done, total),
        "complete_data": "0", "complete_data_percent": 0.0,
        "total_units": units, "complete_units": complete_units,
    }


def report(funcs, matched):
    units = []
    for f in funcs:
        ok = f["name"] in matched
        meta = {"complete": ok, "progress_categories": ["game"]}
        if ok:
            meta["source_path"] = f"src/funcs/{f['name']}.c"
        units.append({
            "name": f"funcs/{f['name']}",
            "measures": measures([f], matched, 1, int(ok)),
            "sections": [{"name": ".text", "size": str(f["size"]),
                          "fuzzy_match_percent": 100.0 if ok else 0.0,
                          "metadata": {"virtual_address": str(f["addr"])}}],
            "functions": [{"name": f["name"], "size": str(f["size"]),
                           "fuzzy_match_percent": 100.0 if ok else 0.0,
                           "metadata": {"virtual_address": str(f["addr"])}, "address": "0"}],
            "metadata": meta,
        })
    m = measures(funcs, matched, len(units), sum(1 for f in funcs if f["name"] in matched))
    return {"measures": m, "units": units, "version": REPORT_VERSION,
            "categories": [{"id": "game", "name": "Game", "measures": m}]}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("-o", "--output", default=str(ROOT / "build" / "report" / VERSION / "report.json"))
    a = ap.parse_args()
    funcs = [f for f in load_functions() if f["segment"] == "game" and f["kind"] == "func"]
    matched = {p.stem for p in SRC_FUNCS.glob("func_*.c")} & {f["name"] for f in funcs}
    rep = report(funcs, matched)
    out = Path(a.output)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(rep, separators=(",", ":")) + "\n")
    m = rep["measures"]
    print(f"{out.relative_to(ROOT) if out.is_relative_to(ROOT) else out}: "
          f"{m['matched_functions']}/{m['total_functions']} functions, "
          f"{m['matched_code']}/{m['total_code']} bytes ({m['matched_code_percent']:.3f}%)")


if __name__ == "__main__":
    main()
