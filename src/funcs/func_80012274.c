#include "common.h"
extern s32 D_80089F54;
extern u16 D_80089F50;
s16 func_80012274(s16 v) {
    if (D_80089F54) {
        v = -v;
    }
    return v + D_80089F50;
}
