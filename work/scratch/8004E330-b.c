#include "common.h"

typedef struct {
    u8 b0;
    u8 b1;
} Pair_8004E330;

typedef struct {
    u8 b0;
    u8 pad[0x4B];
} Rec_8004E330;

extern u8 D_80010848[];
extern u8 D_80010870[];
extern u8 D_80082944[];
extern u8 D_80082948[];
extern u8 D_800B03C4[];
extern u8 D_800AFCA4[];

void printf(u8 *fmt, u8 *msg, ...);
void exit(s32 code);
u8 func_8004DEBC(s32 handle, u8 arg);
void func_8004E6CC(s32 idx, u8 a);
void func_8004E7EC(s32 idx, s32 a);
void func_8004E930(s32 idx, s32 a);
void func_8004E460(s32 idx);

s32 func_8004E330(s32 handle, s32 a1, s32 a2, s32 a3, u8 a4) {
    s32 s0;

    if (*(u32 *) D_80082944 == 0) {
        printf(D_80010848, D_80010870, 0x1F7);
        exit(1);
    }
    if (handle != 0) {
        (*(u32 *) D_80082948)++;
        s0 = func_8004DEBC(handle, a4) & 0xFF;
        if (s0 != 0xFF) {
            func_8004E6CC(s0, a2 & 0xFF);
            func_8004E7EC(s0, (s8) a3);
            func_8004E930(s0, (s16) a1);
            func_8004E460(s0);
            ((Rec_8004E330 *) D_800AFCA4)[((Pair_8004E330 *) D_800B03C4)[s0].b1].b0 |= 1;
        }
        (*(u32 *) D_80082948)--;
    }
    return 0;
}
