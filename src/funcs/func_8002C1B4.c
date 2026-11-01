#include "common.h"

typedef struct S_8002C1B4 {
    u8 pad0[4];
    s32 f4;
    u8 pad8[4];
    s32 fC;
    s32 f10;
    u8 pad14[4];
    s32 f18;
    u8 pad1C[0x7C];
    struct S_8002C1B4 *next;
} S_8002C1B4;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} In_8002C1B4;

extern s32 D_800A4F08[3];
extern S_8002C1B4 *D_8009CE20[];

S_8002C1B4 **func_8002C1B4(In_8002C1B4 *a0, s32 a1) {
    s16 v[3];
    s32 key;
    S_8002C1B4 *n;
    S_8002C1B4 *e;
    S_8002C1B4 **out;

    n = (S_8002C1B4 *) D_800A4F08[0];
    v[0] = a0->x >> 16;
    v[1] = a0->y >> 16;
    key = a1 >> 16;
    v[2] = a0->z >> 16;
    out = D_8009CE20;
    for (; n != 0; n = n->next) {
        e = *(S_8002C1B4 **) ((u8 *) n + 0x2C);
        if (abs(v[0] - e->f4) > (e->f10 >> 1) + key) {
            continue;
        }
        if (abs(v[2] - e->fC) > (e->f18 >> 1) + key) {
            continue;
        }
        *out++ = n;
    }
    *out = 0;
    return D_8009CE20;
}
