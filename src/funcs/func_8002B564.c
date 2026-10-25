#include "common.h"

void func_8002B564(s32 *a0, s32 *a1) {
    a0[0x10] = a1[2];
    a1[2] = a0;
    a0[0xF] = a1;
}
