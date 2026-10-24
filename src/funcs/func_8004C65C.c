#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 unk8;
} Ent_8004C65C;

/* gp-relative address (addiu $v1, $gp): the original declared this small,
   so it lived in .sdata; the 12-byte stride comes from the cast, not the size. */
extern u8 D_8008B408[4];
extern char D_800107F8[];
extern char D_8008A950[];
s32 func_80051574(s32, s32 *);

s32 func_8004C65C(u8 id) {
    Ent_8004C65C *e;
    s32 r;
    s32 t;

    e = &((Ent_8004C65C *) D_8008B408)[id];
    if (e->unk8 == 0) {
        printf(D_800107F8, D_8008A950, 0x1AE);
        exit(1);
    }
    r = func_80051574(e->unk8, &t);
    if (r == 0) {
        r = t;
    }
    return r;
}
