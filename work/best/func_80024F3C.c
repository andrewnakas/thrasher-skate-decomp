#include "common.h"

extern u8 D_8008AF3C;
extern u8 D_8008AF44;
extern u8 D_8008AF34;
extern u32 D_8008A2BC;
extern u32 D_8008A2D8;
extern u32 D_8008A2DC;
extern void func_80024720();
extern void func_80025544();
extern void func_80024D6C();

void func_80024F3C(u8 *p, u8 *q)
{
    func_80024720();
    if (((u32 *) &D_8008AF3C)[D_8008A2BC] != 0) {
        func_80025544(p, q);
    }
    if (((u32 *) &D_8008AF44)[D_8008A2BC] != 0) {
        func_80024D6C(p, q);
    }
    {
        u32 a;
        u32 b;
        u32 c;

        ((u32 *) &D_8008AF34)[D_8008A2BC] = 1;
        a = D_8008A2D8;
        b = D_8008A2DC;
        c = a * 40;
        *(u32 *) (p + c + 0x1020) = 0;
        a = b * 40;
        *(u32 *) (p + a + 0x1020) = 0;
    }
}
