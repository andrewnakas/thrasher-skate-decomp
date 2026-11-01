#include "common.h"

typedef struct { u32 f0; u32 f4; s32 (*f8)(u8 *, s32); } Rec;

extern u8 D_8006F834[];

s32 func_8002DD88(u8 *p, s32 arg1) {
    Rec *tab = (Rec *) D_8006F834;
    s32 (*fn)(u8 *, s32) = tab[p[3]].f8;

    return fn ? fn(p, arg1) : 0;
}
