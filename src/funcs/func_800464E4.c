#include "common.h"

extern s32 D_8008A7F8;
void func_800494A4(void);
void func_800471E8(void);

s32 func_800464E4(void) {
    func_800494A4();
    func_800471E8();
    D_8008A7F8 = 0;
    return 0;
}
