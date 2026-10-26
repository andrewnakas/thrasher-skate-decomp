#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec_8002D81C;

extern s32 func_80035E40(s32, s32);

void func_8002D81C(Vec_8002D81C *a, Vec_8002D81C *b, Vec_8002D81C *out, s32 w) {
    s32 h;
    s32 r;

    if (a->z != b->z) {
        h = (w - b->z) << 12;
        r = func_80035E40(h, (a->z - b->z) << 12);
    } else {
        h = 0;
        r = func_80035E40((w - b->x) << 12, (a->x - b->x) << 12);
    }
    out->z = b->z + (h >> 12);
    out->y = b->y + (((a->y - b->y) * r) >> 12);
    out->x = b->x + (((a->x - b->x) * r) >> 12);
}
