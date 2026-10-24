#include "common.h"

typedef struct {
    u16 unk0;
    u8 pad2[0xE];
} Ent_80047804;

extern Ent_80047804 D_800AB794[];

void func_80047804(u16 i, u32 v) {
    D_800AB794[i].unk0 = (D_800AB794[i].unk0 & 0xFF9F) | ((v & 3) << 5);
}
