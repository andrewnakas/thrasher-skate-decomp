#include "common.h"

extern u8 D_800A76FC[];
extern u8 D_8008A59C[];
extern u8 D_8008A5A0[];
extern void func_800165DC(void);
extern void func_8001651C(u8 *, u8 *);
extern void func_8001655C(u8 *, u8 *);
extern s32 func_800165BC(u8 *, s32);

u8 *func_80035EB8(u8 *a0) {
    u8 *s;

    func_800165DC();
    if (a0[0] != '\\') {
        func_8001651C(D_800A76FC, D_8008A59C);
        func_8001655C(D_800A76FC, a0);
    } else {
        func_8001651C(D_800A76FC, a0);
    }
    s = D_800A76FC;
    if (func_800165BC(s, ';') == 0) {
        func_8001655C(s, D_8008A5A0);
        return s;
    }
    return s;
}
