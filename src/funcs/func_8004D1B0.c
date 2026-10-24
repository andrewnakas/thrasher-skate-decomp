#include "common.h"

extern s32 D_8008A960;
extern s32 D_8008A964;
extern char D_80010820[];
extern char D_8008A96C[];
extern u8 D_800AFA64[];
void func_8004D758(s32);

void func_8004D1B0(void) {
    u8 *p;
    u32 i;

    if (D_8008A960 == 0) {
        printf(D_80010820, D_8008A96C, 0x69);
        exit(1);
    }
    i = 0;
    p = D_800AFA64;
    do {
        if (*(u16 *) p & 0x8000) {
            func_8004D758(i & 0xFFFF);
        }
        i++;
        p += 0x24;
    } while (i < 0x10);
    D_8008A964 = 0;
    D_8008A960 = 0;
}
