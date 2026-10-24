#include "common.h"

extern s32 D_8008B120;
extern u8 D_8008A564[];
extern u8 *D_8008B110;
extern u8 *D_8008B114;
extern s32 func_80036284(u8 *, u8 *, s32);

void func_80035860(void) {
    if (D_8008B120 == 1) {
        if (func_80036284(D_8008A564, D_8008B110, D_8008B114 - D_8008B110) != 0) {
            D_8008B120 = 0;
        }
    }
}
