#include "common.h"

extern u32 D_8008A360;
extern s32 D_8008A364;
extern u8 D_8008A368;
extern u8 D_8008A36A;
extern u8 D_8008A36D;
extern u16 D_8008A37A;
extern u16 D_8008A37C;
extern s32 D_8008A380;
extern s32 D_8008A384;
extern s8 D_8008A388;
extern volatile u8 D_8008A389;
extern u8 D_8008A38C[4];
extern u8 D_8008A390[8];
extern u8 D_8008A3A8;
extern u32 D_8008A3AC;
extern s8 D_8008B0B8;

extern void func_8004BF94(void);
extern s32 func_8004C3A4(u8, s32);
extern s32 func_8004C65C(u8);
extern void func_8004D23C(void);
extern void func_8004DE44(void);
extern u32 func_8004FC00(u16);
extern s32 func_8004FECC(u16, s32);
extern s32 func_8004FF90(u16, s32);
extern void func_80050664(void);
extern void func_800511C0(s32, s32, s32);
extern void func_80051574(s32, s32 *);
extern void func_800515FC(s32);
extern void func_80051844(s32, s32, s32);
extern void func_80052874(void);
extern void func_80052C10(s32, s32, s32);
extern void func_80052F84(s32 *);
extern void func_80053014(void);
extern void func_80053408(s32, s32);

void func_8003062C(void) {
    s32 st;
    s32 sel;
    s32 snd;
    s32 cur;
    s32 k;
    s32 next;
    s8 last;

    if (D_8008A384 != 0) {
        D_8008A384--;
    }
    if (D_8008A360 == -1) {
        return;
    }
    switch (D_8008A360) {
    case 0:
    case 3:
    case 4:
        break;
    case 1:
        func_80052F84(&st);
        if (st != 1) {
            break;
        }
        if (D_8008A384 == 0) {
            D_8008A384 = 60;
            break;
        }
        if (--D_8008A384 != 0) {
            break;
        }
        D_8008B0B8 = D_8008A38C[D_8008A389++];
        D_8008A389 &= 3;
        func_80052C10(func_8004FECC(D_8008A37A, D_8008B0B8), 0, 0);
        func_80053408((u8)((u32)(D_8008A36D * 25) >> 5), 0);
        func_80053014();
        D_8008A384 = 150;
        break;
    case 2:
        switch (D_8008A364) {
        case 0:
            if (D_8008A36A == 8) {
                if (++D_8008A3AC < 0x385) {
                    break;
                }
                /* a case below 6 (value unrecoverable, any of 0..5 matches) sets the tree root to 6 */
                switch (D_8008A368) {
                case 0:
                    sel = -1;
                    break;
                case 6:
                    sel = -1;
                    break;
                case 9:
                    sel = -1;
                    break;
                case 11:
                    sel = 0x2B;
                    break;
                default:
                    sel = -1;
                    break;
                }
                if (sel == -1 || func_8004C3A4(D_8008A3A8, func_8004FF90(D_8008A37C, sel)) == 0) {
                    D_8008A3AC = 0;
                }
                break;
            }
        case 1:
        case 2:
            func_80051574(D_8008A380, &st);
            if (st != 1 && D_8008A388 == -1) {
                break;
            }
            if (D_8008A384 != 0) {
                break;
            }
            cur = D_8008A388;
            if (cur == -1) {
                k = D_8008A364;
                if (k >= 2) {
                    k = 1;
                }
                next = D_8008A390[k + D_8008A368 * 2];
                if (next < func_8004FC00(D_8008A37A)) {
                    D_8008A388 = next;
                } else {
                    D_8008B0B8 = cur;
                }
                if (D_8008A388 == -1) {
                    break;
                }
            }
            snd = func_8004FECC(D_8008A37A, D_8008A388);
            func_800511C0(D_8008A380, snd, 0x140);
            func_80051844(D_8008A380, (u8)((u32)(D_8008A36D * 25) >> 5), 0);
            func_800515FC(D_8008A380);
            last = D_8008A388;
            D_8008A388 = -1;
            D_8008A384 = 60;
            D_8008B0B8 = last;
            break;
        case 4:
            if (func_8004C65C(D_8008A3A8) != 1) {
                break;
            }
            if (++D_8008A3AC < 0x79) {
                break;
            }
            if (func_8004C3A4(D_8008A3A8, func_8004FF90(D_8008A37C, D_8008A36A + 8)) == 0) {
                D_8008A3AC = 0;
            }
            break;
        }
        break;
    }
    func_8004D23C();
    func_8004BF94();
    func_80052874();
    func_80050664();
    func_8004DE44();
}
