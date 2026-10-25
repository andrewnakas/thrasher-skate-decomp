#include "common.h"

extern u8 *func_80034C20(s32 size);
extern u8 *D_8008AE64;
extern u16 D_8008AE68;
extern u8 *D_8008AE4C;
extern u16 D_8008AE50;
extern u8 *D_8008AE54;
extern u16 D_8008AE58;

void func_8001C410(void) {
    u8 *p;

    p = func_80034C20(0x1400);
    D_8008AE64 = p;
    D_8008AE68 = 0;
    memset(p, 0, 0x1400);
    p = func_80034C20(0x400);
    D_8008AE4C = p;
    D_8008AE50 = 0;
    memset(p, 0, 0x400);
    p = func_80034C20(0x180);
    D_8008AE54 = p;
    D_8008AE58 = 0;
    memset(p, 0, 0x180);
}
