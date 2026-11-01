#include "common.h"

typedef struct {
    u8 f0;
    u8 pad1;
    u16 f2;
    u16 f4;
    u16 pad6;
    s32 f8;
} Slot;

typedef struct {
    u8 type;
    u8 pad1[3];
    u8 data[8];
} Item;

typedef struct {
    u8 n;
    u8 pad1[3];
    Item *items;
} Grp;

typedef struct {
    u8 flags;
    u8 ngrp;
    u8 pad2[2];
    u8 data[8];
    Grp grp[1];
} Obj;

extern u8 D_8008B408[4];

s32 func_8004FECC(u16, s32);
s32 func_80050A3C(s32 *, s32, s32, s32, s32);
u32 func_8004FC88(u16);
Obj *func_8004FF90(u16, u32);

u8 func_8004C064(u16 id, s32 a1, s32 a2, s32 flags) {
    Slot *s;
    Obj *o;
    Grp *g;
    u32 i;
    u32 k;
    u32 n;
    u32 j;
    u32 m;
    u32 c;

    for (i = 0; i < 2; i++) {
        s = &((Slot *) D_8008B408)[i];
        if (s->f8 == 0) {
            if (func_80050A3C(&s->f8, func_8004FECC(id, 0), a1, a2, flags | 4) == 0) {
                s->f2 = id;
                s->f0 = flags;
                s->f4 = 0xFFFF;
                n = func_8004FC88(id);
                for (k = 0; k < n; k++) {
                    o = func_8004FF90(id, k);
                    switch (o->flags & 1) {
                    case 0:
                        for (j = 0; j < 8; j++) {
                            o->data[j] = 0;
                        }
                        break;
                    case 1:
                        for (m = 0; m < o->ngrp; m++) {
                            g = &o->grp[m];
                            for (c = 0; c < g->n; c++) {
                                switch (g->items[c].type) {
                                case 0:
                                    for (j = 0; j < 8; j++) {
                                        g->items[c].data[j] = 0;
                                    }
                                    break;
                                case 1:
                                    for (j = 0; j < 8; j++) {
                                        g->items[c].data[j] = 0;
                                    }
                                    break;
                                case 2:
                                    break;
                                }
                            }
                        }
                        for (j = 0; j < 4; j++) {
                            o->data[j] = 0;
                        }
                        break;
                    }
                }
                return i;
            }
            s->f8 = 0;
        }
    }
    return 0xFF;
}
