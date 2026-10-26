#include "common.h"

typedef struct {
    s32 cost;
    u8 *ptr;
} ENTRY;

s32 func_8004CCA0(u8 *arg0, u32 arg1) {
    ENTRY *t;
    u8 *e;
    u8 n;
    u32 c;
    u8 type;

    n = arg0[1];
    for (c = 0; c < n; c++) {
        t = (ENTRY *)(arg0 + 0xC + c * 8);
        e = t->ptr;
        type = e[0];
        if (type == 0) {
            if (arg1 < e[1]) {
                break;
            }
            arg1 -= e[1];
        } else if (type == 1) {
            if (arg1 == 0) {
                break;
            }
            arg1 -= 1;
        } else if (type == 2) {
            if (arg1 == 0) {
                break;
            }
            arg1 -= 1;
        }
    }
    return c;
}
