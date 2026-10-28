# A C-only filter for candidate selection, 2026-10-28 (i)

Tree cut from `origin/main@aa8fe7a6` (680 units) with `lane/select.py sync`; worktree checked before and
after every branch move with the inline equivalent of `verify` (main still has no `verify`; PR #196 open).

**Conversions: 0. Attempts: 1 framed body. Candidates the new filter rejected: 36.**

## The rule

`lane/select.py` now decides, from the listing alone, whether a body can be written in plain C at all:

1. a body that calls builds a frame (`addiu $sp,$sp,-N` as its first instruction) and stores `$ra` inside
   that frame;
2. `$sp` is assigned only by the prologue's first instruction and the epilogue's last one;
3. `$ra` is never parked in a temporary across a call (`addu $t7,$ra,$zero`);
4. `$at` is never a value register — `lui $at` / `addiu $at` / `lw|sw …($at)` address materialisation is
   gcc's own output and stays allowed, but `slt $at` / `slti $at` / `addu $at` is not;
5. `config/functions.us.csv` rows whose `kind` is not `func` are data symbols, not bodies.

`crule` prints the verdict and the reason; `list` drops non-C bodies from `--fresh` and tags them `notC`
otherwise; `draft` refuses them outright.

## Proof on exactly the five bodies the last pass found

```
$ lane/select.py crule func_80011B3C func_80027538 func_80023B1C func_80032E94 func_80033268 \
                      func_80047B28 func_80041538
func_80011B3C: NOT C — csv kind=data (a data symbol, not a function)
func_80027538: NOT C — assigns $sp outside the prologue/epilogue (`sw $sp 0x10($t0)`)
func_80023B1C: NOT C — assigns $sp outside the prologue/epilogue (`sw $sp 0x10($t0)`)
func_80032E94: NOT C — calls but never builds a frame (no prologue `addiu $sp,$sp,-N`)
func_80033268: NOT C — calls but never builds a frame (no prologue `addiu $sp,$sp,-N`)
func_80047B28: C — frame, $ra and $sp are compiler-shaped
func_80041538: C — frame, $ra and $sp are compiler-shaped
```

Two admits are both open, unmerged framed bodies (0xA8 and 0x18 frames, `$ra` in the frame), so the rule is
not "reject everything small".

Reach: `list --max 200 --fresh` now reports **36 rejected as not C** across the range, i.e. the five were
not a one-off band but the tail of a population. The fresh list at 83+ words starts at func_8004B088 (mine,
unmerged) and func_8001E3A0 (mine, unmerged), then func_80047B28.

## The one body worked

| function | words | best | turn-on |
|---|---|---|---|
| func_80047B28 | 91 | 83/91 (0x120, want 0x16c) | the 0x80-byte block copy: the game expands it to lwl/lwr|swl/swr pairs (byte-misaligned path) and to four `lw`/`sw` per 0x10 (aligned path) with a `lw`/`addiu` loop counter; a `S128` struct assignment emits a different copy and loses 19 words |

Decoded along the way and worth keeping: the `sw $a0, 0xA8($sp)` slot in that body is the *incoming
argument home*, used because the 0x80-byte buffer fills the frame — and it exists because the source passes
`&a0` to the callees (`func_80047A44(&a0, a1, i)`, `func_80047ACC(&a0, a2)`), forcing the parameter to
memory. That part of the draft is right; only the copy is wrong.

## Queue and pipeline

680 merged on main + 2 in review (#199, #200), **401 open**, of which the selector now shows **70 open in
range** for the fresh view after the non-C cull. Pipeline green at 680: scan 680 / 0 problems, gate 680/680,
build PASS `16829afba66533e2645bf87af2774671b06ff36b`.
