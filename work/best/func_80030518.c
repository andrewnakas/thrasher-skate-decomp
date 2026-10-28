#include "common.h"

extern u8 D_8008A934[];
extern u8 D_8008A3B0[];
extern u8 D_8008A3B8[];
extern u8 D_8008A3C4[];
extern u8 D_8008A3D0[];
extern u8 D_8008A370;
extern u8 D_8008A37A;
extern u8 D_8008A37C;
extern u8 D_8008B0A8;
extern s32 D_8008A360;
extern void func_8004DBF0();
extern void func_8004AB44();
extern void func_8004D0E0();
extern u32 func_80036E1C();
extern void func_8004F250();

void func_80030518(void)
{
    u8 buf[3];
    u8 *p;
    s32 i;

    buf[0] = 0x7F;
    buf[1] = 0;
    buf[2] = 0;
    func_8004DBF0(buf);
    *(s32 *) D_8008A934 = 0x1E;
    func_8004AB44();
    func_8004D0E0(0xBB8, 0x64);
    func_8004F250(func_80036E1C(D_8008A3B0, D_8008A3B8), 1, &D_8008A370);
    func_8004F250(func_80036E1C(D_8008A3B0, D_8008A3C4), 0, &D_8008A37A);
    func_8004F250(func_80036E1C(D_8008A3B0, D_8008A3D0), 0, &D_8008A37C);
    p = &D_8008B0A8;
    for (i = 0; i < 4; i++) {
        *(u16 *) (p + i * 2) = 0xFFFF;
    }
    D_8008A360 = 0;
}
