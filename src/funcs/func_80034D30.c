#include "common.h"

extern s32 D_8008B0F4;

void func_80034D30(s32 *p) {
    s32 n;

    n = p[-1];
    n += 4;
    D_8008B0F4 = D_8008B0F4 + n;
}
