#include "common.h"

extern u8 D_8008AC08[];
extern u8 D_8008ABF4[];
extern s32 D_800B2508[];
extern void func_800385E8(u8 *);
extern void func_800382F0(u8 *, u8 *);
extern s32 func_80037DC4(u8 *, void *, s32);
extern s32 func_800383E8(void);

s32 func_80056E7C(void) {
    u8 buf[0xC8];

    func_800385E8(D_8008AC08);
    func_800382F0(D_8008ABF4, buf);
    D_800B2508[0] = 0x2A81511C;
    D_800B2508[1] = 1;
    D_800B2508[2] = 0;
    if (func_80037DC4(buf, D_800B2508, 0x774) == 0) {
        return 0;
    }
    switch (func_800383E8()) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 4:
        return 3;
    case 5:
        return 4;
    case 6:
        return 5;
    case 7:
        return 6;
    case 8:
        return 7;
    }
    return 7;
}
