#include "common.h"

typedef struct {
    s32 unk0;
    u8 pad4[4];
    s8 unk8;
    u8 pad9[11];
} Rec_80035060;

extern Rec_80035060 D_800A6244[];
extern s8 D_8008B100[4];
extern u16 D_8008B128;

void func_80035060(s8 *a0) {
    D_800A6244[a0[1]].unk0 = 0;
    D_8008B100[D_800A6244[a0[1]].unk8] = -1;
    a0[1] = -1;
    D_8008B128--;
}
