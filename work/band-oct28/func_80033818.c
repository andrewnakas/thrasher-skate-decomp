#include "common.h"

void func_80033818(s32 *a) {
    s32 v1;
    s32 v3;
    s32 v2;
    s32 v6;
    s32 v5;
    s32 v7;

    v1 = a[1];
    v3 = a[3];
    v2 = a[2];
    v6 = a[6];
    v5 = a[5];
    v7 = a[7];
    a[3] = v1;
    a[1] = v3;
    a[6] = v2;
    a[2] = v6;
    a[7] = v5;
    a[5] = v7;
}
