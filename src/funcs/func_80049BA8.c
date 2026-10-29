#include "common.h"

extern u8 D_8008B3F4;
extern u8 D_8008B3F5;
extern u8 D_8008B3F6;
extern u8 D_8008B3F7;
extern u8 D_8008B3F8;
extern u8 D_800AE994[];

void *memset(void *, s32, u32);

void func_80049BA8(void) {
    D_8008B3F8 = 0;
    D_8008B3F4 = 0x80;
    D_8008B3F5 = 0x80;
    D_8008B3F6 = 0x80;
    D_8008B3F7 = 0;
    memset(D_800AE994, 0, 0x90);
}
