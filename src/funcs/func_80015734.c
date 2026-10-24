#include "common.h"

extern s32 D_80089F68;

void func_800162FC(void);

void func_80015734(void) {
    if (D_80089F68 != 0) {
        func_800162FC();
        D_80089F68 = 0;
    }
}
