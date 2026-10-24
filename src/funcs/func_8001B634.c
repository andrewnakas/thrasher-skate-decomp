#include "common.h"

extern s32 D_8008AE18;
extern u16 D_8008AE14;
extern u16 D_8008AE16;

void func_80027B64(s32, s32, s32, s32);

s32 func_8001B634(void) {
    func_80027B64(*(s32 *)(D_8008AE18 + 4), 0, D_8008AE14, D_8008AE16);
    return 0;
}
