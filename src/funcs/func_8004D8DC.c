#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad18[0xC];
} Ent_8004D8DC;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Src_8004D8DC;

extern s32 D_8008A960;
extern s32 D_8008A968;
extern char D_80010820[];
extern char D_8008A96C[];
extern u8 D_800AFA64[];

s32 func_8004D8DC(s32 idx, Src_8004D8DC *src) {
    Ent_8004D8DC *e;
    u32 i;
    u32 off;

    if (D_8008A960 == 0) {
        printf(D_80010820, D_8008A96C, 0x13A);
        exit(1);
    }
    i = idx & 0xFFFF;
    if (i == 0xFFFF) {
        printf(D_80010820, D_8008A96C, 0x13B);
        exit(1);
    }
    off = i * sizeof(Ent_8004D8DC);
    e = (Ent_8004D8DC *) ((u8 *) D_800AFA64 + off);
    e->unkC = src->a;
    e->unk10 = src->b;
    e->unk14 = src->c;
    e->unk8 = D_8008A968;
    return 0;
}
