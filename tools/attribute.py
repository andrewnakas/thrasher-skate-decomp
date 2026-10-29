#!/usr/bin/env python3
"""Attribute a draft .c file to the unit it was written for, then score it.

Drafts accumulate in `work/` under whatever name the attempt had, and most sweeps could only
use the ones named for a full address (`func_8001C4BC.c`). Two rules find the rest:

1. **Name.** A file name carrying 4-8 hex digits that match the low digits of exactly one
   tracked address (`c4bc-v1.c`, `29488-v1.c`). Four- and five-digit tokens are accepted only
   when they resolve to one unit: this binary's whole span is under 0x100000, so a five-digit
   suffix is unique by construction, while a four-digit token shared by several units is
   ambiguous and is handed to rule 2 instead of being guessed.
2. **Content signature.** The evidence in a listing that survives into any draft of the same
   body: the ordered sequence of calls it makes, the set of globals it touches, and the
   immediate constants it materialises. The nearest unit wins only when it is clearly ahead of
   the runner-up, so a draft that is a near-copy of two units is reported as ambiguous.

    python tools/attribute.py                  # attribute work/**, score what is new
    python tools/attribute.py --dry            # counts only, no compiles
    python tools/attribute.py --drafts work --jobs 4

A score is a measurement of the draft, never a proof that a unit is reachable: a decompiler
body that scores badly says the draft is bad, not that the floor is immovable.

Library use: `scan()` is pure over the units and draft paths it is handed, so tests pin its
counts on a fixture instead of on today's work/ contents.
"""
import argparse
import csv
import hashlib
import re
import sys
from collections import defaultdict
from concurrent.futures import ProcessPoolExecutor
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import BUILD, FUNCTIONS_CSV, ROOT  # noqa: E402

OUT = BUILD / "attribute"
GAME_TOP = 0x80058633
DEFAULT_LENGTHS = (4, 5, 6, 8)

TOKEN = re.compile(r"(?<![0-9A-Fa-f])([0-9A-Fa-f]{4,8})(?![0-9A-Fa-f])")
UNIT_IN_NAME = re.compile(r"func_([0-9A-Fa-f]{8})")

# --- listing side -------------------------------------------------------------------------
L_CALL = re.compile(r"\bjal\s+([A-Za-z_.][\w.]*)")
L_GP = re.compile(r"%gp_rel\(\s*(D_[0-9A-F]{8})\s*\)")
L_ABS = re.compile(r"%hi\(\s*(D_[0-9A-F]{8})\s*\)")
L_IMM = re.compile(r"\b(?:ori|addiu|slti|sltiu|andi|xori)\s+\$\w+,\s*\$\w+,\s*(-?0x[0-9A-Fa-f]+|-?\d+)")

# --- draft side ---------------------------------------------------------------------------
C_DEF = re.compile(r"^[^\n;{}]*?\b(func_[0-9A-F]{8})\s*\([^\n]*\)\s*\{", re.M)
C_CALL = re.compile(r"\b(func_[0-9A-F]{8})\s*\(")
C_GLOBAL = re.compile(r"\b(D_[0-9A-F]{8})\b")
C_IMM = re.compile(r"(?<![\w.])(-?0x[0-9A-Fa-f]+|-?\d+)(?![\w.])")
C_COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)

WEIGHT_CALLS, WEIGHT_GLOBALS, WEIGHT_IMMEDIATES = 0.5, 0.35, 0.15
MIN_SCORE = 0.55
MIN_MARGIN = 0.15


@dataclass(frozen=True)
class Signature:
    calls: tuple
    globals: frozenset
    immediates: frozenset


@dataclass(frozen=True)
class Unit:
    name: str
    listing: str
    signature: Signature


@dataclass
class Draft:
    path: Path
    unit: str = ""
    rule: str = ""          # "name" | "signature" | ""
    score: float = 0.0
    margin: float = 0.0


@dataclass
class Scan:
    drafts: list = field(default_factory=list)
    by_name: int = 0
    by_signature: int = 0
    ambiguous_name: int = 0
    ambiguous_signature: int = 0
    unattributed: int = 0
    duplicates: int = 0


def _imm(text):
    """Normalise an immediate to the unsigned 32-bit value the instruction actually holds."""
    return int(text, 0) & 0xFFFFFFFF


def listing_signature(text):
    calls = tuple(L_CALL.findall(text))
    globals_ = frozenset(L_GP.findall(text)) | frozenset(L_ABS.findall(text))
    imms = frozenset(_imm(v) for v in L_IMM.findall(text))
    return Signature(calls, globals_, imms)


def draft_signature(text):
    text = C_COMMENT.sub(" ", text)
    defs = set(C_DEF.findall(text))
    calls = tuple(c for c in C_CALL.findall(text) if c not in defs)
    globals_ = frozenset(C_GLOBAL.findall(text))
    imms = frozenset(_imm(v) for v in C_IMM.findall(text))
    return Signature(calls, globals_, imms)


def units_from_csv(csv_path=FUNCTIONS_CSV, root=ROOT, lengths=DEFAULT_LENGTHS):
    """Every game function whose listing exists, matched or not."""
    units = []
    with open(csv_path) as f:
        for r in csv.DictReader(f):
            if r["kind"] != "func":
                continue
            addr = int(r["addr"], 16)
            if addr > GAME_TOP:
                continue
            listing = Path(root) / r["asm"]
            if not listing.exists():
                continue
            units.append(Unit("func_%08X" % addr, listing.read_text(),
                              listing_signature(listing.read_text())))
    return units


def suffix_index(names, lengths=DEFAULT_LENGTHS):
    """token length -> suffix -> [unit names]. Built over every tracked function."""
    index = {n: defaultdict(list) for n in lengths}
    for name in names:
        addr = name[5:]
        for n in lengths:
            index[n][addr[-n:]].append(name)
    return index


def identify_name(stem, index):
    """(unit, "") / ("", "ambiguous") / (None, "") for a draft file name."""
    ambiguous = False
    for m in TOKEN.finditer(stem):
        token = m.group(1).upper()
        for n in sorted(index, reverse=True):
            if len(token) != n:
                continue
            hits = index[n].get(token, [])
            if len(hits) == 1:
                return hits[0], ""
            if len(hits) > 1:
                ambiguous = True
    return (None, "ambiguous" if ambiguous else "")


def _lcs(a, b):
    if not a or not b:
        return 0
    prev = [0] * (len(b) + 1)
    for x in a:
        cur = [0]
        for j, y in enumerate(b):
            cur.append(prev[j] + 1 if x == y else max(prev[j + 1], cur[j]))
        prev = cur
    return prev[-1]


def _jaccard(a, b):
    if not a and not b:
        return 0.0
    return len(a & b) / len(a | b)


def similarity(draft, unit):
    """Weighted over the features this pair actually has: a body with nothing but calls must be
    able to score 1.0 instead of being held under the threshold by two empty feature sets."""
    parts = []
    if draft.calls or unit.calls:
        parts.append((WEIGHT_CALLS,
                      _lcs(draft.calls, unit.calls) / max(len(draft.calls), len(unit.calls), 1)))
    if draft.globals or unit.globals:
        parts.append((WEIGHT_GLOBALS, _jaccard(draft.globals, unit.globals)))
    if draft.immediates or unit.immediates:
        parts.append((WEIGHT_IMMEDIATES, _jaccard(draft.immediates, unit.immediates)))
    total = sum(w for w, _ in parts)
    return sum(w * v for w, v in parts) / total if total else 0.0


def candidate_index(units):
    """call or global -> units, so a draft is scored only against plausible owners."""
    index = defaultdict(set)
    for u in units:
        for c in u.signature.calls:
            index[c].add(u.name)
        for g in u.signature.globals:
            index[g].add(u.name)
    return index


def identify_signature(sig, by_name, index):
    """(unit, score, margin) when one unit is clearly nearest, else ("", 0, margin)."""
    if not sig.calls and len(sig.globals) < 2:
        return "", 0.0, 0.0        # nothing distinctive: a guess, not evidence
    names = set()
    for c in sig.calls:
        names |= index.get(c, set())
    for g in sig.globals:
        names |= index.get(g, set())
    scored = sorted(((similarity(sig, by_name[n].signature), n)
                     for n in names if n in by_name), reverse=True)
    if not scored:
        return "", 0.0, 0.0
    best, best_name = scored[0]
    second = scored[1][0] if len(scored) > 1 else 0.0
    margin = best - second
    if best >= MIN_SCORE and margin >= MIN_MARGIN:
        return best_name, best, margin
    return "", best, margin


def scan(drafts, units, index_names=None, lengths=DEFAULT_LENGTHS, signatures=None):
    """Attribute every draft under `drafts` (a directory or a list of paths)."""
    paths = ([p for p in Path(drafts).rglob("*.c")] if not isinstance(drafts, (list, tuple))
             else [Path(p) for p in drafts])
    index_names = index_names or suffix_index([u.name for u in units], lengths)
    by_name = {u.name: u for u in units}
    signatures = candidate_index(units) if signatures is None else signatures
    result = Scan()
    seen = set()
    for path in sorted(paths):
        unit, why = identify_name(path.stem, index_names)
        rule, score, margin = ("name", 1.0, 1.0) if unit else ("", 0.0, 0.0)
        if not unit:
            sig = draft_signature(path.read_text(errors="replace"))
            unit, score, margin = identify_signature(sig, by_name, signatures)
            if unit:
                rule = "signature"
            elif why == "ambiguous":
                result.ambiguous_name += 1      # each draft has exactly one outcome
            elif margin:
                result.ambiguous_signature += 1
            else:
                result.unattributed += 1
            if not unit:
                continue
        digest = hashlib.sha1(path.read_bytes()).hexdigest()
        if (unit, digest) in seen:
            result.duplicates += 1
            continue
        seen.add((unit, digest))
        if rule == "name":
            result.by_name += 1
        else:
            result.by_signature += 1
        result.drafts.append(Draft(path, unit, rule, score, margin))
    return result


def score(job):
    import match as mm
    unit, src, outdir = job
    od = Path(outdir)
    od.mkdir(parents=True, exist_ok=True)
    try:
        res = mm.compare(unit, str(src), outdir=od)
    except Exception as e:  # noqa: BLE001
        return (unit, str(src), None, 0, 0, str(e).splitlines()[0][:90])
    if res.error:
        return (unit, str(src), None, 0, 0, res.error.splitlines()[0][:90])
    return (unit, str(src), len(res.diffs), len(res.target.words),
            len(res.ours.words), "MATCH" if res.ok else "")


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--drafts", default=str(ROOT / "work"))
    ap.add_argument("--dry", action="store_true", help="attribute only, no compiles")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--json", action="store_true", help="one JSON object, for scripts")
    a = ap.parse_args(argv)

    units = units_from_csv()
    unmatched = [u for u in units
                 if not (ROOT / "src" / "funcs" / (u.name + ".c")).exists()]
    index_names = suffix_index([u.name for u in units])
    index_sig = candidate_index(unmatched)

    paths = [p for p in Path(a.drafts).rglob("*.c")
             if "gp-sweep" not in p.parts and "attribute" not in p.parts]
    attributed = scan(paths, units, index_names, signatures=index_sig)
    wanted = {u.name for u in unmatched}
    new = [d for d in attributed.drafts if d.unit in wanted]

    counts = dict(files=len(paths), by_name=attributed.by_name,
                  by_signature=attributed.by_signature,
                  ambiguous_name=attributed.ambiguous_name,
                  ambiguous_signature=attributed.ambiguous_signature,
                  duplicates=attributed.duplicates,
                  unattributed=attributed.unattributed,
                  units=sorted({d.unit for d in new}),
                  drafts_for_unmatched=len(new))
    if a.json:
        import json
        print(json.dumps(counts, indent=2))
        return 0
    print("drafts %(files)d: name %(by_name)d, signature %(by_signature)d, "
          "ambiguous %(ambiguous_name)d name / %(ambiguous_signature)d signature, "
          "duplicate content %(duplicates)d, unattributed %(unattributed)d" % counts)
    print("drafts pointing at still-unmatched units: %d over %d units"
          % (len(new), len(counts["units"])))
    if a.dry:
        for d in sorted(new, key=lambda d: (d.unit, str(d.path))):
            print("  %s  %-38s %-9s %.2f (%.2f)" % (d.unit, d.path.name, d.rule, d.score, d.margin))
        return 0

    OUT.mkdir(parents=True, exist_ok=True)
    jobs = [(d.unit, d.path, str(OUT / "obj" / (d.unit + "-" + d.path.stem))) for d in new]
    with ProcessPoolExecutor(max_workers=a.jobs) as ex:
        rows = list(ex.map(score, jobs, chunksize=2))

    best, errors = {}, 0
    for unit, src, n, target, ours, tag in rows:
        if n is None:
            errors += 1
            continue
        if unit not in best or n < best[unit][1]:
            best[unit] = (src, n, target, ours, tag)
    zeros = sorted(u for u, v in best.items() if v[1] == 0)

    lines = ["# draft attribution", "",
             "drafts %d: name %d, signature %d, ambiguous %d name / %d signature, "
             "duplicate %d, unattributed %d" % (len(paths), attributed.by_name,
                                                attributed.by_signature,
                                                attributed.ambiguous_name,
                                                attributed.ambiguous_signature,
                                                attributed.duplicates,
                                                attributed.unattributed),
             "drafts for unmatched units: %d; scored %d; did not compile %d"
             % (len(new), len(jobs) - errors, errors),
             "units at zero words: %d" % len(zeros), ""]
    for unit in sorted(best, key=lambda k: (best[k][1], k)):
        src, n, target, ours, tag = best[unit]
        lines.append("%-14s %3d/%-3d %s" % (unit, n, target, tag or Path(src).relative_to(ROOT)))
    (OUT / "report.md").write_text("\n".join(lines) + "\n")
    print("\n".join(lines[:5]))
    print("report: %s" % (OUT / "report.md").relative_to(ROOT))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
