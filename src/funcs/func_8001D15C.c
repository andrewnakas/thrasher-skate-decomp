#include "common.h"

extern s32 D_8008AE90;
extern s32 D_8008AE94;
extern s32 D_8008AE98;
s32 func_8001D540(s32, s32, s32);
s32 func_8001D530(s32, s32);

void func_8001D15C(s32 a) {
    s32 r;

    D_8008AE94 = a;
    r = func_8001D540(D_8008AE90, 0x52594C50, 1);
    D_8008AE98 = func_8001D530(D_8008AE90, r);
}
