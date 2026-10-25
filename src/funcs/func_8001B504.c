#include "common.h"

extern u16 D_8008AE12;
extern u16 D_8008AE14;
extern u16 D_8008AE16;
extern s32 D_8008AE18;

s32 func_8001D040(u32);
u8 *func_8001D0A0(u32);
u16 func_8001B3F4(u32);
s32 func_8002770C(u32, u32);
void func_8001BB9C(void);
s32 func_80027798(s32);
u8 *func_8002C3A0(s32);
void func_8001C2B8(s32, u32, u32, void *, s32);
void func_8001BC44(void);
void func_8001B634(void);
void func_8001B664(void);

s32 func_8001B504(void) {
    s32 i;
    u8 *p;
    void (*fn)(void);
    u16 off;
    u32 a;
    u32 b;

    if (func_8001D040(D_8008AE12) != 0) {
        return 1;
    }
    p = func_8001D0A0(D_8008AE12);
    D_8008AE16 = *(u16 *)(p + 6);
    off = func_8001B3F4(D_8008AE16 & 0xFFFF);
    a = *(u16 *)(p + 0);
    b = *(u16 *)(p + 2);
    D_8008AE14 = off;
    D_8008AE18 = func_8002770C(a, b);
    if (D_8008AE18 == 0) {
        return 1;
    }
    func_8001BB9C();
    if (func_80027798(D_8008AE18) != 0) {
        return 1;
    }
    for (i = 0; i < D_8008AE16; i++) {
        if (i == 0) {
            fn = func_8001B634;
        } else {
            fn = 0;
            if (i == D_8008AE16 - 1) {
                fn = func_8001B664;
            }
        }
        func_8001C2B8((*(u8 *)func_8002C3A0(i) >> 4) + 0x2A,
                      (u16)(*(u16 *)(p + 4) + i),
                      (u16)(D_8008AE14 + i), fn, 0);
    }
    func_8001BC44();
    return 0;
}
