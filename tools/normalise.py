#!/usr/bin/env python3
"""Make a raw decompiler draft compile, without changing its shape.

Machine-generated C is usually blocked by types rather than by logic: `?` where nothing was
resolved, `void *` parameters read through `->unkN`, globals read through `D_XXXXXXXX.unkN`.
Rewriting those mechanically makes a draft *measurable*; it does not make it correct, and a
low score on the result measures the draft, not the unit.

    `?`                -> `s32`
    `void *`           -> `u8 *`            (so `p + 4` is a byte offset, not a GNU extension)
    `(unaligned T)`    -> `(T)`             (a decompiler qualifier, not C)
    `p->unkN`          -> `*(T *)(p + 0xN)` T from the mask the value is used under
    `D_XXXXXXXX.unkN`  -> `*(T *)((u8 *) D_XXXXXXXX + 0xN)`

A pointer already typed as a typedef'd struct keeps `->unkN`: the struct definition the
generator emitted supplies those members, and byte arithmetic would be scaled by the struct
size instead of the byte offset. Anything still undefined afterwards (a stack temporary the
generator invented, `unksp12`) is left alone, so the draft still fails to compile and is
reported rather than forced.

    python tools/normalise.py work/drafts/x.c            # to stdout
    python tools/normalise.py --out build/norm work/drafts/x.c ...
"""
import argparse
import re
import sys
from pathlib import Path

MEMBER = re.compile(r"(?P<obj>[A-Za-z_]\w*|\([^()]*\))\s*->\s*unk(?P<off>[0-9A-Fa-f]+)\b")
GMEMBER = re.compile(r"(?P<obj>D_[0-9A-Fa-f]{8})\s*\.\s*unk(?P<off>[0-9A-Fa-f]+)\b")
DECL = re.compile(r"extern\s+[A-Za-z_][\w \*]*\b(?P<name>D_[0-9A-Fa-f]{8})\s*(?P<arr>\[|\s*;)")
STRUCT_PTR = re.compile(r"\b(?:struct\s+)?(S_\w+|T_\w+|\w+_t)\s*\*\s*(?P<name>\w+)")


def _width(lines, needle):
    """Narrowest type the value is used as, over every occurrence of one member access."""
    for line in lines:
        for m in re.finditer(re.escape(needle), line):
            window = line[max(0, m.start() - 40): m.end() + 40]
            if re.search(r"&\s*0xFF\b|==\s*0xFF\b|!=\s*0xFF\b", window):
                return "u8"
            if re.search(r"&\s*0xFFFF\b|==\s*0xFFFF\b|!=\s*0xFFFF\b", window):
                return "u16"
    return "u32"


def _is_array(text, name):
    for m in DECL.finditer(text):
        if m.group("name") == name:
            return m.group("arr").strip() == "["
    return False


def normalise(text):
    keep = {m.group("name") for m in STRUCT_PTR.finditer(text)}
    text = text.replace("void *", "u8 *")
    text = re.sub(r"\(\s*unaligned\s+([A-Za-z_]\w*)\s*\)", r"(\1)", text)
    text = re.sub(r"(?<![\w?])\?(?![\w?])", "s32", text)
    text = re.sub(r"&(D_[0-9A-Fa-f]{8})\b", r"(u8 *) &\1", text)
    lines = text.splitlines()

    def member(m):
        if m.group("obj").strip("()") in keep:
            return m.group(0)
        return "*(%s *)(%s + 0x%X)" % (_width(lines, m.group(0)), m.group("obj"),
                                       int(m.group("off"), 16))

    def gmember(m):
        name = m.group("obj")
        base = name if _is_array(text, name) else "&" + name
        return "*(%s *)((u8 *) %s + 0x%X)" % (_width(lines, m.group(0)), base,
                                              int(m.group("off"), 16))

    return MEMBER.sub(member, GMEMBER.sub(gmember, text))


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("files", nargs="+")
    ap.add_argument("--out", help="write <out>/<name>.c instead of stdout")
    a = ap.parse_args(argv)
    out = Path(a.out) if a.out else None
    if out:
        out.mkdir(parents=True, exist_ok=True)
    for f in a.files:
        p = Path(f)
        text = normalise(p.read_text(errors="replace"))
        if out:
            (out / (p.stem + ".c")).write_text(text)
        else:
            sys.stdout.write(text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
