#include "common.h"

void func_8001C2B8(s32, s32, s32, s32, s32);

void func_8001C2F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    s32 a2_l = a2;

    s32 i;

    for (i = 0; i < a5; i++) {
        if (i != 0 && a6 != 0) {
            func_8001C2B8(a0, a1 & 0xFFFF, 0xFFFF, a3, a4);
        } else {
            func_8001C2B8(a0, a1 & 0xFFFF, (a2_l + i) & 0xFFFF, a3, a4);
        }
        a1++;
    }
}
