# Pass oct29d — the two close parks, one measurement each

Tree `7605c52b` = `origin/main`; no branch switched, no unit file overwritten.

## `func_80034874` — exact size, 41 matching, residue is scheduling

Revision 3 applied all three named fixes: the header pointer is materialised (`hdr = D_8008B0DC`,
`$s5` in the game), the counters are hoisted to the source order the listing uses (`y = 0x10`, `n = 0`
before the record work), and the row loop is the do-while the listing's bottom-edge counter implies.
Result **129/129 words, 41 matching** — up from 7 matching at 127 words.

Reading the alignment, the remaining difference is not the bound at all. It is **where `p` is born**:
the game materialises `s4 = D_800A5634` in the first three words of the body, *before* the
`func_8005A234` call, because the pointer is live across that call and therefore needs a callee-saved
register from entry. Our draft assigns `p = D_800A5634` after the record writes, so gcc allocates it
late and the whole save band shifts. Secondarily, `lim` is stored to 0x90 before the `func_8005A0A8`
call and `r` is computed in that call's delay slot into `$s7`; our order puts `r` after the call, which
is a self-inflicted regression from revision 3 and should be reverted first next time.
Turn-on: `0x80034880`.

## `func_8003599C` — 134/137, frame is the gap

One measurement, and the alignment shows the three words are not the dispatch blocks' setup but the
**frame**: ours is 0x18 against the game's 0x20 because the game keeps *two* bytes from `D_800A6318` in
callee-saved registers — `s1 = p2[0]` (the bit test for the second half) and `s0 = p2[1] >> 4` (the
second nibble) — while our draft keeps the *pointer* `p2` and re-reads both fields at the second switch.
Fixing that means naming both bytes as locals before the first dispatch, which is a source change, not a
spelling. The fill loops' `+4` is also still folded into the base (`addiu $a3,$v0,4` then offset 0)
where the game keeps `$t2 = D_800A6294` and stores at `4($v1)`.
Turn-on: `0x800359C8`.

## Count

conversions **0**, bodies measured **2** (`func_80034874` 129/129 at 41 matching, `func_8003599C`
134/137). No PR. Queue at `7605c52b`: 74 open (fresh), 238 attempted, 693 merged units.

## Note for the next pass

`func_80034874` is one source-order change from a serious attempt: move `p = D_800A5634` above the
first call and restore `r` before `func_8005A0A8`. Nothing else in that body is unresolved.
