#include "common.h"

extern s32 func_800330A4(void *);
extern s32 func_80032C28(s32, s32);

typedef struct V_8002E4B4 {
    s16 x;
    s16 y;
    s16 z;
} V_8002E4B4;

typedef char *CP_8002E4B4;

void func_8002E4B4(V_8002E4B4 *a, V_8002E4B4 *b, V_8002E4B4 *c, V_8002E4B4 *out) {
    V_8002E4B4 *a0copy = (V_8002E4B4 *) (u32) (CP_8002E4B4) (u8 *) a;
    s32 d[3];
    s32 t[3];
    s32 sum;

    d[0] = (b->x - a0copy->x) << 16;
    d[1] = (b->y - a0copy->y) << 16;
    d[2] = (b->z - a0copy->z) << 16;
    func_800330A4(d);

    t[0] = a0copy->x - c->x;
    sum = t[0] * d[0];
    t[1] = a0copy->y - c->y;
    sum += t[1] * d[1];
    t[2] = a0copy->z - c->z;
    sum += t[2] * d[2];
    if (sum >= 0) {
        *out = *a;
        return;
    }

    t[0] = b->x - c->x;
    sum = t[0] * d[0];
    t[1] = b->y - c->y;
    sum += t[1] * d[1];
    t[2] = b->z - c->z;
    sum += t[2] * d[2];
    if (sum > 0) {
        out->x = b->x - (func_80032C28(d[0], sum) >> 16);
        out->y = b->y - (func_80032C28(d[1], sum) >> 16);
        out->z = b->z - (func_80032C28(d[2], sum) >> 16);
    } else {
        *out = *b;
    }
}
