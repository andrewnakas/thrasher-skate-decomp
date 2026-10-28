#include "common.h"

typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
} Hdr;

extern u8 D_800A8404[];
extern void SetDrawLoad(u8 *, Hdr *);

u8 *func_8003A1B8(u8 *dst, u8 *src, u16 *h, u8 kind, u32 a4, u32 a5) {
    Hdr hdr;
    u8 *e;

    if (kind != 2) {
        return dst;
    }

    e = D_800A8404 + 8 * (h[0] >> 8);

    hdr.f0 = *(u16 *) (e + 0);
    hdr.f4 = kind;
    hdr.f2 = *(u16 *) (e + 2);
    hdr.f6 = *(u16 *) (e + 6);
    hdr.f8 = (u16) (((a5 >> 6) & 3) | (((a5 >> 14) & 3) << 5) | (((a5 >> 22) & 3) << 10));
    hdr.fA = (u16) (((a4 >> 6) & 3) | (((a4 >> 14) & 3) << 5) | (((a4 >> 22) & 3) << 10));

    SetDrawLoad(dst, &hdr);

    *(u32 *) (dst + 0x10) = hdr.f8 | (hdr.fA << 16);
    *(u32 *) dst = (*(u32 *) dst & 0xFF000000) | (*(u32 *) src & 0xFFFFFF);
    *(u32 *) src = (*(u32 *) src & 0xFF000000) | ((u32) dst & 0xFFFFFF);

    return dst + 0x44;
}
