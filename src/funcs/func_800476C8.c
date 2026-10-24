#include "common.h"

typedef struct {
    u8 pad0[8];
    s16 unk8;
    s16 unkA;
    u8 padC[4];
} Ent_800476C8;

extern Ent_800476C8 D_800AB794[];
extern s16 func_800476A8(Ent_800476C8 *e);

s32 func_800476C8(u16 i) { return func_800476A8(&D_800AB794[i]); }
