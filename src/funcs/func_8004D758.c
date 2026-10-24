#include "common.h"

typedef struct {
    u16 flags;
    u8 pad2[0x22];
} Ent_8004D758;

extern s32 D_8008A960;
extern char D_80010820[];
extern char D_8008A96C[];
extern Ent_8004D758 D_800AFA64[];
void func_8004E30C(u8);

void func_8004D758(s32 idx) {
    Ent_8004D758 *e;
    u32 i;
    u32 off;

    if (D_8008A960 == 0) {
        printf(D_80010820, D_8008A96C, 0x115);
        exit(1);
    }
    i = idx & 0xFFFF;
    if (i == 0xFFFF) {
        printf(D_80010820, D_8008A96C, 0x116);
        exit(1);
    }
    off = i * sizeof(Ent_8004D758);
    e = (Ent_8004D758 *) ((u8 *) D_800AFA64 + off);
    if (!(e->flags & 0x8000)) {
        printf(D_80010820, D_8008A96C, 0x118);
        exit(1);
    }
    func_8004E30C(((u8 *) e)[2]);
    e->flags = 0;
}
