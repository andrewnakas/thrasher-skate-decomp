#include "common.h"

typedef struct {
    u8 pad0[0xD];
    u8 unkD;
    u8 padE[2];
} Ent_8004774C;

extern Ent_8004774C D_800AB794[];
extern s16 func_8004772C(Ent_8004774C *e);

s32 func_8004774C(u16 i) { return func_8004772C(&D_800AB794[i]); }
