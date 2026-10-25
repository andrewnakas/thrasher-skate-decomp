#include "common.h"

s32 func_8002EFCC(s16 *p, s32 a1, s32 a2) {
    s32 i = (*(u16 *)p & 1) ? 3 : 2;
    s16 *v = *(s16 **)((u8 *)p + 0x1C);
    s16 *w;

    do {
        w = *(s16 **)((u8 *)p + 0x1C + i * 4);
        if ((w[0] - v[0]) * (a2 - v[2]) - (a1 - v[0]) * (w[2] - v[2]) < 0) {
            return 0;
        }
        v = w;
        i--;
    } while (i != -1);
    return 1;
}
