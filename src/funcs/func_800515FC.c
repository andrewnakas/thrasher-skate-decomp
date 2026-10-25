#include "common.h"

typedef struct {
    u16 flags;
    u8 state;
    u8 unk3;
    u8 pad4[8];
    s32 unkC;
    u8 pad10[8];
    s32 unk18;
    u8 pad1C[4];
    s32 unk20;
    s32 unk24;
    u16 unk28;
    u16 unk2A;
    s32 unk2C;
} Hdl_800515FC;

extern s32 D_8008A9C8;
extern char D_800108B0[];
extern char D_8008A9D4[];

void func_80051F9C(s32);
s32 func_80051B9C(Hdl_800515FC *, s32, s32 *, s32);

s32 func_800515FC(Hdl_800515FC *s) {
    s32 tmp;

    if (D_8008A9C8 == 0) {
        printf(D_800108B0, D_8008A9D4, 0x3D2);
        exit(1);
    }
    switch (s->state) {
    case 7:
        s->unk3 = 0;
        s->state = 4;
        break;
    case 1:
    case 2:
        s->state = 2;
        break;
    case 3:
    case 8:
        break;
    case 4:
    case 5:
    case 6:
    default:
        if (!(s->flags & 0x2000)) {
            func_80051F9C(s->unk2C);
            s->unk18 = 0;
            s->unk20 = 0;
            s->state = 2;
            if ((u32) func_80051B9C(s, s->unkC, &tmp, 1) < (u32) s->unkC) {
                s->flags |= 0x1000;
                s->unk24 = tmp;
            } else {
                s->unk24 = 0;
                s->flags &= 0xEFFF;
            }
        } else {
            s->state = 3;
            s->unk2A = 1;
        }
        break;
    }
    return 0;
}
