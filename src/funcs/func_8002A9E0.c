#include "common.h"

extern s32 func_800309C4(s32, s32 *, s32, s32, s32);

void func_8002A9E0(u8 *arg0) {
    s32 n;
    u8 *base;
    s32 c[3];

    n = *(u16 *) (arg0 + 0x22);
    if (n == 0) {
        return;
    }
    n--;
    base = *(u8 **) (arg0 + 0x14);
    if (n == -1) {
        return;
    }
    do {
        c[0] = *(s16 *) (base + 4) << 16;
        c[1] = *(s16 *) (base + 6) << 16;
        c[2] = *(s16 *) (base + 8) << 16;
        if (*(u16 *) base & 1) {
            func_800309C4(0xFA1, c, *(u16 *) (base + 2), 0, 0);
        } else {
            func_800309C4(0xFA1, c, *(u16 *) (base + 2), 0x7F, 0);
        }
        base += 0x10;
    } while (--n != -1);
}
