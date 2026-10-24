#include "common.h"

extern s32 D_8008A9C8;
extern s8 D_800108B0[];
extern s8 D_8008A9D4[];

s32 func_800517C8(u8 *a0, s32 a1) {
    if (D_8008A9C8 == 0) {
        printf(D_800108B0, D_8008A9D4, 0x422);
        exit(1);
    }
    if (a1) {
        a0[3] = a0[3] + 1;
    } else {
        a0[3] = a0[3] - 1;
    }
    if (((s8 *) a0)[3]) {
        a0[2] = 7;
    } else {
        a0[2] = 4;
    }
    return 0;
}
