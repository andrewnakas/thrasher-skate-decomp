#include "common.h"

s32 abs(s32);

typedef struct {
    u8 pad0[0xA];
    s16 x;
    u8 padC[2];
    s16 z;
    u8 pad10[0x26];
    s16 rx;
    u8 pad38[2];
    s16 rz;
} Obj8002B5DC;

typedef struct {
    s32 pad0;
    s32 x;
    s32 pad8;
    s32 z;
    s32 w;
    s32 pad14;
    s32 d;
} Box8002B5DC;

typedef struct {
    u8 pad[0x2C];
    Box8002B5DC *box;
} Hold8002B5DC;
s32 func_8002B5DC(Obj8002B5DC *o, Hold8002B5DC *h) {
    Box8002B5DC *b = h->box;

    if (abs(o->x - b->x) > b->w / 2 - o->rx || abs(o->z - b->z) > b->d / 2 - o->rz) {
        return 0;
    }
    return 1;
}
