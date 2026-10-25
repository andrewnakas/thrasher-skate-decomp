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
