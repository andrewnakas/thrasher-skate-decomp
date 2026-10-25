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


@pytest.mark.skipif(not (ROOT / "toolchain" / "bin" / "cc1").exists(), reason="toolchain not installed")
def test_extern_store_after_load_keeps_nop(tmp_path):
    """Issue #38: `lw $2,A; sw $2,B` on small externs needs the load-delay nop (patches/maspsx)."""
    import cc
    from common import compiler_config
    src = tmp_path / "f.c"
    src.write_text("extern int D_A, D_B, D_C;\n"
                   "void f(void) { D_B = D_A; D_C = D_B + 0x23D0; }\n")
    ops = [line.split()[0] for line in cc.c_to_asm(src, compiler_config()).decode().splitlines()
           if line.strip() and not line.lstrip().startswith((".", "#")) and not line.rstrip().endswith(":")]
    i = ops.index("lw")
    assert ops[i + 1] == "nop" and ops[i + 2] == "sw"
