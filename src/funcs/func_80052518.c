#include "common.h"

typedef struct {
    u8 pad0[2];
    u8 unk2;
    u8 pad3;
    s32 unk4;
    u8 pad8[0x3C];
    s32 unk44;
} St_800B134C;

extern St_800B134C D_800B134C;
extern u8 D_800B13AC[];
extern u8 D_800B13DC[];
extern u8 D_800B146C[];
extern u8 D_8008B460[8];
extern u8 D_8008B490[8];
extern s32 D_8008B450;
extern s32 D_8008A9F4;
extern s32 D_8008B454;
extern s32 D_8008B480;
extern u8 D_8008B491;
extern void *D_8008B4A0;
extern s32 D_8008A9F0;
extern s32 D_8008A9EC;

void func_80054354(void);
void *SpuSetIRQCallback(void (*)(void));
s32 SpuMalloc(s32);

s32 func_80052518(s32 a0) {
    s32 size;
    s32 p;

    memset(&D_800B134C, 0, 0x54);
    memset(D_800B13AC, 0, 0x28);
    D_8008B450 = 0;
    memset(D_800B13DC, 0, 0x90);
    D_8008A9F4 = 0;
    D_8008B454 = 0;
    memset(D_8008B460, 0, 0x20);
    D_8008B480 = 0;
    memset(D_800B146C, 0, 0x800);
    memset(D_8008B490, 0, 0x10);
    D_8008B491 = 3;
    D_8008B4A0 = SpuSetIRQCallback(func_80054354);
    size = a0;
    if (size == 0) {
        size = 0x10000;
    }
    p = SpuMalloc(size);
    D_800B134C.unk44 = p;
    if (p != -1) {
        s32 *pool = &(&D_8008A9EC)[-21];
        D_800B134C.unk2 = 0;
        D_800B134C.unk4 = size;
        D_8008A9F0 = 0;
        D_8008A9EC = 1;
        *pool -= size;
        return 0;
    }
    SpuSetIRQCallback(D_8008B4A0);
    return 0x203;
}
