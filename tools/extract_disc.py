#!/usr/bin/env python3
"""Extract and verify the Thrasher: Skate and Destroy (USA) disc.

Reads ISO9660 straight from a raw MODE2/2352 track (no mounting, no root),
checks SYSTEM.CNF boots SLUS_009.35, writes every file to disc/files/ and
compares SHA-1s against config/checksums.us.sha1.

    python tools/extract_disc.py [path/to/track.bin]   # default: first .bin under disc/
    python tools/extract_disc.py --write-checksums     # (maintainer) record checksums

Form-2 (XA audio / STR video) files are written as raw 2352-byte sectors,
since their payload is not 2048-byte user data.
"""
import argparse
import hashlib
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SECTOR = 2352
USER = 2048
EXPECTED_SERIAL = "SLUS_009.35"
CHECKSUMS = ROOT / "config" / "checksums.us.sha1"


class Disc:
    def __init__(self, path):
        self.f = open(path, "rb")
        self.nsectors = path.stat().st_size // SECTOR

    def raw(self, lba):
        self.f.seek(lba * SECTOR)
        return self.f.read(SECTOR)

    def is_form2(self, lba):
        # mode 2 XA subheader at 16..23, submode byte bit 5 = form 2
        return bool(self.raw(lba)[18] & 0x20)

    def user(self, lba, count=1):
        return b"".join(self.raw(lba + i)[24:24 + USER] for i in range(count))


def walk(disc, lba, size, prefix=""):
    data = disc.user(lba, (size + USER - 1) // USER)
    off = 0
    while off < len(data):
        rlen = data[off]
        if rlen == 0:  # records never straddle sectors; skip to next
            off = (off // USER + 1) * USER
            continue
        rec = data[off:off + rlen]
        ext = struct.unpack_from("<I", rec, 2)[0]
        ln = struct.unpack_from("<I", rec, 10)[0]
        flags = rec[25]
        nlen = rec[32]
        name = rec[33:33 + nlen]
        off += rlen
        if name in (b"\x00", b"\x01"):
            continue
        name = name.decode("ascii").split(";")[0]
        path = prefix + name
        if flags & 2:
            yield from walk(disc, ext, ln, path + "/")
        else:
            yield path, ext, ln


def read_file(disc, ext, ln):
    n = (ln + USER - 1) // USER
    if any(disc.is_form2(ext + i) for i in range(n)):
        return b"".join(disc.raw(ext + i) for i in range(n)), True
    return disc.user(ext, n)[:ln], False


def sha1(b):
    return hashlib.sha1(b).hexdigest()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("track", nargs="?")
    ap.add_argument("--out", default=str(ROOT / "disc" / "files"))
    ap.add_argument("--write-checksums", action="store_true")
    a = ap.parse_args()

    track = Path(a.track) if a.track else next((ROOT / "disc").rglob("*.bin"), None)
    if not track or not track.exists():
        sys.exit("no disc track found: put your dump under disc/ or pass its path")
    disc = Disc(track)

    pvd = disc.user(16)
    if pvd[1:6] != b"CD001":
        sys.exit(f"{track}: no ISO9660 volume descriptor (not a MODE2/2352 dump?)")
    root = pvd[156:156 + 34]
    rlba, rlen = struct.unpack_from("<I", root, 2)[0], struct.unpack_from("<I", root, 10)[0]

    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)
    sums = {}
    for path, ext, ln in walk(disc, rlba, rlen):
        data, raw = read_file(disc, ext, ln)
        dst = out / path
        dst.parent.mkdir(parents=True, exist_ok=True)
        dst.write_bytes(data)
        sums[path] = sha1(data)
        print(f"{ext:7d} {ln:10d} {'raw ' if raw else ''}{path}")

    cnf = (out / "SYSTEM.CNF").read_text(errors="replace")
    boot = next((l for l in cnf.splitlines() if l.strip().upper().startswith("BOOT")), "")
    if EXPECTED_SERIAL not in boot.upper():
        sys.exit(f"SYSTEM.CNF boots {boot.strip()!r}, expected {EXPECTED_SERIAL}: wrong disc/region")
    print(f"boot: {boot.strip()}")

    if a.write_checksums:
        lines = [f"{h}  {p}" for p, h in sorted(sums.items())]
        CHECKSUMS.write_text("\n".join(lines) + "\n")
        print(f"wrote {CHECKSUMS.relative_to(ROOT)} ({len(lines)} files)")
        return

    if not CHECKSUMS.exists():
        sys.exit("config/checksums.us.sha1 missing")
    bad = 0
    for line in CHECKSUMS.read_text().splitlines():
        h, p = line.split(None, 1)
        if sums.get(p) != h:
            print(f"MISMATCH {p}: {sums.get(p)} != {h}")
            bad += 1
    if bad:
        sys.exit(f"{bad} file(s) differ from the known-good USA disc")
    print(f"OK: {len(sums)} files match config/checksums.us.sha1")


if __name__ == "__main__":
    main()
