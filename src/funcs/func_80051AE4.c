#include "common.h"

extern s32 D_800B124C[];
extern s32 D_8008B44C;

void func_80051AE4(u8 *a0) {
    u32 i;

    for (i = 0; i < 16; i++) {
        if (a0 == (u8 *) (D_800B124C + i * 4) + 4) {
            D_800B124C[i * 4] = 0;
            D_8008B44C = i;
            return;
        }
    }
}
