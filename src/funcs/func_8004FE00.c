#include "common.h"

extern u8 D_800B066C[];
extern u8 D_80010888[];
extern s8 D_8008A9A0[];

typedef struct Ent_8004FE00 {
    u8 pad0[0x18];
    u32 count;
    u8 *data;
} Ent_8004FE00;

u8 *func_8004FE00(u16 a0, u32 a1) {
    u8 *r;
    Ent_8004FE00 *e;

    if (a0 >= 0x10) {
        printf(D_80010888, D_8008A9A0, 0x254);
        exit(1);
    }

    r = D_800B066C + a0 * 0x10;
    if (!(*(u32 *) r & 1)) {
        printf(D_80010888, D_8008A9A0, 0x256);
        exit(1);
    }

    e = *(Ent_8004FE00 **) (r + 4);
    if (a1 >= e->count) {
        printf(D_80010888, D_8008A9A0, 0x258);
        exit(1);
    }

    return e->data + a1 * 12;
}
