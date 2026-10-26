#include "common.h"

void *func_8001D5B0(s32, s32, s32);
void *func_80034C20(s32);
void func_80034D4C(void *, void *, s32);
void *memset(void *, s32, u32);

void func_80029320(s32 arg0, u8 *dst, u8 *src) {
    u8 *hdr;
    u8 *s;
    u8 *p;
    u8 *d;
    s32 n;

    if ((*(u32 *)(src + 0x18) & 0x10000) == 0) {
        return;
    }
    hdr = func_8001D5B0(arg0, 0x504D5846, 1);
    s = hdr + 0xC;
    *(u16 *)(dst + 0x24) = *(u16 *)(hdr + 0xA);
    p = func_80034C20(*(u16 *)(dst + 0x24) << 4);
    *(u8 **)(dst + 0x18) = p;
    memset(p, 0, *(u16 *)(dst + 0x24) << 4);

    n = *(u16 *)(dst + 0x24) - 1;
    d = *(u8 **)(dst + 0x18);
    while (n >= 0) {
        func_80034D4C(d, s, 4);
        *(u8 *)(d + 0xA) = *(u8 *)(s + 4);
        *(u8 *)(d + 0xB) = *(u8 *)(s + 6);
        *(u16 *)(d + 4) = *(u16 *)(s + 8);
        *(u16 *)(d + 6) = *(u16 *)(s + 0xA);
        *(u16 *)(d + 8) = *(u16 *)(s + 0xC);
        d += 0x10;
        s += 0x10;
        n--;
    }
}
