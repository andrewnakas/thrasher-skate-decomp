# Lane census (0x80035000-0x80058633), corrected nop rule

<!-- BEGIN GENERATED TABLE -->

## Table of record (generated — do not hand-edit)

Every per-body number in this file is produced by `python work/verify.py --write`; the
journal sections further down keep the reasoning that led to them and their hand-written
counts are history, not authority. Best drafts live at `work/best/<body>.c`, a path with no
number in it, so a measurement cannot go stale in a filename.

507 unmatched bodies in the corpus; **208 drafted and measured here** (compile-error 2, instruction-stream 17, match 1, move-vs-materialise 1, operand 16, register-role 36, scheduling 1, size 134); 1 drafts predate a merge and are prunable.

| body | best draft | words | size | class | status | class verdict |
|---|---|---|---|---|---|---|
| `func_80034B98` | `work/near-miss/func_80034B98-match-scan-blocked.c` | 0/16 | +0 | match | blocked | scan: needs D_801FC000 (issue #101) |
| `func_800382C0` | `work/near-miss/func_800382C0-split.c` | 1/12 | +0 | register-role | parked | - |
| `func_80055820` | `work/near-miss/func_80055820-draft.c` | 1/34 | +0 | scheduling | parked | - |
| `func_8001DB74` | `work/near-miss/func_8001DB74-role.c` | 2/26 | +0 | register-role | parked | holds (register-role) |
| `func_8001F4E8` | `work/near-miss/func_8001F4E8-2of26.c` | 2/26 | +0 | register-role | parked | holds (register-role) |
| `func_8002BCB0` | `work/near-miss/func_8002BCB0-parked.c` | 2/17 | +0 | register-role | parked | - |
| `func_8002C9B8` | `work/near-miss/func_8002C9B8-2of36.c` | 2/36 | +0 | register-role | parked | - |
| `func_8002FE80` | `work/near-miss/func_8002FE80-role.c` | 2/24 | +0 | register-role | parked | holds (register-role) |
| `func_8003BF7C` | `work/near-miss/func_8003BF7C-sweep.c` | 2/79 | +0 | register-role | parked | - |
| `func_80042E9C` | `work/near-miss/func_80042E9C-near-miss.c` | 2/58 | +0 | register-role | parked | - |
| `func_8004BF94` | `work/near-miss/func_8004BF94-sweep.c` | 2/52 | +0 | operand | parked | - |
| `func_80056C90` | `work/near-miss/func_80056C90-sweep.c` | 2/36 | +0 | register-role | parked | - |
| `func_80015D38` | `work/near-miss/func_80015D38-o1-2w.c` | 3/20 | +0 | operand | parked | - |
| `func_80019570` | `work/near-miss/func_80019570.c` | 4/48 | +0 | register-role | parked | - |
| `func_8002050C` | `work/near-miss/func_8002050C-4of25.c` | 4/25 | +0 | move-vs-materialise | parked | holds (move-vs-materialise) |
| `func_80035C14` | `work/near-miss/func_80035C14-subscript.c` | 4/34 | +0 | register-role | parked | - |
| `func_8003B8F8` | `work/near-miss/func_8003B8F8-band.c` | 4/46 | +0 | register-role | parked | - |
| `func_8003ED28` | `work/near-miss/func_8003ED28-near-miss.c` | 5/60 | +0 | register-role | parked | - |
| `func_80056FF4` | `work/near-miss/func_80056FF4-subscript.c` | 5/39 | +2 | size | parked | - |
| `func_80057090` | `work/near-miss/func_80057090-near-miss.c` | 5/92 | +0 | instruction-stream | parked | - |
| `func_800257A0` | `work/near-miss/func_800257A0-fresh.c` | 6/21 | +0 | instruction-stream | parked | - |
| `func_8003BDB8` | `work/near-miss/func_8003BDB8-sweep.c` | 6/31 | +0 | register-role | parked | - |
| `func_80043294` | `work/near-miss/func_80043294-g8.c` | 6/17 | +0 | register-role | parked | - |
| `func_8002D904` | `work/near-miss/func_8002D904-7of46.c` | 7/46 | +0 | operand | parked | - |
| `func_800535EC` | `work/near-miss/func_800535EC-band.c` | 7/67 | +0 | register-role | parked | - |
| `func_8003AC04` | `work/near-miss/func_8003AC04-near-miss.c` | 8/30 | +0 | instruction-stream | parked | - |
| `func_8002B060` | `work/near-miss/func_8002B060-fresh.c` | 9/32 | +0 | register-role | parked | - |
| `func_8002BA64` | `work/near-miss/func_8002BA64-parked.c` | 9/23 | +0 | register-role | parked | - |
| `func_8002BF9C` | `work/near-miss/func_8002BF9C-parked.c` | 9/24 | +1 | size | parked | - |
| `func_8004E930` | `work/near-miss/func_8004E930-near-miss.c` | 9/121 | +0 | register-role | parked | - |
| `func_800120B8` | `work/near-miss/func_800120B8-const-sched-park.c` | 10/76 | +0 | instruction-stream | parked | - |
| `func_80032C28` | `work/near-miss/func_80032C28-signed.c` | 10/11 | -3 | size | parked | - |
| `func_8003A09C` | `work/near-miss/func_8003A09C-near-miss.c` | 10/49 | +2 | size | parked | - |
| `func_8003B3CC` | `work/near-miss/func_8003B3CC-sweep.c` | 10/19 | +0 | instruction-stream | parked | - |
| `func_8001D3B4` | `work/near-miss/func_8001D3B4-11of29.c` | 11/29 | +0 | instruction-stream | parked | - |
| `func_8001D804` | `work/near-miss/func_8001D804-parked.c` | 11/23 | +0 | instruction-stream | parked | - |
| `func_8001DCF8` | `work/near-miss/func_8001DCF8-parked.c` | 11/24 | +1 | size | parked | - |
| `func_8001FCB0` | `work/near-miss/func_8001FCB0-parked.c` | 11/25 | +0 | instruction-stream | parked | - |
| `func_80034758` | `work/near-miss/func_80034758-11of41.c` | 11/41 | +0 | register-role | parked | - |
| `func_800379F4` | `work/near-miss/func_800379F4-near-miss.c` | 11/26 | +0 | register-role | parked | - |
| `func_8004A130` | `work/near-miss/func_8004A130-parked.c` | 11/80 | +0 | operand | parked | - |
| `func_8004CCA0` | `work/near-miss/func_8004CCA0-sweep.c` | 11/34 | +0 | register-role | parked | - |
| `func_80011B48` | `work/near-miss/func_80011B48-parked.c` | 12/17 | +0 | register-role | parked | - |
| `func_80032644` | `work/near-miss/func_80032644.c` | 12/63 | +0 | operand | parked | - |
| `func_80032FF4` | `work/near-miss/func_80032FF4-parked.c` | 12/13 | +0 | register-role | parked | - |
| `func_80033818` | `work/near-miss/func_80033818-parked.c` | 12/13 | +0 | register-role | parked | - |
| `func_8003C220` | `work/near-miss/func_8003C220-near-miss.c` | 12/28 | +0 | register-role | parked | - |
| `func_80056D20` | `work/near-miss/func_80056D20-sweep.c` | 12/44 | +0 | operand | parked | - |
| `func_8002C490` | `work/near-miss/func_8002C490-parked.c` | 13/21 | +1 | size | parked | - |
| `func_80024F3C` | `work/near-miss/func_80024F3C-parked.c` | 14/50 | +1 | size | parked | - |
| `func_80047A44` | `work/near-miss/func_80047A44-sweep.c` | 14/34 | +0 | register-role | parked | - |
| `func_8004E460` | `work/near-miss/func_8004E460-near-miss.c` | 14/50 | +0 | instruction-stream | parked | - |
| `func_80029488` | `work/near-miss/func_80029488-frame.c` | 15/29 | +0 | operand | parked | - |
| `func_80034C8C` | `work/near-miss/func_80034C8C-role.c` | 15/25 | -1 | size | parked | - |
| `func_8004862C` | `work/near-miss/func_8004862C-stmtorder.c` | 15/28 | +0 | instruction-stream | parked | - |
| `func_80052518` | `work/near-miss/func_80052518-near-miss.c` | 15/73 | -1 | size | parked | - |
| `func_8001D620` | `work/near-miss/func_8001D620-parked.c` | 16/46 | -1 | size | parked | - |
| `func_8002BCF4` | `work/near-miss/func_8002BCF4-16of28.c` | 16/28 | +0 | instruction-stream | parked | - |
| `func_80032CF4` | `work/near-miss/func_80032CF4-parked.c` | 16/18 | +0 | register-role | parked | - |
| `func_800337C4` | `work/near-miss/func_800337C4-parked.c` | 16/16 | -1 | size | parked | - |
| `func_8002DD88` | `work/near-miss/func_8002DD88-parked.c` | 17/22 | -1 | size | parked | - |
| `func_8002DDE0` | `work/near-miss/func_8002DDE0-parked.c` | 17/14 | +4 | size | parked | - |
| `func_8002DE18` | `work/near-miss/func_8002DE18-parked.c` | 17/18 | -1 | size | parked | - |
| `func_80032D88` | `work/near-miss/func_80032D88-parked.c` | 17/17 | -2 | size | parked | - |
| `func_80034004` | `work/near-miss/func_80034004-parked.c` | 17/23 | +1 | size | parked | - |
| `func_80035810` | `work/near-miss/func_80035810-sweep.c` | 17/20 | +2 | size | parked | - |
| `func_8001D340` | `work/near-miss/func_8001D340-parked.c` | 18/16 | +2 | size | parked | - |
| `func_80032D3C` | `work/near-miss/func_80032D3C-sched.c` | 18/19 | -1 | size | parked | - |
| `func_80056F4C` | `work/near-miss/func_80056F4C-sweep.c` | 18/42 | -2 | size | parked | - |
| `func_80026E88` | `work/near-miss/func_80026E88-parked.c` | 19/16 | +3 | size | parked | - |
| `func_80035BC0` | `work/near-miss/func_80035BC0-check.c` | 20/21 | -2 | size | parked | - |
| `func_800432D8` | `work/near-miss/func_800432D8-near-miss.c` | 20/24 | -1 | size | parked | - |
| `func_8001D4DC` | `work/near-miss/func_8001D4DC-parked.c` | 21/21 | -3 | size | parked | - |
| `func_8002BFFC` | `work/near-miss/func_8002BFFC-parked.c` | 21/47 | +1 | size | parked | - |
| `func_80030518` | `work/near-miss/func_80030518.c` | 21/55 | -1 | size | parked | - |
| `func_8003834C` | `work/near-miss/func_8003834C-sweep.c` | 21/39 | +0 | operand | parked | - |
| `func_8004F1E0` | `work/near-miss/func_8004F1E0-near-miss.c` | 21/28 | +0 | register-role | parked | - |
| `func_80020D74` | `work/near-miss/func_80020D74-sched-park.c` | 22/39 | -1 | size | parked | - |
| `func_80034824` | `work/near-miss/func_80034824-parked.c` | 22/20 | +3 | size | parked | - |
| `func_80034C20` | `work/near-miss/func_80034C20-parked.c` | 22/23 | -1 | size | parked | - |
| `func_8003BA14` | `work/near-miss/func_8003BA14-sweep.c` | 22/61 | +0 | operand | parked | - |
| `func_8002C148` | `work/near-miss/func_8002C148-parked.c` | 23/27 | +2 | size | parked | - |
| `func_80046878` | `work/near-miss/func_80046878-sweep.c` | 23/41 | -1 | size | parked | - |
| `func_80033714` | `work/near-miss/func_80033714.c` | 24/21 | +3 | size | parked | - |
| `func_80033E14` | `work/near-miss/func_80033E14-parked.c` | 24/25 | +0 | register-role | parked | - |
| `func_80037968` | `work/near-miss/func_80037968-sweep.c` | 24/35 | -4 | size | parked | - |
| `func_800494A4` | `work/near-miss/func_800494A4-check.c` | 24/32 | +1 | size | parked | - |
| `func_80015684` | `work/near-miss/func_80015684-parked.c` | 25/44 | +2 | size | parked | - |
| `func_80033428` | `work/near-miss/func_80033428-parked.c` | 25/22 | +4 | size | parked | - |
| `func_80033480` | `work/near-miss/func_80033480-parked.c` | 25/22 | +4 | size | parked | - |
| `func_800334D8` | `work/near-miss/func_800334D8-parked.c` | 25/25 | -2 | size | parked | - |
| `func_80033DB0` | `work/near-miss/func_80033DB0-parked.c` | 25/25 | -1 | size | parked | - |
| `func_800484B4` | `work/near-miss/func_800484B4-best.c` | 25/57 | +0 | register-role | parked | - |
| `func_8001C2F0` | `work/near-miss/func_8001C2F0-role-park.c` | 26/49 | +0 | operand | parked | - |
| `func_8002F4C0` | `work/near-miss/func_8002F4C0-parked.c` | 26/27 | -1 | size | parked | - |
| `func_80032400` | `work/near-miss/func_80032400-parked.c` | 26/27 | -1 | size | parked | - |
| `func_800333C8` | `work/near-miss/func_800333C8-parked.c` | 26/23 | +3 | size | parked | - |
| `func_800331FC` | `work/near-miss/func_800331FC-o1-27of27.c` | 27/27 | +1 | size | parked | holds (fixed-point) |
| `func_80011F84` | `work/near-miss/func_80011F84-parked.c` | 28/30 | +2 | size | parked | - |
| `func_8002B194` | `work/near-miss/func_8002B194-28of31.c` | 28/31 | -3 | size | parked | - |
| `func_80034698` | `work/near-miss/func_80034698-fresh.c` | 28/48 | +1 | size | parked | - |
| `func_8004584C` | `work/near-miss/func_8004584C-sweep.c` | 28/38 | -2 | size | parked | - |
| `func_80048598` | `work/near-miss/func_80048598-best.c` | 28/37 | +0 | register-role | parked | - |
| `func_800159D8` | `work/near-miss/func_800159D8-parked.c` | 29/47 | +2 | size | parked | - |
| `func_8001D540` | `work/near-miss/func_8001D540-parked.c` | 29/28 | +2 | size | parked | - |
| `func_8002C0B8` | `work/near-miss/func_8002C0B8-29of36.c` | 29/36 | +3 | size | parked | - |
| `func_8004EDF8` | `work/near-miss/func_8004EDF8-sweep.c` | 29/53 | -3 | size | parked | - |
| `func_80057CA4` | `work/near-miss/func_80057CA4-loaddelay.c` | 29/45 | +4 | size | parked | - |
| `func_80014170` | `work/near-miss/func_80014170-fresh.c` | 30/46 | -2 | size | parked | - |
| `func_8002A198` | `work/near-miss/func_8002A198-parked.c` | 30/51 | -4 | size | parked | - |
| `func_8004813C` | `work/near-miss/func_8004813C-sweep.c` | 30/51 | -1 | size | parked | - |
| `func_80051E14` | `work/near-miss/func_80051E14-near-miss.c` | 30/74 | -2 | size | parked | - |
| `func_80022308` | `work/near-miss/func_80022308-parked.c` | 31/41 | -3 | size | parked | holds (filled-nop) |
| `func_800387C8` | `work/near-miss/func_800387C8-near-miss.c` | 31/37 | -1 | size | parked | - |
| `func_8001C4BC` | `work/near-miss/func_8001C4BC-32of33.c` | 32/33 | -1 | size | parked | - |
| `func_8002D734` | `work/near-miss/func_8002D734-role-park.c` | 32/58 | +0 | register-role | parked | - |
| `func_8002D81C` | `work/near-miss/func_8002D81C-role-park.c` | 32/58 | +0 | register-role | parked | - |
| `func_8002DA40` | `work/near-miss/func_8002DA40-32of33.c` | 32/33 | -2 | size | parked | - |
| `func_80035C9C` | `work/near-miss/func_80035C9C-near-miss.c` | 32/36 | -2 | size | parked | - |
| `func_80053EA8` | `work/near-miss/func_80053EA8-near-miss.c` | 32/39 | -3 | size | parked | - |
| `func_8002C5FC` | `work/near-miss/func_8002C5FC-parked.c` | 33/35 | +3 | size | parked | - |
| `func_8003353C` | `work/near-miss/func_8003353C-o1.c` | 33/30 | +3 | size | parked | holds (fixed-point) |
| `func_8004995C` | `work/near-miss/func_8004995C-near-miss.c` | 33/46 | -1 | size | parked | - |
| `func_8001FFB4` | `work/near-miss/func_8001FFB4-34of35.c` | 34/35 | -1 | size | parked | - |
| `func_8002CF94` | `work/near-miss/func_8002CF94-parked.c` | 34/41 | +2 | size | parked | - |
| `func_8003302C` | `work/near-miss/func_8003302C-64bit.c` | 34/29 | +5 | size | parked | holds (fixed-point) |
| `func_8004734C` | `work/near-miss/func_8004734C-sweep.c` | 34/50 | -2 | size | parked | - |
| `func_8002DFF8` | `work/near-miss/func_8002DFF8.c` | 35/55 | -1 | size | parked | - |
| `func_80058448` | `work/near-miss/func_80058448-band.c` | 35/43 | +0 | register-role | parked | - |
| `func_8004669C` | `work/near-miss/func_8004669C-sweep.c` | 37/104 | +0 | operand | parked | - |
| `func_8002AB64` | `work/near-miss/func_8002AB64-parked.c` | 38/44 | -1 | size | parked | - |
| `func_8002C1B4` | `work/near-miss/func_8002C1B4.c` | 38/52 | +2 | size | parked | - |
| `func_800474B4` | `work/near-miss/func_800474B4-sweep.c` | 38/49 | -2 | size | parked | - |
| `func_80047578` | `work/near-miss/func_80047578-sweep.c` | 38/49 | -1 | size | parked | - |
| `func_80052380` | `work/near-miss/func_80052380-near-miss.c` | 38/102 | +0 | instruction-stream | parked | - |
| `func_80035F5C` | `work/near-miss/func_80035F5C-sweep.c` | 39/49 | +1 | size | parked | - |
| `func_800519C4` | `work/near-miss/func_800519C4-band.c` | 39/72 | -1 | size | parked | - |
| `func_8001D428` | `work/near-miss/func_8001D428-40of43.c` | 40/43 | -8 | size | parked | - |
| `func_8003571C` | `work/near-miss/func_8003571C-band.c` | 40/45 | -2 | size | parked | - |
| `func_80038A80` | `work/near-miss/func_80038A80-band.c` | 41/49 | -3 | size | parked | - |
| `func_800223AC` | `work/near-miss/func_800223AC-42of42.c` | 42/42 | -4 | size | parked | holds (filled-nop) |
| `func_80025004` | `work/near-miss/func_80025004-parked.c` | 42/44 | +4 | size | parked | - |
| `func_8002A044` | `work/near-miss/func_8002A044-41of45.c` | 42/45 | +4 | size | parked | - |
| `func_80034A78` | `work/near-miss/func_80034A78.c` | 42/60 | +0 | instruction-stream | parked | - |
| `func_80047014` | `work/near-miss/func_80047014-sweep.c` | 42/62 | -4 | size | parked | - |
| `func_8002AD6C` | `work/near-miss/func_8002AD6C-parked.c` | 43/48 | +0 | register-role | parked | - |
| `func_8002B2B0` | `work/near-miss/func_8002B2B0-parked.c` | 43/44 | -2 | size | parked | - |
| `func_8002EC14` | `work/near-miss/func_8002EC14-parked.c` | 43/41 | +2 | size | parked | - |
| `func_8002C8B8` | `work/near-miss/func_8002C8B8.c` | 44/64 | +0 | operand | parked | - |
| `func_8004836C` | `work/near-miss/func_8004836C-near-miss.c` | 44/57 | -5 | size | parked | - |
| `func_80019F10` | `work/near-miss/func_80019F10-parked.c` | 45/47 | -5 | size | parked | - |
| `func_8001A108` | `work/near-miss/func_8001A108.c` | 45/57 | +0 | instruction-stream | parked | - |
| `func_8002C688` | `work/near-miss/func_8002C688.c` | 46/61 | +7 | size | parked | - |
| `func_800201AC` | `work/near-miss/func_800201AC.c` | 47/56 | -2 | size | parked | - |
| `func_80038970` | `work/near-miss/func_80038970-sweep.c` | 47/68 | +0 | instruction-stream | parked | - |
| `func_80019670` | `work/near-miss/func_80019670-role-park.c` | 48/55 | +0 | operand | parked | - |
| `func_8004A094` | `work/near-miss/func_8004A094-near-miss.c` | 48/39 | +11 | size | parked | - |
| `func_80038864` | `work/near-miss/func_80038864-sweep.c` | 49/67 | +0 | instruction-stream | parked | - |
| `func_8004912C` | `work/near-miss/func_8004912C-sweep.c` | 49/65 | -1 | size | parked | - |
| `func_8001C0AC` | `work/near-miss/func_8001C0AC-parked.c` | 50/50 | -3 | size | parked | - |
| `func_8001F9D0` | `work/near-miss/func_8001F9D0.c` | 50/59 | +2 | size | parked | - |
| `func_80022148` | `work/near-miss/func_80022148.c` | 51/53 | -1 | size | parked | - |
| `func_8004E7EC` | `work/near-miss/func_8004E7EC-clamp-park.c` | 51/81 | +0 | instruction-stream | parked | - |
| `func_800358A8` | `work/near-miss/func_800358A8-near-miss.c` | 52/61 | -3 | size | parked | - |
| `func_8001BD0C` | `work/near-miss/func_8001BD0C.c` | 53/56 | -5 | size | parked | - |
| `func_80036F64` | `work/near-miss/func_80036F64-sweep.c` | 53/67 | -1 | size | parked | - |
| `func_80047268` | `work/near-miss/func_80047268-sweep.c` | 53/57 | -2 | size | parked | - |
| `func_8004E6CC` | `work/near-miss/func_8004E6CC-band.c` | 53/72 | -2 | size | parked | - |
| `func_8002A9E0` | `work/near-miss/func_8002A9E0-parked.c` | 54/50 | +4 | size | parked | - |
| `func_8002DF04` | `work/near-miss/func_8002DF04.c` | 54/61 | +1 | size | parked | - |
| `func_8002221C` | `work/near-miss/func_8002221C.c` | 56/59 | -5 | size | parked | - |
| `func_80042338` | `work/near-miss/func_80042338-sweep.c` | 56/64 | -1 | size | parked | - |
| `func_80046EFC` | `work/near-miss/func_80046EFC-sweep.c` | 56/70 | +0 | operand | parked | - |
| `func_8002FEE0` | `work/near-miss/func_8002FEE0.c` | 57/63 | +0 | operand | parked | - |
| `func_80053A4C` | `work/near-miss/func_80053A4C-sweep.c` | 57/58 | +4 | size | parked | - |
| `func_80029CCC` | `work/near-miss/func_80029CCC.c` | 58/56 | +2 | size | parked | - |
| `func_80015D88` | `work/near-miss/func_80015D88.c` | 59/65 | -2 | size | parked | - |
| `func_8001D88C` | `work/near-miss/func_8001D88C.c` | 60/58 | +5 | size | parked | - |
| `func_80026EC8` | `work/near-miss/func_80026EC8-near-miss.c` | 60/61 | +2 | size | parked | - |
| `func_8002F730` | `work/near-miss/func_8002F730.c` | 60/56 | +4 | size | parked | - |
| `func_8004DBF0` | `work/near-miss/func_8004DBF0-parked.c` | 60/82 | -7 | size | parked | - |
| `func_8002D0B0` | `work/near-miss/func_8002D0B0.c` | 61/58 | +11 | size | parked | - |
| `func_8003A1B8` | `work/near-miss/func_8003A1B8-sweep.c` | 61/71 | +3 | size | parked | - |
| `func_800511C0` | `work/near-miss/func_800511C0-parked.c` | 61/101 | +0 | operand | parked | - |
| `func_80032B1C` | `work/near-miss/func_80032B1C.c` | 62/64 | +1 | size | parked | - |
| `func_80057B94` | `work/near-miss/func_80057B94-sweep.c` | 62/68 | +1 | size | parked | - |
| `func_8003B478` | `work/near-miss/func_8003B478-sweep.c` | 65/71 | -2 | size | parked | - |
| `func_8002EE94` | `work/near-miss/func_8002EE94.c` | 66/78 | -3 | size | parked | - |
| `func_8003BE34` | `work/near-miss/func_8003BE34-sweep.c` | 66/82 | +2 | size | parked | - |
| `func_8004AF80` | `work/near-miss/func_8004AF80-sweep.c` | 66/66 | -3 | size | parked | - |
| `func_80035D2C` | `work/near-miss/func_80035D2C-sweep.c` | 67/69 | -2 | size | parked | - |
| `func_80018FBC` | `work/near-miss/func_80018FBC.c` | 68/73 | +2 | size | parked | - |
| `func_8003AF4C` | `work/near-miss/func_8003AF4C-sweep.c` | 68/71 | -2 | size | parked | - |
| `func_8001C540` | `work/near-miss/func_8001C540.c` | 70/59 | +11 | size | parked | - |
| `func_80029320` | `work/near-miss/func_80029320.c` | 71/64 | +7 | size | parked | - |
| `func_8004E528` | `work/near-miss/func_8004E528-sched-park.c` | 82/105 | -1 | size | parked | - |
| `func_800568C0` | `work/near-miss/func_800568C0-sweep.c` | 90/95 | -11 | size | parked | - |
| `func_80051844` | `work/near-miss/func_80051844-near-miss.c` | 92/96 | -5 | size | parked | - |
| `func_8002DAE8` | `work/near-miss/func_8002DAE8-near-miss.c` | 94/98 | -19 | size | parked | - |
| `func_80017140` | `work/near-miss/func_80017140-near-miss.c` | 113/153 | -10 | size | parked | - |
| `func_8003682C` | `work/near-miss/func_8003682C-sweep.c` | 130/138 | +5 | size | parked | - |
| `func_80051354` | `work/near-miss/func_80051354-parked.c` | 131/136 | -5 | size | parked | - |
| `func_80037DC4` | `work/near-miss/func_80037DC4-sweep.c` | 143/190 | +1 | size | parked | - |
| `func_8003A5A4` | `work/near-miss/func_8003A5A4-sweep.c` | 144/144 | +7 | size | parked | - |
| `func_8003BB1C` | `work/near-miss/func_8003BB1C-sweep.c` | 166/167 | -73 | size | parked | - |
| `func_8003B068` | `work/near-miss/func_8003B068-sweep.c` | 195/217 | -103 | size | parked | - |
| `func_80025544` | `work/near-miss/func_80025544-near-miss.c` | - | - | compile-error | broken | - |
| `func_800363F8` | `work/near-miss/func_800363F8.c` | - | - | compile-error | broken | - |

<!-- END GENERATED TABLE -->

---

## Pass journal (history: numbers here are superseded by the table above)

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

### 41-55 word band: 4 units from 16 drafts

| unit | words | shape |
|---|---|---|
| `func_800248B0` | 42 | `func_80024720(a0, a1)` then a three-level nest over four gp-relative `s32[2]` tables indexed by `D_8008A2BC`, re-read at every use (a cached index loses the second `lw`) |
| `func_80027A9C` | 42 | four chained calls through `func_8001D080()`, each re-invoked rather than cached; two `return 0` paths and a `return r` tail |
| `func_8001E900` | 43 | unlink walk on a singly-linked list at `self+0x24` with a `prev` that stays 0 for the head case; `if (--*(u8 *)(self + 0x35))` is what puts the `andi 0xFF` after the `sb` |
| `func_80018C64` | 45 | `u8 flag` (not `s32`) — the game masks it with `andi 0xFF` before the branch; and `func_8001954C` takes the same `a0` the walker used, which is what materialises `addu $a0,$s0,$zero` in the `bnez` delay slot |

Band yield: **4 of 16 drafts (25%)** — a sharp drop from 69% in the 33-40 band. Twelve parks, every one of
them an instruction stream that is *already correct* with one to four words of allocation or scheduling
residue:

| body | best | residue |
|---|---|---|
| `func_8002D904` | **7/46** | one swapped callee-saved pair: the game keeps the counter in `$s2` and the pointer in `$s1` (reusing the `self` register); declaration order and pointer form do not move it |
| `func_80034758` | 11/41 | size exact, `frac` lands in `$a0` where the game uses `$a3`, and the dependent `sb`/`addiu` then use `$s0` instead of `$a0` |
| `func_80015684` | 25/44 | size 0xb8 against 0xb0: the two `lw`/`sw` pairs on the `0xFF`-filled block keep `D_8008AD34` in a register rather than reloading it |
| `func_8002AB64` | 38/44 | the game carries a 0x10-byte frame for the `mult` spills (`sw $v0,0x0($sp)` of the *operand*) and puts the shared `return 0` block at the end of the function; we spill nothing and place it inline |
| `func_8001D428` | 40/43 | 8 words short: the game emits two `j` paths and an explicit `arg1 = 0` in the third arm of the key test; gcc deletes the dead store and the whole shape collapses |
| `func_8002A044` | 41/45 | `t` has its address taken by `func_8003B754`, and the game keeps a register copy (`addu $v1,$v0,$zero`) beside the stack slot; we reload from the slot each iteration |
| `func_80022308` | 31/41 | 4 words short: the load-delay `nop` after `lw 0xFF8($a0)` is filled by our hoisted `addiu` of the tag constant — see the note below |
| `func_800223AC` | 42/42 | identical stream to `80022308` with tag 7; same filled-nop residue |
| `func_8002CF94` | 34/41 | the game copies the head into a separate walker in the `bnez` delay (`addu $v1,$v0,$zero`) and keeps the common tail starting at the `f0` store; ours folds both |
| `func_8002EC14` | 43/41 | three `beqz`/`bnez` must all share one `return 0` block at the end; nested `if`s, a flat `&&`, and adding a `s16 *p = a` local all change the layout |
| `func_8002B2B0` | 43/44 | `slot` must be `s + 1` off a `(s32 *)(e + 0x1C)` walker to reproduce `addiu $a2,$v1,0x1C` / `lw 0x4($a2)`; 2 words still short |
| `func_80025004` | 42/44 | 4 words over: the six indexed stores each re-load their gp-relative index; we CSE one of them |

Skipped on sight: `func_80032F34` (handwritten — `addi`, `sub`, `add` markers in the listing).

**New residue class: the filled load-delay nop.** `func_80022308`/`800223AC` are 3-4 words short because the
game leaves a `nop` in the load-delay slot after `lw 0xFF8($a0)` and after the second `lw` of the same field,
while our build fills that slot with a hoisted `addiu` of the literal it is about to store. The instruction
streams are otherwise identical (same 9 load/store pairs, same `addiu 0xFFC` / `addu $a0` address form once the
struct form is used). This is the mirror of the #38 class: not a *missing* nop before a store, but a nop the
scheduler is entitled to fill and ours does.

### Retest pass: every parked draft re-measured, 1 conversion, 11 parks survive with the shape named

`work/retest.py` re-ran **every** draft under `work/near-miss/` (313 files, unique bodies only, merged units
excluded) against current `main` and `work/diffscan.py` printed the differing words for each. That is the
measured ordering the table below uses — not the history of previous verdicts. Cheapest first:

| body | before | retest shape (on top of the parked draft) | after | verdict |
|---|---|---|---|---|
| `func_80012274` | 8/11 | parameter declared **`s16`** and negated in place (not through an `s32` local) | **MATCH** | converted — the narrow parameter is what puts `addu $v1,$a0,$zero` in the `beqz` slot |
| `func_800382C0` | 1/12 | `t = a0 + t` instead of `t += a0`; single-expression `a0 + ((a0+4)>>7)` form | 1/12 (13/12) | park stands: gcc canonicalises the commutative `addu` to the *second* pseudo; the game has `$a0` first. Not reachable from source |
| `func_8001CD7C` | 2/10 | typed struct pointer, `u8 *` walker, base local, `s16`/`u16` index | 2/10 | park stands: base in `$a2` + scaled index in `$v1` come out swapped in every form — saved-pair class |
| `func_8002BCB0` | 2/17 | `u16` field (already narrow) feeding the branch | 2/17 | park stands: the `lhu` lands in `$v0`, the game uses `$a1` — role class |
| `func_8002C9B8` | 2/36 | — | 2/36 | park stands: `lhu`/`addiu` chain split into two registers (`$v0`→`$v1`), role class |
| `func_8002FE80` | 2/24 | address-of-local passed as an argument | 2/24 | park stands: `addiu $v0,$sp,0x10` where the game uses `$a1` |
| `func_80056C90` | 2/36 | `-mno-split-addresses` (lui-temp tell) | 31/36 | park stands: the flag is *wrong* here — it costs 29 words |
| `func_8003BF7C` | 2/79 | `-mno-split-addresses` | 78/79 | park stands, same: `lui` temp in `$v0` for `$a0` |
| `func_8003B8F8` | 4/46 | args inline, comma-declaration, `*(u32 *)` of an oversized extern | 4/46 | park stands: the two early global loads want `$a0`/`$a1` (callee argument registers) and stay in `$v0` |
| `func_8004BF94` | 2/52 | — | 2/52 | park stands: two-word schedule rotation (`addiu $s2` before `addiu $s0,$gp`) |
| `func_80036F24` | 4/13 | `u32`/`s32` call-result local, volatile flag globals, `s16` callee, `void` form | 4–5/13 | park stands: the callee result must be copied to `$v1` and stored after `lw $ra`; no spelling creates the copy |

**Tally: 1 conversion from 12 re-tested bodies (8%); 11 parks re-examined and retained, each now naming the
shape tried on top of the original.** The five shapes the pass asked for converted once — `s16` parameter —
and failed on the rest, and each failure is the same physical cause:
`$v0` is the temp register for a freshly loaded or computed value that the game keeps in an argument
(`$a0`/`$a1`) or callee-saved (`$v1`/`$a2`/`$t0`) register. That is allocation, and the retest extends the
role-class verdict (`work/lane-notes.md`) from one-value swaps to *loads into argument registers*.

Skipped on sight, classes already measured dead: `80055820` (1/34, `jal` slot), `80015D38` (3/20), the
64-bit trio, `80022308`/`800223AC` (filled load-delay nop), and `80034B98` (matches but is scan-blocked on a
protected-symbol name — it stays parked).

### Cheap-list pass: all seven workable 3-6 word bodies re-worked, 1 conversion, one halved

The retest left eight bodies at six words or fewer; one is scan-blocked (`80034B98`), so seven were worked,
cheapest first, with the recently-converting shapes (narrow type, base-symbol reuse, frame/stride first):

| body | before | shape tried | after | residue |
|---|---|---|---|---|
| `func_80042E9C` | 4/58 | `return func_80032C54(...)` in the `if` (callee declared `s32`) instead of a statement plus `return 0x27100000`; hoisted `s32 r = 0x27100000` local | **2/58** | only the field load: `lw $a1,0x8($t2)` vs `lw $v0` — the value is a branch condition, so there is no call argument to hang it on |
| `func_80015D38` | 3/20 | bottom-tested `do { … p -= 0x10; } while (lo < p); return 0;` (the shape that has converted the most often) | 7/20 (0x54 vs 0x50) | parked `for (;;)` draft stands: gcc duplicates the pre-loop decrement and reuses it as the back edge, so the decrement never lands in the `bnez` slot |
| `func_8002050C` | 4/25 | — | 4/25 | `addu $a3,$v0,$zero` (a copy of `-1`) and a commutative `addu` operand order; both are the canonicalisation class, and the `andi` is in the `jr` slot |
| `func_80036F24` | 4/13 | `D_8008B144[1]` array view; explicit `(u32)` cast of the call result; `volatile` flag globals | 4-5/13 | the callee result is still stored straight from `$v0`: no spelling creates the `$v1` copy the game has before `lw $ra` |
| `func_8003B8F8` | 4/46 | see the argument-axis table below | 4/46 | two globals loaded into `$v0` for `$a0`/`$a1` |
| `func_8003ED28` | 5/60 | — | 5/60 | `lui` temp in `$v0` for `$v1`, and the final `sw $zero` wants `lui $at` with the return constant materialised first — allocation, not address form |
| `func_8003BDB8` | 6/31 | `a` then `b` assignment order; declaration-initialisers | 6/31 | the game materialises *both* constants up front (`lui $v1,0x1` / `lui $v0,0xFFFF`) before the four stores; gcc sinks the second constant to its single use whatever the source order |
| `func_8001CD7C` | 2/10 | **typed table pointer plus a subscript on the index** — `E_8001CD7C *tab = (E_8001CD7C *) D_8008AE54; tab[i].f0 = b; tab[i].f4 = a;` | **MATCH** | converted: the subscript is what splits base into `$a2` and the scaled index into `$v1`; the `u8 *e = base + i * 8` walker, the struct-pointer arithmetic `(E *) base + i`, the base local and the `s16`/`u16` index all keep them swapped |

**Tally: 1 conversion (`func_8001CD7C`), 1 halved (`func_80042E9C`, 4 → 2 of 58), 5 parks retained with
the shape named.**
Six of the seven are allocation residue whose instruction stream is correct apart from one register name or
one constant's position; the seventh converted on an addressing form, not on allocation — which is the one
result worth carrying forward (see lane-notes: **subscript, not walker**, for a body that indexes a table).

### The argument-register axis: two forms, no movement

Where the game loads a value straight into `$a0`/`$a1` and our build puts it in `$v0`, the axis tested was to
consume the value in the expression that produces it, so gcc is forced to place it in the argument register:

| body | form A (inline argument) | form B (load feeds the first parameter directly) | before |
|---|---|---|---|
| `func_8003B8F8` | `func_8003682C(func_80036E1C(D_80089FE4[0], D_8008A050[0]))` → 4/46 | `func_80036E1C(*(u32 *) D_80089FE4, *(u32 *) D_8008A050)` → 4/46 | 4/46 |
| `func_80042E9C` | field read inline in the `if` → 2/58 | `s32 f = *(s32 *)(a0+8); if (f != 0)` → 2/58 | 4/58 |
| `func_8002BCB0` | n/a — the `lhu` value is a branch condition, never an argument | n/a | 2/17 |

Verdict: **the axis does not move the register.** In all three bodies the value is already consumed in the
same expression that produces it (or is not an argument at all), and gcc still allocates the destination
`$v0`. What the game has is `lui $a0` / `lw $a0` — the address temp *is* the argument register — which is
the `-mno-split-addresses` shape, and that flag is measured wrong for these bodies (`8003BF7C` 78/79,
`80056C90` 31/36). The class stays closed; do not spend another axis on it without a compiler-side lever.

### Fresh-ground pass: the member-base scan, one unit, four fresh parks

`work/memberbase.py` finds every body whose assembly loads a member base and then adds a scaled index into it —
319 bodies, of which all but three already have a draft under `work/near-miss/`. The unopened remainder was
one handwritten body (`func_80033E78`, dropped on sight) and `func_80019444`, so **the pointer-local rule's
fresh-ground hit rate is 0 of 1 candidates that actually needed it**: the rule has already been applied to
everything in the corpus where the pattern appears. The 41+ word queue was then continued per the pass.

| body | words | outcome | shape / residue |
|---|---|---|---|
| `func_80019444` | 24 | **MATCH** | free-list pop: `n = D_8008AD6C; if (!n) return 0; D_8008AD6C = *(u8 **)(n + 4); memset(n, 0, 0x10); *(u8 **)(n + 4) = D_8008AD70; D_8008AD70 = n; return n;` — the reload of the global for the second store is what keeps the node in `$s0` |
| `func_8002B060` | 32 | 9/32 | typed 0x24-byte table + subscript on the first draft gets the game's `sll/addu/sll` then `addu` with the base last; residue is the index register (`$a0` for `$v1`) and base-materialisation order |
| `func_800257A0` | 21 | 6/21 | walker (`e += 0x8C`) is right; gcc biases the walker to element+0x74 so every access becomes a negative offset. Both the `u8 *` and the struct-pointer spelling bias identically |
| `func_80014170` | 46 | 30/46 | third parameter must be **`s32`**: declaring the kind field `u8` inserts `andi $v0,$a2,0xFF`, the game tests `$a2` raw. The record base is a **≤8-byte symbol used as an array** (`extern u8 D_8008AD14[4]` keeps `addiu $a2,$gp,%gp_rel`); a big typed array switches it to `lui`/`addiu` |
| `func_80034698` | 48 | 28/48 | digit loop + zero pad + in-place reverse. Declaration order `char *p = dst; u32 value = v; u16 n = 0;` is what orders the prologue (`t0 = a0`, `v1 = a1`, `a1 = 0`); the pad loop is `n++; do { *p++ = '0'; } while (n++ < width);` (test-before-increment). Residue is which register holds the pad counter (`$a1` vs `$t1`) |

Fresh-ground yield this pass: **1 unit from 5 drafts (20%)**, in line with the 41+ band's ~25%.

### Family pass: cluster the corpus, instantiate one member, 4 units from 7 drafts

`work/cluster.py` clusters bodies by normalised disassembly shape — memory displacements masked to `<off>`,
`%hi`/`%lo`/`%gp_rel` symbols and branch targets to `<sym>`/`<tgt>`, registers renamed to `$Aa..$Zz` in order of
first appearance — and reports two views, since neither is sufficient on its own.

**Shape view (identical stream).** Of the 310 unopened clean bodies there are **309 distinct strict shapes and
exactly one exact-twin pair** (`func_8002D734`/`func_8002D81C`). Similarity clustering at ratio >= 0.90 gives 52
families over the whole 1081-body corpus, but only **6 of them touch unopened ground, holding 10 bodies** — and
the number is identical at 0.80, so these are genuine twins, not a threshold artifact. The unopened population
is large and diverse (median 102 instructions, p75 169); the small near-duplicates were all drafted in earlier
passes.

| shape family | members | outcome |
|---|---|---|
| `func_80017F58` (matched) + `func_80018038` | 2 | **`func_80018038` MATCH on instantiation** — byte-for-byte the merged template with the final field at `+0x16` instead of `+0x14` |
| `func_8002D734` / `func_8002D81C` | 2 | template recovered, **both park at 32/58**; the streams are identical but for the X/Z axis swap, and both build to the same residue: the game copies the `func_80035E40` return into `$a0` (`addu $a0,$v0,$zero`) and we keep it in `$v0`, rotating every later word. A twin diverging identically is the cleanest evidence yet that this is allocation, not body shape |
| `func_800262E8` / `func_80027538` | 2 | **not C**: both switch `$sp` into the scratchpad (`lui 0x1F8003FC` / `sw $sp,0x10($t0)` / `addiu $t0,-4` / `addu $sp,$t0`) — a PsyQ asm macro, not expressible in plain C. Same class as `func_8003B068`, the only other body in the binary with this idiom |
| `func_80026478` / `func_80026870` | 2 | excluded: both call `func_8003353C` and `func_800331FC`, the 64-bit fixed-point dead class |
| `func_80018298` / `func_8001876C` | 2 | **deferred** — the largest unopened family (0x4D4 / 0x4F8, 309 words each with only 6 calls). No dead-class dependency, so this is real work, but 309 words is beyond one pass's shape budget |
| `func_8002BA54` (matched) + `func_80045828` | 2 | **not C**: `lui $gp` / `lw $gp,-0x4C68($gp)` / `jr $ra` — a gp-reload stub, the only body in the corpus that writes `$gp`. Clustered with the matched 4-word getter only because the shape normalisation erases which register is loaded |

**Callee-set view.** Keying on the set of `jal` targets instead finds **543 families, and 56 unopened bodies whose
family already has a matched member** — the families in this codebase differ in length but share a helper set
(the table-manager bodies run from 0xE0 to 0x4D4 and all call `func_80015E8C`/`15F10`/`19518`/`1954C`). This is
where the units came from; the matched sibling supplies types, statement order and branch polarity.

| body | words | family template | outcome |
|---|---|---|---|
| `func_8001F468` | 32 | `func_8001F3AC` | **MATCH** — order is `f24 = a1[0]; f2C = a1[1]; f28 = 0;` then the call: with the zero store last, gcc puts the `a1[1]` load above it and the dependent store in the `jal` delay, which is what produces the game's load-delay `nop` at `+0x14` |
| `func_80022E4C` | 54 | `func_80024DBC` | **MATCH on the first draft** — `s32 v[3]` stack triple, the member base `*(s32 *)(a0 + 8)` re-read on every access, `func_800331FC(v, -a0[9])`, `func_80032FF4(v, a0[1] + 0x44)`, then `v[i] = base[0x11+i] - v[i]`, `func_800331FC(v, -0x9EB)`, `func_80032FF4(base + 0x44, v)` |
| `func_80026FBC` | 53 | `func_80014AE8` | **MATCH in two shapes** — identical idiom to the template but with `s < 7` and the arms written `if (s >= 7)`; writing the game's arm order is what flips our `beqz` back to the game's `bnez` |
| `func_80018038` | 56 | `func_80017F58` | **MATCH on instantiation** (see above) |
| `func_8001C2F0` | 49 | `func_8001C2B8` callers | 26/49 parked: `for` (not `if` + `do`) is what removes the duplicate `blez`; residue is the callee-saved assignment (`$s3`/`$s4` and `$s6`/`$s7` swapped) plus where the `$a0` argument copy lands |
| `func_80019670` | 55 | `func_80016D00` etc. | 48/55 parked: structure right, but `((s32 *) &D_8008AD64)[6 + i]` folds `+0x18` into the symbol (`%gp_rel(D_8008AD7C)`) where the game keeps the base and adds the offset; roles also swap (`$s2`/`$s3`) |
| `func_80020D74` | 39 | `func_80020C34` (6-member family, no matched member) | 22/39 parked: `v[3]` triple of out-parameters, `r = (a0 << 16) | (a1 << 8)`, walk `+0x30`; gcc sinks the `or` into the `beqz` delay slot where the game emits it before the load, and the extra load-delay `nop` is the one missing word |

Family yield: **4 matched of 7 drafted (57%)**, against 1 of 5 (20%) body-at-a-time on the same queue last pass.
The lever is real where a family exists, but the shape view proves the population is almost exhausted: 10 of 310
unopened bodies sit in a near-duplicate family. The callee-set view is what makes the method general, and it
still leaves 49 unopened bodies with a matched template undealt with — that is the queue for the next pass.

### Family-queue pass: nine families, one unopened member each — 0 of 6 drafted

`work/family_queue.py` now reports **9 families with at least one matched template and exactly one unopened
member**, so the premise that made the family key pay last pass — pay the template cost once across several
siblings — has no remaining instances. Six of the nine were attempted; none matched.

| body | words | best | residue |
|---|---|---|---|
| `func_80017140` | 153 | 113 | 23-case switch (case order read from `jtbl_80010188`). gcc merges the three identical `f4`-compare case bodies (compare 1/2/3, then `s32` load, jump to the shared return) into one copy and jumps to it; the game keeps three copies. 10 words short; no shape tried separated them |
| `func_80026EC8` | 61 | 0xf0 vs 0xf4 | 3-deep `i << j` index nest with three descending base walkers. Structure and count right; the last word is which copy of the allocation size gcc keeps |
| `func_80020398` | 87 | **3/87** | Stream identical, size identical. The alloc-size value is homed in `$s2` with a move to `$a0`; the game computes it in `$a0` and copies into `$s2` in the `jal` delay. `-fno-schedule-insns2` 12/87, `-fno-schedule-insns` 53/87 |
| `func_8002DAE8` | 98 | 0x13c vs 0x188 | cross product + `func_800330A4` normalise. 19 words short, and every one of them is the pair of `nop`s the game leaves after each of its seven `mult`s |
| `func_80025544` | 106 | 113/124 (+18) | eighteen index stores. **One extra load-delay `nop` per statement**: the game hoists the next `%gp_rel` load above the previous store, we emit the nop. `-O1` worse (0x204), `-O2`/`-O3` unchanged |
| `func_80052380` | 102 | **38/102**, size exact | gcc folds the walked voice pointer to `base + 0x48` (offsets 4/8/0) and homes `&D_8008A998` in `$fp`; the game keeps `s0 = e` beside `s2 = e` and re-materialises the global address each time |

Not drafted: `func_80047C94` (0x25C), `func_80018D18` (0x2A4), `func_80051FD4` (0x2D0), `func_8004B4A8` (0x314)
— all beyond what the remaining working time covered.

**Family-key yield: 0 of 6 drafted.** Combined with the fact that no multi-member family is left, the method is
retired: its four earlier units came from clusters with 2-4 unopened members, and a one-member family costs the
full template read for a single body.

Template sibling used for each of the nine families (`work/family_queue.py`), member → templates:

| member | template(s) |
|---|---|
| `func_8004B4A8` | `func_8004B448` |
| `func_80026EC8` | `func_80014C60`, `func_80014DA8` (the `func_80032C28` dot-product pair) |
| `func_80020398` | `func_8001C410`, `func_80022118`, `func_8002DC70`, `func_8003AB50`, `func_8003ECE0` |
| `func_8002DAE8` | `func_8004A270` |
| `func_80052380` | `func_8004D758`, `func_8004DD38`, `func_8004DE4C` |
| `func_80025544` | `func_80024D6C`, `func_800256F4`, `func_8002572C`, `func_800257F4`, `func_8002582C` (+4) |
| `func_80047C94` | `func_8003C1A4`, `func_800411E0` |
| `func_80018D18` | `func_80017F58`, `func_80018038`, `func_80018C64` |
| `func_80051FD4` | `func_8005109C` |

The template read paid in only two of the six attempts: `func_80052380` reused the `func_8004D758` group's
mask/voice idiom (and reached an exact-size 38/102), and `func_80026EC8` reused the dot-product template down to
one word. The other four needed no template at all — they are straight-line or nest bodies whose residue is
scheduling or toolchain, so the sibling told us nothing the assembly did not.

### The argument-register birth: `* 16` instead of `<< 4` — `func_80020398` MATCHES

The 3-of-87 park converted on one spelling change. The residue was a value that had to be **born in `$a0` and
copied out to `$s2`**; gcc homed it in `$s2` and moved it into `$a0` for the call, in that order. Fourteen shapes
and eight flags kept that order (see the ranked table below). What flipped it was writing the scale as a
**multiplication** rather than a shift:

```c
    size = *(u32 *) dst * 16;      /* was: *(u32 *) dst << 4 */
    b = func_80034C20(size);
```

The multiply creates the argument pseudo at the call, so gcc computes it in `$a0` and only then copies it to
`$s2` in the `jal` delay slot — exactly the game's two words. Nothing else in the body moved.

Ranked shapes tried on this decision (all with the rest of the draft fixed):

| shape | result |
|---|---|
| `size = *(u32 *) dst * 16; b = f(size);` | **MATCH** |
| `size = *(u32 *) dst << 4; b = f(size);` | 3/87 (`$s2` home + `addu $a0, $s2`) |
| `b = f(size = *(u32 *) dst << 4);` | 3/87 |
| `size = *(u32 *) dst << 4; b = f(*(u32 *) dst << 4);` | 3/87 |
| `s32 size` with and without a cast at the call, `u32` prototype | 3/87 each |
| `-O2`/`-O3`/`-fno-strength-reduce`/`-fno-inline`/`-funsigned-char` | 3/87 each |
| `-fno-schedule-insns2` / `-mno-split-addresses` / `-fno-schedule-insns` / `-O1` | 12 / 13 / 53 / 69 |
| expression used at both sites, no variable (value recomputed at `memset`) | 79 (0x154) |
| local count `n`, shift at both sites | 82 (0x154) |
| `size = *(u32 *) dst; size <<= 4;` | 26 |
| size read from `src` before the copy | 30 |

**The rule, and its limits.** When a value must land in an argument register and survive the call, writing the
scale as a constant multiply instead of a shift changes which pseudo the allocator sees first, and that is the
whole difference. Tested on the two siblings the pass named: `func_80026EC8` re-spelled `(i << j)` as
`i * (1 << j)` and stayed at 0xf0 (one word short) — a variable shift does not take this route; and
`func_80052380`'s residue is the pointer fold plus the `&D_8008A998` home, not argument birth, and its
two-live-pointer form went 38 → 68. So the form needs a **constant** scale and a value that is a call argument
first and a cross-call temporary second.

## Return-signature scan vs size ordering: the scan lost

The pass scanned the unopened set for the two tells that converted at the end of the last batch — a closing
`addu $v0,$zero,$zero` (explicit `return 0` on the fall-through) and one epilogue reached from several returns
— and drafted five bodies picked by that signature rather than by size. All five parked:

| body | scan hit | first draft | residue |
|---|---|---|---|
| `func_80032644` | shared tail return, 0x400 head test | 62/64 (0x108 vs 0x104) | 4 words over; the two `return` arms share an epilogue but our tail merges earlier |
| `func_8002EE94` | several `beqz` to one exit | 68/84 | loop guard order; the shared exit is reproduced, the loop body is not |
| `func_80018FBC` | trailing `addu $v0,$zero,$zero` | 71/73 | two words short at the tail |
| `func_80020C34` | 4-arm span-table dispatch, one exit | 76/80 (0x134 vs 0x140) | 3 words short: the `10800v` scale folds differently |
| `func_8001D1E8` | one `j` exit per arm | 69/71 (0x130 vs 0x11C) | 5 words over: the `$gp` address is materialised per arm instead of reused |

Verdict: **0 of 5** from the scan, against 3 of 24 from size ordering last pass. The two tells are real but they
are *already* what `enumerate.py` bodies usually have — the shared-tail shape is the norm, not a discriminator —
so the scan does not rank the queue better than size does. Do not rebuild the queue around it; keep the tells
as pre-draft checklist items only.

## The four close parks: three re-measured, one matched on a new tell

| body | before | this pass | what was tried |
|---|---|---|---|
| `func_80013EEC` | 2/57 | **MATCH** | the residue was *only* `addu $v0,$s0,$v0` vs ours `addu $v0,$v0,$s0` on the two `self + idx*16` stores. Pointer forms keep our operand order (`u8 *e = s + idx*16` 15/57, `s32 idx` local 16/57); spelling the address as integer addition with the base first — `(u32) s + ((u32) idx << 4) + 0x184` — restores `addu $s0,$v0`. |
| `func_8002FEE0` | 57/63 | 57/63 | no movement; the body is allocation-shaped, not tail-shaped |
| `func_8002C8B8` | 44/64 | 44/64 | no movement |
| `func_80032B1C` | 62/64 | 62/64 (0x104 vs 0x100) | no movement; one word over |

**New tell: `addu` operand order is a source-order decision.** When a diff is one or two `addu` words whose
operands are swapped and the game adds the base first, write the address as integer arithmetic
(`(u32) base + scaled + offset`) rather than pointer arithmetic. This is the cheapest close in the corpus:
it is a two-line edit and it converted a body parked since the -O1 sweep.
