#include "common.h"

typedef struct {
    u16 w;
    u16 h;
    u32 data;
} Hdr2_80038A80;

void func_80038A80(u8 *src, u8 *dst, s16 x, s16 y) {
    Hdr2_80038A80 *sh;
    Hdr2_80038A80 *dh;
    u8 *s;
    u8 *d;
    u32 w;
    s32 i;

    sh = (Hdr2_80038A80 *) (src + 0x14);
    dh = (Hdr2_80038A80 *) (dst + 0x14);
    w = sh->w;
    s = src + sh->data;
    d = dst + dh->data + dh->w * y + x;
    for (i = 0; i < sh->h; i++) {
        memcpy(d, s, w);
        s += sh->w;
        d += dh->w;
    }
}
