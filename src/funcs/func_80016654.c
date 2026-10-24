#include "common.h"

extern u8 D_80089FA4;

s32 func_80054508(void);
u32 func_80016724(void);

s32 func_80016654(void) {
    D_80089FA4 = 1;
    if (func_80054508() != 0) {
        return 1;
    }
    return func_80016724() != 0;
}
