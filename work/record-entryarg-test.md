# pass oct28z — the entry-live-argument hypothesis, four bodies, refuted

Four bodies compile to the game's exact instruction sequence and differ only in which
caller-saved register homes a value. Hypothesis: an argument is live at entry that the drafts do
not name, so gcc's free set is wider in our build than in the game's.

## The test, done three ways

**1. Call sites (the decisive one).** The signature is readable forward from every caller:

| body | caller | registers set before `jal` | args |
|---|---|---|---|
| `func_80032FF4` | `func_8001F984` | `a0 = s0+0x10`, `a1 = s1` (delay slot) | 2 — as drafted |
| `func_80033818` | `func_8003031C` | `a0` already `sp+0x10`, no `a1`–`a3` set | 1 — as drafted |
| `func_800337C4` | `func_80011D60` | `a0 = D_8008ACA0` only | 1 — as drafted |
| `func_80032C28` | `func_800123B0` | `a0 = 0x4(s1)`, `a1 = 0x24(s3)` | 2 — as drafted |

No caller passes a third or fourth argument, so no draft is missing a parameter.

**2. The listings have no room for a use.** Every word is accounted for: 13/13, 13/13, 16/16,
11/11. A parameter can only occupy its register if it is *used*; a declared-but-unused one frees
it. Our own builds prove that directly — the temps take `$a1`–`$a3` in `func_80033818`, which is
only possible because nothing keeps those registers live at entry.

**3. Flags.** `-O1` on all four, `-fno-schedule-insns` on `func_800337C4`: the residues are
unchanged to the instruction. This is not a build-mode difference either.

## Per body

| body | residue | turn-on instruction | test result |
|---|---|---|---|
| `func_80032C28` | 10/11, size `0x20` vs `0x2c` | `0x80032C2C` — `mfhi $a3` where the game has the first of three mult-latency `nop`, then reads `mflo` before `mfhi` | `-O1` measured: identical, 10/11 |
| `func_80032FF4` | 12/13 | `0x80032FF4` — `lw $v0,0x0($a0)` vs `lw $t0,0x0($a0)`; six values live on both sides | `-O1` measured: 12/13, loads reordered but still not the game's |
| `func_80033818` | 12/13 | `0x80033818` — same six-load/six-store plan, homes `$v0,$v1,$a1,$a2,$a3,$t0` vs `$t0..$t5` | `-O1` measured: identical, 12/13 |
| `func_800337C4` | 16/16, size `0x3c` vs `0x40` | `0x800337C4` — `addu $v0,$a0` before `lui`, and the stores go through `$v0` where the game keeps `$a0` | `-fno-schedule-insns` measured: identical, 16/16 |

**What the test proved:** the home difference is not a missing argument and not a build-mode
difference. A declared-but-unused parameter cannot occupy its register (our builds spend `$a1`–`$a3`
as temps), and a used one would add an instruction the listing does not contain. The class stands
as filed: the allocator's choice between `$t*` and `$v*`/`$a*` for a set of simultaneously live
leaf temporaries is not expressible in C.

**Caveat worth keeping:** this refutes the "missing parameter" reading, not the whole of class B.
`func_800337C4` is the one body where the *base* really is in a different register (game `$a0`,
ours `$v0`) — there the cause is the return-value copy being coalesced with the base, which is
still a home, not a signature.

## Conversions and queue

Conversions **0**; bodies tested **4** (one measured shape each, plus the earlier `-O1` pair).

`func_80027880` from the previous pass merged upstream during this one (#209, `5e7ecd3`), so the
tree moved forward under the guard: `select.py sync` cut to `5e7ecd35`, unit files clean, 688
units, and the reconciliation marked exactly one entry now merged.

Final queue at `5e7ecd35`: `318 open`, `239 attempted`, `29 not C`, `7 closed-by-evidence`,
`97 recorded-but-merged`, `688 merged units`.
