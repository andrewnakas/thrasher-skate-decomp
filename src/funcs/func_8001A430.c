#include "common.h"

extern s32 D_80089FD8;
extern s32 D_8008AE0C;
extern u16 D_8008AE10;
extern u8 D_80092684[];

void func_800120B8(s32, void *);
void func_80014464(void *, void *);
void func_80034D4C(void *, void *, s32);
void func_8001C488(s32, s32, void *, void *);
void func_8001A9DC(void);
u8 *func_8002BAC0(s32);
s32 func_8002BAFC(s32);

s32 func_8001A430(u16 *arg0) {
    u8 *slot;
    u8 *base;
    u8 *p;
    s32 i;
    u16 idx;

    if (D_8008AE0C >= 0x20) {
        return 0;
    }
    idx = *arg0;
    base = (u8 *)D_80089FD8 + idx * 448;
    slot = (u8 *)&D_80092684 + D_8008AE0C * 8;
    func_800120B8(3, base);
    *(u16 *)(slot + 6) = D_8008AE10 + D_8008AE0C * 4;
    func_80014464(base, slot);
    func_80034D4C(slot + 4, arg0, 2);
    *(u8 **)slot = base;
    p = func_8002BAC0(*(u16 *)(slot + 4));
    for (i = 0; i < func_8002BAFC(*(u16 *)(slot + 4)); i++) {
        func_8001C488(5, *(u16 *)(p + 0xA), base, func_8001A9DC);
        p += 0xC;
    }
    D_8008AE0C = D_8008AE0C + 1;
    return (s32)base;
}
