#include "common.h"

extern u8 D_800A1C50[];

void func_8002DA40(void) {
    s16 *p = (s16 *) D_800A1C50;
    s32 f4 = p[2];
    s32 fa = p[5];
    s32 f6 = p[3];
    s32 fc = p[6];
    s32 f8 = p[4];
    s32 fe = p[7];
    s32 m;
    s32 d;

    m = (f4 + fa) >> 1;
    d = f4 - m;
    p[0x18] = m;
    if (d < 0) {
        d = -d;
    }
    p[0x1B] = d;

    m = (f6 + fc) >> 1;
    d = f6 - m;
    p[0x19] = m;
    if (d < 0) {
        d = -d;
    }
    p[0x1C] = d;

    m = (f8 + fe) >> 1;
    d = f8 - m;
    if (d < 0) {
        d = -d;
    }
    p[0x1A] = m;
    p[0x1D] = d;
}
