#include "common.h"

extern s32 D_8008B0BC;
void func_80034B68(void);
void func_80033F78(s32);

void func_80033EEC(void) {
    if (D_8008B0BC != 0) {
        func_80034B68();
        func_80033F78(0);
    }
}
