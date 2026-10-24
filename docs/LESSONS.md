# Lessons built into this repo

What earlier projects (the THPS N64 decomp, sotn-decomp, other PS1 decomps) learned the hard way, and where
this repo handles each one. Read this before changing tools.

| Lesson | Where it came from | How it is handled here |
|---|---|---|
| Pin the compiler by testing real functions, not by era guesses | thps64 started on gcc 2.7.2; 2.8.1 was right | `toolchain/compiler.toml` + STATUS.md: 15 hand matches decided between 5 compilers |
| The game mixes flags per source file | thps64: a per-file cflags comment unblocked about half the give-ups | `/* cflags: */` on line 1, allow-list in compiler.toml, enforced by scan.py |
| Masking relocations hides real mismatches | thps64 merged a non-match with masked local jumps (a23bb62) | match.py resolves every relocation to the original address and compares it |
| A missing tool in a shell pipe makes empty objects that link | sotn-decomp on this machine | tools/cc.py runs each stage as a subprocess, checks exit codes, rejects empty objects |
| splat leaves stale .s files; re-splits orphan merged units | thps64 (3d896fa) | split.py always wipes asm/; fresh.py re-splits on input change; check_split.py finds orphans |
| Functions that don't end in a jump are bad splits | thps64's biggest source of churn | check_split.py, with a reviewed exceptions file |
| Permuter setups silently drift from the match pipeline | thps64 (CODEX_PERMUTER_FIXES) | permute.py compiles through cc.py and refuses to start unless both drift checks pass |
| Agents fake matches with asm and register pins | thps64 Codex PRs needed hand rewrites | scan.py rejects them deterministically |
| A model edited the sha1 to fake a match | Snowboard Kids 2 | gates run from main's tools with only the PR's unit files copied in (Steward judge) |
| Unprotected include/ and toolchain/ let PRs move the goalposts | thps64 steward.toml gap | protected in steward.toml; include/game/ is shared but re-checks every unit |
| No pinned requirements, no in-repo toolchain script | thps64 | requirements.txt + toolchain/setup.py with sha256 pins and a canary self-test |
| A tools merge forces a cold re-judge of everything | thps64 (20-30 min) | gate.py caches per (unit, shared-input hash); this executable re-judges in seconds |
| Several agents on one account defeat claims; shared workspaces collide | thps64 handoff | AGENTS.md: one account and one clone per agent, address lanes |
| String literals and jump tables in C break per-function units | thps64 banned string literals | configure.py places a C function's own .rodata where its original rodata was; split.py records ownership |
| `gh pr edit` breaks on projectCards GraphQL | thps64 | use `gh api -X PATCH repos/.../pulls/N` |
| decomp.dev closed its public leaderboard over AI forks | 2026 | progress goes to bytematch.dev from a disc-free objdiff report |
