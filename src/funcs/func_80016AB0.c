#include "common.h"

extern s32 D_8008AD64;

void func_80036A54(s32);
void func_80038784(void);

void func_80016AB0(void) {
    if (D_8008AD64 != 0) {
        func_80036A54(D_8008AD64);
    }
    D_8008AD64 = 0;
    func_80038784();
}
