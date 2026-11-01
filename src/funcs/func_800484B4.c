#include "common.h"

typedef struct {
    s16 x, y, w, h;
} Rect16;

extern u16 D_800AE794[];

s32 func_800484B4(s16 w, s32 a1, s32 a2, Rect16 *r) {
    s32 n = 0x100 / w;
    s32 mask = (1 << (w / 16)) - 1;
    s32 row;
    s32 j;
    s32 k;

    for (row = 255; row >= 0; row--) {
        s32 bits = D_800AE794[row];
        s32 m = mask;
        for (j = n - 1; j >= 0; j--, m <<= 1) {
            if (!(bits & m)) {
                D_800AE794[row] |= m;
                k = j + 1;
                r->x = ((n - k) << 4) + 0x300;
                r->y = row + 0x100;
                r->w = w;
                r->h = 1;
                return 1;
            }
        }
    }
    return 0;
}
