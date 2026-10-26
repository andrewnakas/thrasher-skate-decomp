#include "common.h"

typedef struct {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
} Rec40;

typedef struct {
    s32 g00;
    s32 g04;
    s32 g08;
    s32 g0C;
    s32 g10;
    s32 g14;
    s32 g18;
    s32 g1C;
    s32 g20;
} Src;

typedef struct {
    u8 pad[0xFF8];
    s32 count;
    Rec40 recs[1];
} Hdr;

s32 func_800223AC(Hdr *arg0, Src *arg1) {
    Rec40 *e;

    e = &arg0->recs[arg0->count];
    e->f00 = 7;
    e->f04 = arg1->g08;
    e->f08 = arg1->g0C;
    e->f0C = arg1->g10;
    e->f10 = arg1->g14;
    e->f14 = arg1->g18;
    e->f24 = arg1->g20;
    e->f18 = arg1->g1C;
    e->f1C = arg1->g00;
    e->f20 = arg1->g04;
    return arg0->count++;
}
