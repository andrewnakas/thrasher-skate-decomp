#include "common.h"

extern u32 D_8008ACD4;
extern u32 D_8008ACD8;
extern u32 D_8008ACDC;
extern u16 D_8008ACE0;
extern u16 D_8008ACE2;
extern u16 D_8008ACE4;
extern u16 D_8008ACE6;
extern u32 D_80089F54;
extern u16 D_80089F50;

u8 *func_80013D98(u8 *s0) {
    u8 *p;
    s16 a1;

    p = *(u8 **) (s0 + 0x38);
    if (p[0x114] != 2) {
        return 0;
    }
    D_8008ACD4 = *(u32 *) (p + 0x118);
    D_8008ACD8 = *(u32 *) (*(u8 **) (s0 + 0x38) + 0x11C);
    D_8008ACDC = *(u32 *) (*(u8 **) (s0 + 0x38) + 0x120);
    D_8008ACE6 = 0;
    if (D_80089F54 == 0) {
        a1 = (s16) *(u16 *) &D_80089F50;
    } else {
        a1 = -(s16) *(u16 *) &D_80089F50;
    }
    func_80033428(&D_8008ACD4, a1);
    if (*(u32 *) (s0 + 4) & 8) {
        D_8008ACD4 = func_80032C28(D_8008ACD4, *(u32 *) (s0 + 0x20));
        D_8008ACD8 = func_80032C28(D_8008ACD8, *(u32 *) (s0 + 0x24));
        D_8008ACDC = func_80032C28(D_8008ACDC, *(u32 *) (s0 + 0x28));
    }
    D_8008ACE0 = *(u16 *) (*(u8 **) (s0 + 0x38) + 0x124);
    D_8008ACE2 = *(u16 *) (*(u8 **) (s0 + 0x38) + 0x126);
    D_8008ACE4 = *(u16 *) (*(u8 **) (s0 + 0x38) + 0x128);
    return (u8 *) &D_8008ACD4;
}
