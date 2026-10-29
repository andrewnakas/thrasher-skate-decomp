#include "common.h"

typedef struct {
    u8 mode;
    u8 pad0;
    s16 f2;
    s16 w;
    s16 h;
} HDR;

typedef struct {
    u8 pad0[8];
    s32 w;
    s32 h;
    u8 pad1[1];
    u8 mode;
    u8 pad2[2];
    u8 *dst;
} DST;

void func_80036EF4(s16 *);
u8 *func_80034C20(s32);

s32 func_80047EF0(u8 *src, DST *d) {
    HDR h;
    s32 n;
    u8 m;
    s32 i;
    s32 j;

    h = *(HDR *) src;
    src += 8;
    func_80036EF4(&h.f2);
    func_80036EF4(&h.h);
    func_80036EF4(&h.w);
    d->w = h.w;
    d->h = h.h;
    m = h.mode;
    d->mode = m;
    n = (m + 7) / 8;
    d->dst = func_80034C20(h.w * h.h * n);
    if (d->dst == 0) {
        return 1;
    }
    if (d->mode == 8) {
        for (j = 0; j < d->h; j++) {
            for (i = 0; i < d->w; i++) {
                d->dst[j * d->w + i] = *src;
                src += 2;
            }
        }
        return 0;
    } else if (d->mode == 0x10) {
        for (j = 0; j < d->h; j++) {
            for (i = 0; i < d->w; i++) {
                ((u16 *) d->dst)[j * d->w + i] = *(u16 *) src;
                src += 2;
            }
        }
        return 0;
    } else if (d->mode == 4) {
        for (j = 0; j < d->h; j++) {
            for (i = 0; i < d->w; i++) {
                d->dst[j * d->w + i] = src[0] | (src[2] << 4);
                src += 4;
            }
        }
        return 0;
    }
    return 0;
}
