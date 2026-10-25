#include "common.h"

extern void func_8001D4DC(u8 *a, s32 b, s32 c);
extern s32 func_8001D540(u8 *a, u8 *b, s32 c);
extern s32 func_8001D530(u8 *a, s32 b);

s32 func_8001D5B0(u8 *a0, u8 *a1, s32 a2) {
    s32 r;

    if (a2 != 0) {
        func_8001D4DC(a0, 0, 0);
    }
    r = func_8001D540(a0, a1, a2);
    if (r == -1) {
        return 0;
    }
    return func_8001D530(a0, r);
}
