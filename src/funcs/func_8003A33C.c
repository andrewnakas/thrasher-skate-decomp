#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
} Ent_8003A33C;

extern Ent_8003A33C D_8008232C[];
extern u32 func_80046878(u16 a, u16 b);
extern void func_8004966C(u16 *rp, u16 *gp, u16 *bp, u16 x, u16 y);

void func_8003A33C(void) {
    u32 v;
    u32 i;
    u16 r;
    u16 g;
    u16 b;

    for (i = 0; i < 4; i++) {
        v = func_80046878(D_8008232C[i].unk0, D_8008232C[i].unk2);
        r = v >> 16;
        g = (v >> 8) & 0xFF;
        b = v & 0xFF;
        func_8004966C(&r, &g, &b, D_8008232C[i].unk4, D_8008232C[i].unk6);
    }
}
