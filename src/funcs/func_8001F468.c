#include "common.h"

void func_8001E9AC(s32, s32);

s32 func_8001F468(s32 a0, s32 *a1) {
    s32 f;

    *(s32 *) (a0 + 0x24) = a1[0];
    *(s32 *) (a0 + 0x2C) = a1[1];
    *(s32 *) (a0 + 0x28) = 0;
    func_8001E9AC(a0, 0);
    if (*(s32 *) (a0 + 0x24) & 0x3000) {
        f = *(s32 *) (a0 + 0x28);
        *(s32 *) (a0 + 0x28) = f | 4;
        if (*(s32 *) (a0 + 0x24) & 0x1000) {
            *(s32 *) (a0 + 0x28) = f | 7;
        } else {
            *(s32 *) (a0 + 0x28) = f | 6;
        }
    }
    return 0;
}
