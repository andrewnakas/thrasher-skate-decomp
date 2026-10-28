#include "common.h"

extern s32 D_800A4F00[0x28];

void func_8002C9B8(u8 *p) {
    s32 n = *(u16 *)(p + 4);
    u8 *q = p + *(u16 *)(p + 6);
    s32 i;
    s32 b;
    s32 a;
    u8 *e;

    for (i = n; i > 0; q += 8, i--) {
        e = (u8 *) D_800A4F00[1];
        for (a = *(u16 *)q - 1; a != -1; a--) {
            e = *(u8 **)(e + 0x94);
        }
        e = *(u8 **)(e + 0x4C);
        b = *(u16 *)(q + 2);
        b--;
        for (; b != -1; b--) {
            e += *(u8 *)(e + 2);
        }
        *(s32 *)e = *(s32 *)(q + 4);
    }
}
