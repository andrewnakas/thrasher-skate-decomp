#include "common.h"

extern u8 D_8008AEE4;

u32 func_8002050C(u32 i, u8 id)
{
    u8 *e;
    u8 *p;
    s32 n;

    e = (u8 *) ((u32 *) (&D_8008AEE4))[i];
    for (n = *(s32 *) e - 1; n != -1; n--) {
        p = (u8 *) (*(u32 *) (e + 8) + n * 16);
        if (id == p[0]) {
            return (u8) n;
        }
    }
    return 0;
}
