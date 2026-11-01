#include "common.h"

extern u32 D_800AEA24[];
extern s8 D_8008A93C[];
extern u8 D_80010670[];
extern s32 D_8008A938;

s32 func_8004B088(s32 a0) {
    u32 idx;
    u8 *e;
    u8 *child;

    D_8008A938++;
    idx = a0 & 0xFF;
    if (idx >= 0x20) {
        printf(D_80010670, D_8008A93C, 0x15E);
        exit(1);
    }

    e = (u8 *) D_800AEA24[idx];
    if (e == 0) {
        printf(D_80010670, D_8008A93C, 0x160);
        exit(1);
    }

    if (e[2] != 2) {
        child = *(u8 **) (e + 0x38);
        while (child != 0) {
            func_8004BD20(child);
            child = *(u8 **) (child + 0x10);
        }
        *(u32 *) (e + 0x28) = *(u32 *) (e + 0x24);
        *(u32 *) (e + 0x38) = 0;
        *(u32 *) (e + 0x2C) = func_8004B448(e) << 12;
    } else {
        child = *(u8 **) (e + 0x38);
        while (child != 0) {
            if ((child[0] & 2) == 0) {
                func_8004E460(child[8]);
            }
            child = *(u8 **) (child + 0x10);
        }
    }

    e[2] = 1;
    D_8008A938--;
    return 0;
}
