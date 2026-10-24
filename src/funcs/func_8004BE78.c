#include "common.h"

typedef struct {
    u8 unk0;
    u8 pad1[7];
    s32 unk8;
} Ent_8004BE78;

extern s32 D_8008A94C;
extern s32 D_8008B420;
extern s32 D_8008B424;
extern s32 D_8008B428;
extern u8 D_8008B408[4];
extern Ent_8004BE78 D_800AF8E4[];
extern char D_800107F8[];
extern char D_8008A950[];
s32 func_8004BE78(void) {
    Ent_8004BE78 *e;
    u8 *p;
    u32 i;

    if (D_8008A94C != 0) {
        printf(D_800107F8, D_8008A950, 0x5A);
        exit(1);
    }
    i = 0;
    p = D_8008B408;
    do {
        ((Ent_8004BE78 *) p)->unk8 = 0;
        i++;
        p += 12;
    } while (i < 2);

    for (i = 0; i < 0x20; i++) {
        D_800AF8E4[i].unk0 = 0xFF;
        D_800AF8E4[i].unk8 = 0;
    }
    D_8008B420 = 0;
    D_8008B424 = 0;
    D_8008B428 = 0;
    D_8008A94C = 1;
    return 0;
}
