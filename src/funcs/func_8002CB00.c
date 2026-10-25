/* cflags: -mno-split-addresses */
#include "common.h"

extern u8 D_80089F18[0x100];

extern void func_800335B4(s32 *, s32 *, u8 *, u8 *);
extern void func_800330A4(s32 *);

void func_8002CB00(u8 *p, s32 *out) {
    s32 tv[3];
    s32 v[3];

    tv[0] = -*(s32 *)(p + 0x18);
    tv[1] = 0;
    tv[2] = *(s32 *)(p + 0x10);
    func_800335B4(v, tv, D_80089F18, p + 0x10);
    func_800330A4(v);
    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
}
