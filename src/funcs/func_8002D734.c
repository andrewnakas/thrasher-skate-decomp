#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec_8002D734;

extern s32 func_80035E40(s32, s32);

void func_8002D734(Vec_8002D734 *a, Vec_8002D734 *b, Vec_8002D734 *out, s32 w) {
    s32 h;
    s32 r;

    if (a->x != b->x) {
        h = (w - b->x) << 12;
        r = func_80035E40(h, (a->x - b->x) << 12);
    } else {
        h = 0;
        r = func_80035E40((w - b->z) << 12, (a->z - b->z) << 12);
    }
    out->x = b->x + (h >> 12);
    out->y = b->y + (((a->y - b->y) * r) >> 12);
    out->z = b->z + (((a->z - b->z) * r) >> 12);
}
