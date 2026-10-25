#include "common.h"

extern u8 *D_8008AD90;
extern s32 D_8008AD94;
extern s32 D_8008AD88;

u8 *func_80015E8C(s32);
void func_80015F10(s32);
u8 *func_80019518(u8 *);
void func_8001954C(u8 *);

s32 func_80018038(u8 *arg0, u16 arg1) {
    u8 *p;
    u8 *tbl;
    u8 *e;
    u16 v;
    u8 made;

    if (D_8008AD90 == NULL) {
        made = 0;
        D_8008AD90 = func_80015E8C(D_8008AD94);
    } else {
        made = 1;
    }
    v = 0;
    p = D_8008AD90 + D_8008AD88 * 0x50;
    if (arg0 == NULL) {
        arg0 = *(u8 **)(p + 0x14);
        if (arg0 == NULL) {
            goto done;
        }
    }
    tbl = func_80019518(arg0);
    if (arg1 < *(u16 *)tbl) {
        e = tbl + arg1 * 0x10;
        v = *(u16 *)(e + 0x16);
    }
    func_8001954C(arg0);
done:
    if (made == 0) {
        D_8008AD90 = NULL;
        func_80015F10(D_8008AD94);
    }
    return v;
}
