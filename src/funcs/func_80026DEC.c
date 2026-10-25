#include "common.h"

extern void func_800331FC(s32 *, s32);
extern void func_800335B4(s32, s32, s32 *, s32 *);

void func_80026DEC(s32 a0, s32 *a1, s32 a2) {
    s32 buf[3];
    s32 vec[3];

    memset(buf, 0, 0xC);
    vec[0] = a1[0];
    vec[1] = a1[1];
    vec[2] = a1[2];
    func_800331FC(vec, 0x10000);
    func_800335B4(a2, a0, buf, vec);
}
