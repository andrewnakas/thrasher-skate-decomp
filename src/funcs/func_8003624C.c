#include "common.h"

extern s32 D_8008A594;
s32 func_80037A8C(void);

s32 func_8003624C(void) {
    if (D_8008A594 == 0) {
        if (func_80037A8C() != 0) {
            return 1;
        }
        D_8008A594 = 1;
    }
    return 0;
}
