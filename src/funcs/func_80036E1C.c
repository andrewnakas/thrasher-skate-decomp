#include "common.h"

extern u8 D_800A66FC[];
void func_8001651C(void *, s32);
void func_8001655C(void *, s32);

void *func_80036E1C(s32 a0, s32 a1) {
    func_8001651C(D_800A66FC, a0);
    func_8001655C(D_800A66FC, a1);
    return D_800A66FC;
}
