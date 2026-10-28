#include "common.h"

void func_8003302C(s32 *a, s32 *b) {
    a[0] = (s32) (((long long) a[0] * b[0]) >> 16);
    a[1] = (s32) (((long long) a[1] * b[1]) >> 16);
    a[2] = (s32) (((long long) a[2] * b[2]) >> 16);
}
