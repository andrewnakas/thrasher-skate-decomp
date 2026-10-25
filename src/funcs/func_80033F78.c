#include "common.h"

extern s32 D_8008B0BC;
extern u8 D_800A5634[];
extern u8 D_80082350[16];
extern s32 D_8008A4C4;

void func_80033F78(s32 a0) {
    u8 *p;
    u16 i;

    if (!D_8008B0BC) {
        return;
    }
    if (a0) {
        p = D_800A5634;
        for (i = 0x64C; i != 0; i--) {
            *p++ = 0x20;
        }
        *p = 0;
    } else {
        p = D_800A5634;
        for (i = 0x64C; i != 0; i--) {
            *p++ = 0x20;
        }
    }
    D_8008A4C4 = *(s16 *)D_80082350 / 8 - 1;
}
