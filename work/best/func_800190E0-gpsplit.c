#include "common.h"

typedef struct { u32 f00; u32 f04; u32 f08; } Ent;

extern u8 D_8008AD64;
extern u32 func_80015E8C();
extern void func_80015F10();
extern void func_80015A94();
extern void func_80019210();
extern u32 func_80019630();
extern void func_800194A4();

void func_800190E0(s32 id)
{
    Ent *e;
    u32 i;
    u8 *p;
    u8 *q;
    u32 off;

    if ((u32) (id & 0xFFFF) >= 2) {
        return;
    }
    {
        u8 *b = &D_8008AD64;
        e = (Ent *) ((u32 *) (b + 0x18))[id & 0xFFFF];
    }
    if (e == 0) {
        return;
    }
    p = (u8 *) func_80015E8C(e->f08);
    i = 0;
    off = 4;
    while (i < *(u32 *) p) {
        q = (u8 *) func_80019630(*(u16 *) (p + off));
        if (q != 0) {
            if (*(u16 *) (q + 2) & 2) {
                func_80015F10(e->f08);
                func_80019210(q);
                p = (u8 *) func_80015E8C(e->f08);
            }
        }
        off += 8;
        i++;
    }
    func_80015F10(e->f08);
    func_80015A94(e->f08);
    e->f08 = 0;
    func_800194A4(e);
    {
        u8 *b = &D_8008AD64;
        ((u32 *) (b + 0x18))[id & 0xFFFF] = 0;
    }
}
