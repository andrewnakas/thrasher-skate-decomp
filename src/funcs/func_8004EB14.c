#include "common.h"

extern s32 D_80082944[];
extern u8 D_80010848[];
extern u8 D_80010870[];

typedef struct Rec_8004EB14 {
    u8 pad0[8];
    s32 unk8;
} Rec_8004EB14;

Rec_8004EB14 *func_8004F1E0(u8 a0);

s32 func_8004EB14(u8 a0) {
    Rec_8004EB14 *p;

    if (!D_80082944[0]) {
        printf(D_80010848, D_80010870, 0x2EE);
        exit(1);
    }

    p = func_8004F1E0(a0);
    if (p) {
        return p->unk8;
    }

    return 0;
}
