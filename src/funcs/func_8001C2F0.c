#include "common.h"

void func_8001C2B8(s32, u16, u16, s32, s32);

void func_8001C2F0(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 n, s32 keep) {
    s32 i;

    for (i = 0; i < n; i++) {
        if (i == 0 || keep != 0) {
            func_8001C2B8(a0, a1 + i, a2 + i, a3, a4);
        } else {
            func_8001C2B8(a0, a1 + i, 0xFFFF, a3, a4);
        }
    }
}
