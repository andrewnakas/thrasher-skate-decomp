# Lane census (0x80035000-0x80058633), corrected nop rule

Rule (verified by probe on issue #38): a `nop` after a load is only wrong when the loaded
register is consumed by a following *store*; a load feeding a branch or arithmetic matches.
`ld_st` counts the #38 pattern; `ld_ok` counts load-delays that compile fine; `jal_nop` is
the #17 class; `br_nop` is ordinary branch delay.

| func | instr | #38 | ld-ok | jal | br | blocker |
|---|---|---|---|---|---|---|
| func_800350C8 | 389 | 2 | 21 | 1 | 2 | #38 load->store |
| func_8003571C | 45 | 0 | 1 | 0 | 4 | open |
| func_80035810 | 20 | 0 | 1 | 0 | 0 | open |
| func_800358A8 | 61 | 0 | 4 | 1 | 0 | open |
| func_8003599C | 137 | 0 | 2 | 0 | 0 | open |
| func_80035BC0 | 21 | 0 | 0 | 0 | 0 | open |
| func_80035C14 | 34 | 4 | 1 | 0 | 0 | #38 load->store |
| func_80035C9C | 36 | 4 | 1 | 0 | 0 | #38 load->store |
| func_80035D2C | 69 | 0 | 0 | 0 | 0 | open |
| func_80035E40 | 30 | 0 | 0 | 0 | 2 | handwritten |
| func_80035F5C | 49 | 0 | 1 | 0 | 1 | open |
| func_800363F8 | 145 | 0 | 4 | 2 | 0 | open |
| func_8003682C | 138 | 0 | 3 | 5 | 2 | open |
| func_80036F24 | 13 | 0 | 0 | 1 | 0 | open |
| func_80036F64 | 67 | 0 | 2 | 0 | 0 | open |
| func_80037070 | 319 | 0 | 21 | 4 | 3 | open |
| func_8003756C | 198 | 2 | 7 | 1 | 4 | #38 load->store |
| func_80037968 | 35 | 0 | 1 | 1 | 1 | open |
| func_800379F4 | 26 | 0 | 2 | 0 | 0 | open |
| func_80037DC4 | 190 | 0 | 4 | 3 | 0 | open |
| func_800380BC | 129 | 0 | 5 | 3 | 0 | open |
| func_800382C0 | 12 | 0 | 0 | 0 | 0 | open |
| func_8003834C | 39 | 0 | 1 | 1 | 0 | open |
| func_80038610 | 79 | 0 | 1 | 0 | 0 | open |
| func_800387C8 | 37 | 0 | 2 | 0 | 0 | open |
| func_80038864 | 67 | 0 | 1 | 0 | 0 | open |
| func_80038970 | 68 | 0 | 1 | 0 | 0 | open |
| func_80038A80 | 49 | 0 | 1 | 0 | 0 | open |
| func_80038B44 | 288 | 7 | 6 | 1 | 4 | #38 load->store |
| func_80038FC4 | 303 | 6 | 7 | 1 | 4 | #38 load->store |
| func_80039480 | 268 | 5 | 5 | 1 | 4 | #38 load->store |
| func_800398B0 | 193 | 0 | 4 | 0 | 0 | open |
| func_80039BB4 | 90 | 0 | 1 | 0 | 1 | open |
| func_80039D90 | 130 | 3 | 7 | 0 | 0 | #38 load->store |
| func_8003A09C | 49 | 2 | 1 | 0 | 0 | #38 load->store |
| func_8003A1B8 | 71 | 0 | 0 | 0 | 0 | open |
| func_8003A4A0 | 54 | 1 | 2 | 0 | 0 | #38 load->store |
| func_8003A5A4 | 144 | 0 | 2 | 13 | 2 | open |
| func_8003AC04 | 30 | 0 | 0 | 0 | 0 | open |
| func_8003AF4C | 71 | 0 | 2 | 5 | 4 | open |
| func_8003B068 | 217 | 1 | 10 | 13 | 13 | #38 load->store |
| func_8003B3CC | 19 | 0 | 1 | 0 | 0 | open |
| func_8003B478 | 71 | 0 | 0 | 2 | 1 | open |
| func_8003B60C | 52 | 0 | 1 | 3 | 2 | GTE,handwritten |
| func_8003B8F8 | 46 | 0 | 1 | 1 | 0 | open |
| func_8003BA14 | 61 | 0 | 0 | 0 | 0 | open |
| func_8003BB1C | 167 | 0 | 5 | 0 | 0 | open |
| func_8003BDB8 | 31 | 0 | 1 | 0 | 0 | open |
| func_8003BE34 | 82 | 0 | 0 | 0 | 0 | open |
| func_8003BF7C | 79 | 0 | 0 | 0 | 0 | open |
| func_8003C220 | 28 | 0 | 3 | 0 | 0 | open |
| func_8003C290 | 163 | 0 | 4 | 1 | 2 | open |
| func_8003C51C | 133 | 0 | 3 | 1 | 2 | open |
| func_8003C77C | 82 | 1 | 4 | 0 | 0 | GTE,handwritten,#38 load->store |
| func_8003C8C4 | 25 | 0 | 0 | 0 | 0 | GTE,handwritten |
| func_8003C928 | 114 | 2 | 0 | 3 | 0 | #38 load->store |
| func_8003CAF0 | 288 | 6 | 19 | 0 | 0 | GTE,handwritten,#38 load->store |
| func_8003CF70 | 234 | 3 | 14 | 0 | 1 | GTE,handwritten,#38 load->store |
| func_8003D318 | 136 | 1 | 1 | 2 | 2 | GTE,handwritten,#38 load->store |
| func_8003D538 | 243 | 0 | 1 | 0 | 4 | GTE,handwritten |
| func_8003D904 | 208 | 0 | 3 | 0 | 4 | GTE,handwritten |
| func_8003DC44 | 90 | 0 | 0 | 0 | 0 | GTE,handwritten |
| func_8003DDAC | 409 | 0 | 4 | 1 | 1 | GTE,handwritten |
| func_8003E410 | 228 | 24 | 16 | 0 | 0 | #38 load->store |
| func_8003E7A0 | 336 | 7 | 14 | 0 | 0 | GTE,#38 load->store |
| func_8003ED04 | 7 | 1 | 0 | 0 | 0 | #38 load->store |
| func_8003ED28 | 60 | 0 | 0 | 0 | 0 | open |
| func_8003EE9C | 42 | 0 | 0 | 2 | 2 | GTE,handwritten |
| func_8003EF44 | 326 | 4 | 18 | 1 | 2 | GTE,handwritten,#38 load->store |
| func_8003F45C | 293 | 4 | 12 | 0 | 2 | GTE,handwritten,#38 load->store |
| func_8003FAEC | 151 | 3 | 2 | 0 | 0 | #38 load->store |
| func_8003FD48 | 421 | 22 | 20 | 0 | 0 | #38 load->store |
| func_800403DC | 110 | 0 | 3 | 1 | 0 | open |
| func_80040594 | 242 | 0 | 9 | 0 | 0 | open |
| func_8004095C | 343 | 3 | 13 | 4 | 1 | GTE,handwritten,#38 load->store |
| func_80040EB8 | 202 | 2 | 7 | 3 | 1 | GTE,handwritten,#38 load->store |
| func_80041374 | 113 | 0 | 10 | 0 | 5 | open |
| func_80041538 | 92 | 4 | 5 | 0 | 2 | #38 load->store |
| func_800416A8 | 716 | 0 | 71 | 1 | 0 | open |
| func_80042338 | 64 | 0 | 0 | 0 | 0 | open |
| func_80042438 | 665 | 16 | 16 | 0 | 1 | GTE,#38 load->store |
| func_80042E9C | 58 | 0 | 5 | 0 | 0 | open |
| func_80042F84 | 159 | 4 | 3 | 1 | 0 | GTE,handwritten,#38 load->store |
| func_80043294 | 17 | 0 | 0 | 0 | 0 | open |
| func_800432D8 | 24 | 2 | 1 | 0 | 0 | #38 load->store |
| func_80043338 | 94 | 0 | 0 | 0 | 0 | GTE,handwritten |
| func_800434B0 | 265 | 0 | 2 | 0 | 1 | GTE,handwritten |
| func_800438D4 | 159 | 0 | 3 | 0 | 0 | GTE,handwritten |
| func_80043B50 | 69 | 0 | 0 | 1 | 0 | GTE,handwritten |
| func_80043C64 | 546 | 7 | 28 | 3 | 5 | GTE,handwritten,#38 load->store |
| func_800444EC | 100 | 1 | 2 | 1 | 1 | GTE,handwritten,#38 load->store |
| func_8004467C | 443 | 5 | 13 | 1 | 0 | GTE,handwritten,#38 load->store |
| func_80044D68 | 42 | 0 | 0 | 0 | 0 | GTE,handwritten |
| func_80044E10 | 646 | 0 | 15 | 0 | 3 | GTE,handwritten |
| func_80045828 | 4 | 0 | 0 | 0 | 0 | open |
| func_80045838 | 5 | 0 | 0 | 0 | 0 | open |
| func_8004584C | 38 | 0 | 0 | 0 | 0 | open |
| func_800458F4 | 289 | 4 | 10 | 0 | 1 | #38 load->store |
| func_80045D78 | 448 | 1 | 24 | 0 | 3 | #38 load->store |
| func_8004669C | 104 | 0 | 0 | 0 | 2 | open |
| func_80046878 | 41 | 0 | 3 | 0 | 0 | open |
| func_8004691C | 376 | 0 | 2 | 4 | 6 | open |
| func_80046EFC | 70 | 0 | 0 | 1 | 2 | open |
| func_80047014 | 62 | 0 | 0 | 0 | 0 | open |
| func_80047268 | 57 | 0 | 1 | 0 | 0 | open |
| func_8004734C | 50 | 0 | 3 | 0 | 0 | open |
| func_800474B4 | 49 | 0 | 3 | 0 | 0 | open |
| func_80047578 | 49 | 0 | 2 | 0 | 0 | open |
| func_80047834 | 115 | 0 | 6 | 0 | 1 | open |
| func_80047A44 | 34 | 0 | 2 | 0 | 0 | open |
| func_80047B28 | 91 | 0 | 3 | 0 | 0 | open |
| func_80047C94 | 151 | 5 | 4 | 0 | 2 | #38 load->store |
| func_80047EF0 | 147 | 3 | 7 | 1 | 2 | #38 load->store |
| func_8004813C | 51 | 0 | 2 | 0 | 0 | open |
| func_80048208 | 89 | 0 | 1 | 0 | 0 | open |
| func_8004836C | 57 | 0 | 1 | 0 | 0 | open |
| func_800484B4 | 57 | 0 | 1 | 0 | 2 | open |
| func_80048598 | 37 | 0 | 0 | 0 | 0 | open |
| func_8004862C | 28 | 0 | 0 | 0 | 0 | open |
| func_8004874C | 632 | 11 | 9 | 4 | 1 | GTE,handwritten,#38 load->store |
| func_8004912C | 65 | 0 | 0 | 0 | 0 | open |
| func_80049230 | 157 | 5 | 7 | 0 | 0 | GTE,handwritten,#38 load->store |
| func_800494A4 | 32 | 0 | 0 | 1 | 0 | open |
| func_80049530 | 79 | 0 | 3 | 0 | 0 | open |
| func_8004966C | 164 | 0 | 8 | 0 | 0 | open |
| func_8004995C | 46 | 0 | 0 | 0 | 0 | open |
| func_80049A14 | 101 | 0 | 5 | 0 | 0 | open |
| func_80049CD8 | 60 | 0 | 0 | 0 | 0 | GTE,handwritten |
| func_80049DC8 | 99 | 0 | 1 | 0 | 0 | GTE,handwritten |
| func_80049F54 | 80 | 2 | 4 | 0 | 0 | GTE,handwritten,#38 load->store |
| func_8004A094 | 39 | 0 | 0 | 0 | 0 | open |
| func_8004A130 | 80 | 2 | 0 | 0 | 0 | #38 load->store |
| func_8004A300 | 529 | 13 | 8 | 0 | 16 | #38 load->store |
| func_8004AC1C | 98 | 0 | 9 | 0 | 4 | open |
| func_8004ADA4 | 119 | 0 | 2 | 0 | 1 | open |
| func_8004AF80 | 66 | 0 | 3 | 0 | 0 | open |
| func_8004B088 | 83 | 0 | 7 | 1 | 1 | open |
| func_8004B1D4 | 79 | 0 | 6 | 0 | 0 | open |
| func_8004B4A8 | 279 | 2 | 5 | 0 | 4 | #38 load->store |
| func_8004B7BC | 158 | 3 | 9 | 4 | 1 | #38 load->store |
| func_8004BA34 | 103 | 0 | 8 | 1 | 0 | open |
| func_8004BF94 | 52 | 1 | 6 | 1 | 1 | #38 load->store |
| func_8004C064 | 153 | 0 | 8 | 0 | 3 | open |
| func_8004C2C8 | 55 | 1 | 3 | 1 | 1 | #38 load->store |
| func_8004C3A4 | 136 | 0 | 8 | 1 | 3 | open |
| func_8004C798 | 322 | 4 | 12 | 6 | 5 | #38 load->store |
| func_8004CCA0 | 34 | 0 | 4 | 0 | 2 | open |
| func_8004CD28 | 238 | 0 | 17 | 1 | 4 | open |
| func_8004D23C | 215 | 0 | 15 | 4 | 5 | open |
| func_8004DA90 | 88 | 0 | 6 | 1 | 3 | open |
| func_8004DBF0 | 82 | 2 | 2 | 2 | 0 | #38 load->store |
| func_8004DEBC | 276 | 7 | 15 | 1 | 1 | #38 load->store |
| func_8004E330 | 76 | 0 | 2 | 1 | 0 | open |
| func_8004E460 | 50 | 0 | 0 | 1 | 0 | open |
| func_8004E528 | 105 | 0 | 5 | 1 | 0 | open |
| func_8004E6CC | 72 | 0 | 3 | 1 | 0 | open |
| func_8004E7EC | 81 | 0 | 3 | 1 | 0 | open |
| func_8004E930 | 121 | 0 | 4 | 2 | 0 | open |
| func_8004EB74 | 161 | 0 | 3 | 1 | 1 | open |
| func_8004EDF8 | 53 | 0 | 3 | 0 | 0 | open |
| func_8004EECC | 33 | 0 | 2 | 0 | 0 | open |
| func_8004EF50 | 164 | 1 | 13 | 0 | 4 | #38 load->store |
| func_8004F1E0 | 28 | 0 | 2 | 0 | 0 | open |
| func_8004F250 | 231 | 0 | 7 | 1 | 3 | open |
| func_8004F5EC | 325 | 1 | 18 | 0 | 4 | #38 load->store |
| func_800501E4 | 115 | 0 | 5 | 2 | 1 | open |
| func_800504D4 | 100 | 0 | 2 | 3 | 4 | open |
| func_80050664 | 246 | 0 | 22 | 2 | 2 | open |
| func_80050A3C | 408 | 1 | 11 | 5 | 3 | #38 load->store |
| func_800511C0 | 101 | 0 | 1 | 2 | 0 | parked 61/101, #17 scheduler |
| func_80051354 | 136 | 0 | 6 | 0 | 0 | parked 131/136, allocation |
| func_800515FC | 83 | 0 | 4 | 1 | 0 | **matched** |
| func_80051844 | 96 | 0 | 1 | 1 | 0 | open |
| func_800519C4 | 72 | 0 | 1 | 0 | 2 | open |
| func_80051B9C | 158 | 2 | 7 | 1 | 1 | #38 load->store |
| func_80051E14 | 74 | 0 | 2 | 0 | 1 | open |
| func_80051FD4 | 180 | 1 | 7 | 2 | 0 | #38 load->store |
| func_80052380 | 102 | 0 | 5 | 0 | 0 | open |
| func_80052518 | 73 | 0 | 0 | 1 | 0 | open |
| func_8005263C | 142 | 0 | 6 | 3 | 2 | open |
| func_80052874 | 231 | 0 | 17 | 1 | 1 | open |
| func_80052C10 | 221 | 0 | 6 | 5 | 1 | open |
| func_80053014 | 132 | 0 | 9 | 1 | 0 | open |
| func_80053224 | 82 | 0 | 4 | 0 | 1 | open |
| func_80053408 | 104 | 0 | 1 | 1 | 0 | open |
| func_800535EC | 67 | 0 | 4 | 0 | 0 | open |
| func_80053774 | 182 | 2 | 11 | 0 | 1 | #38 load->store |
| func_80053A4C | 58 | 1 | 3 | 0 | 1 | #38 load->store |
| func_80053BCC | 179 | 4 | 7 | 3 | 1 | #38 load->store |
| func_80053EA8 | 39 | 0 | 2 | 0 | 0 | open |
| func_80053F44 | 260 | 4 | 24 | 2 | 2 | #38 load->store |
| func_80054354 | 109 | 0 | 10 | 0 | 2 | open |
| func_8005458C | 416 | 1 | 10 | 20 | 6 | #38 load->store |
| func_80054BF4 | 791 | 1 | 20 | 38 | 35 | #38 load->store |
| func_80055820 | 34 | 0 | 2 | 6 | 0 | open |
| func_800558A8 | 312 | 0 | 6 | 15 | 16 | open |
| func_80055D64 | 162 | 0 | 1 | 0 | 0 | open |
| func_80055FC4 | 92 | 0 | 3 | 0 | 0 | open |
| func_80056104 | 117 | 0 | 6 | 0 | 0 | open |
| func_80056324 | 246 | 1 | 8 | 0 | 0 | #38 load->store |
| func_800566FC | 118 | 1 | 5 | 1 | 0 | #38 load->store |
| func_800568C0 | 95 | 0 | 0 | 0 | 0 | open |
| func_80056A3C | 10 | 0 | 0 | 0 | 0 | open |
| func_80056A64 | 141 | 1 | 5 | 0 | 1 | #38 load->store |
| func_80056C90 | 36 | 0 | 0 | 0 | 0 | open |
| func_80056D20 | 44 | 0 | 1 | 1 | 0 | open |
| func_80056F4C | 42 | 0 | 0 | 0 | 0 | open |
| func_80056FF4 | 39 | 0 | 0 | 0 | 0 | open |
| func_80057090 | 92 | 1 | 0 | 0 | 0 | #38 load->store |
| func_8005737C | 109 | 0 | 2 | 0 | 0 | open |
| func_8005757C | 259 | 0 | 21 | 1 | 3 | open |
| func_800579E0 | 109 | 0 | 6 | 0 | 2 | open |
| func_80057B94 | 68 | 0 | 2 | 0 | 2 | open |
| func_80057CA4 | 45 | 2 | 3 | 0 | 0 | #38 load->store |
| func_80057E9C | 74 | 0 | 1 | 0 | 0 | open |
| func_80057FC4 | 300 | 0 | 25 | 8 | 13 | open |
| func_80058448 | 43 | 0 | 0 | 4 | 0 | open |

217 unmatched bodies; 137 convertible now, 80 blocked.

## Window 0x80051000-0x80052000: the three undrafted bodies, transcribed

All four bodies in the window now have a verdict.

| func | instr | verdict |
|---|---|---|
| func_800515FC | 83 | **matched.** State machine over a 0x2C-byte handle: assert template (line 0x3D2), `switch (state)` with cases 1/2 -> state 2, 7 -> state 4 + unk3 = 0, 3/8 -> break, and 4/5/6/default sharing the body. The body is `if (!(flags & 0x2000))` on the success path (the state-3 tail sits out of line after it), func_80051F9C(unk2C), unk18/unk20 cleared, state = 2 stored into the call's delay slot, then the `0x51B9C` unsigned completion compare with the 0x1000/0xEFFF flag tail. Six of the eight jump-table slots point where the game's does; build.py confirmed the table bytes. |
| func_800511C0 | 101 | parked 61/101. Structure exact (see the note); the only residue is the mismatch return code: the game materialises 0x206 into $s0 before the bne and returns `addu $v0, $s0`, ours loads a constant after the func_80051F3C call. Literal, hoisted-local and inside-else-local forms all sink the constant. #17 scheduler class. |
| func_80051354 | 136 | parked 131/136, size 0x20C against 0x220. Second arm (the 16-slot allocator over D_800B124C and the `b & 1` insert/append of the node at slot+4) is five words short: the game hoists `n = &s->unk2C` and holds unkC across the allocator in a callee-saved register, which also accounts for its 0x30 frame against our 0x28. Allocation class, and the body is not instruction-complete yet. |
| func_80051E14 | 74 | parked 30/74 from the previous pass; the sweep re-confirmed 30 as the best of twelve variants. |

## New window 0x8001D000-0x8001E000 (claimed on #1): 17 matched first-draft

The lane's own windows were out of small undrafted bodies, so this window was claimed on issue #1 from
freshly fetched `main` — no claim had ever been filed anywhere in 0x80010000-0x80034FFF. 36 unmatched
bodies; the 17 below all matched on the first draft, ordered by real instruction count:

`func_8001D4D4` (2, `*p = 0` in the jr slot), `func_8001D080` (3, return a gp s32), `func_8001D530`
(4, `&e->unk8[i]`), `func_8001D860` (4, two gp stores then `return 0`), `func_8001D08C` (5, `D_8008AE84[2]`),
`func_8001D1D4` (5, u16 load through the same global), `func_8001D7A8` (8, call then clear a gp flag),
`func_8001D870` (7, `D_8008AEC4 + i * 0x44` with a **u16** index — the `andi 0xFFFF` told us the parameter
width), `func_8001D974` (10, `func_80034D4C(&D_8008AED0, v, 4)` — taking a *gp* address needs a 4-byte
extern), `func_8001D99C` (11, bit test; needs a small array declaration `u8 D_8008AED0[8]` so the base is
`addiu $gp` and the scaled index is computed before it), `func_8001D380` (13, set a global to an array
address then clear four 0x14-strided words — `i = 3` must be assigned *before* the pointer expression for
gcc to emit `addiu v1,$zero,3` first), `func_8001D15C` (15, two-call sequence with the `0x52594C50` magic),
`func_8001D198` (15, stride 0x18 + 8 over a u16 count), `func_8001D304` (15, 0xFF-terminated copy; the
counter must be `s32` and the store lvalue written `*(u8 *)(dst + n + 4)` or the `addu` operands swap),
`func_8001D7C8` (15, `func_80034C20(0x6A4)` → store → memset → init), `func_8001DC58` (16, store then
flag test), `func_8001D0A0` (17, `(i * 100 + 8)` folded into a separate `off` local before adding the base).

Parked with their diffs: `func_8001D040` 2/16 (gcc picks `$v1` instead of `$a0` for the `lui` temp of the
absolute `D_80089FE4` load) and `func_8001D340` 11/16 (the table walk's counter lands in `$a1` where the
game keeps it in `$v1`). The remaining 17 bodies in the window (21-402 instructions) are unopened.

## New window 0x80033000-0x80035000 (claimed on #1): 13 matched first-draft

Untouched ground at the top of the low range: 53 unmatched bodies, 25 of them <=22 words with no loop.
Opened 26 in size order; 13 matched on the first draft, 10 parked, 1 skipped on sight.

**Matched** (in this PR, by real instruction count): `func_80034C14` (3, return gp s32), `func_80033F68`
(4, return-old-value then store), `func_80034C7C` (4, `subu` in the jr slot needs the left operand loaded
first), `func_80034D30` (7, `n = p[-1]; n += 4; D = D + n;` — three statements, or gcc commutes the `addu`
and loads the gp global first), `func_80034EF4` (8, bare call), `func_80033F44` (9, `while (n > 0) s += *p++;`),
`func_800347FC` (10, struct fields at +0,+4,+5,+8,+C through a `u8 sym[8]` gp base — the 8-byte declaration
is what keeps `%gp_rel` while the writes reach past it), `func_80033F1C` (10, the global is loaded straight
into `$a0` only when it is *passed*: `s32 v = G; if (v) f(v);`), `func_80033EEC` (12, two-call if),
`func_80033EB4` (14, four-call sequence), `func_80034B68` (12, two constant stores then call — `sw $ra`
lands after them on its own), `func_80034CF0` (16, allocator: `sz = (n + 3) & ~3`, compare with `sltu`
against a `u32` bound), `func_80034654` (17, `'-'` then `negu`; the return is the *original* buffer).

**Parked with their diffs**: `func_80033804` 3/5 and `func_800337C4` 16/16 (0x3C vs 0x40) — the last `sw`
is pulled into the `jr` delay slot, and 337C4 also keeps the base in `$v0` instead of `$a0`; `func_80033818`
12/13 and `func_80033E14` 24/25 — shape identical, the game's twelve temps land in `$t0-$t9,$v0,$v1` while
gcc 2.8.1 starts the pool at `$v0`; `func_80034B98` 2/16 and (from the 0x1D000 window) `func_8001D040` 2/16
— same class both times, the `lui` temp for an absolute global goes to `$v0`/`$v1` instead of the `$a0` the
game reuses as both base and destination; `func_80034BD8` 3/15 — mask temp in `$v1` instead of `$v0`, the
`a0 - (x - 4)` expression folds to `(a0 + 4) - x`; `func_80033428`/`33480`/`333C8` 25/22 — all three read
`d[0..1]` back through `$a0` after the `func_80032F34` call, i.e. the game relies on `$a0` surviving with no
callee-saved register, while gcc keeps the pointer in `$s1`; `func_80033DB0` 25/25 (0x60 vs 0x64) — the
game spills `p` to `0($sp)` and reloads before each call, gcc parks it in `$s0`.
**Skipped on sight**: `func_80033714` — `addu $t9,$ra` save/restore around three unrolled calls, a
hand-unrolled body.

**Unopened in this window** (21-311 instr): the remaining 27 bodies, including `func_80034060` (311),
`func_80034874` (129) and the three 115-word `handwritten` bodies at `0x8003384C`/`0x80033A18`/`0x80033BE4`.

### Yield by band in the low range (all passes)

| band | opened | matched | rate |
|---|---|---|---|
| <=17 words | 20 | 13 | 65% |
| 20-30 words | 5 | 0 | 0% |
| 0x1D000 window (2-17 words) | 19 | 17 | 89% |

Small bodies with no loop and few conditionals convert; from 20 words up, every body in this window
stalled on allocation or a delay-slot fill.

## Low-band pass: 0x80012000, 0x80019000, 0x80025000 — 20 matched first-draft

Claims #29 (0x80011E00-0x80012400, already held) and #37 (0x80025000); 0x80019000 filed this pass.
Every body opened was <=21 instructions with no loop. 20 matched, 4 parked, 0 skipped on sight.

**Matched**: `12238` `123A8` `12208` `12004` `121E8` `12214` `12240` `12024` `12078` `1954C` `19FCC`
`19518` `19630` `256EC` `25A58` `25B5C` `256F4` `257F4` `25A0C` `25B10`.

Shapes worth keeping:
- `func_80012078`: the zero case must be the **early** `return 0` (`if (t == 0) return 0; return f(p, t);`),
  not `if (t != 0) return f(...)`. The ternary and the `!=` form both invert the branch and lose a word.
- `func_80025A0C`/`25B10`: the index is loaded once into a local, and the u16 store's scale must be its own
  statement (`j = i * 2;`) — inline `i * 2` sinks the `sllv` below the `sw` and adds a reload.
- `func_80012240`: the `sll 16`/`sra 16` before the call is a `s16` **parameter**, not a cast in the body.
- `func_80012024`: `count * 0x1C0` compiles as `sll 3; subu; sll 6`; the loop bound compares pointers with
  `sltu`, so the walking pointer must be `u8 *`, not an index.

**Parked**: `func_80012274` 3/11 and `func_800122A0` 10/11 (0x24 vs 0x2C) — `r = -v`/`r = v` select keeps
collapsing into `negu` in place; `func_80019C0C` and `func_80019EE4` 4/11 — counter lands in `$a2` where the
game keeps it in `$v1` (same residue as `func_8001D340`).

### Yield table (updated)

| band | opened | matched | rate |
|---|---|---|---|
| <=17 words, low range (all passes) | 40 | 33 | 83% |
| 18-21 words, low range | 6 | 3 | 50% |
| 20-30 words, 0x33000 window | 5 | 0 | 0% |

### Unopened in these windows (<=21 instr where noted)
`0x80012000`: `800122A0`(parked) `80012024`(done); remaining bodies are >=21 instr except `80012068`-area.
`0x80019000`: `80019C0C`/`80019EE4` parked; next is `80019444`, `80019410`.
`0x80025000`: `800257A0`(21) `80025A58`(done) `80025B5C`(done); remaining >=19 instr: `80025A0C`/`80025B10` done.
`0x8001F000` (unclaimed): 7 easy bodies including `8001F374`(14), `8001F3AC`(10), `8001FD14`(16), `8001F984`(19).

### Flag matrix on the parked clone set (register-role / scheduling residues)

Fifteen cells per body over the per-file flags `toolchain/compiler.toml` permits: none,
`-mno-split-addresses`, `-fno-schedule-insns`, `-fno-schedule-insns2`, `-G0`, `-G4`,
`-fno-strength-reduce`, `-O1`, `-O3`, and the pairs `-mno-split-addresses`+each scheduler flag,
`-fno-schedule-insns`+`-fno-schedule-insns2`, `-mno-split-addresses -G4`, `-G4 -fno-schedule-insns`,
`-O1 -mno-split-addresses`. Source shape held fixed at each body's best draft (variants were
scored first, baseline cell = the best draft).

| body | base | distinct diff counts across cells | best cell |
|---|---|---|---|
| `80033818` | 12/13 | 12 | 12/13 (none) |
| `80032CF4` | 16/18 | 16 | 16/18 (none) |
| `8002BCB0` | 2/17 | 2, 4 | 2/17 (none) |
| `8001D804` | 11/23 | 11, 18, 24 | 11/23 (none) |
| `80036F24` | 4/13 | 4, 15 | 4/13 (none) |
| `80034BD8` | 4/15 | 4, 13 | 4/15 (none) |
| `8002DE18` | 17/18 | 7, 14, 17, 18, 19 | 7/18 `-fno-schedule-insns2` |
| `8001DCF8` | 11/24 | 11 | 11/24 (none) |
| `800382C0` | 1/12 | 1 | 1/12 (none) |
| `80032FE0` | 3/5 | 3 | 3/5 (none) |
| `80033804` | 3/5 | 3 | 3/5 (none) |
| `80019C0C` | 4/11 | 4, 11 | 4/11 (none) |
| `80019EE4` | 4/11 | 4, 11 | 4/11 (none) |
| `80012274` | 3/11 | 3, 13 | 3/11 (none) |
| `800122A0` | 10/11 | 8, 10 | 8/11 `-G0` |
| `8001CD7C` | 2/10 | 2, 5, 10, 11 | 2/10 (none) |
| `80056A3C` | 2/10 | 0, 2, 10 | 0/0 `-O1` |
| `80032FF4` | 12/13 | 12 | 12/13 (none) |
| `800132FC` | 6/15 | 6 | 6/15 (none) |
| `80032D88` | 17/17 | 17 | 17/17 (none) |
| `80011B48` | 12/17 | 12, 16, 18 | 12/17 (none) |
| `8002DDE0` | 17/14 | 17, 20 | 17/14 (none) |

**Reading the matrix.** The register-role class is invariant: `80033818` (12/13 in every cell),
`80032CF4` (16/18 in every cell), `8002BCB0` (2/17 except `-G0` 4/17), `8001D804` (11/23, only `-G0`/`-O1`
and both scheduler flags make it worse), `800132FC`, `80032FF4`, `80032D88`, `80011B48` likewise. Flags
move the *scheduling* bodies, not the allocation bodies:

- **`80056A3C` converts: `-O1` takes it from 2/10 to MATCH**, and the matching source is the plain
  `extern u8 D_80082FA4[]; ... D_80082FA4[idx & 0xFFFF] + *(s32 *) D_8008A160;` shape that was parked
  at 2/10 under `-O2`. This is the first `-O1` conversion of a body outside issue #46's narrow-mask class.
- `8002DE18` improves 17/18 → **7/18 under `-fno-schedule-insns2`** (size becomes exact), but the
  remaining seven are the missing `addu` copy of the bump pointer, not scheduling; parked.
- `800122A0` improves 10/11 → 8/11 under `-G0`; still parked.
- Everything else has a flat row: the flags are inert.

### Sub-16-word tail, this pass
Opened `8002DCA8` (9 words) → **MATCH on first draft** (`struct { u32,u32,u32 }` table at `D_8006F834`,
store at `+8`, `u8` index narrowed by `andi`). Opened fresh `8002DDE0` (14 words) → parked, the loop
exit needs the game's single shared epilogue and the two-return form duplicates it (17 words vs 14).
Re-tested the two closest parked clones by hand after the matrix: `8001CD7C` (2/10, base/offset register
roles swapped in the `addu`; separate `off` statement and a struct-typed table both leave it at 2/10) and
`80012274` (3/11, `negu` in the branch delay slot vs gcc's in-place negate; `r = v; if (f) r = -v;`
leaves it at 3/11) — both parked.

Yield this pass: 2 units (`8002DCA8`, `80056A3C`) from 2 fresh bodies plus the 22-body matrix.

### `-O1` near-miss queue: per-body outcome

Every queue body was re-matched from its best draft with `/* cflags: -O1 */` in place and shapes spent
against the remainder. **The queue itself converts none of the 24**: every residue left after `-O1` is
either a register-role swap or a load/store-delay placement, and both are compiler decisions, not shapes.

| body | best `-O1` | what the remainder is |
|---|---|---|
| `80015D38` | **2/20** | the gp load of `D_8008AD38` lands in `$v0` and is copied by `addiu $v1,$v0,-0x10`; the game loads straight into `$v1`. Source forms tried: declaration order swapped (4/20), split assignment (3/20), cast arithmetic (3/20), `p = D_8008AD38; p -= 0x10;` (3/20, fixes the load but flips the loop's block layout) |
| `80026E88` | 12/16 | two load-delay `nop`s where the game interleaves the neighbouring stores; reordering the loop to the game's statement order gains 2 words but cannot remove them |
| `80034004` | 13/23 | `u16` counter promotion: game masks the counter at the compare and keeps `n` in `$a2`; any source form that says so re-masks at the increment (17/23, 24/23) |
| `80035810` | 18/20 | block layout: `beq` target and a duplicated `andi`/return path |
| `800432D8` | 15/24 | six-value shuffle; `lui`/`addiu` of `D_8008B384` hoisted before the index scale, then the loaded base copied instead of used in place |
| `80035BC0` | 18/21 | struct-store order |
| `80034C20` | 19/23 | rounding fold + a store in the `jr` delay slot |
| `80032400` | 23/27 | prologue save order, `mult` body |
| `80033DB0` | 23/25 | loop strength reduction |
| `80058448` | 27/43 | pointer/index walk |
| `8004734C` | 28/50 | copy-loop strength reduction |
| `80057CA4` | 29/45 | block layout, size still 0xc4 vs 0xb4 |
| `8002C5FC` | 32/35 | loop stride, size 0x9c vs 0x8c |
| `8004995C` | 44/46 | size 0xc4 vs 0xb8, allocation |
| `8004AF80` | 34/66 | size 0x104 vs 0x108 |
| `80047268` | 44/57 | size 0xe0 vs 0xe4 |
| `8004A094` | 45/39 | size 0xb8 vs 0x9c |
| `80057B94` | 45/68 | size 0x118 vs 0x110 |
| `80046EFC` | 55/70 | allocation |
| `80051354` | 125/136 | size 0x22c vs 0x220 |
| `80051844` | 84/96 | size 0x16c vs 0x180 |
| `80053A4C` | 59/58 | size 0xf8 vs 0xe8 |
| `80048450`, `8003A33C`, `8005853C` | — | no draft left after the archive prune (drafts were stale copies of merged units) |

`-O1` axis yield: **0 units from 24 bodies**. The axis is closed; the value it produced was the queue
ordering above, not conversions.

### Delay-slot store class: two units

Probing the tail for the "gcc swallows the last store into the `jr $ra` slot" signature (game
`sw; jr $ra; nop`, ours `sw; jr $ra; sw`) found a source shape that fixes it: mark the pointed-to objects
**`volatile`** so the final store cannot be sunk into the delay slot.

- `func_80032FE0` — `void func_80032FE0(volatile s32 *p) { p[0] = 0; p[1] = 0; p[2] = 0; }` — MATCH
  (was 3/5, 0x10 vs 0x14).
- `func_80033804` — same shape through a padded struct with `volatile` members at `+0x24/+0x28/+0x2C` —
  MATCH (was 3/5, 0x10 vs 0x14).

`volatile` here is a compiler barrier only: the three stores were already unconditional and ordered in the
original; it does not change observable behaviour, and both units are pure stores.

### Delay-slot store class, corpus-wide: it is two bodies, and both already shipped

`work/delay_probe.py` re-matched **every** draft under `work/near-miss/*.c` (274 drafts, 135 distinct
bodies) at the default level — each draft's own `-O1` header stripped, so the level is held fixed — and
classified each body by where its differing words sit relative to the end of the target, not by the
presence of a `nop`:

| probe class | bodies | barrier converts |
|---|---|---|
| sunk final store — size one word short **and** every differing word inside the last three words | 2 (`80032FE0`, `80033804`) | 2, both already shipped in #81 |
| store or load word sitting in a `jr`/branch delay slot | 0 | — |
| everything else (register roles, block layout, `lui` temps, earlier size mismatch) | 133 | 0 |

So the signature is real but rare: two bodies in the whole parked corpus, and they were exactly the ones
#81 found. The rest of the set does not have a delay-slot residue, and `volatile` on a body whose store
already matches wrecks its allocation. The family is closed at two units; the barrier is legitimate only
where the original's stores are unconditional and ordered under a `nop` slot, which is what both shipped
units are.

One barrier shape each on the two closest `-O1` stragglers:

| body | best before | barrier applied | after |
|---|---|---|---|
| `80015D38` | 2/20 (default), 9/20 (`-O1`) | `extern u8 *volatile D_8008AD38;` so the base load cannot be copied forward | 3/20 — worse; the residue is which register takes the load, not its order |
| `80026E88` | 12/16 (`-O1`) | `volatile u32 *d` destination for the three loop stores | 17/16, size 0x44 vs 0x40 — the barrier pins the stores but adds a reload and a frame word |

Both revert to their parked drafts; no barrier survives on either.

### Six units from the sub-20-word tail (fresh bodies, this pass)

| unit | shape that matched |
|---|---|
| `func_80019C0C` | `if (n != 0) { do { *dst++ = *src++; } while (--i != -1); }` with `i = n - 1` — the guard first, then a bottom-tested do-while; the `for (i = n - 1; i != -1; i--)` form emits a duplicated guard and 0x34 against 0x2c |
| `func_80019EE4` | the same body with the pointer roles swapped (copy `a1 → a0`) |
| `func_80013CE8` | three `out[i] = (a[i] + b[i]) >> 1;` statements — last store fills the `jr` slot, which is the *matching* direction here |
| `func_80026DAC` | three `out[i] = a[i] - b[i];` statements, same shape |
| `func_800132FC` | `if (p[0]==0 && p[1]==0 && p[2]==0) return 1; return 0;` — the folded `&&` chain in the *positive* test. Splitting it into `if (p[i]) return 0;` returns makes gcc fold the tail into `sltiu` (6/15) |
| `func_80034BD8` | `t = m - 4; D_8008A560 = a - t;` as **two statements** — writing `a - (m - 4)` inline makes gcc reassociate to `(a + 4) - m` and swap the `andi`/`subu` operands (4/15) |

### Fresh-ground pass: 290 unopened bodies, 7 units, 5 parks

`work/enum_fresh.py` lists every unmatched body on freshly fetched main that has **neither** a draft under
`work/near-miss/` **nor** an address mentioned anywhere in this file, minus handwritten/GTE bodies: **290
bodies**, and the smallest is **20 instructions** — the sub-20 tail is genuinely exhausted, so this pass
started at the 20-word floor.

| unit | words | shape |
|---|---|---|
| `func_80024D6C` | 20 | `idx` read after the call, then two `(&D_8008AF44)[idx] = 0` stores; the 4-byte externs keep both array bases gp-relative |
| `func_80024DBC` | 20 | three calls, argument order preserved (`b, 0x3333`; `a, 0xCCCC`; `a, b`) |
| `func_8002B57C` | 24 | unlink from a singly-linked list; the store `self->f3C = 0` must precede `n = h->head` (declaring `n` with its initialiser lets gcc hoist the load and shift every word) |
| `func_80013D34` | 25 | `(a[i] + b[i] + b[i] + b[i]) >> 1` written as three literal additions — gcc keeps all three `addu`s instead of strength-reducing |
| `func_80029420` | 26 | an early-return guard on `info[0x18] & 0x1000000`, then `func_8001D5B0(self, 0x4F4E4150, 1)`; `D_800A4F00` declared as `u8[0x40]` so the `lui`/`lw %lo` absolute form survives |
| `func_8002E848` | 26 | `buf[0] = *a; buf[1] = 0; buf[2] = *b;` then `f(buf, (s16) c, c)` — the third argument must be the **raw** `s32 c`, with `(s16)` only on the second, or gcc inserts an `addu` copy |
| `func_8001DC98` | 35 | **re-shipped**: still matched on current main but only ever lived in the conflicting PR #77 |

Parks (draft under `work/near-miss/`, residue named):

| body | best | residue |
|---|---|---|
| `8002050C` | **4/25** | `s32 end = -1` materialisation (`addu a3,v0,zero` vs `addiu a3,zero,-1`), one `addu` operand order, and the `(u8)` mask landing in the `jr` delay slot instead of the `beq` delay slot |
| `8001F4E8` | **2/26** | the command word lands in `$v1`; the game loads it into `$a1`. Every other word matches |
| `8002BF9C` | 9/24 | guard-first with a j-back-edge loop; gcc rotates to a bottom-tested loop (`while`) or inverts the guard (`for(;;)`) |
| `80034C8C` | 15/25 | sum computed into `$a0` instead of `$a2`, and the rounding tail one word short |
| `8002FE80` | 2/24 | `&buf` lands in `$v0`; the game uses `$a1` |
| `8001DB74` | 2/26 | `addu` result in `$v0` instead of `$v1` (base/index roles), same body otherwise |

PR dispositions this pass: **#77** is superseded — `func_80013CE8` and `func_80026DAC` landed through #82,
`func_8001DC98` is re-shipped here, and its census hunk is long obsolete. **#80** is census-only and
superseded by this file. **#83** (probe-count correction) is folded into this commit, so it can be closed.

### 20-30 word band pass: 5 units, and the role-forcing matrix

The unopened queue now starts at **27** (`work/enum_fresh.py`, 277 bodies after this pass's units), so this
pass covered the 27-29 word floor.

| unit | words | shape |
|---|---|---|
| `func_8002582C` | 27 | `self+0xFF8 = 6` in the guard's delay slot, then a `u32` counter loop writing `s16` slots at stride 0x8C — the counter **must** be unsigned or the `beqz`/`sltu` pair becomes `blez`/`slt` |
| `func_8002DCCC` | 27 | dispatch table `D_8006F834[self[3]]` with 12-byte entries; re-reading `self[3]` at each use (instead of caching it) is what keeps the reloads the game has |
| `func_800194A4` | 29 | unlink-and-push-front; the `while (p != 0) { nx = p->next; if (nx == self) break; p = nx; }` form with an early `if (self == head)` return |
| `func_8002572C` | 29 | same loop skeleton as `8002582C` but two word stores (`0xB333`, `0x10000`) at +0x40/+0x44 |
| `func_8001CFCC` | 29 | five-argument call with a zero stack argument, then two tagged lookups; the second lookup must reload `D_8008AE80` rather than reuse the local |

Role-forcing matrix on the parks (each body ≤ 4 shapes, source otherwise held at its best draft):

| body | best | shapes tried | outcome |
|---|---|---|---|
| `8002050C` | **4/25** | literal `-1` in both tests; `s32 end = -1` variable; `--i` in the guard; `return (u8) i` | `end` variable moves the compare into `$a3` (17/25); the rest hold at 4 |
| `8001F4E8` | **2/26** | separate `cur`/`nxt` locals; post-increment `self[0xB] += 4`; `tmp` round-trip through a third local | all 2/26 — the command word stays in `$v1` where the game uses `$a1` |
| `8001DB74` | **2/26** | `off = i * 68` local; typed array index; `base` local; `i * 17 * 4` | 2/26 for three of them, 12/26 for the `base` local — `addu` result stays in `$v0` |
| `8002FE80` | 2/24 | `s32 *p = (s32 *) buf; *out = p;`; `s32 buf[42]` | 2/24 — `&buf` stays in `$v0`, the game uses `$a1` |
| `8002BF9C` | 9/24 | `while` + return; `for(;;)` after the guard | the `for(;;)` form inverts the guard (20/24); the `while` form rotates to a bottom test |
| `80034C8C` | 15/25 | best draft re-tested | unchanged (sum lands in `$a0`, game uses `$a2`) |

New parks this pass: `8002BCF4` **16/28** (the `-1` sentinel is materialised in the prologue by the game and
after the loads by us), `8001D3B4` **11/29** (value pointer must be `p + 1` — that part matched; the rest is
load order and an insert-path `addiu` placement), `8002F4C0` 23/27 (`sw $ra` sinks below the guard),
`8001D540` 27/28, `800331FC` 35/27 (64-bit `>> 16` codegen: gcc emits a full shift sequence instead of the
game's `mfhi/mflo` recombination).

### 29-35 word band: 8 units from 11 drafts

| unit | words | shape |
|---|---|---|
| `func_8002EBA0` | 29 | `memset(out, 0, 8)` then a lookup; `out[0] = 1` and `out[1] = r->f3C` on success, returning 1 |
| `func_8002B708` | 29 | nested list walk (outer +0x94, inner +0x40); the tag compare must be written `key == (*(u16 *)(e + 2) & 0x1F)` — the reversed operand order is one word |
| `func_8001C410` | 30 | three identical alloc/clear blocks (`0x1400`, `0x400`, `0x180`); the size words are `u16` globals beside each pointer |
| `func_8001D0E4` | 30 | five-argument call with `1` as the second argument, `func_8001D3B4(0x44484C50, func_8001D15C)`, then lookup/attach |
| `func_8002D038` | 30 | walk `D_8008B050` by +8, call, then store the argument to the absolute `D_800A1C50` and set the flag |
| `func_8002E0D4` | 30 | same body with `func_8002E14C` — the pair confirms the shape |
| `func_8001F2FC` | 30 | walk `self+0x24` by `next`, break on the predicate, then clear `*(*(self+0x60)+0x4C)` when bit 1 of `self+0x5C` is set |
| `func_8001DBDC` | 31 | filter walk over `D_8008AEB0` at stride 0x6C, `u16` flag bit 0, pointer match at +0x1C |

Band yield: **8 of 11 drafts**. Parks: `8002B194` 28/31 (reverse scan of 9 slots; the `do/while` shape is
right but the frame is 0x70 against 0x7c), `80029488` 15/29 (frame 0x20 against 0x28 — one saved register
the game has and we do not), `8003302C` 34/29 and `8003353C` 37/30 (both the 64-bit `>> 16` codegen class).
The register-role parks were not touched this pass.

### 33-40 word band: 11 units from 16 drafts

| unit | words | shape |
|---|---|---|
| `func_80019FF4` | 33 | `func_8001B3A0()` then a guard call; on the early path `return 1`, else five gp-relative zero stores (two of them to `D_8008ADFC`), two calls, `func_8001D6D8(0x30, 0x40)`, `return 0` |
| `func_80025988` | 33 | `u8 work[0x30]` declared before `u16 hdr[3]` so the two stack slots land at sp+0x10 and sp+0x40; `memset(hdr, 0, 6)`, `hdr[0] = D_8008A2C0[D_8008A2BC]`, two calls, then the tail call |
| `func_80025A8C` | 33 | twin of `80025988` on `D_8008A2C4`, storing `hdr[1]` |
| `func_8002D9BC` | 33 | mask test `p[0] & 0x2400000`, three predicates, then `D_800A1C80[-1] = p; return 1` — the store must reuse the `D_800A1C80` base symbol (offset −4) or the `addiu` disappears |
| `func_80013FD0` | 34 | `*(s32 *)(arg0 + i * 0x10 + 0x17C)` indexed straight off the base, **not** through a `u8 *p = arg0` walker: the local makes gcc fold the base into `arg0 + 0x184` and the whole body shifts |
| `func_8002EFCC` | 34 | point-in-polygon over a pointer array at +0x1C; the counter is the third field's ternary (`(p[0] & 1) ? 3 : 2`) declared **before** the array load, and the loop is `do { … } while (i != -1)` |
| `func_800275A4` | 35 | two `memset`s (`0x60`, `0x4E00`) then twelve gp-relative stores then three calls |
| `func_80026DEC` | 35 | `s32 buf[3]; s32 vec[3];` in that order, `memset(buf,0,0xC)`, three copies, `func_800331FC(vec, 0x10000)`, then the five-argument call |
| `func_8002770C` | 35 | `a1 >= 0x81` guard, two `memset`s, `sh` of `a0` into a `u16` global, two zero stores, tail call, return the `D_800A4F00` base |
| `func_8002CB00` | 35 | `/* cflags: -mno-split-addresses */` — without it gcc hoists the `lui` of `D_80089F18` above `lw 0x18(a3)` and four words differ |
| `func_80033F78` | 35 | the fill loop is **duplicated in both arms** of `if (a0)` (the `sb $zero` after the first makes them unequal), and the base is recomputed per arm so the shared `lui` is reused |

Band yield: **11 of 16 drafts (69%)**. Parks, each with its residue:

| body | best | residue |
|---|---|---|
| `func_8002C9B8` | **2/36** | the second inner counter lands in `$v0` where the game uses `$v1`; the base-symbol fix (`D_800A4F00[1]` instead of `D_800A4F00 + 4`) took it from 29 to 2, and four declaration/scope shapes on the two counters did not move the role |
| `func_8002DA40` | 32/33 | size 0x7c against 0x84: gcc sinks each `sh` of the midpoint into the `bgez` delay slot where the game keeps `sh` before the branch and a `nop` in the slot; ternary `abs` and separate locals both reproduce the sink |
| `func_8001C4BC` | 32/33 | size 0x80 against 0x84: gcc cross-jumps the two `return -1` blocks into one and jumps back, the game materialises `-1` twice; `if`/`return`, ternary and mixed forms all merge |
| `func_8001FFB4` | 34/35 | size 0x88 against 0x8c: the game materialises `D_8006F2C0[+8]` in `$v0` and copies to `$s0`; we fold `%lo` straight into `$s0`, and the two saved-register roles (`$s1`/`$s2`) come out swapped |
| `func_8002C0B8` | 29/36 | the half-extent `lw 0x10(a1)` is hoisted before the `abs`, the game loads it beside `lw 0x4(a1)`; `s32 *f` (not `s16 *f`) was needed for the four `lw`s and `a0[2]` for the y component |

### The 64-bit class under `-O1`: sequence reached, one dead word left

`func_800331FC` re-tested with `/* cflags: -O1 */` and the multiply written as three explicit locals in a
`u32` result variable: **27 of 27 words differing, size 0x70 against 0x6c**. The `mult / mflo / mfhi / srl 16 /
sll 16 / or` group is emitted in the game's order — at the default level the same source spills the DImode
pair to the stack (0x8c, 35/27). The single extra word is a dead `srl` of the high half that `-O1` will not
eliminate; `-O2`, `-O3`, `-O1/-O2` with `-fno-schedule-insns{,2}` and the `unsigned long long` / `u32` /
implicit-truncation / explicit-temp spellings all stop at 0x70 or worse. Same treatment on the other two:
`8003302C` 34/29 → **34/29 at `-O1`, 0x88 against 0x74**; `8003353C` 37/30 → **33/30, 0x84 against 0x78**.
Verdict: the class is *reachable* at `-O1` but not closed; the residue is one dead shift per multiply, which
no source spelling tested removes. Drafts parked as `work/near-miss/func_80033{1FC,02C,53C}-o1*.c`.
