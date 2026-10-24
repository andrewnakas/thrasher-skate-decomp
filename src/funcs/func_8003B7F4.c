#include "common.h"

extern s32 D_8008A6D8;
extern void func_8003B754(s32 *a0, s32 *a1);
extern void SetGeomScreen(s32 a0);
extern void func_8003B6EC(s32 a0, s32 a1);
extern void func_8003B60C(void);

void func_8003B7F4(s32 a0) {
    s32 x;
    s32 y;

    func_8003B754(&x, &y);
    D_8008A6D8 = a0;
    SetGeomScreen(a0);
    func_8003B6EC(x, y);
    func_8003B60C();
}
