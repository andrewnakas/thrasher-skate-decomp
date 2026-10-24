#include "common.h"

extern u8 D_800B03C4[];
extern s32 D_80082950[3];
extern void func_8004E30C(u8 a0);

void func_8004DE4C(void) {
    u8 i;

    for (i = 0; i < 0x40; i++) {
        if (*(u8 *) (D_800B03C4 + i * 2) != 0) {
            func_8004E30C(i);
        }
    }

    D_80082950[0] = 0;
}
