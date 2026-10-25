#!/usr/bin/env python3
"""The single owner of every measured number about the parked corpus.

    python work/verify.py              # measure what the cache does not cover, print a summary
    python work/verify.py --write      # ... and rewrite the generated table in the census
    python work/verify.py --only func_80048598
    python work/verify.py --jobs 4     # parallel compiles (default 4)
    python work/verify.py --clear      # drop the cache and measure everything again

Corpus: every unmatched `func_` body in config/functions.us.csv. A body counts as *drafted* when
work/near-miss/ holds a file for it; everything else has nothing to compile yet and gets no row.
Every draft of a drafted body is measured, the best one is copied to work/best/<body>.c (a stable
path with no number in its name) and the table records:

    body   draft   source   words   total   size   class   verdict

`class` is derived from the diff itself, never asserted, so it cannot drift from the measurement:
match, size, register-role, immediate, relocation, operand, instruction-stream, compile-error.
`verdict` checks the census's recorded residue class for that body against what the body now
measures.

Counts live in work/verify-cache.json keyed by the draft's content and the toolchain fingerprint,
so a rerun only compiles what changed and a toolchain change invalidates everything by itself.
No other script measures the corpus: diffscan, diffscan2, level_matrix, level_all, sweep,
scale_sweep, retest, tail_probe, queue_probe and flag_matrix were folded in here and deleted.
The enumerators (enum_fresh, enum_small, enum_band, family_queue) and the scanners (addrscan,
addrpairs, memberbase, delay_probe) find candidate bodies and own no numbers.
"""
import argparse
import hashlib
import json
import os
import re
import shutil
import sys
from collections import Counter, defaultdict
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))

import match as m  # noqa: E402
from common import BUILD, FUNCTIONS_CSV, SRC_FUNCS, load_functions  # noqa: E402

WORK = ROOT / "work"
DRAFTS = WORK / "near-miss"
BEST = WORK / "best"
CACHE = WORK / "verify-cache.json"
TABLE = WORK / "verify-table.tsv"
CENSUS = WORK / "census-corrected.md"
BEGIN = "<!-- BEGIN GENERATED TABLE -->"
END = "<!-- END GENERATED TABLE -->"

BODY = re.compile(r"func_[0-9A-F]{8}$")
REG = re.compile(r"\$[a-z0-9]+")

# The census's measured-dead class claims, restated here so the table tests them every run:
# label -> (class the diff should show if the claim holds, bodies).
CLAIMS = {
    "register-role": ("register-role", ["func_8001F4E8", "func_8001DB74", "func_8002FE80"]),
    "move-vs-materialise": ("move-vs-materialise", ["func_8002050C"]),
    "filled-nop": ("size", ["func_80022308", "func_800223AC"]),
    "fixed-point": ("size", ["func_800331FC", "func_8003302C", "func_8003353C"]),
}
CLASS_OF = {body: (label, want) for label, (want, bodies) in CLAIMS.items() for body in bodies}

# Bodies that match but cannot ship yet, with the reason. Kept here so the table cannot call
# them conversions.
BLOCKED = {"func_80034B98": "scan: needs D_801FC000 (issue #101)"}


# Bump when the classifier or a recorded column changes: it invalidates the cache.
VERSION = 3


def fingerprint():
    """Hash of everything whose change would silently invalidate a cached count."""
    h = hashlib.sha256(str(VERSION).encode())
    for p in (ROOT / "toolchain" / "compiler.toml",
              ROOT / "toolchain" / "maspsx" / "maspsx" / "__init__.py"):
        if p.exists():
            h.update(p.read_bytes())
    return h.hexdigest()[:16]


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()[:16]


def drafted_bodies():
    """body -> [draft paths], from the corpus directory only."""
    out = defaultdict(list)
    for f in sorted(DRAFTS.glob("*.c")):
        hit = re.search(r"func_[0-9A-F]{8}", f.name)
        if hit:
            out[hit.group(0)].append(f)
    return out


def corpus():
    """Unmatched code bodies, split into drafted and undrafted."""
    merged = {f.stem for f in SRC_FUNCS.glob("func_*.c")}
    unmatched = [r["name"] for r in load_functions()
                 if r["kind"] == "func" and r["segment"] == "game" and r["name"] not in merged]
    drafts = drafted_bodies()
    return sorted(unmatched), drafts


def classify(res):
    if res.error:
        return "compile-error"
    if res.ok:
        return "match"
    t, o = res.target, res.ours
    if len(t.words) != len(o.words):
        return "size"
    # Classify by the first differing word: it is the cause far more often than the tail is.
    i = res.diffs[0]
    a = m.disasm(t.words[i], i * 4, t.relocs.get(i))
    b = m.disasm(o.words[i], i * 4, o.relocs.get(i))
    if a == b:
        return "relocation"
    ma, _, oa = a.partition(" ")
    mb, _, ob = b.partition(" ")
    if ma == mb:
        if REG.sub("$R", oa) != REG.sub("$R", ob):
            return "operand"
        if REG.findall(oa) == REG.findall(ob):
            return "immediate"
        return "register-role"
    if "nop" in (ma, mb):
        return "scheduling"
    ops = {ma: oa, mb: ob}
    if set(ops) == {"addu", "addiu"}:
        move = [x.strip() for x in ops["addu"].split(",")]
        imm = [x.strip() for x in ops["addiu"].split(",")]
        # move: `addu d, s, $zero`; materialisation: `addiu d, $zero, imm`
        if len(move) == 3 and move[2] == "$zero" and len(imm) == 3 and imm[1] == "$zero":
            return "move-vs-materialise"
    return "instruction-stream"


def measure(job):
    body, path, dig = job
    outdir = BUILD / "verify" / str(os.getpid())
    try:
        res = m.compare(body, src=Path(path), outdir=outdir)
    except Exception as e:  # a body that is not in the csv, a bad draft, a compile crash
        return body, str(path), dig, {"error": type(e).__name__ + ": " + str(e)[:200]}
    if res.error:
        return body, str(path), dig, {"error": res.error[:200]}
    return body, str(path), dig, {
        "words": len(res.diffs),
        "total": len(res.target.words),
        "size": len(res.ours.words) - len(res.target.words),
        "cls": classify(res),
    }


def load_cache():
    try:
        data = json.loads(CACHE.read_text())
    except (OSError, ValueError):
        data = {}
    if data.get("fingerprint") != fingerprint():
        return {"fingerprint": fingerprint(), "rows": {}}
    return data


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--write", action="store_true", help="rewrite the generated table in the census")
    ap.add_argument("--only", action="append", default=[], help="restrict to these bodies")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--clear", action="store_true")
    ap.add_argument("--drift", action="store_true",
                    help="compare the journal's hand-written counts with this measurement")
    args = ap.parse_args()

    unmatched, drafts = corpus()
    bodies = sorted(drafts)
    if args.only:
        bodies = [b for b in bodies if b in set(args.only)]
    if not bodies:
        print("no drafted bodies in %s" % DRAFTS)
        return 1

    cache = {"fingerprint": fingerprint(), "rows": {}} if args.clear else load_cache()
    rows = cache["rows"]

    jobs = []
    for body in bodies:
        for path in drafts[body]:
            key = "%s::%s::%s" % (body, path.name, digest(path))
            if key not in rows:
                jobs.append((body, str(path), key))
    print("%d drafted bodies, %d drafts, %d to measure" %
          (len(bodies), sum(len(drafts[b]) for b in bodies), len(jobs)))
    if jobs:
        with ProcessPoolExecutor(max_workers=args.jobs) as ex:
            for body, path, key, rec in ex.map(measure, jobs):
                rows[key] = rec
        CACHE.write_text(json.dumps(cache, indent=0, sort_keys=True) + "\n")

    merged = {f.stem for f in SRC_FUNCS.glob("func_*.c")}
    table, stale = [], []
    for body in bodies:
        if body in merged:
            stale.append(body)
            continue
        best = None
        for path in drafts[body]:
            key = "%s::%s::%s" % (body, path.name, digest(path))
            rec = rows[key]
            if "error" in rec:
                cand = (10 ** 6, 10 ** 6, path.name, path, rec)
            else:
                cand = (rec["words"], abs(rec["size"]), path.name, path, rec)
            if best is None or cand[:3] < best[:3]:
                best = cand
        _, _, _, path, rec = best
        if "error" in rec:
            table.append(dict(body=body, cls="compile-error", words="", total="", size="",
                              src=str(path.relative_to(ROOT)), status="broken", verdict=""))
            continue
        verdict = ""
        claimed = CLASS_OF.get(body)
        if claimed:
            label, want = claimed
            verdict = ("holds (%s)" % label) if want == rec["cls"] else \
                      "DRIFT: was %s, now %s" % (label, rec["cls"])
        status = "ready" if rec["cls"] == "match" else "parked"
        if body in BLOCKED:
            verdict = BLOCKED[body]
            status = "blocked"
        table.append(dict(body=body, cls=rec["cls"], words=rec["words"], total=rec["total"],
                          size=rec["size"], src=str(path.relative_to(ROOT)), status=status,
                          verdict=verdict))

    if args.drift:
        report_drift(table)
        return 0

    BEST.mkdir(exist_ok=True)
    for row in table:
        if row["src"]:
            body = row["body"]
            dst = BEST / (body + ".c")
            src = ROOT / row["src"]
            if src.stat().st_size:
                shutil.copyfile(src, dst)
            row["draft"] = str(dst.relative_to(ROOT))
        else:
            row["draft"] = "-"

    TABLE.write_text("body\tstatus\tdraft\tsource\twords\ttotal\tsize\tclass\tverdict\n" + "".join(
        "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n" % (
            r["body"], r["status"], r["draft"], r["src"], r["words"], r["total"], r["size"],
            r["cls"], r["verdict"]) for r in table))

    hist = Counter(r["cls"] for r in table)
    print("corpus: %d unmatched bodies, %d drafted and measured, %d stale drafts to prune" %
          (len(unmatched), len(table), len(stale)))
    if stale:
        print("stale (already merged): " + " ".join(sorted(stale)))
    print("classes: " + ", ".join("%s=%d" % kv for kv in sorted(hist.items())))
    for label, (want, members) in CLAIMS.items():
        seen = [r for r in table if r["body"] in members]
        drift = [r for r in seen if r["verdict"].startswith("DRIFT")]
        print("class %-14s %d claimed, %d measured, %d hold" %
              (label, len(members), len(seen), len(seen) - len(drift)))
        for r in drift:
            print("   " + r["verdict"] + " " + r["body"])
    near = [r for r in table if isinstance(r["words"], int) and r["words"] <= 5]
    if near:
        print("within five words: " + ", ".join("%s %s/%s" % (r["body"], r["words"], r["total"])
                                                for r in near))

    if args.write:
        block = render(table, len(unmatched), hist, len(stale))
        text = CENSUS.read_text()
        if BEGIN in text and END in text:
            text = text[:text.index(BEGIN)] + block + text[text.index(END) + len(END):]
        else:
            head, rest = text.split("\n", 1)
            text = (head + "\n\n" + block.strip() +
                    "\n---\n\n## Pass journal (history: numbers here are superseded by the table above)\n" +
                    rest)
        CENSUS.write_text(text)
        print("census table rewritten (%d rows)" % len(table))
    return 0


def report_drift(table):
    """Report every journal row whose hand-written count disagrees with the measurement."""
    best = {r["body"]: (r["words"], r["total"]) for r in table if isinstance(r["words"], int)}
    text = CENSUS.read_text()
    journal = text[text.index(END):] if END in text else text
    seen = agree = 0
    for line in journal.splitlines():
        head = re.match(r"\|\s*`?(func_[0-9A-F]{8})`?\s*\|([^|]*)\|?", line)
        if not head or head.group(1) not in best:
            continue
        nums = re.findall(r"\*\*(\d+)/(\d+)\*\*|(?<![\d/])(\d+)/(\d+)(?![\d/])", head.group(2))
        flat = [x for tup in nums for x in tup if x]
        if len(flat) < 2:
            continue
        seen += 1
        pair = (int(flat[0]), int(flat[1]))
        if pair == best[head.group(1)]:
            agree += 1
        else:
            print("journal %d/%d  table %d/%d  %s" %
                  (pair[0], pair[1], best[head.group(1)][0], best[head.group(1)][1], head.group(1)))
    print("journal rows compared: %d, agree %d, disagree %d" % (seen, agree, seen - agree))
    return seen - agree


def render(table, unmatched, hist, stale):
    rows = sorted(table, key=lambda r: (r["words"] if isinstance(r["words"], int) else 10 ** 6,
                                        r["body"]))
    out = [BEGIN, "",
           "## Table of record (generated — do not hand-edit)",
           "",
           "Every per-body number in this file is produced by `python work/verify.py --write`; the",
           "journal sections further down keep the reasoning that led to them and their hand-written",
           "counts are history, not authority. Best drafts live at `work/best/<body>.c`, a path with no",
           "number in it, so a measurement cannot go stale in a filename.",
           "",
           "%d unmatched bodies in the corpus; **%d drafted and measured here** (%s); "
           "%d drafts predate a merge and are prunable."
           % (unmatched, len(table), ", ".join("%s %d" % kv for kv in sorted(hist.items())), stale),
           "",
           "| body | best draft | words | size | class | status | class verdict |",
           "|---|---|---|---|---|---|---|"]
    for r in rows:
        words = "-" if r["words"] == "" else "%d/%d" % (r["words"], r["total"])
        size = "-" if r["size"] == "" else "%+d" % r["size"]
        out.append("| `%s` | `%s` | %s | %s | %s | %s | %s |" %
                   (r["body"], r["src"] or "-", words, size, r["cls"], r["status"],
                    r["verdict"] or "-"))
    out += ["", END, ""]
    return "\n".join(out)


if __name__ == "__main__":
    sys.exit(main())
