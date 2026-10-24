#include "common.h"

s32 func_80036A78(u8 *a0, u32 a1, u16 a2) {
    u8 *p;
    s32 stride;
    s32 i;

    stride = *(u16 *) (a0 + 0x1E) * *(u16 *) (a0 + 0xA) + 4;
    if (a1 < *(u16 *) (a0 + 0x8)) {
        p = *(u8 **) (a0 + 0x10) + a1 * stride;
        if (*(u32 *) p == a1) {
            *(u8 **) (a0 + 0xC) = p + 4 + *(u16 *) (a0 + 0x1E) * a2;
            return 0;
        }
    }
    p = *(u8 **) (a0 + 0x10);
    for (i = *(u16 *) (a0 + 0x8); i > 0; i--) {
        if (*(u32 *) p == a1) {
            *(u8 **) (a0 + 0xC) = p + 4 + *(u16 *) (a0 + 0x1E) * a2;
            return 0;
        }
        p += stride;
    }
    return 1;
}
