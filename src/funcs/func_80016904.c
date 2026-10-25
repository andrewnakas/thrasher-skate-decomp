#include "common.h"

void func_8003A4A0(s32, s32, s32, s32, s32, s32);
s32 func_8003A578(void);

s32 func_80016904(s32 **arg0) {
    s32 *p;
    s32 a;

    for (;;) {
        p = *arg0++;
        if (!p) {
            break;
        }
        a = p[0];
        func_8003A4A0(a, p[1], p[2], p[3], p[4], p[5]);
    }
    func_8003A578();
    return 0;
}
