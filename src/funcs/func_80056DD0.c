#include "common.h"

extern u8 D_8008ABF4[];
extern u8 D_800B2508[];
void func_800382F0(u8 *, u8 *);
s32 func_800380BC(u8 *, u8 *, s32);
s32 func_800383E8(void);

s32 func_80056DD0(void) {
    u8 buf[0xC8];
    s32 r;

    func_800382F0(D_8008ABF4, buf);
    r = func_800380BC(buf, D_800B2508, 0x774);
    if (r == 0) {
        return 0;
    }
    switch (func_800383E8()) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 4:
        return 3;
    case 5:
        return 4;
    case 6:
        return 5;
    case 7:
        return 6;
    case 8:
        return 7;
    default:
        return 7;
    }
}
