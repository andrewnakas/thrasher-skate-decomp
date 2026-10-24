#include "common.h"

extern s32 D_8008ADC8;

s32 func_8001A0B4(void) {
    if (D_8008ADC8 != 0) {
        D_8008ADC8 = 0;
    }
    return 0;
}
