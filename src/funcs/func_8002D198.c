#include "common.h"

extern s16 D_8008AFC4[4];
extern s16 D_8008AFCC[4];
extern s32 D_8008AFB4;
extern s32 D_8008AFB8;
extern s32 D_8008AFBC;

s32 func_80032C54(s32, s32);

s32 func_8002D198(s32 *pl, s32 *out, s32 *pt) {
    s32 d0;
    s32 d1;
    s32 den;
    s32 m;
    s32 *p;

    d0 = pl[0] * D_8008AFC4[0] + pl[1] * D_8008AFC4[1] + pl[2] * D_8008AFC4[2] + pl[3];
    d1 = pl[0] * D_8008AFCC[0] + pl[1] * D_8008AFCC[1] + pl[2] * D_8008AFCC[2] + pl[3];
    if ((d0 ^ d1) >= 0) {
        return 0;
    }
    den = pl[0] * D_8008AFB4 + pl[1] * D_8008AFB8 + pl[2] * D_8008AFBC;
    if (den == 0) {
        return 0;
    }
    den = -func_80032C54(d0, den);
    if ((u32) den > 0x10000) {
        return 0;
    }
    if (out != NULL) {
        m = den * D_8008AFB4;
        *out = (D_8008AFC4[0] << 16) + m;
        m = den * D_8008AFB8;
        p = out + 1;
        *p = (D_8008AFC4[1] << 16) + m;
        m = den * D_8008AFBC;
        p = out + 2;
        *p = (D_8008AFC4[2] << 16) + m;
    }
    *pt = den;
    return 1;
}
