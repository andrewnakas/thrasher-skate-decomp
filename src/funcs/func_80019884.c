#include "common.h"

extern void func_80019C0C(u8 *, u8 *, s32);
extern u8 D_80089FBC[];

#define HASH(q) (((((q)[0] << 8) ^ ((q)[1] << 4) ^ (q)[2]) * 0x9E5F >> 1) & 0xFF8)

void func_80019884(u8 *work, u8 *src, s32 len, u8 *dst, s32 *outlen) {
    u8 *s;
    u8 *d;
    u32 flags;
    s32 lit;
    s32 slot;
    u8 *end;
    u8 *lim;
    u8 **tbl;
    u8 **p;
    u32 i;
    s32 n;
    s32 j;
    s32 cnt;
    s32 key;
    u8 *m;
    u8 *start;
    u8 *q;
    u8 b0;
    u8 b1;

    s = src + 4;
    d = dst;
    flags = 1;
    lit = 0;
    slot = 0;
    end = src + len;
    tbl = (u8 **) (((s32) work + 3) & ~3);
    lim = end - 0x20;
    if (*src == 1) {
        func_80019C0C(s, dst, len - 4);
        *outlen = len - 4;
        return;
    }
    p = tbl;
    for (i = 0; i < 0x100; i++) {
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
        *p++ = D_80089FBC;
    }
    while (s != end) {
        if (flags == 1) {
            flags = *s++ | 0x10000;
            flags |= *s++ << 8;
        }
        n = 1;
        if (s <= lim) {
            n = 16;
        }
        while (--n != -1) {
            if (flags & 1) {
                start = d;
                cnt = *s++;
                key = ((cnt & 0xF0) << 4) | *s++;
                cnt &= 0xF;
                m = tbl[key];
                cnt--;
                *d++ = *m++;
                *d++ = *m++;
                *d++ = *m++;
                while (cnt != -1) {
                    *d++ = *m++;
                    cnt--;
                }
                if (lit != 0) {
                    q = start - lit;
                    tbl[HASH(q) + slot] = q;
                    slot++;
                    slot &= 7;
                    if (lit == 2) {
                        q++;
                        tbl[HASH(q) + slot] = q;
                        slot++;
                    slot &= 7;
                    }
                    lit = 0;
                }
                tbl[(key & 0xFF8) + slot] = start;
                slot++;
                    slot &= 7;
            } else {
                *d++ = *s++;
                lit++;
                if (lit == 3) {
                    lit = 2;
                    q = d - 3;
                    tbl[HASH(q) + slot] = q;
                    slot++;
                    slot &= 7;
                }
            }
            flags >>= 1;
        }
    }
    *outlen = d - dst;
}
