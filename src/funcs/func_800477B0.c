#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 unk2;
    u8 pad4[0xC];
} Ent_800477B0;

extern Ent_800477B0 D_800AB794[];

u16 func_800477B0(u16 i) { return D_800AB794[i].unk2; }
