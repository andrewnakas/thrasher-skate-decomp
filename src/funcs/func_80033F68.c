#include "common.h"

extern s32 D_8008B0BC;

s32 func_80033F68(s32 v) {
    s32 old = D_8008B0BC;

    D_8008B0BC = v;
    return old;
}
