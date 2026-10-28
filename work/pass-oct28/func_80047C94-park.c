#include "common.h"

typedef struct S_80047C94_Hdr {
    s32 size;
    s32 w;
    s32 h;
    u8 padC[2];
    u16 fmt;
    u8 pad10[0x10];
    s32 unk20;
} S_80047C94_Hdr;

typedef struct S_80047C94_Dst {
    u8 pad0[8];
    s32 w;
    s32 h;
    u8 pad10;
    u8 fmt;
    u8 pad12[2];
    u8 *buf;
} S_80047C94_Dst;

extern u8 D_8008A8B4;

extern void func_80034D4C(u8 *dst, u8 *src, s32 n);
extern u8 *func_80034C20(s32 size);
extern void *memcpy(void *dst, void *src, u32 n);

s32 func_80047C94(u8 *a0, S_80047C94_Dst *a1, u8 *a2) {
    u8 name[0xE];
    S_80047C94_Hdr hdr;
    u8 *src;
    u8 *dst;
    s32 n;
    s32 i;
    s32 j;
    s32 stride;
    s32 block;
    u8 v;

    func_80034D4C(name, a0, 0xE);
    a0 += 0xE;
    func_80034D4C((u8 *) &hdr, a0, 0x28);

    a1->fmt = *(u8 *) &hdr.fmt;
    a1->w = hdr.w;
    a1->h = hdr.h;

    src = a0 + hdr.size;
    a1->buf = func_80034C20(hdr.w * hdr.h);
    if (a1->buf == 0) {
        return 1;
    }

    n = hdr.unk20;
    if (n == 0) {
        n = (*(s16 *) &hdr.fmt == 4) ? 0x10 : 0x100;
    }

    if (a2 != 0 && n > 0) {
        dst = a2;
        for (i = 0; i < n; i++) {
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            if (D_8008A8B4 != 0) {
                dst[3] = src[3];
            } else {
                dst[3] = 0xFF;
            }
            dst += 4;
            src += 4;
        }
    }

    stride = hdr.w * (s16) hdr.fmt;
    if (stride < 0) {
        stride += 7;
    }
    stride >>= 3;

    src += n << 2;

    block = stride + 3;
    if (block < 0) {
        block = stride + 6;
    }
    block = (block >> 2) << 2;

    if (*(s16 *) &hdr.fmt == 4) {
        for (i = 0; i < hdr.h; i++) {
            dst = a1->buf + (hdr.h - i - 1) * stride;
            for (j = 0; j < stride; j++) {
                v = src[j];
                dst[j] = ((v & 0xF) << 4) | (v >> 4);
            }
            src += block;
        }
        return 0;
    }

    for (i = 0; i < hdr.h; i++) {
        memcpy(a1->buf + (hdr.h - i - 1) * stride, src, stride);
        src += block;
    }
    return 0;
}
