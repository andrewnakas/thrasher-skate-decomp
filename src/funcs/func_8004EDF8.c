#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 id;
    u32 mask;
    u8 pad10[0x3C];
} Voice_8004EDF8;

extern u32 D_80082944[3];
extern volatile u32 D_80082948[3];
extern u8 D_80082958[];
extern u8 D_8008295C[];
extern u8 D_80082960[];
extern Voice_8004EDF8 D_800AFCA4[24];
extern char D_80010848[];
extern char D_80010870[];

void func_8004EDF8(s32 id) {
    u32 i;

    if (D_80082944[0] == 0) {
        printf(D_80010848, D_80010870, 0x33E);
        exit(1);
    }
    D_80082948[0]++;
    for (i = 0; i < 24; i++) {
        if (D_800AFCA4[i].id == id) {
            (*(volatile u32 *) D_8008295C) |= D_800AFCA4[i].mask;
            (*(volatile u32 *) D_80082960) |= D_800AFCA4[i].mask;
            (*(volatile u32 *) D_80082958) &= ~D_800AFCA4[i].mask;
        }
    }
    D_80082948[0]--;
}
