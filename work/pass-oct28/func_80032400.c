#include "common.h"

extern s32 func_8004DA90(u8 *, u8 *, u8 *);

s32 func_80032400(u8 *a0, u32 a1, u8 *a2, u8 *a3) {
    s32 r;

    if (a0 != 0) {
        r = func_8004DA90(a0, a2, a3);
        a2[0] = ((u32) a2[0] * (a1 & 0xFF)) >> 7;
    } else {
        r = 1;
        a2[0] = a1;
        a3[0] = 0;
    }
    return r;
}
