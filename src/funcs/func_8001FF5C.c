#include "common.h"

extern u8 D_80092964[0x320];

s32 func_8001FF5C(void) {
    s32 i;
    u8 *p;

    for (i = 0, p = D_80092964; i < 10; i++, p += 0x50) {
        memset(p, 0, 0x50);
        p[0x4C] = 0;
    }
    return 0;
}
