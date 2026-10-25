#include "common.h"

s32 func_8001D340(u16 *arg0, s32 count, u16 value, u16 *out) {
    s32 i;

    i = count - 1;
    if (count != 0) {
        for (;;) {
            if (*arg0 == value) {
                out[1] = arg0[1];
                return 1;
            }
            if (--i == -1) {
                break;
            }
            arg0 += 2;
        }
    }
    return 0;
}
