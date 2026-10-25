#include "common.h"

s16 func_80012274(s16);

void func_80012240(s32 p, s16 v) {
    s16 r = func_80012274(v);

    *(u16 *) (p + 0x18) = r;
    *(u16 *) (p + 0x1C) = r;
}
