#include "common.h"

typedef struct {
    u8 pad0[0x21];
    s8 unk21;
    u8 pad22[2];
} Ent_8004DA08;

extern s32 D_8008A960;
extern char D_80010820[];
extern char D_8008A96C[];
extern Ent_8004DA08 D_800AFA64[];

s32 func_8004DA08(s32 idx, s8 val) {
    Ent_8004DA08 *e;
    u32 i;
    u32 off;

    if (D_8008A960 == 0) {
        printf(D_80010820, D_8008A96C, 0x168);
        exit(1);
    }
    i = idx & 0xFFFF;
    if (i == 0xFFFF) {
        printf(D_80010820, D_8008A96C, 0x169);
        exit(1);
    }
    off = i * sizeof(Ent_8004DA08);
    e = (Ent_8004DA08 *) ((u8 *) D_800AFA64 + off);
    e->unk21 = val;
    return 0;
}
