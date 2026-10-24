#include "common.h"

extern void func_8004995C();

s32 func_800498FC(u8 a0, u16 a1, u16 a2, u16 a3, u16 a4) {
    u16 x = (a3 + 7) & ~7;
    u16 y = (a4 + 7) & ~7;

    x >>= 3;
    y >>= 3;

    func_8004995C(a0, a1 >> 3, a2 >> 3, x, y, 0);
    return 0;
}
