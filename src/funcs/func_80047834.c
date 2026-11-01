#include "common.h"

typedef struct {
    u8 pad0[4];
    s16 w;
    s16 h;
} Hdr_80047834;

typedef struct {
    u8 pad0[8];
    u32 a;
    u32 b;
    u8 pad10[4];
    u16 *pix;
} Img_80047834;

void func_80047834(Hdr_80047834 *hdr, Img_80047834 *img, u16 *dst, s32 bpp) {
    s32 y;
    s32 x;
    s16 w;
    u16 *s;
    u16 *d;

    switch (bpp) {
        case 4:
            for (y = 0; y < hdr->h; y += 2) {
                w = hdr->w;
                s = img->pix + y * w;
                d = dst + (y / 2 * w) / 2;
                for (x = 0; x < hdr->w; x += 2) {
                    u16 p0 = s[0];
                    u16 p1 = s[1];

                    s += 2;
                    *d++ = ((p0 & 0xF000) >> 8) | ((p0 & 0xF0) >> 4) | (p1 & 0xF000) | ((p1 & 0xF0) << 4);
                }
            }
            break;
        case 16:
            break;
        case 8:
            for (y = 0; y < hdr->h; y += 2) {
                w = hdr->w;
                s = img->pix + y * w;
                d = dst + (y / 2 * w) / 2;
                for (x = 0; x < hdr->w; x += 2) {
                    u16 p0 = s[0];
                    u16 p1 = s[1];

                    s += 2;
                    *d++ = (p0 >> 8) | (p1 & 0xFF00);
                }
            }
            break;
    }
    hdr->w = hdr->w >> 1;
    hdr->h = hdr->h >> 1;
    img->a >>= 1;
    img->b >>= 1;
}
