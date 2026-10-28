"""tools/normalise.py: the rewrites that make decompiler output compile, and nothing more."""
import normalise


def test_unresolved_type_and_void_pointer():
    out = normalise.normalise("void f(? a, void *b) { return; }\n")
    assert "s32 a" in out and "u8 *b" in out


def test_unaligned_qualifier_is_dropped():
    assert normalise.normalise("x = (unaligned u16) y;\n") == "x = (u16) y;\n"


def test_member_offsets_become_byte_arithmetic():
    out = normalise.normalise("u32 f(u8 *p) { return p->unk8; }\n")
    assert out == "u32 f(u8 *p) { return *(u32 *)(p + 0x8); }\n"


def test_member_width_follows_the_mask():
    out = normalise.normalise("u8 f(u8 *p) { return p->unkC & 0xFF; }\n")
    assert "*(u8 *)" in out


def test_global_member_uses_the_declaration():
    arr = "extern u8 D_80080ABC[];\nu32 f(void) { return D_80080ABC.unk4; }\n"
    assert "((u8 *) D_80080ABC + 0x4)" in normalise.normalise(arr)
    scalar = "extern s32 D_80080ABC;\nu32 f(void) { return D_80080ABC.unk4; }\n"
    assert "((u8 *) &D_80080ABC + 0x4)" in normalise.normalise(scalar)


def test_a_typed_struct_pointer_keeps_its_member():
    text = "typedef struct S_1 S_1;\nvoid f(S_1 *p) { p->unk4 = 0; }\n"
    assert normalise.normalise(text) == text


def test_the_unit_address_is_never_rewritten_as_a_member():
    text = "void f(void) { func_80080ABC(); }\n"
    assert normalise.normalise(text) == text
