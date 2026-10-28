#include "common.h"

typedef struct { u32 f00; u32 f04; u32 f08; } Rec;

extern u8 D_8006F834[];
extern u8 *D_8008B060;

s32 func_8002DE18(u8 *p) {
    Rec *cur = (Rec *) D_8008B060;
    Rec *old = cur;
    Rec *tab = (Rec *) D_8006F834;

    cur = (Rec *) ((u8 *) cur + 0xC);
    D_8008B060 = (u8 *) cur;
    old->f00 = (u32) p;
    old->f04 = 0;
    old->f08 = tab[p[3]].f08;
    return 0;
}
