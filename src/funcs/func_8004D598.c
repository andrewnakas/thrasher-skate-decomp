#include "common.h"

typedef struct {
    u16 flags;
    u8 pad2[6];
    s32 unk8;
    u8 padC[0x10];
    s16 unk1C;
    s16 unk1E;
    u8 pad20[4];
} Ent_8004D598;

extern s32 D_8008B438;
extern u8 D_800AFA64[];
void func_8004D980(s32, s16);

void func_8004D598(void) {
    Ent_8004D598 *e;
    u32 i;

    D_8008B438 = 1;
    e = (Ent_8004D598 *) D_800AFA64;
    for (i = 0; i < 0x10; i++) {
        if ((e[i].flags & 0x8000) && e[i].unk8 != 0 && e[i].unk1C != 0) {
            func_8004D980(i & 0xFFFF, e[i].unk1E);
        }
    }
}
