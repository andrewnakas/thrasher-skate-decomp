#include "common.h"

typedef struct {
    u8 pad0[0x24];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
} Ctx_8004BC50;

s32 func_8004B448(Ctx_8004BC50 *);

s32 func_8004BC50(Ctx_8004BC50 **ctx) {
    Ctx_8004BC50 *c;

    c = ctx[0];
    c->unk28 = c->unk24 + (s32) ctx[2];
    c->unk2C = func_8004B448(c) << 12;
    return 1;
}
