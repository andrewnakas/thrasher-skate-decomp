#include "common.h"

extern s32 D_8008A360;
extern s32 D_8008A364;
extern u8 D_8008A368;
extern u8 D_8008A36A;
extern u8 D_8008A36D;
extern u16 D_8008A37A;
extern u16 D_8008A37C;
extern s32 D_8008A380;
extern s32 D_8008A384;
extern s8 D_8008A388;
extern u8 D_8008A389;
extern u8 D_8008A38C[];
extern u8 D_8008A390[];
extern u8 D_8008A3A8;
extern s32 D_8008A3AC;
extern u8 D_8008B0B8;

extern s32 func_80052F84(s32 *);
extern s32 func_8004FECC(s32, s32);
extern s32 func_80052C10(s32, s32, s32);
extern s32 func_80053408(s32, s32);
extern void func_80053014(void);
extern s32 func_80051574(s32, s32 *);
extern s32 func_8004FC00(s32);
extern s32 func_800511C0(s32, s32, s32);
extern s32 func_80051844(s32, s32, s32);
extern s32 func_800515FC(s32);
extern s32 func_8004C65C(s32);
extern s32 func_8004FF90(s32, s32);
extern s32 func_8004C3A4(s32, s32);
extern s32 func_8004D23C(void);
extern s32 func_8004BF94(void);
extern s32 func_80052874(void);
extern s32 func_80050664(void);
extern s32 func_8004DE44(void);

void func_8003062C(void) {
    s32 scratch;
    s32 state;
    s32 value;
    s32 out;
    s32 pick;
    s32 sel;
    s32 cand;
    s32 vol;

    if (D_8008A384 != 0) {
        D_8008A384--;
    }

    state = D_8008A360;
    if (state == -1) {
        return;
    }

    switch (state) {
    case 0:
    case 3:
    case 4:
        break;
    case 1:
        func_80052F84(&scratch);
        if (scratch != 1) {
            break;
        }
        if (D_8008A384 == 0) {
            D_8008A384 = 0x3C;
            break;
        }
        D_8008A384--;
        if (D_8008A384 != 0) {
            break;
        }
        value = D_8008A389;
        D_8008A389 = value + 1;
        out = D_8008A38C[value & 0xFF];
        vol = D_8008A389;
        D_8008B0B8 = out;
        D_8008A389 = vol & 3;
        value = func_8004FECC(D_8008A37A, (s8) out);
        func_80052C10(value, 0, 0);
        func_80053408(((u32) (D_8008A36D * 25) >> 5) & 0xFF, 0);
        func_80053014();
        D_8008A384 = 0x96;
        break;
    case 2:
        value = D_8008A364;
        if (value < 3) {
            if (value > 0) {
                goto play;
            }
            if (value == 0) {
                goto spin;
            }
            break;
        }
        if (value != 4) {
            break;
        }
        goto start79;

    spin:
        if (D_8008A36A != 8) {
            goto play;
        }
        D_8008A3AC++;
        if ((u32) D_8008A3AC < 0x385) {
            break;
        }
        if (D_8008A368 == 6 || D_8008A368 < 7 || D_8008A368 == 9) {
            pick = -1;
        } else if (D_8008A368 == 0xB) {
            pick = 0x2B;
        } else {
            pick = -1;
        }
        if (pick == -1) {
            goto zero;
        }
        goto submit;

    play:
        func_80051574(D_8008A380, &scratch);
        if (scratch != 1 && D_8008A388 == -1) {
            break;
        }
        if (D_8008A384 != 0) {
            break;
        }
        sel = D_8008A388;
        if (sel == -1) {
            value = D_8008A364;
            if (value >= 2) {
                value = 1;
            }
            cand = D_8008A390[D_8008A368 * 2 + value];
            if ((u32) cand < (u32) func_8004FC00(D_8008A37A)) {
                D_8008A388 = cand;
            } else {
                D_8008B0B8 = sel;
            }
            if (D_8008A388 == -1) {
                break;
            }
            sel = D_8008A388;
        }
        value = func_8004FECC(D_8008A37A, sel);
        func_800511C0(D_8008A380, value, 0x140);
        func_80051844(D_8008A380, ((u32) (D_8008A36D * 25) >> 5) & 0xFF, 0);
        func_800515FC(D_8008A380);
        out = *(u8 *) &D_8008A388;
        D_8008A388 = -1;
        D_8008A384 = 0x3C;
        D_8008B0B8 = out;
        break;
    start79:
        if (func_8004C65C(D_8008A3A8) != 1) {
            break;
        }
        value = D_8008A3AC + 1;
        D_8008A3AC = value;
        if ((u32) value < 0x79) {
            break;
        }
        pick = D_8008A36A + 8;
    submit:
        out = func_8004FF90(D_8008A37C, pick);
        if (func_8004C3A4(D_8008A3A8, out) != 0) {
            break;
        }
    zero:
        D_8008A3AC = 0;
        break;

    }

    func_8004D23C();
    func_8004BF94();
    func_80052874();
    func_80050664();
    func_8004DE44();
}
