"""The pinned toolchain compiles the canary to the recorded bytes (skipped without a toolchain)."""
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parent.parent


@pytest.mark.skipif(not (ROOT / "toolchain" / "bin" / "cc1").exists(), reason="toolchain not installed")
def test_canary():
    import toolcheck
    want = (ROOT / "tests" / "fixtures" / "canary.sha1").read_text().split()[0]
    assert toolcheck.canary_digest() == want


def test_compiler_config_is_complete():
    from common import compiler_config
    cfg = compiler_config()
    assert cfg["compiler"]["name"] in cfg["compilers"]
    assert "-mno-split-addresses" in cfg["per_file"]["allowed_cflags"]
