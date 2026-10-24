#include "common.h"

extern u32 D_8008B228;
extern void func_8003B6EC(s32 a, s32 b);

void func_8003B794(void) {
    s32 v = 0x7FFF;

    D_8008B228 = 1;
    func_8003B6EC(v, v);
}
