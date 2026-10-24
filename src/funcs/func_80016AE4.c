#include "common.h"

extern s32 D_8008AD64;

void func_80036A54(s32);
s32 func_8003682C(s32);

void func_80016AE4(s32 arg0) {
    if (D_8008AD64 != 0) {
        func_80036A54(D_8008AD64);
    }
    D_8008AD64 = 0;
    D_8008AD64 = func_8003682C(arg0);
}
