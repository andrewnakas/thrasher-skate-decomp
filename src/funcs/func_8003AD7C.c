#include "common.h"

extern void func_80059F0C(s32 a, u8 b, u8 c, u8 d);
extern void func_80059D88(s32 v);

void func_8003AD7C(s32 a, u8 b, u8 c, u8 d, s32 flag) {
    func_80059F0C(a, b, c, d);
    if (flag != 0) {
        func_80059D88(0);
    }
}
