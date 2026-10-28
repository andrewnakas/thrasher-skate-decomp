#include "common.h"

void func_800337C4(void *);
void func_80026DAC(u8 *, u8 *, s32 *);
s32 func_8003353C(s32 *, u8 *);
void func_800331FC(s32 *, s32);
void func_80032FF4(s32 *, s32 *);
void func_80026B34(u8 *, s32 *, u8 *, u8 *);

/* Builds the rotation that takes the frame of record arg2 to that of record
   arg1 (0x8C-byte records, the heading triple at +0x48), folds the axis arg3
   into it, then hands the result to func_80026B34 with the caller's arg4.
   arg5 picks which sign of the returned angle is kept. */
void func_80026C88(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3, u8 *arg4, s32 arg5) {
    s32 work[4];
    s32 dir[3];
    s32 scale[0xB];
    s32 v;
    s32 *d;

    func_800337C4(arg4);
    func_800337C4(scale);
    func_80026DAC((u8 *) (arg1 * 0x8C) + (u32) arg0 + 0x48, (u8 *) (arg2 * 0x8C) + (u32) arg0 + 0x48, work);
    v = func_8003353C(work, arg3);
    dir[0] = *(s32 *) (arg3 + 0);
    dir[1] = *(s32 *) (arg3 + 4);
    dir[2] = *(s32 *) (arg3 + 8);
    if (arg5 == 0) {
        d = dir;
        if (v < 0) {
            v = -v;
        }
    } else {
        d = dir;
        if (v > 0) {
            v = -v;
        }
    }
    func_800331FC(d, v << 1);
    func_80032FF4(work, d);
    func_80026B34(arg0, work, arg3, arg4);
}
