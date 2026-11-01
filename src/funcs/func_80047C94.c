#include "common.h"

typedef struct {
    s32 size;
    s32 width;
    s32 height;
    s16 planes;
    s16 bitcount;
    s32 compression;
    s32 sizeimage;
    s32 xppm;
    s32 yppm;
    s32 clrused;
    s32 clrimportant;
} BmpInfo;

typedef struct {
    u8 pad0[8];
    s32 w;
    s32 h;
    u8 pad10;
    u8 bpp;
    u8 pad12[2];
    u8 *data;
} Img;

extern u8 D_8008A8B4;

void func_80034D4C(void *, void *, s32);
u8 *func_80034C20(s32);
void memcpy(void *, void *, s32);

s32 func_80047C94(u8 *src, Img *d, u8 *pal) {
    u8 fh[14];
    BmpInfo ih;
    s32 ncol;
    s32 i;
    s32 rowbytes;
    s32 h;
    s32 stride;
    s32 x;
    u8 *dst;

    func_80034D4C(fh, src, 14);
    src += 14;
    func_80034D4C(&ih, src, 40);
    src += ih.size;
    d->bpp = ih.bitcount;
    d->w = ih.width;
    d->h = ih.height;
    d->data = func_80034C20(ih.width * ih.height);
    if (d->data == NULL) {
        return 1;
    }
    if (ih.clrused == 0) {
        ncol = 0x100;
        if (ih.bitcount == 4) {
            ncol = 0x10;
        }
    } else {
        ncol = ih.clrused;
    }
    if (pal != NULL) {
        for (i = 0; i < ncol; i++) {
            pal[i * 4 + 0] = src[i * 4 + 0];
            pal[i * 4 + 1] = src[i * 4 + 1];
            pal[i * 4 + 2] = src[i * 4 + 2];
            if (D_8008A8B4 != 0) {
                pal[i * 4 + 3] = src[i * 4 + 3];
            } else {
                pal[i * 4 + 3] = 0xFF;
            }
        }
    }
    src += ncol * 4;
    rowbytes = (ih.width * ih.bitcount) / 8;
    h = ih.height;
    stride = ((rowbytes + 3) / 4) * 4;
    if (ih.bitcount == 4) {
        for (i = 0; i < h; i++) {
            dst = d->data + (h - i - 1) * rowbytes;
            for (x = 0; x < rowbytes; x++) {
                dst[x] = ((src[x] & 0xF) << 4) | (src[x] >> 4);
            }
            src += stride;
        }
        return 0;
    }
    for (i = 0; i < h; i++) {
        memcpy(d->data + (h - i - 1) * rowbytes, src, rowbytes);
        src += stride;
    }
    return 0;
}
