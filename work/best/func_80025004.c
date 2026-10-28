#include "common.h"

extern u32 D_8008A2BC;
extern u32 D_8008A2D8;
extern u32 D_8008A2DC;
extern u32 D_8008A2E0;
extern u32 D_8008A2E4;
extern u32 D_8008A2E8;
extern u32 D_8008A2EC;
extern u8 D_8008AF34;
extern void func_80024720();

void func_80025004(u8 *p)
{
    u32 big = 0x100000;
    u32 small = 0x10000;

    func_80024720();
    *(u32 *) (p + D_8008A2E0 * 32 + 0xAFC) = big;
    *(u32 *) (p + D_8008A2E4 * 32 + 0xAFC) = big;
    *(u32 *) (p + D_8008A2E8 * 32 + 0xAFC) = big;
    *(u32 *) (p + D_8008A2EC * 32 + 0xAFC) = big;
    *(u32 *) (p + D_8008A2D8 * 40 + 0x1020) = small;
    *(u32 *) (p + D_8008A2DC * 40 + 0x1020) = small;
    ((u32 *) &D_8008AF34)[D_8008A2BC] = 0;
}
