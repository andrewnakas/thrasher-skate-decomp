#include "common.h"

typedef struct {
    u32 f00;
    u32 f04;
    s32 f08;
} Ent_800190E0;

extern u8 D_8008AD64[8];

u8 *func_80015E8C(s32);
void func_80015F10(s32);
void func_80015A94(s32);
void func_80019210(u8 *);
u8 *func_80019630(u16);
void func_800194A4(Ent_800190E0 *);

void func_800190E0(u16 id) {
    Ent_800190E0 *e;
    u32 i;
    u8 *p;
    u8 *q;
    u32 off;


    if (id >= 2) {
        return;
    }
    {
        u32 o = id * 4;
        u8 *b = D_8008AD64;
        e = *(Ent_800190E0 **) (b + o + 0x18);
    }
    if (e == 0) {
        return;
    }
    i = 0;
    p = func_80015E8C(e->f08);
    while (i < *(u32 *) p) {
        off = i * 8 + 4;
        q = func_80019630(*(u16 *) (p + off));
        if (q != 0) {
            if (*(u16 *) (q + 2) & 2) {
                func_80015F10(e->f08);
                func_80019210(q);
                p = func_80015E8C(e->f08);
            }
        }
        i++;
    }
    func_80015F10(e->f08);
    func_80015A94(e->f08);
    e->f08 = 0;
    func_800194A4(e);
    {
        u32 o = id * 4;
        u8 *b = D_8008AD64;
        *(Ent_800190E0 **) (b + o + 0x18) = 0;
    }
}
