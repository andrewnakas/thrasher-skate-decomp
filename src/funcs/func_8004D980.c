#include "common.h"

typedef struct {
    u8 pad0[0x1E];
    s16 unk1E;
    u8 pad20[4];
} Ent_8004D980;

extern s32 D_8008A960;
extern char D_80010820[];
extern char D_8008A96C[];
extern Ent_8004D980 D_800AFA64[];
s32 func_8004D980(s32 idx, s16 val) {
    Ent_8004D980 *e;
    u32 i;
    u32 off;

    if (D_8008A960 == 0) {
        printf(D_80010820, D_8008A96C, 0x154);
        exit(1);
    }
    i = idx & 0xFFFF;
    if (i == 0xFFFF) {
        printf(D_80010820, D_8008A96C, 0x155);
        exit(1);
    }
    off = i * sizeof(Ent_8004D980);
    e = (Ent_8004D980 *) ((u8 *) D_800AFA64 + off);
    e->unk1E = val;
    return 0;
}
