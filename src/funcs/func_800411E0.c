#include "common.h"

extern s32 func_80034C20(s32 a0);
extern void func_80034D4C(void *a0, void *a1, s32 a2);

s32 func_800411E0(u8 *a0) {
    u32 n = *(u16 *) (a0 + 6);
    s32 size = (n + 1) << 4;
    s32 p = func_80034C20(size);

    func_80034D4C((void *) p, *(void **) (a0 + 0x24), size);
    return p;
}
