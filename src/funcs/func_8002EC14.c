#include "common.h"

typedef struct {
    s16 x, y, z, w, h, d;
} Box_8002EC14;

s32 func_8002EC14(Box_8002EC14 *a, Box_8002EC14 *b) {
    if (abs(a->x - b->x) >= a->w + b->w || abs(a->z - b->z) >= a->d + b->d ||
        abs(a->y - b->y) >= a->h + b->h) {
        return 0;
    }
    return 1;
}
