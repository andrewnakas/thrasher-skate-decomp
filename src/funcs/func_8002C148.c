#include "common.h"

typedef struct {
    s32 unk0;
    s32 x;
    s32 unk8;
    s32 z;
    s32 w;
    s32 unk14;
    s32 d;
} Box_8002C148;

typedef struct {
    u8 pad[0x2C];
    Box_8002C148 *box;
} Obj_8002C148;

extern s32 abs(s32);

/* point (x, z) inside the object's box footprint (half extents w/2, d/2) */
s32 func_8002C148(Obj_8002C148 *o, s32 x, s32 z) {
    Box_8002C148 *b = o->box;

    if (abs(x - b->x) <= (b->w >> 1) && abs(z - b->z) <= (b->d >> 1)) {
        return 1;
    }
    return 0;
}
