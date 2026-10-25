#include "common.h"

extern u8 *func_8002DF04(u8 *a, u8 *b);

s32 func_8002EBA0(u8 *a, u8 *b, u32 *out) {
    u8 *r;

    memset(out, 0, 8);
    r = func_8002DF04(a, b);
    if (r != 0) {
        out[0] = 1;
        out[1] = *(u32 *) (r + 0x3C);
        return 1;
    }
    return 0;
}
