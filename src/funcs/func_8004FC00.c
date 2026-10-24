#include "common.h"

extern u8 D_800B066C[];
extern u8 D_80010888[];
extern s8 D_8008A9A0[];

typedef struct Ent_8004FC00 {
    u8 pad0[0x20];
    u32 data;
} Ent_8004FC00;

s32 func_8004FC00(u16 a0) {
    u8 *r;

    if (a0 >= 0x10) {
        printf(D_80010888, D_8008A9A0, 0x1EA);
        exit(1);
    }

    r = D_800B066C + a0 * 0x10;
    if (!(*(u32 *) r & 1)) {
        printf(D_80010888, D_8008A9A0, 0x1EC);
        exit(1);
    }

    return ((Ent_8004FC00 *) *(u32 *) (r + 4))->data;
}
