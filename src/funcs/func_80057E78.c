#include "common.h"

extern u8 *D_8008AC60;
void *func_80034C20(s32);

s32 func_80057E78(void) {
    u8 *p;

    p = func_80034C20(0x2000);
    D_8008AC60 = p;
    return p == 0;
}
