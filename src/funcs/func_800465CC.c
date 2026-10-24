#include "common.h"

typedef struct {
    u32 v[4];
} Ent_800465CC;

extern Ent_800465CC D_800AB794[];

void func_800465CC(u16 src, u16 dst) { D_800AB794[dst] = D_800AB794[src]; }
