#include "common.h"

typedef struct {
    u16 flags;
    u8 unk2;
    u8 pad3[0x21];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad30[8];
    s32 unk38;
    void *unk3C;
    s32 unk40;
} Ent_8004BBB8;

s32 func_8004B448(u8 *);

s32 func_8004BBB8(u8 *p) {
    Ent_8004BBB8 *e;
    s32 v;
    s32 r;

    e = (Ent_8004BBB8 *) *(void **) p;
    if (p[8] == 1) {
        if (!(e->flags & 0x800)) {
            e->unk2 = 0;
        } else {
            v = e->unk24;
            e->unk38 = 0;
            e->unk28 = v;
            r = func_8004B448((u8 *) e);
            e->unk2C = r << 12;
        }
    }
    if (e->unk3C != 0) {
        ((void (*)(s32, u8, u8)) e->unk3C)(e->unk40, p[8], p[9]);
    }
    return 1;
}
