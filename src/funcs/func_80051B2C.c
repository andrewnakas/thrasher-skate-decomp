#include "common.h"

void func_80051B2C(u32 a0, u8 *a1, s32 a2) {
    if (a2 == 0) {
        *(u16 *) a1 |= 0x2000;
        *(u32 *) (a1 + 0x1C) = 0;
        if (a1[2] == 2) {
            a1[2] = 3;
            *(u16 *) (a1 + 0x2A) = 1;
            return;
        }
        if (a1[2] == 1) {
            a1[2] = 0;
            return;
        }
    } else {
        a1[2] = 0;
    }
}
