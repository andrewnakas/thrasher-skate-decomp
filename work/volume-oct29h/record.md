# Pass oct29h — the easy band is empty; six bodies measured, one new close park

Tree `7605c52` = `origin/main`; unit count 693 local = 693 upstream; `src/funcs` clean.
No branch switched; records landed through a temporary index.

## Toolchain: the dirty submodule is the project's own patch, not a rogue edit

This pass opened by reverting `toolchain/maspsx` to the gitlink `4ffa8b5`, believing the dirty file was a
local experiment. It is not. `toolchain/setup.py` applies
`toolchain/patches/maspsx/0001-extern-sdata-symbols-use-gp.patch` and *refuses to run* if that patch is
missing, so a clean submodule is the broken state: with it reverted `gate.py` reported **684/693, 9
failing** — all nine merged units shifted one word around a `$gp` store. `setup.py` re-applied the patch
and gate returned to 693/693.

All six numbers below were re-measured after the patch was back and are identical to the ones taken
without it (none of these bodies declares a small extern), so the table stands either way. The standing
description of this state is: **`m toolchain/maspsx` is expected; a clean submodule is a broken toolchain.**

Pipeline on this tree: `scan.py` 693 files / 0 problems, `gate.py` **693/693 GATE PASS**, `build.py`
**BUILD PASS**, image sha1 `16829afba66533e2645bf87af2774671b06ff36b`.

## Selection: the profile that converted is exhausted

`work/pick-straight.py` ranks open bodies by the profile the lane's two conversions had (short, no or few
conditional branches, call-heavy, small frame, ≤3 saves). Result:

| filter | candidates | fresh (never attempted) |
|---|---|---|
| ≤24 insn, 0 branches, ≤3 saves | 20 | **0** |
| ≤90 insn, ≤4 branches, ≤3 saves, frame ≤0x40 | — | **0** |
| ≤200 insn, ≤8 saves | 23 | **0** |

All 72 fresh bodies in range at pass start are ≥123 bytes and carry either a dense branch set or a 5-8
register save set. The band this lane converts in has been fully attempted; that is a fact about the queue, not about
this pass.

## Per-body numbers (one measurement each unless noted)

| body | first | best | size | residue / turn-on |
|---|---|---|---|---|
| `func_80047EF0` | 122/147 | **118/147** | 146/147 (`0x248` vs `0x24c`) | `sb d->mode` sunk into the `bgez` delay slot; see below |
| `func_800337C4` | 0/16 | 0/16 (2 shapes) | 15/16 (`0x3c` vs `0x40`) | stores go through the return register; game stores via `$a0`; `0x80033800` |
| `func_80032FF4` | 12/13 | 12/13 | 13/13 exact | six temporaries in `$t0-$t5`; ours `$v0/$v1/$a2`; identical sequence |
| `func_80033818` | 12/13 | 12/13 | 13/13 exact | same home class: `$t0-$t5` vs `$v0/$v1/$a1-$a3` |
| `func_80032C28` | 10/11 | 10/11 | 8/11 | 64-bit multiply expansion, see below |
| `func_800331FC` | 27/27 differ | 27/27 differ | 28/27 | same expansion; saved drafts re-measured, neither is 27 |

`func_80032FF4` and `func_80033818` are **12 of 13 words with the game's exact instruction sequence** — the
only difference is which caller-saved register homes each of six simultaneous temporaries. That is the
filed home class, so both are parked in seconds per the standing rule, not reshaped.

## The 64-bit multiply idiom does not expand the way the retail build did

`func_80032C28` and `func_800331FC` are the same `(u64) x * y >> 16` shape. The game's block is six words:

```
mult a,b | mflo $v1 | mfhi $v0 | srl $v1,16 | sll $v0,16 | or $v0,$v0,$v1
```

Under the pinned toolchain the same source emits **seven**, with a dead `srl $v1,$hi,16` (the high half of
the 64-bit shift, computed and discarded) — visible in both bodies. `func_80032C28` additionally shows the
game's three-nop `mult` blockage where the pinned maspsx hoists `mfhi`/`mflo` into those slots. No merged
unit in `src/funcs` uses a 64-bit multiply, so there is no in-repo precedent that it can match. Recorded as
a characterised residue; not promoted to a closed class on two bodies.

## `func_80047EF0` — written whole from the listing, 122 → 118, size 146/147

Decoded shape, all of which the draft reproduces exactly: prologue `0x28` with `s0=src`, `s1=d`, `ra`; an
8-byte unaligned header copy (`lwl`/`lwr` pairs into `sp+0x10`) from an 8-byte `HDR` struct; `src += 8`;
three `func_80036EF4(&h.f2 / &h.h / &h.w)` swaps in that order; `d->w`, `d->h`, `d->mode` assigned from the
swapped halves; `n = (m + 7) / 8` on a `u8 m` (which is what produces the `andi` + `bgez` pair); a single
`d->dst = func_80034C20(w * h * n)` tested immediately, returning 1 on null; then an **if/else chain**
(mode 8 → 0x10 → 4, not a `switch`) of three nested loops, each `for (j) for (i)` storing
`d->dst[j * d->w + i]` and advancing `src` by 2, 2, 4 with the advance in the back-edge delay slot.

Two shape corrections during the pass each paid: naming one `u8 m` instead of reading `h.mode` twice
(153 → 147 words) and dropping the `dst` local in favour of `d->dst` everywhere (which restores the
per-iteration reload of the destination base).

Remaining residue, from the alignment: the game issues `sb $v0,0x11($s1)` **before** `andi $v0,$v0,0xFF`
and leaves a `nop` in the `bgez` delay slot; ours sinks that store into the delay slot (−1 word), and
because the store moved the mode value keeps `$v0`, so `h.h` stays live instead of being reloaded at
`0x80047F80`. That single scheduling choice accounts for the one-word size gap and the cascade after it.
Turn-on `0x80047F64`. Parked, not retired: this is the closest body in the lane.

## Reconcile was re-deriving measured bests from prose, and now does not

`reconcile` rewrote every row's `best` from whatever number pair a `work/` record happened to spell first,
so each sync republished `func_80034874` as `41/129` over a measured `66/129` and `func_8003599C` as
`129/137` (a size from the retirement table) over `61/137`. This pass tried the obvious inverse heuristic
(max matching) and it was worse — the records mix `matching/total` and `size/matching` orders, so it
published `func_80034874` as `129/129` and `func_80020C34` as `1440/4800`. The fix that holds is that
reconcile owns **status only**: an existing row keeps its number and source, new rows still get one.
Landing as `lane/select.py` on branch `freebuff/select-status-only` (tooling PR, no unit files); the table
is unchanged and the run is now idempotent (`355 entries, 0 changes`).

## Count

conversions **0**, bodies measured **6** (`func_80047EF0` 118/147, `func_800337C4` 0/16, `func_80032FF4`
12/13, `func_80033818` 12/13, `func_80032C28` 10/11, `func_800331FC` 27/27 differ). No unit PR. Queue
after the pass: **71 open fresh, 239 attempted**, 693 merged, 29 not C, 102 recorded-but-merged, 9
closed-by-evidence — `func_80047EF0` moved from fresh to attempted and no body left the queue.

## What the next pass should attack

Not the profile band — it is empty. The two highest-value targets the record now names are
`func_80047EF0` (one scheduling choice from exact) and the `$t0-$t5` home pair, and both need a lever this
lane has never had. Ahead of that, the honest statement is that 72 fresh bodies remain and every one of
them is a 123-198 word body with a dense branch set; a pass that writes three of those whole will produce
three parks like `func_80047EF0`, and one of them will land.
