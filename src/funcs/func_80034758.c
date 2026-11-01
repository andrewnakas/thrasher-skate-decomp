#include "common.h"

u8 *func_80034698(u8 *buf, s32 v, u16 radix, u16 flags);

u8 *func_80034758(u8 *buf, u32 v, u16 shift) {
    u8 *p = buf;
    u32 frac = v << (32 - shift);
    s32 ip = v >> shift;

    if (ip < 0 && frac != 0) {
        frac = -frac;
    }
    frac >>= 32 - shift;
    *p++ = '.';
    func_80034698(p, (frac * 9999 + (1 << (shift - 1))) >> shift, 10, 4);
    return buf;
}
