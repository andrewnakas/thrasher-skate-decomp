#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 *unk8;
} Ent_8001D530;

s32 *func_8001D530(Ent_8001D530 *e, s32 i) {
    return &e->unk8[i];
}
