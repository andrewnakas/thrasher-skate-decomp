# Fresh band, five bodies: two conversions, and the frame lever's hit record, 2026-10-28 (f)

Branch `freebuff/records-oct26`, cut work from `origin/main@09f0878`. Candidates came from
`lane/select.py list --min 70 --fresh`, ascending size; both matches were re-confirmed on freshly fetched
`origin/main` before shaping and again before their PRs (each branch is a single-file commit off
`09f0878`).

**Conversions: 2 — func_8004B088 (PR #199) and func_8001E3A0 (PR #200). Attempts: 5.**
Queue: **678 merged on origin/main + 2 in review, 403 open** (401 once both land).

## Per-body table

| function | words | best | outcome / residue |
|---|---|---|---|
| func_8004B088 | 83 | **MATCH** | shipped, PR #199. First transcription; one word differed (`slti` vs `sltiu`) |
| func_8001E3A0 | 84 | **MATCH** | shipped, PR #200. First transcription; two words differed (`lh` vs `lhu`, plus the missing sign-extend pair) |
| func_80053224 | 82 | 67/82 (0x164, want 0x148) | parked — frame content: the game's 0x48 frame carries a switch + `printf` layout ours does not; seven words long |
| func_8002475C | 85 | 47/85 (0x15c, want 0x154) | parked — frame content: ours keeps an extra saved register (`$s6`) because gcc hoists the literal `1` out of the record loop, which the game re-materialises with `addiu $v0,$zero,0x1` inside it; the game also builds the transform address as `$s2 + $s3 + 0x68` with an offset counter initialised to 4 |
| func_80026B34 | 85 | 64/85 (0x150, want 0x154) | parked — one instruction short with all five saved registers permuted (a1→`$s2`/`$s0`/`$s3`, a3→`$s1`/`$s3`, result→`$s4`/`$s1`); allocation residue with a one-word structural gap under it |

## What closed the two

Both were whole-body transcriptions that landed inside three words, so no lever was applied after the
first measurement — prologue-first fixed frame, save set and save order for both on the first pass
(0x20/`$ra,$s1,$s0` and 0x28/`$ra,$s1,$s0`). The corrections were narrow-type facts:

1. **`sltiu` wants an unsigned value, and a local is enough.** `(a0 & 0xFF) >= 0x20` emits `slti`; the same
   test through a `u32 idx = a0 & 0xFF;` emits the game's `sltiu $v0,$a0,0x20`. The parameter itself need
   not be narrowed in the declaration — this is the `func_8003F000` rule reached through a local instead
   of through the signature.
2. **`lhu` + `(s16)` at the call site.** A field negated and then narrowed — `negu; sll $a1,16; sra $a1,16`
   — is `(s16) -*(u16 *) (a0 + off)`. Reading the field as `s16` gives `lh`, which is one word short of the
   game and takes the size with it.
3. **Offset-left on a symbol base, fifth confirmation.** `extern u32 D_800AEA24[];` with
   `e = (u8 *) D_800AEA24[idx];` emits `sll $v0,$a0,2; addu $v0,$v0,$v1` — index left, base right, as the
   merged sibling `func_8004B310` does. The rule was previously only proved on struct bases.

## The frame lever: 0 hits this pass, and the reason is worth banking

The widened-block lever did **not** fire: both matches got their frame and every stack-argument offset
right on the first transcription, and both parks' frames were wrong for reasons the extent cannot fix
(one is *over* by seven words of content, one carries an extra saved register). Two measurements that
keep the lever honest, and one new variant of it:

- **The frame tells you the call's stack-argument count.** `func_80026B34` first went in reading the
  three words stored at `0x10($sp)` as the 4th-6th arguments of `func_80026DEC`; the frame came out `0x40`
  against the game's `0x38`. Reading them as a *local vector* (`u32 v[3]`, which `func_800331FC` and
  `func_80032FF4` then take by address) dropped the frame to `0x38` in one step and took the body from
  78/85 to 64/85. When a frame is one word-block too big, look for arguments you invented.
- Widening a block is still the lever for a frame that is too *small* and whose stack arguments sit at
  the wrong offsets; nothing this pass needed it, and the two former confirmations stand.

## The worktree check

`lane/select.py verify` compares `src/funcs` against `origin/main` in both directions and refuses on a
missing or in-place-edited merged unit; `sync`, `check`, `list` and `draft` all call it. Proved this pass
on a deliberately removed merged file (`func_80011B48`, restored immediately):

```
$ rm src/funcs/func_80011B48.c
$ lane/select.py verify
MISSING src/funcs/func_80011B48.c: merged on origin/main but absent from the worktree
verify: REFUSED — 1 missing, 0 edited          (exit 1)

$ lane/select.py draft func_80011B48 --src /tmp/x.c
select: src/funcs has local edits, selection would be unsound:
  D src/funcs/func_80011B48.c                  (exit 1, no file written)

$ cp back; lane/select.py verify
verify: 679 unit files, every merged body from origin/main present and unedited   (exit 0)
```

It did not fire during the drafting itself: no branch switch was needed between bodies, because both
drafts were moved into `work/pass-oct28/` before any checkout.

Two facts about its state, because a guard that lives on an unmerged branch has been lost before:

- The assertion was **not on `origin/main`** when this pass started: main's `lane/select.py` has the
  freshness classification but no `lost_units`/`verify`. It is now pushed for main in **PR #196**
  (`freebuff/lane-select`, `lane/` only, mergeable), so the next main checkout inherits it.
- `dirty_units()` counted untracked drafts (`??`) as local edits, so `list` refused to run as soon as a
  draft existed — the opposite of the README's "untracked drafts are expected". Fixed in the same PR.

## Rule check

- Prologue-first: 5 of 5 frames and save sets right on the first transcription.
- The permuter was not used; no body reached one differing word.
- Address forms, arm polarity and loop rotation did not come up in this band. The two conversions turned
  on narrow types, not on shape.
