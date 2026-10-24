#include "common.h"

extern s32 func_80033E78(s32 *v);

s32 func_80043200(u8 *a0, s16 *a1) {
    s32 d[2];
    s32 n = a0[1];
    s32 k = 1;

    d[0] = a1[4] - a1[0];
    d[1] = a1[6] - a1[2];

    if (func_80033E78(d) < n * 2) {
        a1[0] = (a1[0] + a1[4]) >> k;
        a1[2] = (a1[2] + a1[6]) >> k;
        return k;
    }

    return 0;
}
