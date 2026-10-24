#include "common.h"

u32 func_8004BE4C(u8 *p) {
    return p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
}
