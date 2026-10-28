#include "common.h"

void func_80033818(s32 *a0) {
    s32 f4 = a0[1];
    s32 fC = a0[3];
    s32 f8 = a0[2];
    s32 f18 = a0[6];
    s32 f14 = a0[5];
    s32 f1C = a0[7];

    a0[3] = f4;
    a0[1] = fC;
    a0[6] = f8;
    a0[2] = f18;
    a0[7] = f14;
    a0[5] = f1C;
}
