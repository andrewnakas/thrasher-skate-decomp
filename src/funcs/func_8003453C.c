#include "common.h"

u8 *func_80034654(u8 *buf, s32 v, u16 radix, u16 flags);
u8 *func_80034698(u8 *buf, s32 v, u16 radix, u16 flags);

u8 *func_8003453C(u8 *buf, s32 v, u16 shift) {
    u8 *p = buf;
    s32 ip = v >> shift;
    u32 frac = v << (32 - shift);

    if (ip < 0 && frac != 0) {
        if (++ip == 0) {
            *buf = '-';
            p = buf + 1;
        }
        frac = -frac;
    }
    frac >>= 32 - shift;
    func_80034654(p, ip, 10, 0);
    while (*p != 0) {
        p++;
    }
    *p = '.';
    func_80034698(p + 1, (frac * 9999 + (1 << (shift - 1))) >> shift, 10, 4);
    return buf;
}
