#include "common.h"

void func_80013CE8(s32 *a, s32 *b, s32 *out) {
    out[0] = (a[0] + b[0]) >> 1;
    out[1] = (a[1] + b[1]) >> 1;
    out[2] = (a[2] + b[2]) >> 1;
}
