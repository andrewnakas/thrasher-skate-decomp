#include "common.h"

extern u16 D_8008ADC4;

u16 func_8001B3F4(u16 arg0) {
    s16 old = D_8008ADC4;
    D_8008ADC4 = old + arg0;
    return old;
}
