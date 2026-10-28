#include "common.h"

extern void func_800330A4(s32 *a0);
extern void func_800331FC(s32 *a0, s32 a1);
extern void func_80032FF4(u8 *a0, s32 *a1);

void func_80023BB4(u8 *o) {
    s32 d[3];
    s32 v[3];
    u8 *a;
    u8 *b;
    s32 *pa;
    s32 *pb;

    a = *(u8 **) (o + 8);
    b = *(u8 **) (o + 0xC);
    pa = (s32 *) (a + 0x44);
    pb = (s32 *) (b + 0x44);
    d[0] = pa[0] - pb[0];
    d[1] = pa[1] - pb[1];
    d[2] = pa[2] - pb[2];
    func_800330A4(d);
    func_800331FC(d, *(s32 *) (o + 0x10));
    v[0] = d[0] + pb[0];
    v[1] = d[1] + pb[1];
    v[2] = d[2] + pb[2];
    func_800331FC(v, *(s32 *) (o + 4));
    func_80032FF4(*(u8 **) (o + 8) + 0x5C, v);
    v[0] = pa[0] - d[0];
    v[1] = pa[1] - d[1];
    v[2] = pa[2] - d[2];
    func_800331FC(v, *(s32 *) (o + 4));
    func_80032FF4(*(u8 **) (o + 0xC) + 0x5C, v);
    *(s32 *) (*(u8 **) (o + 8) + 0x38) += *(s32 *) (o + 4);
    *(s32 *) (*(u8 **) (o + 0xC) + 0x38) += *(s32 *) (o + 4);
}
