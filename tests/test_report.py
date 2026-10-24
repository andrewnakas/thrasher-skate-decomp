"""tools/objdiff_report.py produces a well-formed report from a toy table."""
import objdiff_report

FUNCS = [{"name": "func_80010000", "addr": 0x80010000, "size": 0x20},
         {"name": "func_80010020", "addr": 0x80010020, "size": 0x60}]


def test_measures():
    r = objdiff_report.report(FUNCS, {"func_80010000"})
    m = r["measures"]
    assert r["version"] == 2
    assert m["matched_functions"] == 1 and m["total_functions"] == 2
    assert m["matched_code"] == "32" and m["total_code"] == "128"
    assert r["units"][0]["metadata"]["source_path"] == "src/funcs/func_80010000.c"
    assert "source_path" not in r["units"][1]["metadata"]
