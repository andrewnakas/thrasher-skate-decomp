#include "common.h"

typedef struct {
    s32 unk0;
    u8 pad4[0x2C];
} Ent_80057530;

extern Ent_80057530 D_800B2C7C[];
void func_80035060(s32);

void func_80057530(void) {
    Ent_80057530 *e;
    u32 i;

    e = D_800B2C7C;
    for (i = 0; i < 2; i++) {
        func_80035060(e[i].unk0);
    }
}
