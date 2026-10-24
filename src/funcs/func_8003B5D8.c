#include "common.h"

extern s32 D_8008B220;
extern s32 D_8008B224;
extern s32 D_8008B240;
extern s32 D_8008B244;
extern void SetGeomOffset();

void func_8003B5D8(s32 a0, s32 a1) {
    D_8008B220 = a0;
    D_8008B224 = a1;
    SetGeomOffset(a0 + D_8008B240, a1 + D_8008B244);
}
