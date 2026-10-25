#include "common.h"

extern void func_8001EA78(u8 *p);
extern void func_8001E9AC(u8 *p, s32 a);

s32 func_8001F8BC(u8 *a0, u8 *a1) {
    func_8001EA78(a0);
    *(s32 *) (a0 + 0x44) = *(s32 *) (a1 + 0x18);
    *(s32 *) (a0 + 0x48) = *(s32 *) (a1 + 0x1C);
    *(s32 *) (a0 + 0x4C) = *(s32 *) (a1 + 0x20);
    *(s32 *) (a0 + 0x50) = *(s32 *) (a1 + 0x24);
    *(s32 *) (a0 + 0x54) = *(s32 *) (a1 + 0x28);
    *(s32 *) (a0 + 0x58) = *(s32 *) (a1 + 0x2C);
    func_8001E9AC(a0, 0);
    if ((*(u16 *) a1 & 0x400) != 0) {
        *(u16 *) a0 |= 0x400;
    }
    if ((*(u16 *) a1 & 0x800) != 0) {
        *(u16 *) a0 |= 0x800;
    }
    return 0;
}
