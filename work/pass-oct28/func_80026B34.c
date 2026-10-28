#include "common.h"

void func_80026B34(s32 a0, u8 *a1, u8 *a2, u8 *a3) {
    u32 v[3];
    s32 s4;
    u8 *s3;

    func_800337C4(a3);
    *(u32 *) (a3 + 0xC) = *(u32 *) (a1 + 0);
    *(u32 *) (a3 + 0x10) = *(u32 *) (a1 + 4);
    *(u32 *) (a3 + 0x14) = *(u32 *) (a1 + 8);
    s3 = a3 + 0xC;
    func_800330A4(s3);
    s4 = func_8003353C(a2, s3);
    func_8003353C(a2 + 0xC, s3);
    func_8003353C(a2 + 0x18, s3);

    v[0] = *(u32 *) (a2 + 0x18);
    v[1] = *(u32 *) (a2 + 0x1C);
    v[2] = *(u32 *) (a2 + 0x20);
    func_80026DEC(a2, s3, a1);
    func_800330A4(a1);

    if (s4 < 0) {
        s4 = -s4;
    }
    func_800331FC(v, s4);
    func_800331FC(a1, 0x10000 - s4);
    func_80032FF4(v, a1);

    *(u32 *) (a3 + 0x18) = v[0];
    *(u32 *) (a3 + 0x1C) = v[1];
    *(u32 *) (a3 + 0x20) = v[2];
    func_80026DEC(a3 + 0xC, a3 + 0x18, a3);
    func_800330A4(a3);
    func_80026DEC(a3, a3 + 0xC, a3 + 0x18);
    func_800330A4(a3 + 0x18);
}
