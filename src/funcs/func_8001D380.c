#include "common.h"

extern u8 D_800928C4[];
extern u8 D_80092914[];
extern s32 D_8008AEA8;

s32 func_8001D380(void) {
    s32 i;
    s32 *p;

    D_8008AEA8 = (s32) D_800928C4;
    i = 3;
    p = (s32 *) D_80092914;
    p += 15;
    for (; i >= 0; i--) {
        *p = 0;
        p -= 5;
    }
    return 0;
}
