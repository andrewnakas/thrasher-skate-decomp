#include "common.h"
u8 *func_80034824(u8 *arg0, u8 arg1) {
    s32 n;
    s32 i;
    u8 *p;
    i = 0;
    if (arg0[5] != 0) {
        n = arg0[5];
        p = *(u8 **)(arg0 + 8);
        do {
            if (*p == arg1) {
                return p;
            }
            i++;
            p += 8;
        } while (i < n);
    }
    return *(u8 **)(arg0 + 8);
}
