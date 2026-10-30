#include "common.h"

extern s32 D_8008A800[4];
extern u32 *D_8008A8EC;
extern u32 D_8008A8F0;

s32 func_80034C20(s32);
void func_80049530(void);

s32 func_800494A4(void) {
    s32 i;
    u32 v;

    D_8008A8EC = (u32 *) func_80034C20(D_8008A800[0] * 4);
    for (i = 0; i < D_8008A800[0]; i++) {
        v = func_80034C20(0x80);
        D_8008A8EC[i] = v;
    }
    D_8008A8F0 = 1;
    func_80049530();
    return 0;
}
