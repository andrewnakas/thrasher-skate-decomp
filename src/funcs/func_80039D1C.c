#include "common.h"

extern s32 D_8008B19C;
extern u8 D_800A8404[];

s32 func_8003A09C(s32, s32, s32, s32 *);
void func_8003AE98(u8 *, u8 *, s32);

void func_80039D1C(u8 *a0) {
    u32 n;
    s32 v;
    s32 buf[2];

    n = *(u16 *) (a0 + 2);
    D_8008B19C = 0;
    if (n >= 0x101) {
        *(u16 *) (a0 + 2) = 0x100;
    }
    v = func_8003A09C(0x100, 0, 0, buf);
    if ((v & 0xFF) != 0) {
        *a0 = v;
        func_8003AE98(D_800A8404 + (v & 0xFF) * 8, a0 + 4, 0);
    }
}
