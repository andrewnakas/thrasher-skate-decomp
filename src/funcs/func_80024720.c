#include "common.h"

extern s32 D_8008AF2C[2];
extern s32 D_8008A2BC;

void func_80024720(s32 v) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_8008AF2C[i] == v) {
            D_8008A2BC = i;
            return;
        }
    }
}
