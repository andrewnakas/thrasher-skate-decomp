#include "common.h"

void func_80013CE8(s32 *a, s32 *b, s32 *c) {
    c[0] = (a[0] + b[0]) >> 1;
    c[1] = (a[1] + b[1]) >> 1;
    c[2] = (a[2] + b[2]) >> 1;
}
