#include "common.h"

extern s32 D_8008A9C8;
extern s8 D_800108B0[];
extern s8 D_8008A9D4[];

s32 func_80051158(u8 *a0, s32 a1) {
    u32 v;

    if (D_8008A9C8 == 0) {
        printf(D_800108B0, D_8008A9D4, 0x2D9);
        exit(1);
    }
    v = *(s32 *) (a0 + 0xC) * a1;
    *(u32 *) (a0 + 0x10) = v / 100;
    return 0;
}
