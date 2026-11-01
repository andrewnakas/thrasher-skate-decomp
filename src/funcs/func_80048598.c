/* Table base in a block-scoped pointer assigned before the index: its la is emitted (and scheduled) first. */
#include "common.h"

typedef struct {
    s16 x, y, w, h;
} Rect16;

extern u16 D_800AE794[];

s32 func_80048598(s16 w, s16 clut, s32 unused, Rect16 *r) {
    s32 x = (clut & 0x3F) << 4;
    s32 y = clut >> 6;
    u16 mask = (1 << (w / 16)) - 1;
    u16 *p;
    u32 bits;
    s32 i;

    bits = mask << ((x - 0x300) / 16);
    {
        u16 *b = D_800AE794;
        i = y - 0x100;
        p = &b[i];
    }
    if (!(*p & bits)) {
        *p |= bits;
        r->x = x;
        r->y = y;
        r->w = w;
        r->h = 1;
        return 1;
    }
    return 0;
}
