#include "common.h"

extern s32 D_8008AE78;
void func_80036A54(s32);

s32 func_8001C1B0(void) {
    if (D_8008AE78 != 0) {
        func_80036A54(D_8008AE78);
        D_8008AE78 = 0;
    }
    return 0;
}
