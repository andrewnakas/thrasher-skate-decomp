#!/usr/bin/env python3
"""In-repo permuter: random search over source spellings, scored by tools/match.py.

    python3 work/permute_search.py func_80033818 --src work/best/func_80033818.c \
            --seconds 240 [--max-compiles N] [--stall 800] [--seed 1]

Mutates liveness and register pressure, not just statement order: typed aliases of a
value used once, extra temporaries introduced then used, expressions split apart and
merged back, early-return and guard forms that move a value's last use, and copy
insertion at different points. Every variant is judged by the project's own matcher
(tools/match.py), the same pipeline the gate uses.

Score is (words differ, |size delta|, -register agreement): the third term counts how
many register fields of the differing words already agree, so an allocation-only
residue is not a flat landscape.

Writes work/permute-work/<name>/best.c and, on a match, MATCH.c. Nothing outside
work/ is written.
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
INT_TYPES = "u32|s32|u16|s16|u8|s8"
DECL = re.compile(rf"^(\s*)({INT_TYPES})\s+\*?(\w+)\s*=\s*(.*);\s*$")
PLAIN_DECL = re.compile(rf"^(\s*)({INT_TYPES})\s+\*?(\w+);\s*$")
ASSIGN = re.compile(r"^(\s*)([^=;]+?)\s*=\s*([^=].*);\s*$")
BINOP = re.compile(r"^(\s*)([^=;]+?)\s*=\s*(.+?)\s*([+\-*/])\s*([^=]+?);\s*$")
NON_STMT = ("return", "if", "else", "while", "for", "}", "{", "goto", "switch", "case")


def is_decl(line):
    s = line.strip()
    return bool(re.match(rf"^({INT_TYPES}|void)\b", s)) and s.endswith(";")


def split_source(text):
    lines = text.splitlines()
    start = next(i for i, l in enumerate(lines) if "(" in l and l.rstrip().endswith("{"))
    end = max(i for i, l in enumerate(lines) if l.strip() == "}")
    return lines[:start + 1], lines[start + 1:end], lines[end:]


def join(head, body, tail):
    return "\n".join(head + body + tail) + "\n"


def decl_indices(body):
    return [i for i, l in enumerate(body) if DECL.match(l)]


def stmt_indices(body):
    out = []
    for i, l in enumerate(body):
        s = l.strip()
        if not s or s.startswith(NON_STMT) or "==" in s or "!=" in s or is_decl(l):
            continue
        if ASSIGN.match(l):
            out.append(i)
    return out


def fresh_name(body, base):
    n = 0
    while any(re.search(rf"\b{base}_{n}\b", l) for l in body):
        n += 1
    return f"{base}_{n}"


def swap_lines(body, i, j):
    if i == j or i < 0 or j < 0 or i >= len(body) or j >= len(body):
        return None
    b = list(body)
    b[i], b[j] = b[j], b[i]
    return b


def rename_from(body, idx, old, new):
    for k in range(idx, len(body)):
        body[k] = re.sub(rf"\b{old}\b", new, body[k])
    return body


# ---------------------------------------------------------------- order / types

def m_swap_decls(body, rng):
    d = decl_indices(body)
    if len(d) < 2:
        return None
    return swap_lines(body, *rng.sample(d, 2))


def m_swap_stmts(body, rng):
    s = stmt_indices(body)
    if len(s) < 2:
        return None
    return swap_lines(body, *rng.sample(s, 2))


def m_retype(body, rng):
    d = decl_indices(body)
    if not d:
        return None
    i = rng.choice(d)
    m = re.search(rf"\b({INT_TYPES})\b", body[i])
    b = list(body)
    b[i] = b[i][:m.start()] + rng.choice(TYPES) + b[i][m.end():]
    return b


def m_cast_rhs(body, rng):
    for i in rng.sample(range(len(body)), len(body)):
        m = ASSIGN.match(body[i])
        if m and not m.group(3).startswith("("):
            b = list(body)
            b[i] = f"{m.group(1)}{m.group(2)} = ({rng.choice(TYPES)}) {m.group(3)};"
            return b
    return None


# ---------------------------------------------------------------- liveness / pressure

def m_alias_typed_once(body, rng):
    """`T x = E;` -> `T x = E;  T2 y = (T2) x;` and later uses of x read y."""
    d = decl_indices(body)
    if not d:
        return None
    i = rng.choice(d)
    m = DECL.match(body[i])
    if not m:
        return None
    indent, ty, name, rhs = m.groups()
    ty2 = rng.choice(TYPES)
    alias = fresh_name(body, name)
    b = list(body)
    b.insert(i + 1, f"{indent}{ty2} {alias} = ({ty2}) {name};")
    return rename_from(b, i + 2, name, alias)


def m_alias_at_use(body, rng):
    """Insert `T y = x;` immediately before a later use of x, then use y from there."""
    names = [m.group(3) for m in (DECL.match(l) for l in body) if m]
    if not names:
        return None
    name = rng.choice(names)
    uses = [i for i, l in enumerate(body) if i and re.search(rf"\b{name}\b", l) and not is_decl(l)]
    if not uses:
        return None
    k = rng.choice(uses)
    alias = fresh_name(body, name)
    ty = next((m.group(2) for m in (DECL.match(l) for l in body) if m and m.group(3) == name), "u32")
    b = list(body)
    b.insert(k, f"    {ty} {alias} = {name};")
    return rename_from(b, k + 1, name, alias)


def m_extra_temp(body, rng):
    """`x = A op B;` -> `T t = A; x = t op B;` (a new live value at that point)."""
    s = stmt_indices(body)
    if not s:
        return None
    i = rng.choice(s)
    m = BINOP.match(body[i])
    if not m:
        return None
    indent, lhs, a, op, b = m.groups()
    t = fresh_name(body, "tv")
    ty = rng.choice(TYPES)
    out = list(body)
    out[i:i + 1] = [f"{indent}{ty} {t} = {a};", f"{indent}{lhs} = {t} {op} {b};"]
    return out


def m_merge_temp(body, rng):
    """`T t = A;  x = t op B;` -> `x = A op B;` (removes a temporary)."""
    for i in range(len(body) - 1):
        d = DECL.match(body[i])
        n = BINOP.match(body[i + 1])
        if d and n:
            ts = re.findall(rf"\b{d.group(3)}\b", body[i + 1])
            if len(ts) == 1:
                out = list(body)
                out[i:i + 2] = [f"{n.group(1)}{n.group(2)} = "
                                + f"{n.group(3).replace(d.group(3), d.group(4))} "
                                + f"{n.group(4)} {n.group(5)};"]
                return out
    return None


def m_split_assign(body, rng):
    """`x = A op B;` -> `x = A;  x op= B;` (moves x's def later)."""
    s = stmt_indices(body)
    if not s:
        return None
    i = rng.choice(s)
    m = BINOP.match(body[i])
    if not m or m.group(4) not in "+-":
        return None
    indent, lhs, a, op, b = m.groups()
    out = list(body)
    out[i:i + 1] = [f"{indent}{lhs} = {a};", f"{indent}{lhs} {op}= {b};"]
    return out


def m_early_return(body, rng):
    """`if (c) { v = K; }  return v;` -> `if (c) { return K; }  return v;`."""
    for i in range(len(body) - 3):
        m = re.match(r"^\s*if\s*\((.*)\)\s*\{\s*$", body[i])
        if not m:
            continue
        if i + 1 >= len(body):
            continue
        a = ASSIGN.match(body[i + 1])
        if not a or body[i + 2].strip() != "}" or i + 3 >= len(body):
            continue
        r = re.match(r"^\s*return\s+(.*)\b" + a.group(2) + r"\b.*;\s*$", body[i + 3])
        if not r:
            continue
        out = list(body)
        out[i + 1] = f"        return {a.group(3)};"
        return out
    return None


def m_late_return(body, rng):
    """`if (c) { return K; } ... return v;` -> assign K to v and fall through."""
    for i in range(len(body) - 1):
        m = re.match(r"^\s*if\s*\((.*)\)\s*\{\s*$", body[i])
        if not m or not body[i + 1].strip().startswith("return "):
            continue
        if body[i + 2].strip() != "}":
            continue
        ret = re.search(r"return\s+(.*);", body[i + 1]).group(1)
        out = list(body)
        out[i + 1] = f"        v = {ret};"
        return out
    return None


def m_move_copy(body, rng):
    """Move a pure copy declaration to just after the previous statement."""
    d = decl_indices(body)
    if not d:
        return None
    i = rng.choice(d)
    m = re.match(rf"^(\s*)({INT_TYPES})\s+(\w+)\s*=\s*(\w+);\s*$", body[i])
    if not m or m.group(3) == m.group(4):
        return None
    j = rng.randrange(0, len(body))
    if j == i or not is_decl(body[j]) and not stmt_indices(body):
        return None
    b = list(body)
    line = b.pop(i)
    b.insert(min(j, len(b)), line)
    return b


def m_drop_copy(body, rng):
    for i in reversed(range(len(body))):
        m = re.match(rf"^\s*({INT_TYPES})\s+(\w+)\s*=\s*(\w+);\s*$", body[i])
        if m and m.group(2) != m.group(3):
            b = list(body)
            del b[i]
            return rename_from(b, i, m.group(2), m.group(3))
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


MUTATORS = [m_swap_decls, m_swap_stmts, m_retype, m_cast_rhs,
            m_alias_typed_once, m_alias_at_use, m_extra_temp, m_merge_temp,
            m_split_assign, m_early_return, m_late_return, m_move_copy,
            m_drop_copy, m_compound, m_swap_addends]

REG_FIELDS = ((21, 5), (16, 5), (11, 5))


def reg_overlap(tw, ow):
    n = 0
    for shift, width in REG_FIELDS:
        mask = (1 << width) - 1
        if (tw >> shift) & mask == (ow >> shift) & mask:
            n += 1
    return n


def score(name, path, outdir=None):
    r = match.compare(name, src=path, outdir=outdir)
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


def neighbourhood(body):
    """Every single-applicator variant of the families that move liveness."""
    out = []
    decls = decl_indices(body)
    for i in decls:
        m = re.search(rf"\b({INT_TYPES})\b", body[i])
        if m:
            for ty in TYPES:
                if ty == m.group(1):
                    continue
                b = list(body)
                b[i] = b[i][:m.start()] + ty + b[i][m.end():]
                out.append((f"retype {i} {ty}", b))
        d = DECL.match(body[i])
        if d:
            for ty in TYPES:
                alias = f"{d.group(3)}_a"
                if any(re.search(rf"\b{alias}\b", l) for l in body):
                    continue
                b = list(body)
                b.insert(i + 1, f"{d.group(1)}{ty} {alias} = ({ty}) {d.group(3)};")
                out.append((f"alias {i} {ty}", rename_from(b, i + 2, d.group(3), alias)))
            for j in range(0, len(body) + 1):
                if j == i:
                    continue
                b = list(body)
                line = b.pop(i)
                b.insert(min(j, len(b)), line)
                out.append((f"move decl {i}->{j}", b))
    stmts = stmt_indices(body)
    for a in range(len(stmts)):
        for c in range(a + 1, len(stmts)):
            out.append((f"swap {stmts[a]},{stmts[c]}", swap_lines(body, stmts[a], stmts[c])))
    for i in stmts:
        m = BINOP.match(body[i])
        if m:
            t = "tv_x"
            b = list(body)
            b[i:i + 1] = [f"{m.group(1)}u32 {t} = {m.group(3)};",
                          f"{m.group(1)}{m.group(2)} = {t} {m.group(4)} {m.group(5)};"]
            out.append((f"temp {i}", b))
            if m.group(4) in "+-":
                b2 = list(body)
                b2[i:i + 1] = [f"{m.group(1)}{m.group(2)} = {m.group(3)};",
                               f"{m.group(1)}{m.group(2)} {m.group(4)}= {m.group(5)};"]
                out.append((f"split {i}", b2))
    for fn in (m_early_return, m_late_return):
        b = fn(body, None)
        if b is not None:
            out.append((fn.__name__, b))
    return [(d, b) for d, b in out if b is not None]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("name")
    ap.add_argument("--src", required=True)
    ap.add_argument("--seconds", type=float, default=180)
    ap.add_argument("--max-compiles", type=int, default=100000)
    ap.add_argument("--stall", type=int, default=700, help="stop after this many compiles without improvement")
    ap.add_argument("--seed", type=int, default=0)
    ap.add_argument("--quiet", action="store_true")
    ap.add_argument("--exhaustive", action="store_true",
                    help="score the whole single-mutation neighbourhood each round")
    ap.add_argument("--jobs", type=int, default=6)
    ap.add_argument("--rounds", type=int, default=3)
    args = ap.parse_args()

    rng = random.Random(args.seed)
    outdir = ROOT / "work" / "permute-work" / args.name
    outdir.mkdir(parents=True, exist_ok=True)
    variant = outdir / "variant.c"

    head, body, tail = split_source(Path(args.src).read_text())
    best_body = list(body)
    variant.write_text(join(head, best_body, tail))
    best = score(args.name, variant)
    if best is None:
        print("base draft does not compile", file=sys.stderr)
        return 2
    if best[0] == 0:
        (outdir / "MATCH.c").write_text(join(head, best_body, tail))
        print(f"{args.name}: MATCH already")
        return 0
    print(f"base: {best[0]} words differ, reg agreement {-best[2]}", flush=True)

    if args.exhaustive:
        return exhaustive(args, head, best_body, tail, outdir, best)

    t0 = time.time()
    compiles = 0
    last_gain = 0
    while compiles < args.max_compiles and time.time() - t0 < args.seconds:
        if compiles - last_gain >= args.stall:
            break
        cand = best_body
        for _ in range(rng.choice([1, 1, 1, 2, 3])):
            out = rng.choice(MUTATORS)(cand, rng)
            if out is not None:
                cand = out
        if cand == best_body:
            continue
        variant.write_text(join(head, cand, tail))
        s = score(args.name, variant)
        compiles += 1
        if s is None:
            continue
        if s < best:
            best, best_body, last_gain = s, cand, compiles
            if not args.quiet:
                print(f"  {s[0]:3d} words differ  (size {s[1]}, reg { -s[2]})  [{compiles} compiles]",
                      flush=True)
            if s[0] == 0:
                (outdir / "MATCH.c").write_text(join(head, best_body, tail))
                print(f"{args.name}: MATCH after {compiles} compiles")
                return 0
        elif s == best and rng.random() < 0.05:
            best_body = cand

    (outdir / "best.c").write_text(join(head, best_body, tail))
    print(f"{args.name}: no match; best {best[0]} words differ "
          f"(size {best[1]}, reg {-best[2]}), {compiles} compiles")
    return 1


def exhaustive(args, head, body, tail, outdir, best):
    """Full single-mutation sweep per round, scored in parallel."""
    from concurrent.futures import ProcessPoolExecutor
    workdir = outdir / "pool"
    workdir.mkdir(parents=True, exist_ok=True)
    for rnd in range(args.rounds):
        cands = neighbourhood(body)
        if not cands:
            break
        jobs = []
        for k, (desc, b) in enumerate(cands):
            p = workdir / f"{rnd}-{k}.c"
            p.write_text(join(head, b, tail))
            jobs.append((desc, b, str(p), str(workdir / f"o{k}")))
        with ProcessPoolExecutor(max_workers=args.jobs) as ex:
            results = list(ex.map(_score_one, [(args.name, j[2], j[3]) for j in jobs]))
        best_i, gain = None, best
        for i, s in enumerate(results):
            if s is not None and s < gain:
                best_i, gain = i, s
        print(f"round {rnd}: {len(cands)} variants, best {gain}", flush=True)
        if best_i is None:
            break
        best, body = gain, jobs[best_i][1]
        print(f"  kept: {jobs[best_i][0]} -> {best}", flush=True)
        (outdir / "best.c").write_text(join(head, body, tail))
        if best[0] == 0:
            (outdir / "MATCH.c").write_text(join(head, body, tail))
            print(f"{args.name}: MATCH (size {best[1]})")
            return 0
    (outdir / "best.c").write_text(join(head, body, tail))
    print(f"{args.name}: no match; best {best[0]} words differ (size {best[1]}, reg {-best[2]})")
    return 1


def _score_one(job):
    name, path, outdir = job
    return score(name, Path(path), outdir=Path(outdir))


if __name__ == "__main__":
    sys.exit(main())
