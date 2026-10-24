#!/usr/bin/env python3
"""One-command, idempotent toolchain install. No root needed.

    python3 toolchain/setup.py            # everything
    python3 toolchain/setup.py --check    # verify only (what the judge runs)

Installs into toolchain/ (git-ignored):
  bin/cc1                      pinned compiler (compiler.toml), sha256-verified
  bin/mipsel-linux-gnu-*       GNU binutils (PATH, or the distro .deb unpacked without root)
  bin/objdiff-cli              pinned release, sha256-verified
  m2c/, decomp-permuter/       pinned commits
  dl/psx_psyq_signatures/      pinned commit (tools/psyq_identify.py)
  ../.venv                     Python deps from requirements.txt (via uv if present)
  maspsx                       git submodule at the commit recorded in the superproject

Ends with a self-test: a canary C file must compile to known bytes, so a
broken toolchain is caught before it judges anything.
"""
import argparse
import hashlib
import os
import shutil
import subprocess
import sys
import tarfile
import tomllib
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TC = ROOT / "toolchain"
BIN = TC / "bin"
DL = TC / "dl"

OBJDIFF = {
    "url": "https://github.com/encounter/objdiff/releases/download/v3.8.2/objdiff-cli-linux-x86_64",
    "sha256": "e5445089a6f707e30cb5e02992451b604619cedfd2660ee2373a86bfefd9e718",
}
GIT_PINS = {
    "m2c": ("https://github.com/matt-kempster/m2c", "c632946b8cfbe8fce442b522dba92dfa72f1f317", TC / "m2c"),
    "decomp-permuter": ("https://github.com/simonlindholm/decomp-permuter",
                        "8556c81d80d1c1af98a858c8f4dc951357f29139", TC / "decomp-permuter"),
    "psx_psyq_signatures": ("https://github.com/lab313ru/psx_psyq_signatures",
                            "e9e46e7e133ef275a79bfce650924f98edb086bc", DL / "psx_psyq_signatures"),
}
BINUTILS = ["as", "ld", "objcopy", "objdump", "nm", "readelf"]
BINUTILS_DEB = "binutils-mipsel-linux-gnu"



def say(msg):
    print(f"[setup] {msg}", flush=True)


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def fetch(url, dest, want):
    dest.parent.mkdir(parents=True, exist_ok=True)
    if dest.exists() and sha256(dest) == want:
        return dest
    say(f"download {url}")
    tmp = dest.with_suffix(dest.suffix + ".part")
    with urllib.request.urlopen(url) as r, open(tmp, "wb") as f:
        shutil.copyfileobj(r, f)
    got = sha256(tmp)
    if got != want:
        tmp.unlink()
        sys.exit(f"sha256 mismatch for {url}: {got} != {want}")
    os.replace(tmp, dest)
    return dest


def install_compiler(cfg, check):
    name = cfg["compiler"]["name"]
    spec = cfg["compilers"][name]
    tgz = DL / Path(spec["url"]).name
    out = DL / name
    cc1 = BIN / "cc1"
    if check:
        if not cc1.exists():
            sys.exit("cc1 missing")
        return
    fetch(spec["url"], tgz, spec["sha256"])
    if not (out / "cc1").exists():
        out.mkdir(parents=True, exist_ok=True)
        with tarfile.open(tgz) as t:
            t.extractall(out, filter="data")
    BIN.mkdir(exist_ok=True)
    if cc1.exists() or cc1.is_symlink():
        cc1.unlink()
    shutil.copy2(out / "cc1", cc1)
    cc1.chmod(0o755)
    say(f"compiler {name} -> toolchain/bin/cc1")


def install_binutils(check):
    BIN.mkdir(exist_ok=True)
    have = all((BIN / f"mipsel-linux-gnu-{t}").exists() for t in BINUTILS)
    if have:
        return
    if check:
        sys.exit("binutils missing")
    on_path = shutil.which("mipsel-linux-gnu-as")
    if on_path:
        prefix = Path(on_path).parent
        for t in BINUTILS:
            (BIN / f"mipsel-linux-gnu-{t}").symlink_to(prefix / f"mipsel-linux-gnu-{t}")
        say(f"binutils from PATH ({prefix})")
        return
    if not shutil.which("apt-get"):
        sys.exit("need mipsel-linux-gnu binutils: install binutils-mipsel-linux-gnu or use the Dockerfile")
    root = DL / "binutils"
    root.mkdir(parents=True, exist_ok=True)
    subprocess.run(["apt-get", "download", BINUTILS_DEB], cwd=root, check=True)
    deb = next(root.glob(f"{BINUTILS_DEB}_*.deb"))
    subprocess.run(["dpkg-deb", "-x", str(deb), str(root)], check=True)
    libdir = next(p for p in root.rglob("libbfd-*mipsel*.so")).parent
    for t in BINUTILS:
        w = BIN / f"mipsel-linux-gnu-{t}"
        w.write_text(f'#!/bin/sh\nexport LD_LIBRARY_PATH="{libdir}${{LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}}"\n'
                     f'exec "{root}/usr/bin/mipsel-linux-gnu-{t}" "$@"\n')
        w.chmod(0o755)
    say(f"binutils unpacked from {deb.name} (no root)")


def install_objdiff(check):
    dest = BIN / "objdiff-cli"
    if check:
        if not dest.exists() or sha256(dest) != OBJDIFF["sha256"]:
            sys.exit("objdiff-cli missing or wrong sha256")
        return
    fetch(OBJDIFF["url"], dest, OBJDIFF["sha256"])
    dest.chmod(0o755)


def install_git(check):
    for name, (url, rev, dest) in GIT_PINS.items():
        if check:
            if not dest.exists():
                sys.exit(f"{name} missing")
            continue
        if not (dest / ".git").exists():
            say(f"clone {name}")
            subprocess.run(["git", "clone", "-q", url, str(dest)], check=True)
        cur = subprocess.run(["git", "-C", str(dest), "rev-parse", "HEAD"], capture_output=True,
                             text=True).stdout.strip()
        if cur != rev:
            subprocess.run(["git", "-C", str(dest), "fetch", "-q", "origin", rev], check=False)
            subprocess.run(["git", "-C", str(dest), "checkout", "-q", rev], check=True)


def install_submodules(check):
    if check:
        if not (TC / "maspsx" / "maspsx.py").exists():
            sys.exit("maspsx submodule missing: git submodule update --init")
        return
    subprocess.run(["git", "submodule", "update", "--init", "--recursive"], cwd=ROOT, check=True)


def install_venv(check):
    venv = ROOT / ".venv"
    py = venv / "bin" / "python"
    if check:
        if not py.exists():
            sys.exit(".venv missing")
        return
    uv = shutil.which("uv")
    if not py.exists():
        if uv:
            subprocess.run([uv, "venv", "-q", str(venv)], check=True)
        else:
            subprocess.run([sys.executable, "-m", "venv", str(venv)], check=True)
    if uv:
        subprocess.run([uv, "pip", "install", "-q", "-p", str(py), "-r", "requirements.txt"],
                       cwd=ROOT, check=True)
    else:
        subprocess.run([str(py), "-m", "pip", "install", "-q", "-r", "requirements.txt"],
                       cwd=ROOT, check=True)


def self_test():
    py = ROOT / ".venv" / "bin" / "python"
    r = subprocess.run([str(py), "tools/toolcheck.py"], cwd=ROOT)
    if r.returncode != 0:
        sys.exit("toolchain self-test FAILED")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--minimal", action="store_true",
                    help="compiler, binutils, objdiff, venv only (CI compile job)")
    a = ap.parse_args()
    cfg = tomllib.loads((TC / "compiler.toml").read_text())
    install_submodules(a.check)
    install_venv(a.check)
    install_compiler(cfg, a.check)
    install_binutils(a.check)
    install_objdiff(a.check)
    if not a.minimal:
        install_git(a.check)
    self_test()
    say("OK")


if __name__ == "__main__":
    main()
