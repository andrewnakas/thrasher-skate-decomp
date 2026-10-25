#include "common.h"

extern u8 *D_8008AEC4;
s32 func_80034C20(s32);
void func_8001FFB4(void);

void func_8001D7C8(void) {
    u8 *p;

    p = (u8 *) func_80034C20(0x6A4);
    D_8008AEC4 = p;
    memset(p, 0, 0x6A4);
    func_8001FFB4();
}
