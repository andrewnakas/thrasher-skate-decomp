#include "common.h"

extern u8 D_800A4F00[];

s32 func_8002AB64(s32 a0, s16 *a1) {
    s32 n;
    s32 i;
    u8 *rec;
    s32 dx;
    s32 dy;
    s32 d;

    if (a0 == -1) {
        return 0;
    }

    n = *(s32 *) (D_800A4F00 + 0x4C);
    rec = *(u8 **) (D_800A4F00 + 0x50);
    if (n <= 0) {
        return 0;
    }

    for (i = 0; i < n; i++, rec += 0x20) {
        if (a0 != -2 && rec[4] != a0) {
            continue;
        }
        if (a1 == 0) {
            return (s32) rec;
        }
        dx = a1[1] - *(s16 *) (rec + 6);
        d = dx * dx;
        dy = a1[5] - *(s16 *) (rec + 0xA);
        d = d + dy * dy;
        if (d < 0x7A12) {
            return (s32) rec;
        }
    }
    return 0;
}
