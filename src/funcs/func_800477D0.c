#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 unk2;
    u8 pad4[0xA];
    u8 unkE;
} Ent_800477D0;

extern Ent_800477D0 D_800AB794[];

void func_800477D0(u16 src, u16 dst) {
    D_800AB794[dst].unk2 = D_800AB794[src].unk2;
    D_800AB794[dst].unkE = D_800AB794[src].unkE;
}
