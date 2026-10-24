#include "common.h"

s32 func_8004B41C(u8 *a0) {
    u32 v;

    if (a0[2] == 1) {
        return 1;
    }

    v = *(u16 *) a0 & 0x4000;
    return v != 0;
}
