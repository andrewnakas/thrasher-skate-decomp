"""tools/attribute.py: the two attribution rules and the counts they produce.

The fixture is synthetic on purpose: pinning these numbers against today's `work/` contents
would make the test fail every time a draft is added, without saying whether a rule broke.
"""
import attribute as A

LISTING = """nonmatching func_%(addr)s, 0x40
glabel func_%(addr)s
%(body)s
endlabel func_%(addr)s
"""


def listing(addr, body=""):
    return LISTING % {"addr": addr, "body": body}


def unit(name, body=""):
    text = listing(name[5:], body)
    return A.Unit(name, text, A.listing_signature(text))


def index(*names):
    return A.suffix_index(list(names))


def test_listing_signature_reads_calls_globals_and_immediates():
    sig = A.listing_signature(listing("80010000", """\
    jal        func_80020000
    nop
    jal        func_80030000
    nop
    lw         $v0, %gp_rel(D_8008B2EC)($gp)
    lui        $v0, %hi(D_8008B3A8)
    lw         $v0, %lo(D_8008B3A8)($v0)
    ori        $v1, $zero, 0xFFFF
    addiu      $at, $zero, -0x1
"""))
    assert sig.calls == ("func_80020000", "func_80030000")
    assert sig.globals == {"D_8008B2EC", "D_8008B3A8"}
    assert sig.immediates == {0xFFFF, 0xFFFFFFFF}


def test_draft_signature_ignores_its_own_definition():
    sig = A.draft_signature("""\
#include "common.h"
void func_80010000(void) {
    func_80020000();
    func_80030000();
    D_8008B2EC = 0xFFFF;
}
""")
    assert sig.calls == ("func_80020000", "func_80030000")
    assert sig.globals == {"D_8008B2EC"}


def test_name_rule_accepts_only_unambiguous_suffixes():
    idx = index("func_8001C4BC", "func_80022F24", "func_80022998")
    assert A.identify_name("c4bc-v1", idx) == ("func_8001C4BC", "")
    assert A.identify_name("func_80022F24", idx) == ("func_80022F24", "")
    assert A.identify_name("22F24-r3", idx) == ("func_80022F24", "")
    assert A.identify_name("probe", idx) == (None, "")


def test_name_rule_reports_a_shared_token_instead_of_guessing():
    idx = index("func_80019998", "func_80029998")
    assert A.identify_name("9998-a", idx) == (None, "ambiguous")
    # a second, unique token in the same name still wins
    assert A.identify_name("9998-func_80019998", idx) == ("func_80019998", "")


def test_signature_rule_needs_a_clear_nearest_unit():
    a = unit("func_80010000", "jal func_80020000\njal func_80030000")
    b = unit("func_80011000", "jal func_80020000\njal func_80040000")
    by_name = {u.name: u for u in (a, b)}
    idx = A.candidate_index([a, b])

    drafts = A.draft_signature("void f(void){ func_80020000(); func_80030000(); }")
    name, score, margin = A.identify_signature(drafts, by_name, idx)
    assert name == "func_80010000" and score > 0.5 and margin > 0.1

    # both calls in common: the two units are not separable, so neither is claimed
    shared = A.draft_signature("void f(void){ func_80020000(); }")
    assert A.identify_signature(shared, by_name, idx)[0] == ""


def test_signature_rule_refuses_bodies_with_no_distinctive_evidence():
    u = unit("func_80010000", "jal func_80020000")
    by_name = {u.name: u}
    idx = A.candidate_index([u])
    assert A.identify_signature(A.draft_signature("void f(void){ return; }"), by_name, idx) == ("", 0.0, 0.0)


def test_scan_counts_on_a_fixture(tmp_path):
    u1 = unit("func_80010000", "jal func_80020000\njal func_80030000\nlw $v0, %gp_rel(D_8008B2EC)($gp)")
    u2 = unit("func_80011000", "jal func_80040000\njal func_80050000\nlw $v0, %gp_rel(D_8008B3A8)($gp)")
    u3 = unit("func_80012998", "jal func_80060000")
    u4 = unit("func_80022998", "jal func_80070000")   # shares only the 4-digit suffix 2998 with u3
    units = [u1, u2, u3, u4]
    idx = A.suffix_index([u.name for u in units])
    sig = A.candidate_index(units)

    (tmp_path / "10000-a.c").write_text("void func_80010000(void) { func_80020000(); }\n")
    (tmp_path / "10000-a-copy.c").write_text("void func_80010000(void) { func_80020000(); }\n")
    (tmp_path / "probe.c").write_text(
        "void f(void) { func_80040000(); func_80050000(); D_8008B3A8 = 0; }\n")
    (tmp_path / "2998-x.c").write_text("void f(void) { return; }\n")      # ambiguous name, no signature
    (tmp_path / "wip.c").write_text("void f(void) { return; }\n")         # nothing at all

    got = A.scan(tmp_path, units, idx, signatures=sig)
    assert (got.by_name, got.by_signature, got.ambiguous_name,
            got.duplicates, got.unattributed) == (1, 1, 1, 1, 1)
    assert sorted((d.unit, d.rule) for d in got.drafts) == [
        ("func_80010000", "name"), ("func_80011000", "signature")]
