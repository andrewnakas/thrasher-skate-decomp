#include "common.h"

extern u8 D_800B066C[];
extern u8 D_80010888[];
extern s8 D_8008A9A0[];

typedef struct Ent_8004FB78 {
    u8 pad0[0x10];
    u32 count;
} Ent_8004FB78;

s32 func_8004FB78(u16 a0) {
    u8 *r;

    if (a0 >= 0x10) {
        printf(D_80010888, D_8008A9A0, 0x1C6);
        exit(1);
    }

    r = D_800B066C + a0 * 0x10;
    if (!(*(u32 *) r & 1)) {
        printf(D_80010888, D_8008A9A0, 0x1C8);
        exit(1);
    }

    return ((Ent_8004FB78 *) *(u32 *) (r + 4))->count;
}
