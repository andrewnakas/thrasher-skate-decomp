#include "common.h"

u8 *func_80034698(u8 *, s32, u16, u16);

u8 *func_80034654(u8 *dst, s32 val, u16 width, u16 base) {
    u8 *ret;

    ret = dst;
    if (val < 0) {
        *dst = 0x2D;
        dst = dst + 1;
        val = -val;
    }
    func_80034698(dst, val, width, base);
    return ret;
}
