#include "common.h"

extern s32 D_8008B2EC;
extern s32 D_8008B2F0;
extern s32 D_8008B2F4;
extern s32 D_8008B2F8;
extern s32 D_8008B2FC;
extern u8 *func_80034C20(s32);
extern void func_80034D4C(u8 *, void *, s32);

void func_8003C1A4(u16 a0, u16 a1, s16 a2, void *a3) {
    s32 size = a0 * a1;
    s32 len = size * 28;
    u8 *p;

    D_8008B2EC = 1;
    D_8008B2F0 = a0;
    D_8008B2F4 = a1;
    D_8008B2F8 = a2;
    p = func_80034C20(len);
    D_8008B2FC = (s32) p;
    func_80034D4C(p, a3, len);
}
