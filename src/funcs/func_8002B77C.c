#include "common.h"

extern void func_8003031C(u8 *a);
extern s16 func_800122A0(s32 a);
extern void func_80014784(s32 a, u16 *b);

void func_8002B77C(u8 *p, u8 *d) {
    u8 *src = d;
    u8 *self = p;
    u16 v[3];

    if ((*(u32 *) self & 0xC00000) != 0xC00000) {
        func_8003031C(self);
    }
    *(u16 *) (self + 4) = *(u16 *) src;
    *(u16 *) (self + 6) = *(u16 *) (src + 2);
    *(u16 *) (self + 8) = *(u16 *) (src + 4);
    if (*(u32 *) (self + 0x1C) != 0) {
        v[0] = *(u16 *) src;
        v[1] = func_800122A0(*(s16 *) (src + 2));
        v[2] = *(u16 *) (src + 4);
        func_80014784(*(u32 *) (self + 0x1C), v);
    }
}
