#include "common.h"

typedef struct {
    u8 pad0[0xA];
    s16 unkA;
} Ent_800474A4;

s32 func_800474A4(Ent_800474A4 *e, s16 v) {
    e->unkA = v;
    return v;
}
