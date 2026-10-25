#include "common.h"

void func_8002CF94(u32 a0, s32 a1);

void func_8002CF58(u8 *p, s32 a1) {
    u32 v = *(u32 *) (p + 4);

    if (v != 0) {
        if (a1 < 0) {
            a1 = -a1;
        }
        func_8002CF94(v, a1);
    }
}
