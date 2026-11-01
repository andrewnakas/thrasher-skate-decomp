#include "common.h"

extern void *func_80036E1C(u8 *, u8 *);
extern s32 func_8004AB44(void);
extern s32 func_8004D0E0(u32, u32);
extern void func_8004DBF0(u8 *);
extern void func_8004F250(void *, s32, u8 *);
extern s32 D_8008A360;
extern u8 D_8008A370[8];
extern u8 D_8008A37A[2];
extern u8 D_8008A37C[8];
extern u8 D_8008A3B0[];
extern u8 D_8008A3B8[];
extern u8 D_8008A3C4[];
extern u8 D_8008A3D0[];
extern s32 D_8008A938[2];
extern u16 D_8008B0A8[4];

void func_80030518(void) {
    u8 col[3];
    u32 i;

    col[0] = 0x7F;
    col[1] = 0;
    col[2] = 0;
    func_8004DBF0(col);
    D_8008A938[-1] = 0x1E;
    func_8004AB44();
    func_8004D0E0(0xBB8, 0x64);
    func_8004F250(func_80036E1C(D_8008A3B0, D_8008A3B8), 1, D_8008A370);
    func_8004F250(func_80036E1C(D_8008A3B0, D_8008A3C4), 0, D_8008A37A);
    func_8004F250(func_80036E1C(D_8008A3B0, D_8008A3D0), 0, D_8008A37C);
    for (i = 0; i < 4; i++) {
        D_8008B0A8[i] = 0xFFFF;
    }
    D_8008A360 = 0;
}
