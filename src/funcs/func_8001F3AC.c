#include "common.h"

void func_8001E9AC(s32, s32);

s32 func_8001F3AC(s32 a0, s32 *a1) {
    *(s32 *) (a0 + 0x24) = a1[0];
    func_8001E9AC(a0, 0);
    return 0;
}
