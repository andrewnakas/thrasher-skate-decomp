#include "common.h"

extern char D_80010848[];
extern char D_80010870[];
extern u8 D_800B03C4[];

void printf(char *, char *, s32);
void exit(s32);

u8 func_8004EECC(u32 arg0) {
    u8 *table;
    u8 *p;
    u8 idx;

    idx = arg0 & 0xFF;
    if ((u32) idx >= 0x40) {
        printf(D_80010848, D_80010870, 0x355);
        exit(1);
    }
    table = D_800B03C4;
    p = table + idx * 2;
    if (p[0] == 0) {
        printf(D_80010848, D_80010870, 0x356);
        exit(1);
    }
    return p[1];
}
