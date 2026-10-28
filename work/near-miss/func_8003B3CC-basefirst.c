#include "common.h"

extern u8 D_8008234C[];
extern u32 D_8008A710;
extern u32 D_8008B3A8[];

void func_8003B3CC(void) {
    u8 *base;
    u32 v;

    if (D_8008A710 != 0) {
        return;
    }
    base = D_8008234C;
    v = *(u32 *) (base + 0xE0);
    D_8008A710 = 1;
    v ^= 1;
    *(u32 *) (base + 0xE0) = v;
    *(u32 *) (base + 0xE4) = (u32) (base + v * 0x70);
    D_8008B3A8[0] = v;
}
