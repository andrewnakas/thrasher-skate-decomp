#include "common.h"

extern u32 D_8008B3A8[4];

u32 func_8003AB20(u32 *p) {
    u32 *e = &p[D_8008B3A8[0] ^ 1];
    return e[1];
}
