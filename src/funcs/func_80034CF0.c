#include "common.h"

extern u32 D_8008A560;
extern s32 D_8008B0F4;

s32 func_80034CF0(s32 n) {
    s32 sz = (n + 3) & ~3;
    s32 top = D_8008B0F4 - sz;
    s32 newtop = top - 4;

    if (D_8008A560 < (u32) newtop) {
        *(s32 *) (top - 4) = sz;
        D_8008B0F4 = newtop;
        return top;
    }
    return 0;
}
