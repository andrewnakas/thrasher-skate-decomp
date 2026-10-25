#include "common.h"

extern u8 *D_8008AD90;
extern s32 D_8008AD94;
extern s32 D_8008AD88;

u8 *func_80015E8C(s32);
void func_80015F10(s32);

void func_80017540(void) {
    u8 made;
    u8 *p;

    if (D_8008AD90 == NULL) {
        D_8008AD90 = func_80015E8C(D_8008AD94);
        made = 0;
    } else {
        made = 1;
    }
    p = D_8008AD90 + D_8008AD88 * 0x50;
    *(s32 *)(p + 0x28) = 0x10000;
    *(s32 *)(p + 0x2C) = 0x10000;
    if (made == 0) {
        D_8008AD90 = NULL;
        func_80015F10(D_8008AD94);
    }
}
