#include "common.h"

s32 func_80047B28(u8 *a0, u8 *a1, u8 *a2) {
    u8 buf[0x80];
    s32 n;
    s32 i;
    u8 *p;

    memcpy(buf, a0, 0x80);
    a0 += 0x80;

    *(s32 *) (a1 + 8) = *(u16 *) (buf + 8) - *(u16 *) (buf + 4) + 1;
    *(s32 *) (a1 + 0xC) = *(u16 *) (buf + 0xA) - *(u16 *) (buf + 6) + 1;

    p = (u8 *) func_80034C20(*(s32 *) (a1 + 8) * *(s32 *) (a1 + 0xC));
    *(u8 **) (a1 + 0x14) = p;
    if (p == 0) {
        return 0;
    }

    n = *(s32 *) (a1 + 0xC);
    for (i = 0; i < n; i++) {
        func_80047A44(&a0, a1, i);
    }

    if (a2 != 0) {
        func_80047ACC(&a0, a2);
    }
    return 0;
}
