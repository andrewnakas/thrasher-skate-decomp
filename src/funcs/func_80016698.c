#include "common.h"

extern u8 D_80089F9C;
extern s32 D_80089FA0;
s32 func_80016724(void);
s32 func_8005853C(void);
s32 func_80054BF4(void);

s32 func_80016698(void) {
    s32 st;
    s32 r;
    s32 v;

    if (D_80089FA0 == 0) {
        st = D_80089F9C;
        switch (st) {
        case 0:
            goto zero;
        case 1:
            r = func_8005853C();
            break;
        case 2:
            r = func_80054BF4();
            break;
        default:
            goto zero;
        }
        if (r == 0) {
            goto zero;
        }
        return 1;
    }
    v = func_80016724();
    if (v != 0) {
        return 1;
    }
zero:
    return 0;
}
