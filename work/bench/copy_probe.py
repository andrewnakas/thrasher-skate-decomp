#!/usr/bin/env python3
"""Bench: what makes gcc 2.8.1-psx emit a second entry copy (`t1 = a0; s2 = t1`)?

The wall: the game copies an incoming argument into a temporary and then into a callee-saved
register. Our draft's single `s2 = a0` goes straight to `$s2`. Compiled through the project's own
stage chain (`cpp | cc1 | maspsx`), words counted on the expanded asm.
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import cc  # noqa: E402
from common import compiler_config  # noqa: E402

PRE = """extern void bar(u8 *, u8 *);
extern u8 *out;
"""

VARIANTS = {
"0 plain s2 = a0": PRE + """
s32 probe(u8 *a0) {
    u8 *s2;
    s2 = a0;
    bar(a0, out);
    return s2[2] + 3;
}
""",
"1 typed temp": PRE + """
s32 probe(u8 *a0) {
    u8 *s2;
    u32 t;
    t = (u32) a0;
    s2 = (u8 *) t;
    bar(a0, out);
    return s2[2] + 3;
}
""",
"2 struct member": PRE + """
typedef struct { u8 *p; } H;
s32 probe(u8 *a0) {
    H h;
    u8 *s2;
    h.p = a0;
    s2 = h.p;
    bar(a0, out);
    return s2[2] + 3;
}
""",
"3 through param pointer": PRE + """
s32 probe(u8 *a0) {
    u8 *s2;
    u8 **pp;
    pp = &a0;
    s2 = *pp;
    bar(a0, out);
    return s2[2] + 3;
}
""",
"4 a0 live after the call": PRE + """
s32 probe(u8 *a0) {
    u8 *s2;
    s2 = a0;
    bar(a0, out);
    s2[0] = 1;
    out[8] = a0[1];
    return s2[2];
}
""",
"5 widen then narrow, a0 live": PRE + """
s32 probe(u8 *a0) {
    u8 *s2;
    unsigned long long w;
    w = (unsigned long long) a0;
    s2 = (u8 *) (u32) w;
    bar(a0, out);
    out[8] = a0[1];
    return s2[2];
}
""",
"6 cast chain, a0 live": PRE + """
typedef char *CP;
s32 probe(u8 *a0) {
    u8 *s2;
    s2 = (u8 *) (u32) (CP) (u8 *) a0;
    bar(a0, out);
    out[8] = a0[1];
    return s2[2];
}
""",
"7 two locals, a0 live": PRE + """
s32 probe(u8 *a0) {
    u8 *t1;
    u8 *s2;
    t1 = a0;
    s2 = t1;
    bar(a0, out);
    out[8] = a0[1];
    return s2[2];
}
""",
"8 a0 only in the call": PRE + """
s32 probe(u8 *a0) {
    u8 *s2;
    s2 = a0;
    out[8] = a0[1];
    bar(s2, a0);
    return s2[2];
}
""",
"9 a0 reused later, no call": PRE + """
s32 probe(u8 *a0) {
    u8 *s2;
    s2 = a0;
    s2[0] = 1;
    out[8] = a0[1];
    return s2[2];
}
""",
"10 a0 stored as u32, no call": PRE + """
s32 probe(u8 *a0) {
    u8 *s2;
    s2 = a0;
    *(u32 *) (out + 8) = (u32) a0;
    s2[0] = 1;
    return s2[2];
}
""",
"11 a0 reused, call after": PRE + """
s32 probe(u8 *a0) {
    u8 *s2;
    s2 = a0;
    s2[0] = 1;
    out[8] = a0[1];
    bar(s2, out);
    return s2[2];
}
""",
"12 struct arg, a0 stored in it": PRE + """
s32 probe(u8 *a0) {
    u8 *s2;
    s2 = a0;
    *(u32 *) (s2 + 8) = (u32) a0;
    s2[0] = 1;
    return s2[2];
}
""",
"13 a0 reassigned later": PRE + """
s32 probe(u8 *a0) {
    u8 *s2;
    s2 = a0;
    *(u32 *) (out + 8) = (u32) a0;
    a0 = out;
    s2[0] = 1;
    return s2[2] + a0[0];
}
""",
"14 a0 reassigned, s2 used first": PRE + """
s32 probe(u8 *a0) {
    u8 *s2;
    s2 = a0;
    s2[0] = 1;
    *(u32 *) (out + 8) = (u32) a0;
    a0 = out;
    return s2[2] + a0[0];
}
""",
"15 two params both copied": """
extern u8 *out;
s32 probe(u8 *a0, u8 *a1) {
    u8 *s2;
    u8 *s3;
    s2 = a0;
    s3 = a1;
    *(u32 *) (out + 8) = (u32) a0;
    a0 = out;
    return s2[2] + s3[0] + a0[0];
}
""",
}

INSN = re.compile(r"^([a-z][a-z0-9.]*)\s*(.*)$")
SKIP = {"set", "section", "text", "globl", "align", "ent", "end", "include", "file", "loc"}


def words(asm_text):
    out = []
    for line in asm_text.decode(errors="replace").splitlines():
        st = line.strip()
        if not st or st.startswith("#") or st.startswith(".") or st.endswith(":"):
            continue
        m = INSN.match(st)
        if not m:
            continue
        op, rest = m.group(1), m.group(2).split("#")[0].strip()
        if op in SKIP:
            continue
        out.append(f"{op} {rest}".strip())
    return out


def main():
    cfg = compiler_config()
    tmp = ROOT / "work" / "scratch" / "probe_entry_copy.c"
    tmp.parent.mkdir(parents=True, exist_ok=True)
    print(f"{'variant':34s} {'n':>3s}  first words")
    for name, body in VARIANTS.items():
        tmp.write_text('#include "common.h"\n' + body)
        try:
            asm = cc.c_to_asm(tmp, cfg)
        except cc.StageError as e:
            print(f"{name:34s} FAIL  {e}")
            continue
        w = words(asm)
        print(f"{name:34s} {len(w):3d}  " + " | ".join(w[:8]))


if __name__ == "__main__":
    main()
