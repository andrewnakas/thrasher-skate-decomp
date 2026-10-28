#!/usr/bin/env python3
"""In-repo permuter: random search over source spellings, scored by tools/match.py.

    python3 work/permute_search.py func_80033818 --src work/best/func_80033818.c \
            --seconds 240 [--max-compiles 400] [--seed 1]

Mutates declaration order, statement order, expression forms, local types and
copy placement of the base draft, scores every variant with the project's own
matcher (same pipeline as the gate), keeps improvements, and exits on MATCH.

The result is written to work/permute-work/<name>/best.c and, on a match, to
work/permute-work/<name>/MATCH.c. Nothing outside work/ is written.
"""
import argparse
import random
import re
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import match  # noqa: E402

TYPES = ["u32", "s32", "u16", "s16", "u8", "s8"]
SIMPLE_STMT = re.compile(r"^\s{4}\S.*;\s*$")


def is_decl(line):
    s = line.strip()
    return s.endswith(";") and re.match(r"^(u|s)(8|16|32|64)\b", s) and "=" in s or \
        (s.endswith(";") and re.match(r"^(u|s)(8|16|32|64)\s+\*?\w+;$", s) is not None)


def split_source(text):
    lines = text.splitlines()
    start = next(i for i, l in enumerate(lines) if "(" in l and l.rstrip().endswith("{"))
    end = max(i for i, l in enumerate(lines) if l.strip() in ("}", "})") or l.strip() == "}")
    return lines[:start + 1], lines[start + 1:end], lines[end:]


def join(head, body, tail):
    return "\n".join(head + body + tail) + "\n"


def decl_indices(body):
    out = []
    for i, l in enumerate(body):
        s = l.strip()
        if s.endswith(";") and re.match(r"^(u|s)(8|16|32|64|void|char|int)\b", s):
            out.append(i)
    return out


def stmt_indices(body):
    return [i for i, l in enumerate(body) if SIMPLE_STMT.match(l) and not is_decl(l)
            and not l.strip().startswith("return")]


def swap_lines(body, i, j):
    if i == j or i < 0 or j < 0 or i >= len(body) or j >= len(body):
        return None
    b = list(body)
    b[i], b[j] = b[j], b[i]
    return b


# ---------------------------------------------------------------- mutators

def m_swap_decls(body, rng):
    d = decl_indices(body)
    if len(d) < 2:
        return None
    i, j = rng.sample(d, 2)
    return swap_lines(body, i, j)


def m_swap_stmts(body, rng):
    s = stmt_indices(body)
    if len(s) < 2:
        return None
    i, j = rng.sample(s, 2)
    return swap_lines(body, i, j)


def m_retype(body, rng):
    d = decl_indices(body)
    if not d:
        return None
    i = rng.choice(d)
    m = re.search(r"\b(u|s)(8|16|32|64)\b", body[i])
    if not m:
        return None
    new = rng.choice(TYPES)
    b = list(body)
    b[i] = b[i][:m.start()] + new + b[i][m.end():]
    return b


def m_copy_local(body, rng):
    """`T x = expr;` -> `T x = expr;` plus `T xN = x;`, using xN afterwards."""
    d = decl_indices(body)
    if not d:
        return None
    i = rng.choice(d)
    m = re.match(r"^(\s*)((?:u|s)(?:8|16|32|64))\s+\*?(\w+)\s*(.*);\s*$", body[i])
    if not m:
        return None
    indent, ty, name, rest = m.groups()
    n = 0
    while any(re.search(rf"\b{name}_{n}\b", l) for l in body):
        n += 1
    alias = f"{name}_{n}"
    b = list(body)
    b.insert(i + 1, f"{indent}{ty} {alias} = {name};")
    for k in range(i + 2, len(b)):
        b[k] = re.sub(rf"\b{name}\b", alias, b[k])
    return b


def m_drop_copy(body, rng):
    """Remove a pure copy declaration and its uses alias back to the source."""
    for i in reversed(range(len(body))):
        m = re.match(r"^\s*(?:u|s)(?:8|16|32|64)\s+(\w+)\s*=\s*(\w+);\s*$", body[i])
        if m and m.group(1) != m.group(2):
            src, dst = m.group(2), m.group(1)
            b = list(body)
            del b[i]
            for k in range(len(b)):
                b[k] = re.sub(rf"\b{dst}\b", src, b[k])
            return b
    return None


def m_compound(body, rng):
    for i in rng.sample(range(len(body)), len(body)):
        m = re.match(r"^(\s*)(.*?)\s*=\s*(.*?)\s*\+\s*(.*?);\s*$", body[i])
        if m and m.group(2) == m.group(3):
            b = list(body)
            b[i] = f"{m.group(1)}{m.group(2)} += {m.group(4)};"
            return b
        m = re.match(r"^(\s*)(.*?)\s*\+=\s*(.*?);\s*$", body[i])
        if m:
            b = list(body)
            b[i] = f"{m.group(1)}{m.group(2)} = {m.group(2)} + {m.group(3)};"
            return b
    return None


def m_swap_addends(body, rng):
    for i in rng.sample(range(len(body)), len(body)):
        m = re.match(r"^(\s*)(.*?)\s*=\s*(.*?)\s*\+\s*(.*?);\s*$", body[i])
        if m and m.group(3) != m.group(4):
            b = list(body)
            b[i] = f"{m.group(1)}{m.group(2)} = {m.group(4)} + {m.group(3)};"
            return b
    return None


def m_cast_rhs(body, rng):
    for i in rng.sample(range(len(body)), len(body)):
        m = re.match(r"^(\s*)(.*?)\s*=\s*([^;]+);\s*$", body[i])
        if m and not m.group(3).startswith("("):
            b = list(body)
            b[i] = f"{m.group(1)}{m.group(2)} = (u32) {m.group(3)};"
            return b
    return None


MUTATORS = [m_swap_decls, m_swap_stmts, m_retype, m_copy_local, m_drop_copy,
            m_compound, m_swap_addends, m_cast_rhs]


REG_FIELDS = ((21, 5), (16, 5), (11, 5))


def reg_overlap(tw, ow):
    """How many register fields of two otherwise-similar words agree.

    A body that differs only in register names is a flat landscape for a plain
    diff count, so the search gets a gradient from how much of the allocation
    already agrees.
    """
    n = 0
    for shift, width in REG_FIELDS:
        if (tw >> shift) & ((1 << width) - 1) == (ow >> shift) & ((1 << width) - 1):
            n += 1
    return n


def score(name, path):
    r = match.compare(name, src=path)
    if r.error:
        return None
    if not r.ours or not r.target:
        return (99, 0, 0)
    size_delta = abs(len(r.ours.words) - len(r.target.words))
    overlap = 0
    for i in range(min(len(r.ours.words), len(r.target.words))):
        tw, ow = r.target.words[i], r.ours.words[i]
        if tw != ow:
            overlap += reg_overlap(tw, ow)
    return (len(r.diffs), size_delta, -overlap)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("name")
    ap.add_argument("--src", required=True)
    ap.add_argument("--seconds", type=float, default=180)
    ap.add_argument("--max-compiles", type=int, default=100000)
    ap.add_argument("--seed", type=int, default=0)
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args()

    rng = random.Random(args.seed)
    outdir = ROOT / "work" / "permute-work" / args.name
    outdir.mkdir(parents=True, exist_ok=True)
    variant = outdir / "variant.c"

    text = Path(args.src).read_text()
    head, body, tail = split_source(text)
    best_body = list(body)
    variant.write_text(join(head, best_body, tail))
    base_score = score(args.name, variant)
    if base_score is None:
        print("base draft does not compile", file=sys.stderr)
        return 2
    if base_score[0] == 0:
        (outdir / "MATCH.c").write_text(join(head, best_body, tail))
        print(f"{args.name}: MATCH already (0 words differ)")
        return 0
    print(f"base: {base_score[0]} words differ, reg agreement {-base_score[2]}", flush=True)

    best = base_score
    t0 = time.time()
    compiles = 0
    tried = 0
    while compiles < args.max_compiles and time.time() - t0 < args.seconds:
        cand = best_body
        for _ in range(rng.choice([1, 1, 1, 2, 3])):
            mut = rng.choice(MUTATORS)
            out = mut(cand, rng)
            if out is not None:
                cand = out
        if cand == best_body:
            continue
        variant.write_text(join(head, cand, tail))
        tried += 1
        s = score(args.name, variant)
        compiles += 1
        if s is None:
            continue
        if s < best:
            best, best_body = s, cand
            if not args.quiet:
                print(f"  {s[0]:3d} words differ  (size delta {s[1]}, reg agreement {-s[2]})  [{compiles} compiles]", flush=True)
            if s[0] == 0:
                (outdir / "MATCH.c").write_text(join(head, best_body, tail))
                print(f"{args.name}: MATCH after {compiles} compiles ({tried} variants)")
                return 0
        elif s == best and rng.random() < 0.05:
            best_body = cand  # plateau move

    (outdir / "best.c").write_text(join(head, best_body, tail))
    print(f"{args.name}: no match; best {best[0]} words differ, {compiles} compiles, {tried} variants")
    return 1


if __name__ == "__main__":
    sys.exit(main())
