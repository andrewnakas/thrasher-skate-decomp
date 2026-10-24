#include "common.h"

extern u8 D_8008ABF0;
extern s32 D_8008AC24;

void func_8005726C(u8, u32);
void func_800384FC(void (*)(u8, u32));

s32 func_800572AC(void) {
    s32 v;

    v = D_8008ABF0;
    if (v != 0) {
        D_8008ABF0 = 0;
        D_8008AC24 = 0x1E;
        return v;
    }
    v = D_8008AC24;
    if (v > 0) {
        v = v - 1;
    } else {
        func_800384FC(func_8005726C);
        v = 0x1E;
    }
    D_8008AC24 = v;
    return 0;
}
