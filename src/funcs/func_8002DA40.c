#include "common.h"

typedef struct {
    u8 pad0[4];
    s16 min[3];
    s16 max[3];
    u8 pad10[0x20];
    s16 mid[3];
    s16 ext[3];
} Box8002DA40;

extern Box8002DA40 D_800A1C50;

void func_8002DA40(void) {
    Box8002DA40 *b = &D_800A1C50;

    b->mid[0] = (b->min[0] + b->max[0]) >> 1;
    b->ext[0] = abs(b->min[0] - b->mid[0]);

    b->mid[1] = (b->min[1] + b->max[1]) >> 1;
    b->ext[1] = abs(b->min[1] - b->mid[1]);

    b->mid[2] = (b->min[2] + b->max[2]) >> 1;
    b->ext[2] = abs(b->min[2] - b->mid[2]);
}
