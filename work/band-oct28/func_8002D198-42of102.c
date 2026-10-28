#include "common.h"

extern s32 D_8008AFB4;
extern s32 D_8008AFB8;
extern s32 D_8008AFBC;
extern s16 D_8008AFC4;
extern s16 D_8008AFC6;
extern s16 D_8008AFC8;
extern s16 D_8008AFCC;
extern s16 D_8008AFCE;
extern s16 D_8008AFD0;

extern s32 func_80032C54(void);

s32 func_8002D198(s32 *p, s32 *out, s32 *tval) {
    s32 r1;
    s32 r2;
    s32 d;
    s32 t;

    r1 = p[0] * D_8008AFC4 + p[1] * D_8008AFC6 + p[2] * D_8008AFC8 + p[3];
    r2 = p[0] * D_8008AFCC + p[1] * D_8008AFCE + p[2] * D_8008AFD0 + p[3];
    if ((r1 ^ r2) >= 0) {
        return 0;
    }
    d = p[0] * D_8008AFB4 + p[1] * D_8008AFB8 + p[2] * D_8008AFBC;
    if (d == 0) {
        return 0;
    }
    t = -func_80032C54();
    if ((u32) t > 0x10000) {
        return 0;
    }
    if (out != 0) {
        out[0] = (D_8008AFC4 << 16) + t * D_8008AFB4;
        out[1] = (D_8008AFC6 << 16) + t * D_8008AFB8;
        out[2] = (D_8008AFC8 << 16) + t * D_8008AFBC;
    }
    *tval = t;
    return 1;
}
