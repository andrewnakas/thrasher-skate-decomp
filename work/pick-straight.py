#!/usr/bin/env python3
"""Rank open game bodies by the profile that has actually converted in this lane:
short, few conditional branches, call-heavy, small frame, at most three saves.

usage: work/pick-straight.py [--max-insn 40] [--max-branch 2] [--max-save 3] [--max-frame 0x30]
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ASM = ROOT / "asm" / "nonmatchings" / "game"
UNITS = ROOT / "src" / "funcs"

INSN = re.compile(r"^\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s*\*/")
BRANCH = re.compile(
    r"^\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s*\*/\s+"
    r"(beq|bne|beqz|bnez|bgez|bgtz|blez|bltz|bgezal|bltzal)\b"
)
FRAME = re.compile(r"addiu\s+\$sp,\s*\$sp,\s*-0x([0-9A-Fa-f]+)")
SAVE = re.compile(r"\bsw\s+\$(s[0-7]),")
CALL = re.compile(r"\bjal\b")
SIZE = re.compile(r"^nonmatching\s+(\S+),\s*0x([0-9A-Fa-f]+)")


def main() -> int:
    args = dict(max_insn=40, max_branch=2, max_save=3, max_frame=0x30)
    argv = sys.argv[1:]
    for key in list(args):
        flag = "--" + key.replace("_", "-")
        if flag in argv:
            args[key] = int(argv[argv.index(flag) + 1], 0)

    rows = []
    for path in sorted(ASM.glob("func_*.s")):
        name = path.stem
        if (UNITS / f"{name}.c").exists():
            continue
        lines = path.read_text().splitlines()
        head = SIZE.match(lines[0].strip()) if lines else None
        if not head:
            continue
        text = "\n".join(lines)
        frame = FRAME.search(text)
        frame_sz = int(frame.group(1), 16) if frame else 0
        insn = len([l for l in lines if INSN.match(l)])
        branches = len([l for l in lines if BRANCH.match(l)])
        saves = len(SAVE.findall(text))
        calls = len(CALL.findall(text))
        if insn > args["max_insn"] or branches > args["max_branch"]:
            continue
        if saves > args["max_save"] or (frame and frame_sz > args["max_frame"]):
            continue
        rows.append((branches, -calls, insn, name, frame_sz, saves, calls))
    rows.sort()
    for branches, negcalls, insn, name, frame_sz, saves, calls in rows:
        print(f"{name}  insn={insn:3d}  br={branches}  calls={calls}  frame=0x{frame_sz:02X}  saves={saves}")
    print(f"\n{len(rows)} bodies in profile")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
