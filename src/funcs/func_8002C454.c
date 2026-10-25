#include "common.h"

s32 func_8002C454(u16 *p) {
    u16 v = p[0];
    s32 r;

    if (v & 2) {
        if (v & 1) {
            r = p[0x1A];
        } else {
            r = p[0x17];
        }
    } else {
        r = -1;
    }
    return r;
}
