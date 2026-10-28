#include "common.h"

typedef struct {
    u8 pad0[4];
    s32 f4;
    u8 pad8[4];
    s32 fC;
    s32 f10;
    u8 pad14[4];
    s32 f18;
} Rec_C148;

s32 func_8002C148(u8 *o, s32 x, s32 y) {
    Rec_C148 *r = *(Rec_C148 **) (o + 0x2C);
    s32 d;

    d = x - r->f4;
    if (d < 0) {
        d = -d;
    }
    if ((r->f10 >> 1) < d) {
        return 0;
    }
    d = y - r->fC;
    if (d < 0) {
        d = -d;
    }
    if ((r->f18 >> 1) < d) {
        return 0;
    }
    return 1;
}
