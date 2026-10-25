#include "common.h"

void func_80034698(u8 *, s32, u16, u16);

u8 *func_80034654(u8 *buf, s32 v, u16 radix, u16 flags) {
    u8 *p = buf;

    if (v < 0) {
        *buf = '-';
        buf++;
        v = -v;
    }
    func_80034698(buf, v, radix, flags);
    return p;
}
