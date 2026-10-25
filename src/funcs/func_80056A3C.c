/* cflags: -O1 */
#include "common.h"

extern u8 D_80082FA4[];
extern u8 D_8008A160[];

s32 func_80056A3C(s32 idx) {
    s32 *t;
    s32 v;
    u32 i;

    t = (s32 *) D_80082FA4;
    i = idx & 0xFFFF;
    v = t[i];
    return v + *(s32 *) D_8008A160;
}
