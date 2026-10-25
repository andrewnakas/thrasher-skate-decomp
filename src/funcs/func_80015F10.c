#include "common.h"

extern u8 *D_8008AD38;
extern u8 *D_8008AD3C;
extern s32 D_8008AD48;

void func_8001628C(u8 *);
void func_80016264(u8 *);

void func_80015F10(s32 idx) {
    u8 *p;

    p = D_8008AD38 - idx * 0x10;
    if (idx == 0) {
        return;
    }
    if (p < D_8008AD3C) {
        return;
    }
    if (p[0] == 0) {
        return;
    }
    if (p[1] == 0) {
        return;
    }
    func_8001628C(p);
    D_8008AD48 = D_8008AD48 - 1;
    p[1] = p[1] - 1;
    func_80016264(p);
}
