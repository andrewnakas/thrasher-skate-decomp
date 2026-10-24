#include "common.h"

typedef struct {
    u16 flags;
    u8 pad2[2];
    s32 unk4;
    u8 pad8[0x1C];
} Ent_8004D820;

extern s32 D_8008A960;
extern char D_80010820[];
extern char D_8008A96C[];
extern Ent_8004D820 D_800AFA64[];

s32 func_8004D820(s32 idx, s32 val) {
    Ent_8004D820 *e;
    u32 i;
    u32 off;

    if (D_8008A960 == 0) {
        printf(D_80010820, D_8008A96C, 0x127);
        exit(1);
    }
    i = idx & 0xFFFF;
    if (i == 0xFFFF) {
        printf(D_80010820, D_8008A96C, 0x128);
        exit(1);
    }
    off = i * sizeof(Ent_8004D820);
    e = (Ent_8004D820 *) ((u8 *) D_800AFA64 + off);
    if (!(e->flags & 0x8000)) {
        printf(D_80010820, D_8008A96C, 0x12A);
        exit(1);
    }
    e->unk4 = val;
    return 0;
}
