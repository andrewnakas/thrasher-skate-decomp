#include "common.h"

extern s32 D_80082944[];
extern volatile s32 D_80082948[3];
extern volatile s32 D_80082958[3];
extern s32 D_8008295C[3];
extern volatile s32 D_80082960[3];
extern u8 D_800B03C4[];
extern u8 D_80010848[];
extern u8 D_80010870[];


typedef struct {
    u8 b0;
    u8 b1;
} Pair_8004E528;

typedef struct {
    u8 f0;
    u8 f1;
    u8 pad2[2];
    u16 f4;
    u8 f6;
    u8 pad7[5];
    s32 fC;
} Ent_8004E528;

Ent_8004E528 *func_8004F1E0(u8);

s32 func_8004E528(u8 a0, u32 a1) {
    Ent_8004E528 *p;
    s32 t;

    if (!D_80082944[0]) {
        printf(D_80010848, D_80010870, 0x22E);
        exit(1);
    }
    D_80082948[0]++;
    p = func_8004F1E0(a0);
    if (p != NULL) {
        t = p->f4;
        if (t < 7) {
            if (t >= 2) {
                *(s32 *) &D_8008295C |= p->fC;
                D_80082958[0] &= ~p->fC;
                if (a1 & 1) {
                    D_80082960[0] |= p->fC;
                } else {
                    D_80082960[0] &= ~p->fC;
                }
            }
        }
        if (a1 & 2) {
            if ((a1 & 1) || p->f4 == 1) {
                p->f1 = 0;
                p->f0 = 0;
                p->f4 = 0;
                ((Pair_8004E528 *) D_800B03C4)[p->f6].b1 = 0xFF;
                ((Pair_8004E528 *) D_800B03C4)[p->f6].b0 = 0;
            } else {
                p->f0 |= 1;
            }
        }
    } else if (a1 & 2) {
        ((Pair_8004E528 *) D_800B03C4)[a0].b0 = 0;
    }
    D_80082948[0]--;
    return 0;
}
