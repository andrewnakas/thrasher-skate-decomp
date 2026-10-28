#include "common.h"

typedef struct { s32 f0; s32 f4; s32 f8; } Vec3;

void func_80032FF4(Vec3 *a, Vec3 *b) {
    s32 x = a->f0 + b->f0;
    s32 y = a->f4 + b->f4;
    s32 z = a->f8 + b->f8;

    a->f0 = x;
    a->f4 = y;
    a->f8 = z;
}
