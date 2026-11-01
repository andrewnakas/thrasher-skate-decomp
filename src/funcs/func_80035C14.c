#include "common.h"

/* 0xC-byte entry in the D_800A6294 list. */
typedef struct {
    u8 f0;              /* 0x0 */
    u8 pad0[3];         /* 0x1 */
    u32 f4;             /* 0x4 */
    u8 f8;              /* 0x8 */
    u8 f9;              /* 0x9 */
    u8 fA;              /* 0xA */
    u8 fB;              /* 0xB */
} T_80035C14_ent;

extern T_80035C14_ent D_800A6294[];
extern s32 D_8008B108;

void func_80035C14(u8 *arg0, s32 arg1) {
    T_80035C14_ent *base;
    T_80035C14_ent *e;
    u8 a;
    u8 b;

    base = D_800A6294;
    e = &base[arg1];
    a = arg0[2];
    b = arg0[3];
    e->f0 = 2;
    e->f4 = (u16) ~(b | (a << 8));
    e->f8 = arg0[4];
    e->f9 = arg0[5];
    e->fA = arg0[6];
    e->fB = arg0[7];
    D_8008B108 = D_8008B108 + 1;
}
