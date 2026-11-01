#include "common.h"

typedef struct {
    u8 pad0[4];
    s32 x;
    u8 pad8[4];
    s32 z;
    s32 w;
    u8 pad14[4];
    s32 d;
} Box_8002B674;

typedef struct {
    u8 pad0[0x2C];
    Box_8002B674 *box;
} Obj_8002B674;

typedef struct {
    u8 pad0[0xA];
    s16 x;
    u8 padC[2];
    s16 z;
    u8 pad10[0x26];
    s16 rx;
    u8 pad38[2];
    s16 rz;
} Ent_8002B674;

s32 func_8002B674(Ent_8002B674 *e, Obj_8002B674 *o) {
    Box_8002B674 *b = o->box;

    if (abs(e->x - b->x) < b->w / 2 + e->rx && abs(e->z - b->z) < b->d / 2 + e->rz) {
        return 1;
    }
    return 0;
}
