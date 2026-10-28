#include "common.h"

void func_800337C4(void *);
void func_80026DAC(u8 *, u8 *, s32 *);
void func_800330A4(s32 *);
s32 func_8003353C(s32 *, s32 *);
s32 func_80032D88(s32);
void func_8003384C(void *, s16);
void func_80033E14(void *, void *);
void func_80032B1C(void *, void *);

/* Aim the frame at a point: the angle from record arg1's heading to record
   arg2's, clamped to +-0x10000, folded through func_80032D88 and wrapped into
   the -0x8000.. range before it is applied. */
void func_8002673C(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3, u8 *arg4) {
    s32 work[4];
    s32 quat[0xC];
    s32 ang;
    s32 v;

    func_800337C4(arg4);
    func_800337C4(quat);
    func_80026DAC((u8 *) (arg1 * 0x8C) + (u32) arg0 + 0x48, (u8 *) (arg2 * 0x8C) + (u32) arg0 + 0x48, work);
    func_800330A4(work);
    ang = func_8003353C(work, (s32 *) (arg3 + 0xC));
    if (ang < -0x10000) {
        ang = -0x10000;
    }
    if (ang > 0x10000) {
        ang = 0x10000;
    }
    v = func_80032D88(ang);
    if (ang < 0) {
        v = -0x8000 - v;
    }
    func_8003384C(arg4, (s16) v);
    func_80033E14(arg3, quat);
    func_80032B1C(quat, arg4);
    func_80033E14(quat, arg4);
}
