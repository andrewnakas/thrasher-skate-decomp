#include "common.h"
s32 f(u8 *p, u32 len) {
    while (*(u32 *)(p + 8) < len) {
        p = *(u8 **)(p + 4);
        if (p == 0) return 0;
    }
    return 1;
}
