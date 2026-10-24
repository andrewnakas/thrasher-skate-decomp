#include "common.h"

s32 func_8004BE4C(u8 *);

s32 func_8004B448(u8 *a0) {
    u8 *p;
    u32 b;
    u32 v;

    p = *(u8 **) (a0 + 0x28);
    b = *p;
    p++;
    v = b & 7;
    if (v < 3) {
        return 0;
    }
    if (v < 6) {
        return *p;
    }
    return func_8004BE4C(p);
}
