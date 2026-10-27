#include "common.h"

u8 *func_80034D4C(u8 *dst, u8 *src, s32 n) {
    u32 t;
    s32 i;

    t = (u32)dst | (u32)src | (u32)n;
    if (!(t & 3)) {
        for (i = n >> 2; i > 0; i--) {
            *(u32 *)dst = *(u32 *)src;
            dst += 4;
            src += 4;
        }
    } else if (!(t & 1)) {
        for (i = n >> 1; i > 0; i--) {
            *(u16 *)dst = *(u16 *)src;
            dst += 2;
            src += 2;
        }
    } else {
        for (i = n; i > 0; i--) {
            *dst++ = *src++;
        }
    }
    return dst - n;
}
