#include "common.h"

extern void func_80066D2C(s32 a0, s32 a1);

s32 func_800522A4(s32 a0, s32 a1) {
    if (a1 == 4) {
        func_80066D2C(5, a0);
    }
    return 0;
}
