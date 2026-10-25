#include "common.h"

void func_8001D9C8(s32, s32 *, s32 *);

s32 func_8001F374(s32 *p) {
    s32 v[2];
    s32 *n = (s32 *) p[0x18];

    if (n != 0) {
        func_8001D9C8(n[0x12], n, v);
    }
    return v[0];
}
