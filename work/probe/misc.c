#include "common.h"

static s32 mask8(s32 x) { return x & 0xFF; }

u32 m17(u8 *p) { return ~((mask8(p[2]) << 8) | mask8(p[3])) & 0xFFFF; }

extern s32 D_8008B384[];

void k01(s32 a, s32 *src, s32 tag, s32 i) {
    s32 *p;
    s32 *slot;
    if (tag == 0x1000) return;
    slot = &D_8008B384[i];
    p = (s32 *)*slot;
    *slot = (s32)(p + 5);
    p[0] = a; p[1] = src[0]; p[2] = src[1]; p[3] = src[2]; p[4] = tag;
}

void k02(s32 a, s32 *src, s32 tag, s32 i) {
    s32 *p;
    s32 v;
    if (tag == 0x1000) return;
    v = D_8008B384[i];
    *D_8008B384 = v;
    D_8008B384[i] = v + 0x14;
    p = (s32 *)v;
    *p = a;
}

void k03(s32 a, s32 *src, s32 tag, s32 i) {
    s32 *p;
    s32 *slot;
    if (tag == 0x1000) return;
    slot = &D_8008B384[i];
    p = (s32 *)*slot;
    *slot += 0x14;
    p[0] = a; p[1] = src[0]; p[2] = src[1]; p[3] = src[2]; p[4] = tag;
}

void k04(s32 a, s32 *src, s32 tag, s32 i) {
    s32 *p;
    s32 *entry;
    if (tag == 0x1000) return;
    entry = (s32 *)D_8008B384[i];
    D_8008B384[i] = entry[0] + 0x14;
    p = entry;
    p[0] = a;
}

void k05(s32 a, s32 *src, s32 tag, s32 i) {
    s32 *p;
    s32 old;
    if (tag == 0x1000) return;
    old = D_8008B384[i];
    p = (s32 *)old;
    D_8008B384[i] = old + 0x14;
    p[0] = a; p[1] = src[0];
}
