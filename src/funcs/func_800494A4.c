#include "common.h"

extern s32 D_8008A804;
extern s32 *D_8008A8EC;
extern s32 D_8008A8F0;

void *func_80034C20(s32);
void func_80049530(void);

#define D_8008A800 *(&D_8008A804 - 1)

s32 func_800494A4(void) {
    s32 i;

    D_8008A8EC = func_80034C20(D_8008A800 * 4);
    for (i = 0; i < D_8008A800; i++) {
        D_8008A8EC[i] = (s32) func_80034C20(0x80);
    }
    D_8008A8F0 = 1;
    func_80049530();
    return 0;
}
