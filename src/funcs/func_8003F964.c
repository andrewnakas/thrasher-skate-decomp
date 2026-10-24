/* cflags: -mno-split-addresses */
#include "common.h"

typedef struct { s32 v; s32 pad1; s32 pad2; } Word12;

extern Word12 D_80089FE4;
extern Word12 D_8008A008;
extern s32 D_8008A79C;
extern s32 func_80036E1C(s32, s32);
extern s32 func_8003682C(s32);

s32 func_8003F964(void) {
    s32 r = func_8003682C(func_80036E1C(D_80089FE4.v, D_8008A008.v));

    D_8008A79C = r;
    return r == 0;
}
