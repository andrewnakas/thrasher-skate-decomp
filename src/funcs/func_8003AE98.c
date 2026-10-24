#include "common.h"

extern void func_80059F9C(s32 a, s32 b, s32 c);
extern void func_80059D88(s32 v);

void func_8003AE98(s32 a, s32 b, s32 c) {
    func_80059F9C(a, b, c);
    if (c != 0) {
        func_80059D88(0);
    }
}
