#include "common.h"

extern u8 *D_8008B05C;
extern u8 *D_8008B060;
u8 *func_80034C20(s32);

void func_8002DC70(void) {
    u8 *p = func_80034C20(0xF0);

    D_8008B05C = p;
    memset(p, 0, 0xF0);
    D_8008B060 = D_8008B05C;
}
