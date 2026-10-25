#include "common.h"

extern void func_80026E88(u8 *a, u8 *b);
extern void func_80033E14(u8 *a, u8 *b);
extern void func_80032B1C(u8 *a, u8 *b);
extern void func_80026DAC(u8 *a, u8 *b, u8 *c);
extern void func_80033714(u8 *a, u8 *b, u8 *c);
extern void func_80032FF4(u8 *a, u8 *b);

void func_80025898(u8 *self, u8 *a1, u8 *a2) {
    u8 buf[0xA0];
    u8 m1[0x30];
    u8 m2[0x30];
    u8 *p;
    s32 i;

    func_80026E88(self + 8, m1);
    func_80033E14(self + 8, m2);
    func_80032B1C(m2, a2);
    func_80032B1C(m2, m1);
    for (i = 1; i < 0xD; i++) {
        p = self + 0x90 + (i - 1) * 0x8C + 0x44;
        func_80026DAC(p, self + 0x48, buf + i * 0xC);
        func_80033714(m2, buf + i * 0xC, p);
        func_80032FF4(p, self + 0x48);
    }
}
