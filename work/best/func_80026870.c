#include "common.h"

extern s32 func_800337C4(void *);
extern s32 func_80026DAC(void *, void *, void *);
extern s32 func_800330A4(void *);
extern s32 func_8003353C(void *, void *);
extern s32 func_80032C54(s32, s32);
extern s32 func_800331FC(void *, s32);
extern s32 func_80032FF4(void *, void *);
extern s32 func_80026DEC(void *, void *, void *);

void func_80026870(u8 *base, s32 i1, s32 i2, u8 *src, u8 *out) {
    s32 v[3];
    s32 a[3];
    s32 b[3];
    s32 c[3];
    s32 r1;
    s32 r2;
    s32 r3;
    s32 s4;
    s32 s1;
    s32 s2;
    s32 sum;
    u8 *p1;
    u8 *p2;

    func_800337C4(out);
    func_80026DAC((u8 *) (i1 * 140 + (s32) base) + 0x48, (u8 *) (i2 * 140 + (s32) base) + 0x48, out + 0xC);
    func_800330A4(out + 0xC);

    r1 = func_8003353C(src, out + 0xC);
    r2 = func_8003353C(src + 0xC, out + 0xC);
    r3 = func_8003353C(src + 0x18, out + 0xC);

    if (r1 > 0) {
        s4 = r1;
        a[0] = *(s32 *) (src + 0x18);
        a[1] = *(s32 *) (src + 0x1C);
        a[2] = *(s32 *) (src + 0x20);
        a[0] = -a[0];
        a[1] = -a[1];
        a[2] = -a[2];
    } else {
        s4 = -r1;
        a[0] = *(s32 *) (src + 0x18);
        a[1] = *(s32 *) (src + 0x1C);
        a[2] = *(s32 *) (src + 0x20);
    }

    if (r2 > 0) {
        b[0] = *(s32 *) src;
        b[1] = *(s32 *) (src + 4);
        b[2] = *(s32 *) (src + 8);
        s1 = r2;
    } else {
        b[0] = *(s32 *) src;
        b[1] = *(s32 *) (src + 4);
        b[2] = *(s32 *) (src + 8);
        s1 = -r2;
    }

    if (r3 > 0) {
        c[0] = *(s32 *) src;
        c[1] = *(s32 *) (src + 4);
        c[2] = *(s32 *) (src + 8);
        s2 = r3;
    } else {
        c[0] = *(s32 *) src;
        c[1] = *(s32 *) (src + 4);
        c[2] = *(s32 *) (src + 8);
        s2 = -r3;
    }

    sum = s4 + s1 + s2;
    s4 = func_80032C54(s4, sum);
    s1 = func_80032C54(s1, sum);
    s2 = func_80032C54(s2, sum);

    func_800331FC(a, s4);
    func_800331FC(b, s1);
    func_800331FC(c, s2);

    v[0] = a[0];
    v[1] = a[1];
    v[2] = a[2];
    func_80032FF4(v, b);
    func_80032FF4(v, c);
    func_800330A4(v);

    *(s32 *) out = v[0];
    *(s32 *) (out + 4) = v[1];
    *(s32 *) (out + 8) = v[2];
    func_80026DEC(out, out + 0xC, out + 0x18);
    func_800330A4(out + 0x18);
    func_80026DEC(out + 0xC, out + 0x18, out);
    func_800330A4(out);
}
