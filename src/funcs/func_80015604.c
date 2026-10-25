#include "common.h"

extern s32 D_8008AD2C;

s32 func_800123B0(u8 *, s32, u16, u8 *, s32);
void func_80014DA8(u8 *, u8 *, s32, u32);

s32 func_80015604(u8 *arg0, s32 arg1, u16 arg2, s32 arg3) {
    struct {
        u8 buf[0x18];
        u8 *b;
        u8 *c;
    } s;
    u8 *base;

    base = *(u8 **)(arg0 + 0x38);
    s.b = base + 0x1AC;
    s.c = *(u8 **)(arg0 + 0x38) + 0x504;
    *(s32 *)(s.c + 0xD8) = arg1;
    D_8008AD2C = func_800123B0(arg0, 0x10000, arg2, s.buf, 2);
    func_80014DA8(s.b + 0x134, s.c + 0x134, arg3, *(u8 *)(base + 0x115));
    return D_8008AD2C;
}
