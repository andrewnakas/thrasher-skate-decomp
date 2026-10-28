#include "common.h"

s32 t1(s32 a) {
    return ((u32) a < 0x200) ? ((a > 0) ? a : 0) : (((u32) a <= 0x200) ? a : 0x200);
}

s32 t2(s32 a) {
    if ((u32) a < 0x200) {
        if (a <= 0) {
            a = 0;
        }
    } else if ((u32) a <= 0x200) {
        /* keep */
    } else {
        a = 0x200;
    }
    return a;
}

s32 t3(s32 a) {
    s32 r;
    r = a;
    if ((u32) r < 0x200) {
        r = (r > 0) ? r : 0;
    } else {
        r = ((u32) r <= 0x200) ? r : 0x200;
    }
    return r;
}

s32 t4(u32 a) {
    if (a < 0x200) {
        if ((s32) a <= 0) {
            a = 0;
        }
    } else {
        a = (a <= 0x200) ? a : 0x200;
    }
    return a;
}
