#include "common.h"

extern u8 D_8006F2C0[];

s32 func_80020048(u16 i) {
    u8 *p = D_8006F2C0;

    return *(s32 *) (p + i * 0x4C + 4);
}
