#include "common.h"

extern s32 D_80089F54;

s16 func_800142CC(s16 arg0, s16 arg1) {
    if (D_80089F54 != 0) {
        return arg0 - arg1;
    }
    return arg0 + arg1;
}
