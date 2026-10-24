#include "common.h"

typedef struct {
    u32 unk0;
    u16 unk4;
    u16 unk6;
} Ent_8003F9F8;

extern Ent_8003F9F8 D_800A964C[];

void func_8003F9F8(u32 a0, s32 a1) {
    Ent_8003F9F8 *e;

    for (e = D_800A964C; e->unk0 != 0; e++) {
    }
    e->unk4 = a1;
    e->unk0 = a0;
}
