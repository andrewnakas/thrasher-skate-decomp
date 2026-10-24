#include "common.h"

extern u8 D_80092614[];

s32 func_80016470(u8 *arg0) {
    u8 **slot = (u8 **)(D_80092614 + ((*(u16 *)(arg0 + 4) >> 12) << 2));

    if (*slot == arg0) {
        *slot = 0;
        return 0;
    }
    return 1;
}
