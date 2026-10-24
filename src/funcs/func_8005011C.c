#include "common.h"

extern u8 D_800B066C[];
extern u8 D_80010888[];
extern s8 D_8008A9A0[];

typedef struct {
    u8 pad0[0x40];
    u32 count;
    s32 *data;
} Ent_8005011C;

s32 func_8005011C(u16 a0, u32 a1) {
    u8 *r;
    Ent_8005011C *e;

    if (a0 >= 0x10) {
        printf(D_80010888, D_8008A9A0, 0x2A9);
        exit(1);
    }

    r = D_800B066C + a0 * 0x10;
    if (!(*(u32 *) r & 1)) {
        printf(D_80010888, D_8008A9A0, 0x2AB);
        exit(1);
    }

    e = *(Ent_8005011C **) (r + 4);
    if (a1 >= e->count) {
        printf(D_80010888, D_8008A9A0, 0x2AD);
        exit(1);
    }

    return e->data[a1];
}
