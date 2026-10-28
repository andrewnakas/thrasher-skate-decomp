#include "common.h"

s32 m5(s32 a) {
    if ((u32) a < 0x200) {
        if (a <= 0) {
            a = 0;
        }
    }
    if ((u32) a > 0x200) {
        a = 0x200;
    }
    return a;
}

s32 m6(s32 a) {
    if ((u32) a >= 0x200) {
        if ((u32) a > 0x200) {
            a = 0x200;
        }
    } else if (a <= 0) {
        a = 0;
    }
    return a;
}

s32 m7(u16 a) {
    if (a < 0x200) {
        if ((s32) a <= 0) {
            a = 0;
        }
    }
    if (a > 0x200) {
        a = 0x200;
    }
    return a;
}
