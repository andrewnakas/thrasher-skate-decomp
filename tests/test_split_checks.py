"""tools/check_split.py helpers on toy asm (no disc)."""
from check_split import ends_in_jump, extent_end

ASM = """glabel func_80010000
    /* 800 80010000 0800E003 */  jr         $ra
    /* 804 80010004 00000000 */   nop
endlabel func_80010000
    /* 808 80010008 00000000 */  nop
    /* 80C 8001000C 00000000 */  nop
"""
FALLS = """glabel func_80010000
    /* 800 80010000 21104000 */  addu       $v0, $v0, $zero
    /* 804 80010004 21104000 */  addu       $v0, $v0, $zero
endlabel func_80010000
"""


def test_ends_in_jump(tmp_path):
    p = tmp_path / "a.s"
    p.write_text(ASM)
    assert ends_in_jump(p) is True
    p.write_text(FALLS)
    assert ends_in_jump(p) is False


def test_extent_includes_padding(tmp_path):
    p = tmp_path / "a.s"
    p.write_text(ASM)
    assert extent_end(p) == 0x80010010
