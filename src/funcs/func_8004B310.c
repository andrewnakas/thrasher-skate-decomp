#include "common.h"

extern u32 D_800AEA24[];
extern s8 D_8008A93C[];
extern u8 D_80010670[];

s32 func_8004B310(s32 a0, u8 a1, u8 a2) {
    u32 idx;
    u8 *e;
    u8 *child;

    idx = a0 & 0xFF;
    if (idx >= 0x20) {
        printf(D_80010670, D_8008A93C, 0x296);
        exit(1);
    }

    e = (u8 *) D_800AEA24[idx];
    if (e == 0) {
        printf(D_80010670, D_8008A93C, 0x298);
        exit(1);
    }

    child = *(u8 **) (e + 0x38);
    e[4] = a1;
    e[6] = a2;

    while (child != 0) {
        if ((child[0] & 2) == 0) {
            func_8004E6CC(child[8], (((u32) (child[1] * e[4]) >> 7) & 0xFF) * e[5] >> 7 & 0xFF);
            func_8004E7EC(child[8], (s8) e[6]);
        }
        child = *(u8 **) (child + 0x10);
    }

    return 0;
}
