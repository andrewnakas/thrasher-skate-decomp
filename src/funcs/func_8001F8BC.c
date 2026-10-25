#include "common.h"

extern void func_8001EA78(u8 *, u8 *);
extern void func_8001E9AC(u8 *, s32);

s32 func_8001F8BC(u8 *a0, u8 *a1) {
    func_8001EA78(a0, a1);
    *(u32 *) (a0 + 0x44) = *(u32 *) (a1 + 0x18);
    *(u32 *) (a0 + 0x48) = *(u32 *) (a1 + 0x1C);
    *(u32 *) (a0 + 0x4C) = *(u32 *) (a1 + 0x20);
    *(u32 *) (a0 + 0x50) = *(u32 *) (a1 + 0x24);
    *(u32 *) (a0 + 0x54) = *(u32 *) (a1 + 0x28);
    *(u32 *) (a0 + 0x58) = *(u32 *) (a1 + 0x2C);
    func_8001E9AC(a0, 0);
    if ((*(u16 *) a1 & 0x400) != 0) {
        *(u16 *) a0 = *(u16 *) a0 | 0x400;
    }
    if ((*(u16 *) a1 & 0x800) != 0) {
        *(u16 *) a0 = *(u16 *) a0 | 0x800;
    }
    return 0;
}
