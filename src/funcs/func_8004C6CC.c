#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 unk8;
} Ent_8004C6CC;

/* gp-relative address (addiu $v1, $gp): declared small, so it lived in .sdata. */
extern u8 D_8008B408[4];
extern char D_800107F8[];
extern char D_8008A950[];
s32 func_80051844(s32, u8, s32);

s32 func_8004C6CC(u8 id, u8 a) {
    Ent_8004C6CC *e;
    s32 r;

    e = &((Ent_8004C6CC *) D_8008B408)[id];
    if (e->unk8 == 0) {
        printf(D_800107F8, D_8008A950, 0x1C5);
        exit(1);
    }
    r = func_80051844(e->unk8, a & 0xFF, 0);
    if (r == 0) {
        return 0;
    }
    return r;
}
