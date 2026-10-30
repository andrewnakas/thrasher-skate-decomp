#include "common.h"

extern u32 D_8008AFAC;
extern u32 D_8008AFA8;

u8 *func_8001D5B0(s32, u32, s32);
s32 func_80034C20(s32);
void func_80034D4C(s32, void *, s32);

void func_80029488(s32 a0, s32 a1, u8 *h) {
    s32 n;
    u8 *p;

    if ((*(u32 *) (h + 0x18) & 0x800000) == 0) {
        return;
    }
    p = func_8001D5B0(a0, 0x4954414D, 1);
    n = *(s32 *) (p + 4) - 4;
    D_8008AFAC = *(u16 *) (p + 0xA);
    D_8008AFA8 = func_80034C20(n);
    func_80034D4C(D_8008AFA8, p + 0xC, n);
}
