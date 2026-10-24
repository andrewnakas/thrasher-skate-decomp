#include "common.h"

typedef struct {
    s32 a;
    s32 b;
} Pair_80057988;

typedef struct {
    u8 pad0[4];
    s32 unk4;
    s32 unk8;
    s16 unkC;
    u8 padE[2];
    Pair_80057988 p[2];
    Pair_80057988 q[2];
} Rec_80057988;

extern Rec_80057988 D_800B2C7C[];

void func_80057988(void) {
    Rec_80057988 *r;
    u32 i;
    u32 j;

    for (j = 0; j < 2; j++) {
        r = &D_800B2C7C[j];
        r->unk4 = 0;
        r->unk8 = 0;
        r->unkC = 0;
        for (i = 0; i < 2; i++) {
            r->p[i].a = 0;
            r->p[i].b = 0;
            r->q[i].a = 0;
            r->q[i].b = 0;
        }
    }
}
