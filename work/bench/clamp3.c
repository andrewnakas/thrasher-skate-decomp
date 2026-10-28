#include "common.h"

#define CLAMP(x, lo, hi) ((x) >= (hi) ? ((x) > (hi) ? (hi) : (x)) : ((x) <= (lo) ? (lo) : (x)))

s32 m1(s32 a) {
    a = CLAMP(a, 0, 0x200);
    return a;
}

s32 m2(s32 a) {
    if ((u32) a >= 0x200) {
        if ((u32) a > 0x200) {
            a = 0x200;
        }
    } else if (a <= 0) {
        a = 0;
    }
    return a;
}

u32 m3(u32 a) {
    a = CLAMP(a, 0, 0x200);
    return a;
}

s32 m4(s32 a) {
    a = (a >= 0x200) ? ((a > 0x200) ? 0x200 : a) : ((a <= 0) ? 0 : a);
    return a;
}
