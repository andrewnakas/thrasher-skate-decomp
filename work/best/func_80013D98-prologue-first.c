#include "common.h"

typedef struct {
    u8 pad0[0x4];
    u32 f04;
    u8 pad8[0x18];
    u32 f20;
    u32 f24;
    u32 f28;
    u8 pad2C[0xC];
    u32 f38;
} Obj_80013D98;

extern u32 D_8008ACD4;
extern u32 D_8008ACD8;
extern u32 D_8008ACDC;
extern u16 D_8008ACE0;
extern u16 D_8008ACE2;
extern u16 D_8008ACE4;
extern u16 D_8008ACE6;
extern u16 D_80089F50;
extern u32 D_80089F54;

extern void func_80033428();
extern u32 func_80032C28();

u8 *func_80013D98(Obj_80013D98 *obj)
{
    u8 *p;
    s16 a1;

    p = (u8 *) obj->f38;
    if (*(u8 *) (p + 0x114) != 2) {
        return 0;
    }
    D_8008ACD4 = *(u32 *) (p + 0x118);
    p = (u8 *) obj->f38;
    D_8008ACD8 = *(u32 *) (p + 0x11C);
    p = (u8 *) obj->f38;
    D_8008ACDC = *(u32 *) (p + 0x120);
    D_8008ACE6 = 0;
    if (D_80089F54 != 0) {
        a1 = (s16) (-D_80089F50);
    } else {
        a1 = *(s16 *) &D_80089F50;
    }
    func_80033428(&D_8008ACD4, a1);
    if (obj->f04 & 8) {
        D_8008ACD4 = func_80032C28(D_8008ACD4, obj->f20);
        D_8008ACD8 = func_80032C28(D_8008ACD8, obj->f24);
        D_8008ACDC = func_80032C28(D_8008ACDC, obj->f28);
    }
    p = (u8 *) obj->f38;
    D_8008ACE0 = *(u16 *) (p + 0x124);
    p = (u8 *) obj->f38;
    D_8008ACE2 = *(u16 *) (p + 0x126);
    p = (u8 *) obj->f38;
    D_8008ACE4 = *(u16 *) (p + 0x128);
    return (u8 *) &D_8008ACD4;
}
