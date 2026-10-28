#!/usr/bin/env python3
"""Guarded candidate selection for decomp passes.

Two failures this prevents, both of which cost this lane real work:

  1. drafting a body that is already merged upstream, because the tree the list came from was cut
     before the merge (cost a third of one pass, four times over);
  2. drafting a body that has already been attempted and parked, because `work/` is gitignored and
     the parks live on the records branch — a main-based tree cannot see them (cost a full
     transcription of func_8002AC14 in the pass of 2026-10-28c, previously closed out at 81/86).

  sync    fetch origin, cut the working tree to the fetched sha in the same command, and record
          that sha. Refuses to finish unless HEAD == origin/main and no unit file differs from it.
  list    enumerate open bodies from that tree, ascending size, each tagged fresh / attempted /
          merged. Merged bodies are never printed. `--fresh` prints only never-attempted bodies and
          reports how many were classified as already attempted.
  check   verdict for one body: MERGED, ATTEMPTED (with its best recorded residue) or FRESH.
          MERGED is always a refusal, and ATTEMPTED is a refusal when the intent is fresh ground.
  draft   the only sanctioned way to start a body: check first, then write, then measure. Refuses a
          recorded draft unless --allow-attempted, and never overwrites an existing unit file.

Attempt state is read out of a records branch (`freebuff/records-*`, newest by commit date, or
--records REF / LANE_RECORDS_REF): every path under `work/` on that branch that names a unit counts
as a recorded attempt, and a `N/M` residue in a file name or a record table row keeps the best one.

Needs `asm/nonmatchings/game/` (produced by tools/split.py) to know sizes and to know whether a
body still has a listing; without it sync/check/draft still work and say what is missing.

Usage:
    python lane/select.py sync [--branch NAME]
    python lane/select.py list [--min N] [--max N] [--limit N] [--fresh]
    python lane/select.py check func_80012345 [--intent fresh|any]
    python lane/select.py draft func_80012345 --src path/to/body.c [--allow-attempted] [--no-measure]
"""
import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ASM = Path("asm/nonmatchings/game")
UNITS = Path("src/funcs")
INSN = re.compile(r"^\s*/\*\s+[0-9A-F]{4,6}\s+[0-9A-F]{8}\s+[0-9A-F]{8}\s+\*/")
UNIT = re.compile(r"\b(?:func_)?(80[0-9A-Fa-f]{6})\b")
RESIDUE = re.compile(r"(\d+)\s*(?:of|/)\s*(\d+)")


def git(*args, cwd=None):
    return subprocess.run(["git", *args], cwd=cwd or ROOT, capture_output=True, text=True)


def head():
    return git("rev-parse", "HEAD").stdout.strip()


def stamp_path():
    """State lives in the git dir, not the worktree: it has to survive branch switches."""
    gd = git("rev-parse", "--git-dir").stdout.strip() or ".git"
    p = Path(gd)
    return (p if p.is_absolute() else ROOT / p) / "lane-select-sha"


def synced_sha():
    p = stamp_path()
    return p.read_text().strip() if p.exists() else None


def have_listings():
    return (ROOT / ASM).is_dir()


def dirty_units():
    out = git("status", "--porcelain", "--", str(UNITS)).stdout.strip()
    return [l for l in out.splitlines() if l.strip()]


def ahead_only_lane(sha):
    """True when HEAD is origin/main plus lane/ tooling that has not merged yet."""
    changed = git("diff", "--name-only", sha, "HEAD").stdout.split()
    return bool(changed) and all(p.startswith("lane/") for p in changed)


def require_fresh():
    """The tree must be the sha recorded at sync, with no local edits to unit files."""
    sha = synced_sha()
    if sha is None:
        sys.exit("select: no sync recorded. run: python lane/select.py sync")
    have = head()
    if have != sha and not ahead_only_lane(sha):
        sys.exit(f"select: tree is at {have[:8]}, sync recorded {sha[:8]} — run sync again")
    bad = dirty_units()
    if bad:
        sys.exit("select: src/funcs has local edits, selection would be unsound:\n  "
                 + "\n  ".join(bad[:10]))
    return sha


def merged(name):
    return (ROOT / UNITS / f"{name}.c").exists()


def words(name):
    p = ROOT / ASM / f"{name}.s"
    return sum(1 for l in p.read_text().splitlines() if INSN.match(l))


def handwritten(name):
    """splat marks listings it could not have come from compiled C; they are not drafting work."""
    p = ROOT / ASM / f"{name}.s"
    head = p.read_text().splitlines()[:2]
    return any("Handwritten function" in l for l in head)


AT_OK = {"lui", "addiu", "sw", "lw", "swl", "swr", "sh", "lh", "sb", "lbu", "lhu", "swc1", "lwc1"}


def csv_kind(name):
    """`kind` column of config/functions.us.csv for one row, or None."""
    p = ROOT / "config/functions.us.csv"
    if not p.exists():
        return None
    for line in p.read_text().splitlines()[1:]:
        parts = line.split(",")
        if len(parts) > 4 and parts[0] == name:
            return parts[4]
    return None


def listing_ops(name):
    """-> [(mnemonic, [operands])] for one listing, comments and directives dropped."""
    p = ROOT / ASM / f"{name}.s"
    if not p.exists():
        return []
    ops = []
    for line in p.read_text().splitlines():
        if not INSN.match(line):
            continue
        body = line.split("*/", 1)[1].strip()
        if not body:
            continue
        mnemonic, _, rest = body.partition(" ")
        ops.append((mnemonic.strip(), rest.replace(",", " ").split()))
    return ops


def c_writable(name):
    """Can this body be written in plain C at all?  -> (bool, reason).

    Decided from the listing alone, because a body that fails these four cannot be expressed in C
    no matter what the draft says:

      * a body that calls builds a frame, and keeps $ra inside that frame;
      * $sp is assigned only by the prologue's first instruction and the epilogue's last one;
      * $ra is never parked in a temporary across a call;
      * $at is never a value register (its use for address materialisation is gcc's own).

    This is the rule that keeps hand-written bodies out of a drafting pass: a manual `$sp` swap and a
    frameless caller that lives on `$ra` in `$t7` both pass `handwritten()` and neither is C.
    """
    kind = csv_kind(name)
    if kind not in (None, "func"):
        return False, f"csv kind={kind} (a data symbol, not a function)"
    ops = listing_ops(name)
    if not ops:
        return False, "no listing"
    calls = any(mn == "jal" for mn, _ in ops)
    if calls:
        if not (ops[0][0] == "addiu" and ops[0][1][:2] == ["$sp", "$sp"]):
            return False, "calls but never builds a frame (no prologue `addiu $sp,$sp,-N`)"
        if not any(mn == "sw" and o[:1] == ["$ra"] and "($sp)" in o[-1] for mn, o in ops):
            return False, "calls but never stores $ra in the frame"
    last = len(ops) - 1
    for i, (mn, o) in enumerate(ops):
        if o[:1] == ["$sp"]:
            if not (mn == "addiu" and len(o) == 3 and o[1] == "$sp"):
                return False, f"assigns $sp outside the prologue/epilogue (`{mn} {' '.join(o)}`)"
            if i not in (0, last):
                return False, "assigns $sp mid-body"
        if mn == "addu" and "$ra" in o[1:] and o[0] != "$sp":
            return False, f"keeps $ra in a temporary (`addu {o[0]}, $ra, ...`)"
        if any("$at" in t for t in o) and mn not in AT_OK:
            return False, f"uses $at as a value register (`{mn} {' '.join(o)}`)"
    return True, ""


def records_ref():
    """Where attempt state lives. Newest origin-side records branch unless overridden."""
    want = os.environ.get("LANE_RECORDS_REF")
    if want:
        return want
    out = git("for-each-ref", "--format=%(committerdate:unix) %(refname:short)",
              "refs/remotes/origin/*/records-*")
    best = None
    for line in out.stdout.splitlines():
        when, _, ref = line.partition(" ")
        if not when.isdigit():
            continue
        if best is None or int(when) > best[0]:
            best = (int(when), ref)
    return best[1] if best else None


def attempt_state(ref):
    """name -> (best residue as 'a/b' or None, example path), from `work/` on the records branch.

    A file name is enough to prove an attempt. Inside a markdown record a line counts only when it
    also carries evidence — a `work/` path, a `N/M` residue or a "not C" verdict — so a queue census
    row that merely lists a body as open does not turn every body in the project into an attempt.
    """
    state = {}
    if ref is None:
        return state
    ls = git("ls-tree", "-r", "--name-only", ref, "--", "work/")
    if ls.returncode != 0:
        return state
    for path in ls.stdout.splitlines():
        lines = []
        if path.endswith(".md"):
            body = git("show", f"{ref}:{path}").stdout
            lines = body.splitlines()
        else:
            lines = [Path(path).name]
        for line in lines:
            m = UNIT.search(line)
            if not m:
                continue
            if path.endswith(".md") and not ("work/" in line or RESIDUE.search(line)
                                            or "not C" in line):
                continue
            name = "func_" + m.group(1)
            prev = state.get(name, (None, path))
            r = RESIDUE.search(line)
            best = prev[0]
            if r:
                cand = (int(r.group(1)), int(r.group(2)))
                if best is None or cand < best:
                    best = cand
            state[name] = (best, prev[1])
    return state


def fmt(res):
    return f"{res[0]}/{res[1]}" if res else "unrecorded"


ATTEMPTS = "work/attempts.tsv"


def reconcile(state, write=True):
    """Re-derive every recorded attempt against the tree, which sync has pinned to upstream.

    The records branch never drops an entry, so a park that merges upstream stays in `work/`
    forever and used to be counted as open by every later pass. This is the one place that answers
    "is this entry still open?", and it runs on every sync, so the published table cannot drift
    from what the selector refuses. Returns (total, status changes, now-merged, new, gone).
    """
    path = ROOT / ATTEMPTS
    prev = {}
    if path.exists():
        for line in path.read_text().splitlines()[1:]:
            f = line.split("\t")
            if len(f) >= 2:
                prev[f[0]] = f[1]
    rows, changed, now_merged, new = [], [], 0, 0
    for name in sorted(state):
        res, srcpath = state[name]
        status = "merged" if merged(name) else "open"
        rows.append(f"{name}\t{status}\t{fmt(res)}\t{srcpath}")
        old = prev.get(name)
        if old is None:
            new += 1
        elif old != status:
            changed.append((name, old, status))
        if status == "merged" and old != "merged":
            now_merged += 1
    gone = len([n for n in prev if n not in state])
    if write:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text("body\tstatus\tbest\tsource\n" + "\n".join(rows) + "\n")
    return len(rows), len(changed), now_merged, new, gone


CLOSED_FILE = "work/closed-by-evidence.md"


def closed_set():
    """Bodies whose only residue is a class proved unreachable (work/closed-by-evidence.md).

    Only table rows count (`| `func_XXXXXXXX` | residue | evidence |`). A body merely *named
    in the proof prose* is evidence, not a retirement — harvesting every address closed the
    twins and func_8001A710's siblings by mention alone, and only their merging hid it.
    """
    p = ROOT / CLOSED_FILE
    if not p.exists():
        return set()
    rows = re.findall(r"^\|\s*`?func_([0-9A-F]{8})`?\s*\|", p.read_text(), re.M)
    return {"func_" + m for m in rows}


def classify(name, state):
    """(kind, detail): merged / closed / attempted / fresh."""
    if merged(name):
        return "merged", "unit file on main"
    if name in closed_set():
        return "closed", f"class proved — {CLOSED_FILE}"
    if name in state:
        res, path = state[name]
        return "attempted", f"best {fmt(res)} — {path}"
    return "fresh", ""


def cmd_sync(a):
    f = git("fetch", "origin")
    if f.returncode != 0:
        sys.exit(f"select: fetch failed\n{f.stderr}")
    sha = git("rev-parse", "origin/main").stdout.strip()
    if head() != sha and not ahead_only_lane(sha):
        co = git("checkout", "-B", a.branch, sha)
        if co.returncode != 0:
            sys.exit(f"select: cannot cut to {sha[:8]} (local work in the way?)\n{co.stderr}")
    if head() != sha and not ahead_only_lane(sha):
        sys.exit(f"select: tree at {head()[:8]} but upstream is {sha[:8]}")
    bad = dirty_units()
    if bad:
        sys.exit("select: unit files differ from upstream after cut:\n  " + "\n  ".join(bad[:10]))
    stamp_path().write_text(sha + "\n")
    n = len(list((ROOT / UNITS).glob("*.c")))
    ref = records_ref()
    known = len(attempt_state(ref))
    print(f"synced: HEAD = origin/main = {sha[:8]}, src/funcs clean, {n} units"
          + ("" if have_listings() else " (no asm listings here: sizes unavailable until tools/split.py)"))
    print(f"attempts: {known} bodies recorded on {ref}" if ref
          else "attempts: no records branch found — freshness cannot be judged (set LANE_RECORDS_REF)")
    if ref:
        total, changed, now_merged, new, gone = reconcile(attempt_state(ref))
        print(f"reconciled: {total} entries, {now_merged} now merged, {changed} status changes, "
              f"{new} new, {gone} dropped — published {ATTEMPTS}")


def cmd_check(a):
    sha = require_fresh()
    name = a.name if a.name.startswith("func_") else f"func_{a.name}"
    ref = records_ref()
    kind, detail = classify(name, attempt_state(ref))
    if kind == "merged":
        print(f"REFUSED {name}: MERGED on main@{sha[:8]} (src/funcs/{name}.c exists)")
        return 1
    if kind == "closed":
        print(f"REFUSED {name}: CLOSED BY EVIDENCE — {detail}")
        return 1
    if kind == "attempted":
        verdict = "REFUSED (intent fresh)" if a.intent == "fresh" else "OPEN"
        print(f"{verdict} {name}: ATTEMPTED — {detail}")
        return 1 if a.intent == "fresh" else 0
    if not have_listings():
        print(f"OPEN {name}: FRESH at main@{sha[:8]} (no listings in this checkout)")
        return 0
    if not (ROOT / ASM / f"{name}.s").exists():
        print(f"REFUSED {name}: no listing in {ASM}")
        return 1
    if handwritten(name):
        print(f"REFUSED {name}: HANDWRITTEN in {ASM} — not C work")
        return 1
    print(f"OPEN {name}: FRESH, {words(name)} words, absent from main@{sha[:8]}")
    return 0


def cmd_list(a):
    sha = require_fresh()
    if not have_listings():
        sys.exit(f"select: no {ASM} in this checkout — run tools/split.py first "
                 "(a fresh clone has no listings)")
    ref = records_ref()
    state = attempt_state(ref)
    rows, merged_n, attempted_n, nonc_n, closed_n = [], 0, 0, 0, 0
    recorded_merged = sorted(n for n in state if merged(n))
    reasons = {}
    for p in (ROOT / ASM).glob("func_*.s"):
        n = p.stem
        kind, _ = classify(n, state)
        if kind == "merged":
            merged_n += 1
            continue
        if kind == "closed":
            closed_n += 1
            if a.fresh:
                continue
        if kind == "attempted":
            attempted_n += 1
            if a.fresh:
                continue
        if handwritten(n):
            if a.fresh:
                continue
            kind = "handwritten"
        if kind == "fresh":
            ok, why = c_writable(n)
            if not ok:
                nonc_n += 1
                if a.fresh:
                    continue
                kind = "notC"
                reasons[n] = why
        w = words(n)
        if a.min is not None and w < a.min:
            continue
        if a.max is not None and w > a.max:
            continue
        rows.append((w, n, kind))
    rows.sort()
    for w, n, kind in rows[: a.limit]:
        if kind == "handwritten":
            tag = "handwritten"
        elif kind == "notC":
            tag = f"notC: {reasons[n]}"
        elif kind == "closed":
            tag = "closed-by-evidence"
        elif kind == "fresh":
            tag = "fresh"
        else:
            tag = fmt(state[n][0]) if n in state else "attempted"
        print(f"{w:4d} {n} {tag}")
    print(f"# {len(rows)} open in range, {attempted_n} attempted (records: {ref or 'none'}), "
          f"{merged_n} suppressed as merged, {nonc_n} rejected as not C, "
          f"{len(recorded_merged)} recorded-but-merged, {closed_n} closed-by-evidence, tree at {sha[:8]}")


def cmd_draft(a):
    sha = require_fresh()
    name = a.name if a.name.startswith("func_") else f"func_{a.name}"
    ref = records_ref()
    kind, detail = classify(name, attempt_state(ref))
    if kind == "merged":
        sys.exit(f"select: REFUSED {name}: MERGED on main@{sha[:8]} — nothing drafted")
    if kind == "fresh":
        ok, why = c_writable(name)
        if not ok:
            sys.exit(f"select: REFUSED {name}: not writable in C — {why}")
    if kind == "attempted" and not a.allow_attempted:
        sys.exit(f"select: REFUSED {name}: ATTEMPTED — {detail}\n"
                 "select: fresh ground was asked for; pass --allow-attempted to re-test a park")
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
    print(f"drafted {dest.relative_to(ROOT)} (main@{sha[:8]}, {kind})")
    if a.no_measure:
        return 0
    if not have_listings():
        print("select: not measured — no asm listings in this checkout")
        return 0
    return subprocess.run([sys.executable, "tools/match.py", name, "--show"], cwd=ROOT).returncode


def cmd_crule(a):
    require_fresh()
    for raw in a.names:
        name = raw if raw.startswith("func_") else f"func_{raw}"
        ok, why = c_writable(name)
        print(f"{name}: {'C' if ok else 'NOT C'} — {why or 'frame, $ra and $sp are compiler-shaped'}")
    return 0


def cmd_reconcile(a):
    require_fresh()
    ref = records_ref()
    if not ref:
        sys.exit("select: no records branch — nothing to reconcile")
    state = attempt_state(ref)
    total, changed, now_merged, new, gone = reconcile(state)
    print(f"reconciled: {total} entries, {now_merged} now merged, {changed} status changes, "
          f"{new} new, {gone} dropped — published {ATTEMPTS}")
    for name in sorted(n for n in state if merged(n)):
        print(f"  merged  {name}")
    return 0


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("sync")
    s.add_argument("--branch", default="lane/work")
    s.set_defaults(fn=cmd_sync)
    r = sub.add_parser("reconcile")
    r.add_argument("--records", default=None)
    r.set_defaults(fn=cmd_reconcile)
    for name, fn in (("check", cmd_check), ("list", cmd_list), ("draft", cmd_draft)):
        p = sub.add_parser(name)
        p.add_argument("--records", default=None, help="records ref to read attempt state from")
        p.set_defaults(fn=fn)
        if name == "check":
            p.add_argument("name")
            p.add_argument("--intent", choices=("fresh", "any"), default="fresh")
        elif name == "list":
            p.add_argument("--min", type=int)
            p.add_argument("--max", type=int)
            p.add_argument("--limit", type=int, default=20)
            p.add_argument("--fresh", action="store_true", help="never-attempted bodies only")
        else:
            p.add_argument("name")
            p.add_argument("--src", required=True)
            p.add_argument("--allow-attempted", action="store_true")
            p.add_argument("--no-measure", action="store_true")
    p = sub.add_parser("crule")
    p.add_argument("--records", default=None)
    p.add_argument("names", nargs="+")
    p.set_defaults(fn=cmd_crule)
    a = ap.parse_args()
    if getattr(a, "records", None):
        os.environ["LANE_RECORDS_REF"] = a.records
    sys.exit(a.fn(a) or 0)


if __name__ == "__main__":
    main()
