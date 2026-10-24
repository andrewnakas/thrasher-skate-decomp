#include "common.h"

extern u32 D_80082944[3];
extern u8 D_8008294C[];
extern u32 D_80082990[3];
extern u8 D_800B03C4[];
extern char D_80010848[];
extern char D_80010870[];

void func_8004E30C(u8);

void func_8004DD38(void) {
    u8 i;

    if (D_80082944[0] == 0) {
        printf(D_80010848, D_80010870, 0x121);
        exit(1);
    }
    VSync(0x1E);
    for (i = 0; i < 0x40; i++) {
        if (D_800B03C4[i * 2] != 0) {
            func_8004E30C(i);
        }
    }
    if (D_8008294C[0] != 0) {
        SpuSetReverb(0);
        SpuIsTransferCompleted(1);
        if (SpuClearReverbWorkArea(D_80082990[0]) != 0) {
            printf(D_80010848, D_80010870, 0x137);
            exit(1);
        }
    }
    VSync(0x1E);
    SpuQuit();
    D_80082944[0] = 0;
}
