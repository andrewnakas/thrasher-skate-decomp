#include "common.h"

typedef struct { u32 w[4]; } Blk;

extern u8 *D_8008AEC4;

s32 func_8001D804(u16 a0, u8 *a1) {
    u8 *base = D_8008AEC4;
    Blk *s = (Blk *) a1;
    Blk *e = (Blk *) (a1 + 0x40);
    Blk *d = (Blk *) (base + a0 * 0x44);

    do {
        *d = *s;
        s++;
        d++;
    } while (s != e);

    d->w[0] = s->w[0];
    return 0;
}
