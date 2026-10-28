#include "common.h"

extern void func_800337C4(void *);
extern void func_80026DAC(u8 *, u8 *, void *);
extern s32 func_8003353C(void *, void *);
extern void func_800331FC(s32 *, s32);
extern void func_80032FF4(u32 *, u32 *);
extern void func_80026B34(u8 *, void *, void *, void *);

void func_80026C88(u8 *a0, s32 a1, s32 a2, u32 *a3, u8 *a4, s32 a5) {
    u32 m[4];
    u32 v[4];
    u32 t[12];
    s32 s;

    func_800337C4(a4);
    func_800337C4(t);
    func_80026DAC((u8 *) (a1 * 140) + (u32) a0 + 0x48, (u8 *) (a2 * 140) + (u32) a0 + 0x48, m);
    s = func_8003353C(m, a3);
    v[0] = a3[0];
    v[1] = a3[1];
    v[2] = a3[2];
    if (a5 == 0) {
        if (s < 0) {
            s = -s;
        }
    } else {
        if (s > 0) {
            s = -s;
        }
    }
    func_800331FC((s32 *) v, s << 1);
    func_80032FF4(m, v);
    func_80026B34(a0, m, a3, a4);
}
