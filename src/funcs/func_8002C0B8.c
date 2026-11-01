#include "common.h"

typedef struct {
    s32 pad0;
    s32 x;
    s32 pad8;
    s32 z;
    s32 w;
    s32 pad14;
    s32 d;
} Box;

typedef struct Zone {
    u8 pad0[0x2C];
    Box *box;
    u8 pad30[0x68];
    struct Zone *next;
} Zone;

extern Zone *D_800A4F08[];

Zone *func_8002C0B8(s16 *pos) {
    Zone *z;

    for (z = D_800A4F08[0]; z != NULL; z = z->next) {
        Box *b = z->box;
        if (abs(pos[0] - b->x) <= b->w >> 1 && abs(pos[2] - b->z) <= b->d >> 1) {
            break;
        }
    }
    return z;
}
