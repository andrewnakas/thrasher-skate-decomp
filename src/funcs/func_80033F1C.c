#include "common.h"

extern s32 D_8008A4C8;
void func_80036758(s32);

void func_80033F1C(void) {
    s32 v = D_8008A4C8;

    if (v != 0) {
        func_80036758(v);
    }
}
