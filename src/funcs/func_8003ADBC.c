#include "common.h"

extern void func_8003AD7C();

void func_8003ADBC(u8 a0, u8 a1, u8 a2, s32 a3) {
    s16 v[4];

    v[2] = 0x400;
    v[3] = 0x200;
    v[0] = 0;
    v[1] = 0;

    func_8003AD7C(v, a0, a1, a2, a3);
}
