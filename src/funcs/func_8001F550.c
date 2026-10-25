#include "common.h"

extern s32 func_8002AB64(s32 a, s32 b);
extern s32 func_8002AAE4(s32 a, s32 b);
extern void func_8001E9AC(u8 *p, u32 flags);

s32 func_8001F550(u8 *dst, u8 *src) {
    *(s32 *) (dst + 0x24) = *(s32 *) (src + 4);
    *(u16 *) (dst + 0x3C) = *(u16 *) (src + 2);
    *(s32 *) (dst + 0x4C) = *(s32 *) (src + 8);
    if (*(s16 *) (src + 0x12) != -1) {
        *(s32 *) (dst + 0x48) = func_8002AB64(*(s16 *) (src + 0x12), 0);
    }
    if (*(s16 *) (src + 0x10) != -1) {
        *(s32 *) (dst + 0x40) = func_8002AAE4(*(s16 *) (src + 0x10), 0);
    }
    *(s32 *) (dst + 0x44) = *(s32 *) (src + 0xC);
    *(s32 *) (dst + 0x50) = *(s32 *) (src + 0x18);
    *(u16 *) (dst + 0x3E) = *(u16 *) (src + 0x14);
    *(s32 *) (dst + 0x54) = *(s32 *) (src + 0x1C);
    func_8001E9AC(dst, *(u16 *) src);
    *(u16 *) dst |= *(u16 *) src & 0xF000;
    return 0;
}
