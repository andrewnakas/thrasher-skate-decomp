#include "common.h"

extern u8 *D_8008AD68;
extern u8 *D_8008AD6C;
extern s32 D_8008AD70;
extern u8 *D_8008AD90;
extern s32 D_8008AD88;
extern s32 D_8008AD94;
extern s32 D_8008AD64[2];
extern u16 D_8008AD60;

s32 func_8003874C(void);
s32 func_800159D8(s32);
u8 *func_80015E8C(s32);
void func_80015F10(s32);
void func_80017540(void);
void func_80016DA4(void);
void func_80016CC4(s32, s32, s32, s32);
u8 *func_80034C20(s32);
void *memset(void *, s32, u32);

s32 func_80016970(void) {
    u8 *p;
    s32 i;
    s32 n;
    s32 e;
    s32 j;

    if (func_8003874C() != 0) {
        return 1;
    }
    n = func_800159D8(0x320);
    D_8008AD94 = n;
    if (n == 0) {
        return 1;
    }
    p = func_80015E8C(n);
    D_8008AD90 = p;
    D_8008AD88 = 0;
    memset(p, 0, 0x320);
    memset(p, 0, 0x50);
    func_80017540();
    func_80016DA4();
    func_80015F10(D_8008AD94);
    memset(D_8008AD64, 0, 0x20);
    func_80016CC4(0, 0, 0x1FF, 0x1DF);
    D_8008AD68 = func_80034C20(0x640);
    if (D_8008AD68 == 0) {
        return 1;
    }
    memset(D_8008AD68, 0, 0x640);
    D_8008AD6C = D_8008AD68;
    for (i = 0; i < 0x64; i++) {
        if (i != 0x63) {
            *(s32 *)((u8 *)D_8008AD68 + i * 0x10 + 4) = (s32)((u8 *)D_8008AD68 + (i + 1) * 0x10);
        } else {
            *(s32 *)((u8 *)D_8008AD68 + 0x634) = 0;
        }
    }
    D_8008AD70 = 0;
    *(s32 *)(p + 0xC) = 0xFFFF;
    D_8008AD60 = 0xC001;
    return 0;
}
