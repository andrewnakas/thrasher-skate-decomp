#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 width;
    u8 pad1[8];
    u8 *pixels;
} Img_80047A44;

s32 func_80047A44(u8 **src, Img_80047A44 *img, s32 row) {
    s32 w;
    s32 x;
    s32 i;
    s32 c;
    u8 *s;
    u8 *dst;
    u8 v;

    x = 0;
    dst = img->pixels + row * img->width;
    s = *src;
    w = img->width;
    while (x < w) {
        c = *s++;
        if (c >= 0xC0) {
            v = *s++;
            c -= 0xC0;
        } else {
            v = c;
            c = 1;
        }
        for (i = 0; i < c; i++) {
            dst[x] = v;
            x++;
        }
    }
    *src = s;
    return 1;
}
