#include "common.h"

void func_80032FF4(s32 *a, s32 *b) {
    s32 a0;
    s32 b0;
    s32 a1;
    s32 b1;
    s32 a2;
    s32 b2;

    a0 = a[0];
    b0 = b[0];
    a1 = a[1];
    b1 = b[1];
    a2 = a[2];
    b2 = b[2];
    a[0] = a0 + b0;
    a[1] = a1 + b1;
    a[2] = a2 + b2;
}
