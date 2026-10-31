#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

void func_80026DAC(Vec3 *a, Vec3 *b, Vec3 *o) {
    o->x = a->x - b->x;
    o->y = a->y - b->y;
    o->z = a->z - b->z;
}
