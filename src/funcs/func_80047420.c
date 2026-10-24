#include "common.h"

typedef struct {
    u8 pad0[8];
    s16 unk8;
    s16 unkA;
    u8 padC[4];
} Ent_80047420;

extern Ent_80047420 D_800AB794[];
extern s16 func_80047414(Ent_80047420 *e);

s32 func_80047420(u16 i) { return func_80047414(&D_800AB794[i]); }
