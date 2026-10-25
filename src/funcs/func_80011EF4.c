#include "common.h"

extern s32 D_8008ACA0;
void func_80033714(s32 a0, s32 a1, s32 a2);

void func_80011EF4(s32 a0, s32 a1) {
    func_80033714(D_8008ACA0 + 0x28, a0, a1);
}
