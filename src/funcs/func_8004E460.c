#include "common.h"

extern char D_80010848[];
extern char D_80010870[];
extern u8 D_80082944[];
extern u8 D_80082948[];
extern u8 D_80082958[];
extern u8 D_8008295C[];
extern u8 D_80082960[];

typedef struct Node_8004E460 {
    u8 pad0[4];
    s16 unk4;
    u8 pad6[6];
    s32 unkC;
} Node_8004E460;

Node_8004E460 *func_8004F1E0(s32);
void printf(char *, char *, s32);
void exit(s32);

s32 func_8004E460(u32 arg0) {
    Node_8004E460 *n;

    if (*(u32 *) D_80082944 == 0) {
        printf(D_80010848, D_80010870, 0x213);
        exit(1);
    }
    *(volatile u32 *) D_80082948 = *(volatile u32 *) D_80082948 + 1;
    n = func_8004F1E0(arg0 & 0xFF);
    if (n != 0) {
        *(u32 *) D_80082958 |= n->unkC;
        n->unk4 = 2;
        *(u32 *) D_8008295C &= ~n->unkC;
        *(u32 *) D_80082960 &= ~n->unkC;
    }
    *(volatile u32 *) D_80082948 = *(volatile u32 *) D_80082948 - 1;
    return 0;
}
