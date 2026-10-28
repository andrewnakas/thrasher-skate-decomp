#include "common.h"

typedef struct {
    u8 pad0[0x44];
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    u8 pad1[0x8C - 0x50];
} Blk_8002221C;

typedef struct {
    u32 unk0;
    u32 unk4;
    Blk_8002221C *unk8;
    Blk_8002221C *unkC;
    s32 unk10;
    u8 pad0[0x20 - 0x14];
} Rec_8002221C;

typedef struct {
    u32 unk0;
    Blk_8002221C blk[20];
    u32 unkAF4;
    Rec_8002221C rec[1];
} O_8002221C;

extern s32 func_80033268(s32 *v);

s32 func_8002221C(O_8002221C *o, s32 i, s32 j, s32 k) {
    Rec_8002221C *r;
    s32 v[3];

    r = &o->rec[o->unkAF4];

    r->unk8 = &o->blk[i];
    r->unk0 = 0;
    r->unk4 = k;
    r->unkC = &o->blk[j];
    v[0] = r->unk8->unk44 - r->unkC->unk44;
    v[1] = r->unk8->unk48 - r->unkC->unk48;
    v[2] = r->unk8->unk4C - r->unkC->unk4C;
    r->unk10 = func_80033268(v);
    return o->unkAF4++;
}
