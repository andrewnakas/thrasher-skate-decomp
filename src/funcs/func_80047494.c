#include "common.h"

typedef struct {
    u8 pad0[8];
    s16 unk8;
} Ent_80047494;

s32 func_80047494(Ent_80047494 *e, s16 v) {
    e->unk8 = v;
    return v;
}
