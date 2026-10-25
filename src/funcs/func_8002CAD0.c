#include "common.h"

s32 func_8002CAD0(u8 *p) {
    u32 v = *p;

    if (v & 1) {
        return 1;
    }
    if (v & 2) {
        return -1;
    }
    return 0;
}
