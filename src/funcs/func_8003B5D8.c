#include "common.h"

extern s32 D_8008B240;
extern s32 D_8008B244;
extern s32 D_8008B220;
extern s32 D_8008B224;
extern void SetGeomOffset(s32 x, s32 y);

void func_8003B5D8(s32 x, s32 y) {
    s32 ox = D_8008B240;
    s32 oy = D_8008B244;

    D_8008B220 = x;
    D_8008B224 = y;
    SetGeomOffset(x + ox, y + oy);
}
