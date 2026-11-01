#include "common.h"

extern u32 D_8008A9C8;
extern u32 D_8008A934[3];
extern char D_800108B0[];
extern char D_8008A9D4[];

void SpuGetVoiceVolumeAttr(s32, s16 *, s16 *, s16 *, s16 *);

s32 func_800519C4(u8 *a0, u32 a1, u8 a2, u32 a3) {
    s16 va;
    s16 vb;
    s16 vc;
    s16 vd;
    s32 n;
    s32 c;
    s32 hi;
    s32 lo;

    if (D_8008A9C8 == 0) {
        printf(D_800108B0, D_8008A9D4, 0x47A);
        exit(1);
    }
    SpuGetVoiceVolumeAttr(*(s32 *) (a0 + 0x4C), &va, &vb, &vc, &vd);
    n = (a1 * D_8008A934[0]) / 1000;
    c = 1;
    if (n != 0) {
        c = n;
    }
    lo = (va << 9) & 0xFFFF0000;
    *(u32 *) (a0 + 0x3C) = lo;
    hi = a2 << 16;
    *(u32 *) (a0 + 0x40) = hi;
    *(u32 *) (a0 + 0x44) = (hi - *(s32 *) (a0 + 0x3C)) / c;
    *(u32 *) (a0 + 0x38) = a3 | 1;
    return 0;
}
