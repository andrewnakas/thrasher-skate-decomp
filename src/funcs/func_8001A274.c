#include "common.h"

extern s32 D_8008ADCC;
extern u16 D_8008ADD0;
extern u8 D_80092654[];

void *func_80012078(s32);
void func_8001475C(void *, s32);
void func_80014464(void *, void *);
void func_80034D4C(void *, void *, s32);
void func_8001C488(s32, s32, void *, void *);
void func_8001A550(void);
void func_80014324(void *);
void *func_8001D198(s32);

void *func_8001A274(void *arg0) {
    u8 *slot;
    u8 *p;
    u8 *q;

    if (D_8008ADCC >= 2) {
        return 0;
    }
    slot = (u8 *)&D_80092654 + D_8008ADCC * 24;
    p = func_80012078(1);
    if (p == 0) {
        return 0;
    }
    func_8001475C(p, 0);
    *(u16 *)(slot + 0x14) = D_8008ADD0 + D_8008ADCC * 12;
    func_80014464(p, slot);
    func_80034D4C(slot + 4, arg0, 0xC);
    *(u8 **)slot = p;
    func_80014324(p);
    q = func_8001D198(*(u16 *)(slot + 4));
    *(u8 **)(slot + 0x10) = q;
    func_8001C488(0, *(u16 *)(q + 4), p, func_8001A550);
    D_8008ADCC = D_8008ADCC + 1;
    return p;
}
