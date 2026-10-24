#include "common.h"

extern void func_80059F9C();
extern void func_80059D88();

void func_8003AE98(s32 a0, s32 a1, s32 a2) {
    func_80059F9C(a0, a1, a2);
    if (a2) {
        func_80059D88(0);
    }
}
