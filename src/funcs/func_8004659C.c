#include "common.h"

typedef struct {
    u8 pad0[0x10];
} Ent_8004659C;

extern Ent_8004659C D_800AB794[];

Ent_8004659C *func_8004659C(u16 i) { return &D_800AB794[i]; }
