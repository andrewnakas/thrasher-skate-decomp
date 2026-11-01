#include "common.h"

typedef struct {
    u32 flags;
    u16 unk4;
    u16 pad6;
    u32 pad8;
} R_8001CE98;

extern u32 D_8008AE40;
extern u32 D_8008AE44;
extern u32 D_8008AE48;
typedef union {
    u32 w;
    u8 b[4];
} T_8006EE04;

extern T_8006EE04 D_8006EE04[];

extern void *memset(void *dst, s32 c, u32 n);
extern void *func_80034C20(u32 size);
extern void func_8001CA74(void);

s32 func_8001CE98(void) {
    R_8001CE98 *r;
    R_8001CE98 *e;
    T_8006EE04 *t;
    s32 i;
    s32 n;

    D_8008AE48 = 0xF00;
    D_8008AE40 = (u32)func_80034C20(D_8008AE48);
    memset((void *)D_8008AE40, 0, D_8008AE48);

    r = (R_8001CE98 *)(D_8008AE40 + 0xEF4);
    i = 0x13F;
    do {
        r->unk4 = 0xFFFF;
        i--;
        r = (R_8001CE98 *)((u8 *)r - 0xC);
    } while (i != -1);

    D_8008AE44 = D_8008AE40;
    t = D_8006EE04;
    n = 0x23;
    i = 0;
    do {
        e = (R_8001CE98 *)D_8008AE44;
        e->flags = (e->flags & 0xFFFFFF7F) | ((t->w & 1) << 7);
        e->flags = (e->flags & 0xFFFFFF80) | (t->b[0] >> 1);
        ((u8 *)D_8008AE44)[1] = t->b[1];
        ((u8 *)D_8008AE44)[2] = t->b[2];
        ((u8 *)D_8008AE44)[3] = t->b[3];
        i++;
        t++;
        D_8008AE44 += 0xC;
    } while (i < n);

    func_8001CA74();
    return 0;
}
