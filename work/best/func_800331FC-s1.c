#include "common.h"

void func_800331FC(s32 *v, s32 m) {
    s32 k = m;

    v[0] = (s32) (((long long) v[0] * k) >> 16);
    v[1] = (s32) (((long long) v[1] * k) >> 16);
    v[2] = (s32) (((long long) v[2] * k) >> 16);
}
