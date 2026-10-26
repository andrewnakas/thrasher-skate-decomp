#include "common.h"
s32 f1(u8 *p, u32 len) {
loop:
    if (*(u32 *)(p + 8) < len) {
        p = *(u8 **)(p + 4);
        if (p == 0) return 0;
        goto loop;
    }
    return 1;
}
s32 f2(u8 *p, u32 len) {
    while (*(u32 *)(p + 8) < len) {
        p = *(u8 **)(p + 4);
        if (p == 0) return 0;
        continue;
    }
    return 1;
}
s32 f3(u8 *p, u32 len) {
    s32 r = 1;
    while (*(u32 *)(p + 8) < len) {
        p = *(u8 **)(p + 4);
        if (p == 0) { r = 0; break; }
    }
    return r;
}
