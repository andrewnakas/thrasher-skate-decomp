#include "common.h"

s32 func_8004734C(u16);
s32 func_800474B4(u16);
s32 func_80047578(u16);
s32 func_800477B0(u16);
s32 func_80047014(u16);
s32 func_800465B4(void);
s32 func_800465C0(u16);
u16 func_80046EFC(u16, u16, u16, u16, s32);

s32 func_8004710C(u16 id, u16 arg) {
    s32 out;
    s32 c;
    s32 b;
    s32 a;
    s32 snd;
    u16 r;
    s32 t;

    a = func_8004734C(id);
    b = func_800474B4(id);
    c = func_80047578(id);
    t = func_800477B0(id);
    out = t;
    func_80047014(id);
    snd = func_800465B4();
    out &= 0xFFFF;
    func_800465C0(id);
    r = func_80046EFC(arg, a & 0xFF, b, c, out | 0x8000000);
    if (r != 0xFFFF) {
        func_800477B0(r);
        func_800465C0(snd);
        return r;
    }
    return r;
}
