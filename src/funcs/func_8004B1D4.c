#include "common.h"

extern s32 D_8008A938;
extern u8 *D_800AEA24[];
extern u8 D_80010670[];
extern u8 D_8008A93C[];

void printf(u8 *, u8 *, s32);
void exit(s32);
s32 func_8004B41C(u8 *);
void func_8004E528(u8, s32);

/* Releases node slot arg0 (0..0x1F): sweeps the list hanging off +0x38 calling
   func_8004E528 on each entry that is not flagged with bit 1, then marks the
   slot released. The gp counter is the nesting guard around the whole unit. */
s32 func_8004B1D4(s32 arg0) {
    u8 *p;
    u8 *v;

    D_8008A938 = D_8008A938 + 1;
    if ((u32) (arg0 & 0xFF) >= 0x20) {
        printf(D_80010670, D_8008A93C, 0x1AB);
        exit(1);
    }
    v = D_800AEA24[arg0 & 0xFF];
    if (v == 0) {
        printf(D_80010670, D_8008A93C, 0x1AD);
        exit(1);
    }
    if (func_8004B41C(v) != 0) {
        switch (*(u16 *) v & 3) {
        case 0:
            p = *(u8 **) (v + 0x38);
            if (p != 0) {
                do {
                    if ((*(u8 *) p & 2) == 0) {
                        func_8004E528(*(u8 *) (p + 8), 0);
                    }
                    p = *(u8 **) (p + 0x10);
                } while (p != 0);
            }
            break;
        case 1:
            break;
        default:
            *(u16 *) v |= 0x4000;
            break;
        }
    }
    *(u8 *) (v + 2) = 2;
    D_8008A938 = D_8008A938 - 1;
    return 0;
}
