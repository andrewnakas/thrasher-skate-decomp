#include "common.h"

typedef struct {
    s32 f00;
    u8 pad04[8];
    s32 f0C;
} Rec_800367F4;

extern u8 D_800A677C[];

s32 func_800367F4(s32 idx) {
    u8 *p;
    Rec_800367F4 *r;

    p = D_800A677C;
    p += (idx - 1) * 96;
    r = (Rec_800367F4 *) p;
    if (r->f00 != 0) {
        return r->f0C;
    }
    return -1;
}
