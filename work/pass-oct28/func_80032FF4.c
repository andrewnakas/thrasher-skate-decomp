#include "common.h"

void func_80032FF4(u32 *a0, u32 *a1) {
    u32 a;
    u32 b;
    u32 c;
    u32 d;
    u32 e;
    u32 f;

    a = a0[0];
    b = a1[0];
    c = a0[1];
    d = a1[1];
    e = a0[2];
    f = a1[2];
    a0[0] = a + b;
    a0[1] = c + d;
    a0[2] = e + f;
}
