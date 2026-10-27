#include "common.h"

extern u8 D_800A9444[];
extern u8 *D_8008B208;
s32 func_8003AB00(u8 *);
s32 func_8003AB44(u8 *);
void func_80059FFC(s32, s32);

void func_8003AC04(void) {
    u8 *p = D_8008B208;

    p -= 0x14;
    while (p >= &D_800A9444) {
        func_80059FFC(func_8003AB00(p), func_8003AB44(p));
        p -= 0x14;
    }
}
