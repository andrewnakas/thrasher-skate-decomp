# Handoff: `func_80034B98` matches, but only with a RAM literal (protected rule)

**Status: proven byte-exact match, blocked by `tools/scan.py`, not by the compiler.**

`func_80034B98` (16 words) matches under `/* cflags: -mno-split-addresses */` — `work/verify.py`
classifies it `match` and `work/best/func_80034B98.c` is the body. It cannot ship because its last
statement stores `0x801FC000`, which is inside the `0x80010000..0x801FFFFF` range the scanner rejects
("use the symbol"). This file records what was tested so the decision is a small one.

## What the body needs, and why the obvious fix does not work

The game's epilogue is literally

```
lui  $v0, 0x801F
ori  $v0, $v0, 0xC000
sw   $v0, %gp_rel(D_8008B0F4)($gp)
```

`lui`+`ori` is the encoding of a **full 32-bit constant**, not of a symbolic address. Adding the
symbol the rule asks for does *not* reproduce it — tested:

| spelling | emitted | result |
|---|---|---|
| `D_8008B0F4 = (s32) &D_801FC000;` with `extern u8 D_801FC000;` | `addiu $v0, $gp, %gp_rel(D_801FC000)` (1-byte object → gp-relative) | **11/16, no match** |
| `extern u8 D_801FC000[];` + `(s32) D_801FC000` | `lui`/`addiu %lo` pair, low half assembled as `-0x4000` | does not match `lui`/`ori` |
| literal `0x801FC000` | `lui 0x801F` / `ori 0xC000` | **MATCH**, but scanner rejects |
| `(0x801F << 16) \| 0xC000` | `lui 0x801F` / `ori 0xC000` | **MATCH**, scanner passes (no 8-digit literal) |

There is no `D_801FC000` in `config/symbol_addrs.us.txt` (the file is empty), `config/link_aliases.us.txt`
or `include/` — checked, not assumed.

## The decision this needs

1. **Preferred, no code change needed by the lane:** allow one named constant for this address, i.e.
   the maintainer adds to `config/symbol_addrs.us.txt`
   ```
   D_801FC000 = 0x801FC000;
   ```
   *and* the scanner learns that a symbol-only address is acceptable when used as a value — but note
   the test above: the symbol spelling changes codegen, so the unit would then have to keep the shifted
   literal anyway to match. The symbol alone does not unblock it.
2. **Or:** accept the split-literal spelling `(0x801F << 16) | 0xC000` in this one unit. It matches
   byte-exactly and is not a scanner evasion in the sense the rule guards against (it carries no
   provenance risk), but it is plainly assembled to dodge the literal check, so it is the maintainer's
   call, not the lane's. The lane has **not** shipped it.

Either way the body is finished decompilation work sitting at zero cost once decided.
