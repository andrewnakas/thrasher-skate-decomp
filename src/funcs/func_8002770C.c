#include "common.h"

extern u8 D_800A4F00[];
extern u8 D_8008B088[8];

extern u16 D_8008B018;
extern s32 D_8008B01C;
extern s32 D_8008B020;
extern s32 D_8008B024;

extern s32 func_80027880(u8 *, s32);

s32 func_8002770C(s32 a0, s32 a1) {
    if (a1 >= 0x81) {
        return 0;
    }
    memset(D_800A4F00, 0, 0x60);
    memset(D_8008B088, 0, 0x18);
    D_8008B018 = a0;
    D_8008B01C = a1;
    D_8008B020 = 0;
    D_8008B024 = 0;
    func_80027880(D_800A4F00, a1 - 1);
    return (s32) D_800A4F00;
}
