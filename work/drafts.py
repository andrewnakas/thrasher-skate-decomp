#!/usr/bin/env python3
"""The one owner of "which draft files exist, and which body is each one for".

enumerate.py, extern_audit.py and verify.py each used to glob work/near-miss/ and work/best/ on
their own, which is how the work/shapes/ batch drafts stayed invisible: the enumerator reported
bodies that already had five drafts as undrafted ground, and the measure script gave them no row at
all. Import this instead of globbing.

Filenames written by hand over the session use four conventions for the same address
(`func_80019C0C-w1.c`, `c1db74-a.c`, `n159D8-b.c`, `v19c4-a.c`), so a name is resolved by its
trailing hex run checked against the corpus: the body it names is the unique game function whose
address ends in those digits. An ambiguous or unknown name is reported rather than guessed, because
attributing a draft to the wrong body silently corrupts every count derived from it.
"""
import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DIRS = (ROOT / "work" / "near-miss", ROOT / "work" / "shapes")

FUNC = re.compile(r"func_([0-9A-Fa-f]{8})")
HEXRUN = re.compile(r"[0-9A-Fa-f]+$")

# Four hex digits are not enough to name an address uniquely, so the handful of drafts written that
# way are listed here instead of guessed. Each was checked against its listing before being added.
ALIASES = {
    "v19c4": "func_800519C4",
    "v84b4": "func_800484B4",
    "v8598": "func_80058598",
}


def game_bodies():
    """Every game function address in the corpus, as func_XXXXXXXX names."""
    import csv
    out = []
    with open(ROOT / "config" / "functions.us.csv") as fh:
        for row in csv.DictReader(fh):
            try:
                addr = int(row["addr"], 16)
            except (KeyError, ValueError):
                continue
            if 0x80010000 <= addr <= 0x80058633:
                out.append("func_%08X" % addr)
    return out


def resolver(bodies=None):
    """name -> body, for every draft file name under DIRS (body is None when unresolved)."""
    known = bodies if bodies is not None else game_bodies()
    def body_of(name):
        hit = FUNC.search(name)
        if hit:
            return "func_" + hit.group(1).upper()
        # A trailing `-b` shape tag is a label, not part of the address.
        stem = name.split(".")[0].lower().split("-")[0]
        for alias, body in ALIASES.items():
            if stem.startswith(alias):
                return body
        # Longest trailing hex run first: `c1db74` is a `c`-prefixed 5-digit address, not a 6-digit
        # one, and the longer reading never resolves while the shorter one does.
        hit = HEXRUN.search(stem)
        if hit:
            run = hit.group(0).upper()
            for size in range(min(6, len(run)), 3, -1):
                cands = [b for b in known if b.endswith(run[-size:])]
                if len(cands) == 1:
                    return cands[0]
        return None
    return body_of


def paths():
    """(path, body) for every draft on disk; body may be None for an unresolvable name."""
    body_of = resolver()
    for d in DIRS:
        for f in sorted(d.glob("*.c")):
            yield f, body_of(f.name)


def by_body():
    """body -> [draft paths], both corpus directories merged."""
    out = {}
    for f, body in paths():
        if body:
            out.setdefault(body, []).append(f)
    return out


def unresolved():
    return [f for f, body in paths() if body is None]


def merged_bodies():
    """Bodies with a unit file that is committed here or on origin/main.

    Tracked files only, and that is the point: a pass that measures a draft by copying it to
    src/funcs/<body>.c leaves a file with no commit behind it, and a corpus check that trusts any file
    present reports the body as shipped. Pass 31 rewrote the census table with func_800212BC copied in
    for measurement, pruned its parked row as stale and counted 394 bodies in the queue instead of
    395. The origin/main side stays because a records branch behind main must still see the units
    another lane shipped.
    """
    out = set()
    for cmd in (["git", "ls-files", "src/funcs/"],
                ["git", "ls-tree", "--name-only", "origin/main", "src/funcs/"]):
        try:
            listed = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True,
                                    timeout=30, check=False)
        except (OSError, subprocess.SubprocessError):
            continue
        for line in listed.stdout.splitlines():
            name = Path(line).stem
            if name.startswith("func_"):
                out.add(name)
    if not out:
        # No git to ask. The working tree is the right answer whenever it is clean, which is how a
        # records branch is supposed to be regenerated.
        out = {p.stem for p in (ROOT / "src" / "funcs").glob("func_*.c")}
    return out


if __name__ == "__main__":
    grouped = by_body()
    print("%d bodies drafted, %d draft files, %s" %
          (len(grouped), sum(len(v) for v in grouped.values()),
           ", ".join(d.name for d in DIRS)))
    lost = unresolved()
    if lost:
        print("unresolved names (%d): %s" % (len(lost), " ".join(f.name for f in lost)))
