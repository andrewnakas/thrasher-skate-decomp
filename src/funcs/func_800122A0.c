#include "common.h"
extern s32 D_80089F54;
extern u16 D_80089F50;
s16 func_800122A0(s16 v) {
    v = v - D_80089F50;
    if (D_80089F54) {
        v = -v;
    }
    return v;
}
