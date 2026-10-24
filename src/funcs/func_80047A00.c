#include "common.h"

typedef struct {
    u8 pad0[0x14];
    u32 unk14;
} Ent_80047A00;

void func_80047A00(Ent_80047A00 *e) { e->unk14 = 0; }
