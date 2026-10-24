#include "common.h"

extern void func_800366D0(s32, s32, s32);

s32 func_80051F9C(u8 *a0) {
    func_800366D0(*(s32 *) (a0 + 0xC), 0, 0);
    *(s32 *) (a0 + 8) = 0;
    return 0;
}
