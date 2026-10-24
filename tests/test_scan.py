"""tools/scan.py: the forbidden-construct gate (runs in CI with no disc)."""
import scan
from common import compiler_config

ALLOWED = set(compiler_config()["per_file"]["allowed_cflags"])
FUNCS = {"func_80011C9C"}


def run(tmp_path, body, name="func_80011C9C.c"):
    p = tmp_path / name
    p.write_text(body)
    return scan.scan_file(p, ALLOWED, FUNCS)


def test_plain_c_passes(tmp_path):
    assert run(tmp_path, '#include "common.h"\nvoid func_8003B068(void);\n'
                         'void func_80011C9C(void) { func_8003B068(); }\n') == []



def test_inline_asm(tmp_path):
    assert any("inline asm" in p for p in run(tmp_path, 'void func_80011C9C(void) { __asm__("nop"); }\n'))
    assert any("inline asm" in p for p in run(tmp_path, 'void func_80011C9C(void) { asm volatile("nop"); }\n'))


def test_register_pinning(tmp_path):
    probs = run(tmp_path, 'void func_80011C9C(void) { register int x asm("$s0"); }\n')
    assert any("register pinning" in p for p in probs)


def test_pragma_and_include_asm(tmp_path):
    assert any("#pragma" in p for p in run(tmp_path, '#pragma GLOBAL_ASM("x.s")\n'))
    assert any("asm include" in p for p in run(tmp_path, 'INCLUDE_ASM("asm", func_80011C9C);\n'))


def test_hardcoded_address(tmp_path):
    probs = run(tmp_path, 'int func_80011C9C(void) { return *(int *)0x8008AEE4; }\n')
    assert any("hard-coded address" in p for p in probs)
    assert run(tmp_path, 'unsigned func_80011C9C(unsigned x) { return x & 0x80000000; }\n') == []


def test_comments_are_ignored(tmp_path):
    assert run(tmp_path, '/* asm("nop") 0x80012345 */\nvoid func_80011C9C(void) {}\n') == []


def test_cflags(tmp_path):
    assert run(tmp_path, '/* cflags: -O1 */\nvoid func_80011C9C(void) {}\n') == []
    assert any("not in" in p for p in run(tmp_path, '/* cflags: -fomit-everything */\nvoid func_80011C9C(void) {}\n'))
    assert any("first line" in p for p in run(tmp_path, '\n/* cflags: -O1 */\nvoid func_80011C9C(void) {}\n'))


def test_file_names(tmp_path):
    assert any("file name" in p for p in run(tmp_path, "void f(void) {}\n", "func_80011c9c.c"))
    assert any("not a function" in p for p in run(tmp_path, "void f(void) {}\n", "func_80011CA0.c"))


def test_include_non_header(tmp_path):
    assert any("only headers" in p for p in run(tmp_path, '#include "other.c"\n'))
