#include "common.h"

extern s32 D_8008B0C0;
extern s32 D_8008B0C4;
void func_80034874(void);

void func_80034B68(void) {
    D_8008B0C0 = 1;
    D_8008B0C4 = 2;
    func_80034874();
}
