#include "common.h"

extern s32 D_8008A6D8;
extern void func_8003B754(s32 *px, s32 *py);
extern void SetGeomScreen(s32 h);
extern void func_8003B6EC(s32 a, s32 b);
extern void func_8003B60C(void);

void func_8003B7F4(s32 v) {
    s32 a;
    s32 b;

    func_8003B754(&a, &b);
    D_8008A6D8 = v;
    SetGeomScreen(v);
    func_8003B6EC(a, b);
    func_8003B60C();
}
