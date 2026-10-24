#include "common.h"

extern s16 D_8008ADD0;
extern s16 D_8008ADF8;
extern s16 D_8008AE08;
extern s16 D_8008AE10;

u16 func_8001B3F4(u16);

void func_8001B3B0(void) {
    D_8008ADD0 = func_8001B3F4(0x18);
    D_8008ADF8 = func_8001B3F4(6);
    D_8008AE08 = func_8001B3F4(6);
    D_8008AE10 = func_8001B3F4(0x80);
}
