#!/usr/bin/env python3
"""Candidate selection with the stale-body defect built out.

The lane lost a third of one pass to drafting bodies that were already merged upstream. This
tool makes that impossible to reach by accident:

  sync    fetch origin, cut the working tree to the fetched sha in the same command, and record
          that sha. Refuses to leave a tree that is not exactly upstream, and refuses to run if
          any tracked unit file differs from upstream.
  list    enumerate open bodies from *that* tree, ascending size. A body whose unit file exists
          is merged by definition and is never printed; the count of suppressed bodies is.
  check   verdict for one body. Exits non-zero on MERGED, on a dirty src/funcs, or on a tree
          whose HEAD is not the sha recorded at sync.
  draft   the only sanctioned way to start a body: check first (hard refuse), then write the
          draft, then measure it. An existing unit file is never overwritten or removed.

Every subcommand except bare `sync` re-validates the tree, so a draft cannot be created or
measured without the merge check having passed in the same tree.
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
STAMP = ROOT / "work" / ".select-sha"
ASM = Path("asm/nonmatchings/game")
UNITS = Path("src/funcs")
INSN = re.compile(r"^\s*/\*\s+[0-9A-F]{4,6}\s+[0-9A-F]{8}\s+[0-9A-F]{8}\s+\*/")


def git(*args, cwd=None):
    return subprocess.run(["git", *args], cwd=cwd or ROOT, capture_output=True, text=True)


def head():
    return git("rev-parse", "HEAD").stdout.strip()


def synced_sha():
    return STAMP.read_text().strip() if STAMP.exists() else None


def dirty_units():
    out = git("status", "--porcelain", "--", str(UNITS)).stdout.strip()
    return [l for l in out.splitlines() if l.strip()]


def require_fresh(tree=ROOT):
    """The tree must be the sha recorded at sync, with no local edits to unit files."""
    sha = synced_sha()
    if sha is None:
        sys.exit("select: no sync recorded. run: work/select.py sync")
    have = git("rev-parse", "HEAD", cwd=tree).stdout.strip()
    if have != sha:
        sys.exit(f"select: tree is at {have[:8]}, sync recorded {sha[:8]} — run sync again")
    if tree == ROOT:
        bad = dirty_units()
        if bad:
            sys.exit("select: src/funcs has local edits, selection would be unsound:\n  "
                     + "\n  ".join(bad[:10]))
    return sha


def merged(name, tree=ROOT):
    return (tree / UNITS / f"{name}.c").exists()


def words(name, tree=ROOT):
    p = tree / ASM / f"{name}.s"
    return sum(1 for l in p.read_text().splitlines() if INSN.match(l))


def cmd_sync(a):
    f = git("fetch", "origin")
    if f.returncode != 0:
        sys.exit(f"select: fetch failed\n{f.stderr}")
    sha = git("rev-parse", "origin/main").stdout.strip()
    if head() != sha:
        co = git("checkout", "-B", a.branch, sha)
        if co.returncode != 0:
            sys.exit(f"select: cannot cut to {sha[:8]} (local work in the way?)\n{co.stderr}")
    if head() != sha:
        sys.exit(f"select: tree at {head()[:8]} but upstream is {sha[:8]}")
    bad = dirty_units()
    if bad:
        sys.exit("select: unit files differ from upstream after cut:\n  " + "\n  ".join(bad[:10]))
    STAMP.write_text(sha + "\n")
    print(f"synced: HEAD = origin/main = {sha[:8]}, src/funcs clean, {len(list((ROOT / UNITS).glob('*.c')))} units")


def cmd_check(a):
    sha = require_fresh()
    name = a.name if a.name.startswith("func_") else f"func_{a.name}"
    if merged(name):
        print(f"REFUSED {name}: MERGED on main@{sha[:8]} (src/funcs/{name}.c exists)")
        return 1
    if not (ROOT / ASM / f"{name}.s").exists():
        print(f"REFUSED {name}: no listing in {ASM}")
        return 1
    print(f"OPEN {name}: {words(name)} words, absent from main@{sha[:8]}")
    return 0


def cmd_list(a):
    sha = require_fresh()
    rows, suppressed = [], 0
    for p in (ROOT / ASM).glob("func_*.s"):
        n = p.stem
        if merged(n):
            suppressed += 1
            continue
        w = words(n)
        if a.min is not None and w < a.min:
            continue
        if a.max is not None and w > a.max:
            continue
        rows.append((w, n))
    rows.sort()
    for w, n in rows[: a.limit]:
        print(f"{w:4d} {n}")
    print(f"# {len(rows)} open in range, {suppressed} suppressed as merged, tree at {sha[:8]}")


def cmd_draft(a):
    sha = require_fresh()
    name = a.name if a.name.startswith("func_") else f"func_{a.name}"
    if merged(name):
        sys.exit(f"select: REFUSED {name}: MERGED on main@{sha[:8]} — nothing drafted")
    dest = ROOT / UNITS / f"{name}.c"
    if dest.exists():
        sys.exit(f"select: REFUSED {name}: {dest.relative_to(ROOT)} already exists, not overwriting")
    src = Path(a.src)
    if not src.is_file():
        sys.exit(f"select: REFUSED {name}: draft source {src} does not exist — nothing written")
    try:
        body = src.read_text()
    except OSError as e:
        sys.exit(f"select: REFUSED {name}: cannot read {src}: {e.strerror} — nothing written")
    dest.write_text(body)
    print(f"drafted {dest.relative_to(ROOT)} ({words(name)} words target, main@{sha[:8]})")
    if not a.no_measure:
        m = subprocess.run([sys.executable, "tools/match.py", name, "--show"], cwd=ROOT)
        return m.returncode
    return 0


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("sync")
    s.add_argument("--branch", default="freebuff/band-oct29")
    s.set_defaults(fn=cmd_sync)
    for name, fn in (("check", cmd_check), ("list", cmd_list), ("draft", cmd_draft)):
        p = sub.add_parser(name)
        p.set_defaults(fn=fn)
        if name == "check":
            p.add_argument("name")
        elif name == "list":
            p.add_argument("--min", type=int)
            p.add_argument("--max", type=int)
            p.add_argument("--limit", type=int, default=20)
        else:
            p.add_argument("name")
            p.add_argument("--src", required=True)
            p.add_argument("--no-measure", action="store_true")
    a = ap.parse_args()
    sys.exit(a.fn(a) or 0)


if __name__ == "__main__":
    main()
