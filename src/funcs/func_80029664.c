#include "common.h"

typedef struct {
    u16 x, y, z, w;
} Light_80029664;

typedef struct {
    u8 pad0[0xA];
    u16 flags;
    Light_80029664 light[4];
    u8 pad2C[0x20];
    u8 c0[3];
    u8 c1[3];
    u8 c2[3];
    u8 pad55[3];
    u8 sub[0x10];
    s32 val[4];
} Neg_80029664;

typedef struct {
    s32 flags;
    u8 pad4[8];
    u16 a[4][3];
    u16 b[4][3];
    s32 val[4];
} State_80029664;

typedef struct {
    u8 pad0[0x18];
    s32 flags;
} Arg_80029664;

extern Neg_80029664 *func_8001D5B0(u8 *, u32, s32);
extern void func_8003B8C8(s32, s32, s32);
extern void func_8003C18C(s32, s32);
extern void func_8003B794();
extern void func_8003B6EC(s32, s32);
extern void func_8001D974(u8 *);
extern State_80029664 D_800A4F00;

void func_80029664(u8 *arg0, s32 arg1, Arg_80029664 *arg2) {
    Neg_80029664 *n;
    s32 i;
    u32 j;
    s32 c0, c1, c2;
    u16 fl;
    State_80029664 *st = &D_800A4F00;

    if (arg2->flags & 0x400000) {
        n = func_8001D5B0(arg0, 0x4E454742, 1);
        fl = n->flags;
        D_800A4F00.flags = fl;
        if (fl & 1) {
            D_800A4F00.flags = fl & 0xFFFD;
        }
        for (i = 0; i < 4; i++) {
            st->a[i][0] = n->light[i].x;
            st->a[i][1] = n->light[i].y;
            st->a[i][2] = n->light[i].z;
            st->b[i][0] = 0;
            st->b[i][1] = n->light[i].w;
            st->b[i][2] = 0;
        }
        func_8003B8C8(n->c0[0], n->c0[1], n->c0[2]);
        c0 = n->c0[0] | (n->c0[1] << 8) | (n->c0[2] << 16);
        c1 = n->c1[0] | (n->c1[1] << 8) | (n->c1[2] << 16);
        c2 = n->c2[0] | (n->c2[1] << 8) | (n->c2[2] << 16);
        if (c0 != c1 || c1 != c2) {
            if (c1 | c2) {
                func_8003C18C(c1, c2);
            }
        }
        for (j = 0; j < 4; j++) {
            st->val[j] = n->val[j];
        }
        if (st->val[0] > 0x7FFF) {
            func_8003B794(st->val[0]);
        } else {
            func_8003B6EC(st->val[0], 0);
        }
        func_8001D974(n->sub);
    }
}
