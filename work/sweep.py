#!/usr/bin/env python3
"""Lever sweep over the measured near-misses.

Every one of these units is already characterised: the body is right and the residue is a
handful of words that depend on *codegen levers* -- per-site global re-read vs cached local,
offset-first arithmetic, named vs inline narrow reads, folded vs nested compares, struct
padding vs field sums, declaration/statement order, and the allowed `-fno-schedule-*` flags.
Guessing one spelling per pass wastes the pass, so this driver tries the combinations in one
run and reports which lever moves which unit.

    python work/sweep.py                     # every registered unit
    python work/sweep.py --unit func_80015684
    python work/sweep.py --list              # registered units and their axes
    python work/sweep.py --fresh             # ignore work/sweep-results.json
    python work/sweep.py --json              # machine-readable report

Run it inside the pinned toolchain container, like the other tools:

    work/drun.sh '.venv/bin/python work/sweep.py'

Each variant is compiled with tools/match.py's own pipeline (no second toolchain), and the
score is the number of differing words, so 0 == MATCH. Results are cached in
work/sweep-results.json keyed by unit + label, so a later pass pays only for new variants.

Adding a unit: append to UNITS with a `template` containing {axis} placeholders and an `axes`
dict of (label, snippet) pairs. The driver takes the cartesian product of the axes crossed
with FLAGS; keep the product small (<= ~20 variants per unit).
"""
import argparse
import hashlib
import itertools
import json
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent / "tools"))
import match  # noqa: E402

OUT = HERE / "sweep"
CACHE = HERE / "sweep-results.json"
FLAGS = ["", "-fno-schedule-insns", "-fno-schedule-insns2"]

# ---------------------------------------------------------------- unit registry

UNITS = {}

UNITS["func_80015684"] = {
    "note": "7/44: tail keeps the allocation pointer in $a0 and the size in $v0",
    "template": """
extern s32 D_80089F68;
extern s32 D_80089F6C;
extern s32 D_80089F70;
extern s32 D_8008AD44;
extern u8 *D_8008AD34;
extern u8 *D_8008AD40;
extern u8 *D_8008AD38;
extern u8 *D_8008AD3C;
extern s32 D_8008AD48;
extern s32 D_8008AD50;
extern u8 *D_8008AD4C;

void *func_80034C20(s32);
void func_800161DC(void);

s32 func_80015684(s32 arg0, s32 arg1) {
{decl}
    if (D_80089F68) {
        return 1;
    }
    D_80089F6C = 0;
    D_80089F70 = 0;
    D_8008AD44 = arg1;
    v = arg1 & 3;
    if (v) {
        v -= 4;
        D_8008AD44 = arg1 - v;
    }
{palloc}    if (!p) {
        return 1;
    }
    D_8008AD40 = p;
    D_8008AD48 = 0;
    D_8008AD50 = 0;
    D_8008AD38 = p + D_8008AD44;
    D_8008AD3C = D_8008AD38;
    memset(p, 0xFF, D_8008AD44);
{tail}    func_800161DC();
    D_80089F68 = 1;
    return 0;
}
""",
    "axes": {
        "decl": [
            ("v-p-h-sz", "    s32 v;\n    u8 *p;\n    s32 *h;\n    s32 sz;\n"),
            ("v-h-p-sz", "    s32 v;\n    s32 *h;\n    u8 *p;\n    s32 sz;\n"),
            ("v-p-sz-h", "    s32 v;\n    u8 *p;\n    s32 sz;\n    s32 *h;\n"),
        ],
        "palloc": [
            ("local", "    p = func_80034C20(D_8008AD44);\n    D_8008AD34 = p;\n"),
            ("local-cast", "    p = (u8 *)func_80034C20(D_8008AD44);\n    D_8008AD34 = p;\n"),
        ],
        "tail": [
            ("reread-sz-first",
             "    sz = D_8008AD44 - 0x10;\n    h = (s32 *)D_8008AD34;\n"
             "    D_8008AD4C = (u8 *)h;\n    h[0] = 0;\n    h[1] = 0;\n    h[2] = sz;\n"),
            ("reread-h-first",
             "    h = (s32 *)D_8008AD34;\n    sz = D_8008AD44 - 0x10;\n"
             "    D_8008AD4C = (u8 *)h;\n    h[0] = 0;\n    h[1] = 0;\n    h[2] = sz;\n"),
            ("global-cast",
             "    D_8008AD4C = D_8008AD34;\n"
             "    *(s32 *)(D_8008AD34 + 0) = 0;\n"
             "    *(s32 *)(D_8008AD34 + 4) = 0;\n"
             "    *(s32 *)(D_8008AD34 + 8) = D_8008AD44 - 0x10;\n"),
        ],
    },
}

UNITS["func_80029488"] = {
    "note": "11/29: frame 0x20 vs 0x28 and s0/s1 roles",
    "template": """
extern s32 D_8008AFAC;
extern u8 *D_8008AFA8;

void *func_80034C20(s32);
void func_80034D4C(void *, void *, s32);
u8 *func_8001D5B0(u8 *, u32, s32);

void func_80029488(u8 *arg0, s32 arg1, u8 *arg2) {
    u16 v;
{decl}
    if (*(s32 *)(arg2 + 0x18) & 0x800000) {
        h = func_8001D5B0(arg0, 0x4954414D, 1);
{read}        D_8008AFA8 = func_80034C20(n);
        func_80034D4C(D_8008AFA8, h + 0xC, n);
    }
}
""",
    "axes": {
        "decl": [
            ("n-h", "    s32 n;\n    u8 *h;\n"),
            ("h-n", "    u8 *h;\n    s32 n;\n"),
        ],
        "read": [
            ("inline", "        n = *(s32 *)(h + 4) - 4;\n        D_8008AFAC = *(u16 *)(h + 0xA);\n"),
            ("named", "        n = *(s32 *)(h + 4) - 4;\n        v = *(u16 *)(h + 0xA);\n"
                      "        D_8008AFAC = v;\n"),
            ("size-first", "        D_8008AFAC = *(u16 *)(h + 0xA);\n"
                           "        n = *(s32 *)(h + 4) - 4;\n"),
        ],
    },
}

UNITS["func_800382C0"] = {
    "note": "8/12: game keeps the running value in $v0, gcc reuses $a0",
    "template": """
s32 func_800382C0(s32 arg0) {
{decl}
{body}
}
""",
    "axes": {
        "decl": [
            ("u32-v", "    u32 v;\n"),
            ("s32-v", "    s32 v;\n"),
        ],
        "body": [
            ("assign",
             "    v = arg0 + ((u32)(arg0 + 4) >> 7) + 0x205;\n"
             "    if (v > 0x1E000) {\n        v = (u32)-1;\n    }\n    return v;\n"),
            ("two-returns",
             "    v = arg0 + ((u32)(arg0 + 4) >> 7) + 0x205;\n"
             "    if ((u32)v > 0x1E000) {\n        return -1;\n    }\n    return v;\n"),
            ("inline-return",
             "    v = (u32)(arg0 + ((u32)(arg0 + 4) >> 7) + 0x205);\n"
             "    if (v > 0x1E000) {\n        v = (u32)-1;\n    }\n    return v;\n"),
            ("temp-first-assign",
             "    v = ((u32)(arg0 + 4) >> 7) + arg0 + 0x205;\n"
             "    if (v > 0x1E000) {\n        v = (u32)-1;\n    }\n    return v;\n"),
            ("temp-first-two-returns",
             "    v = ((u32)(arg0 + 4) >> 7) + arg0 + 0x205;\n"
             "    if (v > 0x1E000) {\n        return -1;\n    }\n    return v;\n"),
            ("temp-first-split",
             "    v = (u32)(arg0 + 4) >> 7;\n    v = v + arg0;\n    v = v + 0x205;\n"
             "    if (v > 0x1E000) {\n        v = (u32)-1;\n    }\n    return v;\n"),
            ("copy-unsigned",
             "    u32 a;\n\n    a = (u32)arg0;\n    v = a + ((a + 4) >> 7) + 0x205;\n"
             "    if (v > 0x1E000) {\n        v = (u32)-1;\n    }\n    return v;\n"),
            ("copy-signed",
             "    s32 a;\n\n    a = arg0;\n    v = a + ((u32)(a + 4) >> 7) + 0x205;\n"
             "    if (v > 0x1E000) {\n        v = (u32)-1;\n    }\n    return v;\n"),
        ],
    },
}

UNITS["func_80032FF4"] = {
    "note": "12/13: game batches six loads into $t0-$t5, gcc interleaves per component",
    "template": """
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

{body}
""",
    "axes": {
        "body": [
            ("compound",
             "void func_80032FF4(Vec3 *arg0, Vec3 *arg1) {\n"
             "    arg0->x += arg1->x;\n    arg0->y += arg1->y;\n    arg0->z += arg1->z;\n}\n"),
            ("named-temps",
             "void func_80032FF4(Vec3 *arg0, Vec3 *arg1) {\n"
             "    s32 x;\n    s32 y;\n    s32 z;\n\n"
             "    x = arg1->x;\n    y = arg1->y;\n    z = arg1->z;\n"
             "    arg0->x += x;\n    arg0->y += y;\n    arg0->z += z;\n}\n"),
            ("batch-sum-store",
             "void func_80032FF4(Vec3 *arg0, Vec3 *arg1) {\n"
             "    s32 x = arg0->x + arg1->x;\n"
             "    s32 y = arg0->y + arg1->y;\n"
             "    s32 z = arg0->z + arg1->z;\n\n"
             "    arg0->x = x;\n    arg0->y = y;\n    arg0->z = z;\n}\n"),
        ],
    },
}

UNITS["func_80033818"] = {
    "note": "12/13: three word swaps; game does six loads then six stores",
    "template": """
typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
} S;

{body}
""",
    "axes": {
        "body": [
            ("temp-swaps",
             "void func_80033818(S *arg0) {\n    s32 t;\n\n"
             "    t = arg0->f4;\n    arg0->f4 = arg0->fC;\n    arg0->fC = t;\n"
             "    t = arg0->f8;\n    arg0->f8 = arg0->f18;\n    arg0->f18 = t;\n"
             "    t = arg0->f14;\n    arg0->f14 = arg0->f1C;\n    arg0->f1C = t;\n}\n"),
            ("batch",
             "void func_80033818(S *arg0) {\n"
             "    s32 a, b, c, d, e, f;\n\n"
             "    a = arg0->f4;\n    b = arg0->fC;\n    c = arg0->f8;\n"
             "    d = arg0->f18;\n    e = arg0->f14;\n    f = arg0->f1C;\n"
             "    arg0->fC = a;\n    arg0->f4 = b;\n    arg0->f18 = c;\n"
             "    arg0->f8 = d;\n    arg0->f1C = e;\n    arg0->f14 = f;\n}\n"),
            ("pair-arrays",
             "void func_80033818(S *arg0) {\n    s32 *p;\n    s32 t;\n\n"
             "    p = (s32 *)arg0;\n"
             "    t = p[1];\n    p[1] = p[3];\n    p[3] = t;\n"
             "    t = p[2];\n    p[2] = p[6];\n    p[6] = t;\n"
             "    t = p[5];\n    p[5] = p[7];\n    p[7] = t;\n}\n"),
        ],
    },
}

UNITS["func_8002DDE0"] = {
    "note": "15/14: reverse 0xC-stride search, one extra frame word",
    "template": """
extern u8 *D_8008B060;
extern u8 *D_8008B05C;

{body}
""",
    "axes": {
        "body": [
            ("while",
             "u8 *func_8002DDE0(s32 arg0) {\n    u8 *p;\n    u8 *end;\n\n"
             "    p = D_8008B060 - 0xC;\n    end = D_8008B05C;\n"
             "    while (p >= end) {\n        if (*(s32 *)p == arg0) {\n            return p;\n"
             "        }\n        p -= 0xC;\n    }\n    return 0;\n}\n"),
            ("do-while",
             "u8 *func_8002DDE0(s32 arg0) {\n    u8 *p;\n    u8 *end;\n\n"
             "    p = D_8008B060 - 0xC;\n    end = D_8008B05C;\n"
             "    if (p >= end) {\n        do {\n            if (*(s32 *)p == arg0) {\n"
             "                return p;\n            }\n            p -= 0xC;\n"
             "        } while (p >= end);\n    }\n    return 0;\n}\n"),
            ("for",
             "u8 *func_8002DDE0(s32 arg0) {\n    u8 *p;\n\n"
             "    for (p = D_8008B060 - 0xC; p >= D_8008B05C; p -= 0xC) {\n"
             "        if (*(s32 *)p == arg0) {\n            return p;\n        }\n    }\n"
             "    return 0;\n}\n"),
        ],
    },
}

UNITS["func_800337C4"] = {
    "note": "16/16: const in $t0 and pointer in $a0 in the game, $v1/$v0 ours",
    "template": """
typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} Row;

{body}
""",
    "axes": {
        "body": [
            ("indexed",
             "Row *func_800337C4(Row *arg0) {\n    s32 i;\n\n"
             "    for (i = 0; i < 3; i++) {\n        arg0[i].x = 0x10000;\n"
             "        arg0[i].y = 0;\n        arg0[i].z = 0;\n        arg0[i].w = 0;\n    }\n"
             "    return arg0;\n}\n"),
            ("local-ptr",
             "Row *func_800337C4(Row *arg0) {\n    Row *p;\n\n    p = arg0;\n"
             "    p[0].x = 0x10000;\n    p[0].y = 0;\n    p[0].z = 0;\n    p[0].w = 0;\n"
             "    p[1].x = 0x10000;\n    p[1].y = 0;\n    p[1].z = 0;\n    p[1].w = 0;\n"
             "    p[2].x = 0x10000;\n    p[2].y = 0;\n    p[2].z = 0;\n    p[2].w = 0;\n"
             "    return p;\n}\n"),
            ("word-array",
             "s32 *func_800337C4(s32 *arg0) {\n"
             "    arg0[0] = 0x10000;\n    arg0[1] = 0;\n    arg0[2] = 0;\n    arg0[3] = 0;\n"
             "    arg0[4] = 0x10000;\n    arg0[5] = 0;\n    arg0[6] = 0;\n    arg0[7] = 0;\n"
             "    arg0[8] = 0x10000;\n    arg0[9] = 0;\n    arg0[10] = 0;\n    arg0[11] = 0;\n"
             "    return arg0;\n}\n"),
        ],
    },
}

UNITS["func_80032D88"] = {
    "note": "17/17: clamp then index D_8007F8C8[arg0 >> 5]",
    "template": """
extern s16 D_8007F8C8[];

s32 func_80032D88(s32 arg0) {
{decl}
{body}    return D_8007F8C8[{index}];
}
""",
    "axes": {
        "decl": [("v", "    s32 v;\n"), ("v-unsigned", "    u32 v;\n")],
        "body": [
            ("two-ifs",
             "    v = arg0 >> 16;\n    if (v < 1) {\n        arg0 = 0x10000;\n    }\n"
             "    if (v < -1) {\n        arg0 = (s32)0xFFFF0000;\n    }\n"),
            ("nested",
             "    v = arg0 >> 16;\n    if (v < 1) {\n        arg0 = 0x10000;\n    } else if (v < -1) {\n"
             "        arg0 = (s32)0xFFFF0000;\n    }\n"),
            ("assign-match",
             "    v = arg0 >> 16;\n    if (v < 1) {\n        arg0 = 0x10000;\n    }\n"
             "    if (v < -1) {\n        arg0 = -0x10000;\n    }\n"),
        ],
        "index": [("shift", "arg0 >> 5"), ("shift-paren", "(arg0 >> 5)")],
    },
}

# ---------------------------------------------------------------- driver


def header(flag):
    return (f"/* cflags: {flag} */\n" if flag else "") + '#include "common.h"\n'


def variants(spec):
    keys = list(spec["axes"])
    for combo in itertools.product(*[spec["axes"][k] for k in keys]):
        body = spec["template"]
        label = []
        for k, (name, snippet) in zip(keys, combo):
            body = body.replace("{%s}" % k, snippet)
            label.append(f"{k}={name}")
        for flag in FLAGS:
            tag = " + ".join(label) + (f" [{flag}]" if flag else "")
            yield tag, header(flag) + body


def load_cache():
    if CACHE.exists():
        try:
            return json.loads(CACHE.read_text())
        except json.JSONDecodeError:
            pass
    return {}


def save_cache(cache):
    CACHE.write_text(json.dumps(cache, indent=1, sort_keys=True))


def score(name, tag, text, cache, fresh):
    key = f"{name}|{tag}"
    if not fresh and key in cache:
        return cache[key]
    OUT.mkdir(parents=True, exist_ok=True)
    slug = hashlib.md5(tag.encode()).hexdigest()[:8]
    path = OUT / f"{name}.{slug}.c"
    path.write_text(text)
    res = match.compare(name, str(path))
    if res.error:
        val = ["ERROR", res.error]
    else:
        val = [len(res.diffs), len(res.target.words)]
    cache[key] = val
    save_cache(cache)
    return val


def main(argv):
    ap = argparse.ArgumentParser()
    ap.add_argument("--unit", action="append")
    ap.add_argument("--fresh", action="store_true")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--list", action="store_true")
    a = ap.parse_args(argv)

    if a.list:
        for name, spec in UNITS.items():
            axes = ", ".join(f"{k}({len(v)})" for k, v in spec["axes"].items())
            print(f"{name}: {axes}  -- {spec['note']}")
        return 0

    names = a.unit or list(UNITS)
    cache = load_cache()
    report = {}
    for name in names:
        spec = UNITS[name]
        rows = []
        for tag, text in variants(spec):
            val = score(name, tag, text, cache, a.fresh)
            rows.append((val[0] if val[0] != "ERROR" else 10 ** 6, tag, val))
        rows.sort()
        report[name] = {"note": spec["note"], "best": rows[0][1], "best_score": rows[0][0],
                        "rows": [{"tag": t, "score": v[0], "words": v[1] if len(v) > 1 else None}
                                 for _, t, v in rows]}

    if a.json:
        print(json.dumps(report, indent=1))
        return 0

    for name, rep in report.items():
        print(f"\n{name}  ({rep['note']})")
        best = rep["best_score"]
        for row in rep["rows"][:6]:
            mark = "MATCH" if row["score"] == 0 else f"{row['score']} words"
            print(f"  {mark:>10}  {row['tag']}")
        if best == 0:
            print(f"  -> WINNER: {rep['best']}")

    winners = [n for n, rep in report.items() if rep["best_score"] == 0]
    print(f"\nsweep: {len(report)} units, {sum(len(r['rows']) for r in report.values())} variants, "
          f"{len(winners)} matched")
    for n in winners:
        print(f"  MATCH {n}: {report[n]['best']}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
