#include "common.h"

void func_80032FF4(s32 *a0, s32 *a1) {
    s32 ax = a0[0];
    s32 ay = a0[1];
    s32 az = a0[2];
    s32 bx = a1[0];
    s32 by = a1[1];
    s32 bz = a1[2];

    a0[0] = ax + bx;
    a0[1] = ay + by;
    a0[2] = az + bz;
}
