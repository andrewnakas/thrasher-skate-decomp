#include "common.h"

extern void func_80059F0C();
extern void func_80059D88();

void func_8003AD7C(s32 a0, u8 a1, u8 a2, u8 a3, s32 a4) {
    func_80059F0C(a0, a1, a2, a3);
    if (a4) {
        func_80059D88(0);
    }
}
