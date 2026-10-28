#include "common.h"

extern void func_800337C4(void *);
extern void func_80026DAC(u8 *, u8 *, void *);
extern void func_800330A4(void *);
extern s32 func_8003353C(void *, void *);
extern s32 func_80032D88(s32);
extern void func_8003384C(void *, s16);
extern void func_80033E14(void *, void *);
extern void func_80032B1C(void *, void *);

void func_8002673C(u8 *a0, s32 a1, s32 a2, u8 *a3, void *a4) {
    u32 m[4];
    u32 t[12];
    s32 v;
    s32 r;

    func_800337C4(a4);
    func_800337C4(t);
    func_80026DAC((u8 *) (a1 * 140) + (u32) a0 + 0x48, (u8 *) (a2 * 140) + (u32) a0 + 0x48, m);
    func_800330A4(m);
    v = func_8003353C(m, a3 + 0xC);
    if (v < -0x10000) {
        v = -0x10000;
    }
    if (v > 0x10000) {
        v = 0x10000;
    }
    r = func_80032D88(v);
    if (v < 0) {
        r = -0x8000 - r;
    }
    func_8003384C(a4, (s16) r);
    func_80033E14(a3, t);
    func_80032B1C(t, a4);
    func_80033E14(t, a4);
}
