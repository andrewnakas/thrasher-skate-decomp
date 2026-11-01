#include "common.h"

typedef struct PTag_80020824 {
    u32 addr : 24;
    u32 len : 8;
} PTag_80020824;

typedef struct Prim_80020824 {
    PTag_80020824 tag;
    u8 pad4[0x24];
    u8 unk28;
    u8 pad29[3];
    s32 unk2C;
} Prim_80020824;

typedef union Ent_80020824 {
    u32 w;
    u8 b[4];
} Ent_80020824;

extern u8 D_8008A2AC;
extern u8 D_8008A2AD;
extern u32 D_8008A2A4;
extern u32 D_8008A2A8;
typedef struct DrMode_80020824 {
    PTag_80020824 tag;
    u32 code[1];
} DrMode_80020824;

extern DrMode_80020824 D_8008AF04;
/* ordering-table pointer D_8008B3A0, spelled via its neighbour so it loads as lui/lw */
extern PTag_80020824 *D_8008B3A8;
#define OT_80020824 (*(&D_8008B3A8 - 2))
extern Prim_80020824 D_800937C4[2][100];
extern Prim_80020824 D_80092C84[2][30];
extern Prim_80020824 D_80096C44[2][225];
extern Prim_80020824 D_80095D44[2][40];
extern Ent_80020824 D_8009C6D4[];
extern Ent_80020824 D_8009C0A4[];

extern s32 func_80020C34(u8, u8, u8, Prim_80020824 **, s32 *, s32 *);
extern void func_80034D4C(void *, void *, s32);

#define ADDPRIMS(ot, p0, p1) ((p1)->tag.addr = (ot)->addr, (ot)->addr = (u32) (p0))

s32 func_80020824(void) {
    Prim_80020824 *a;
    s32 n;
    s32 m;
    Prim_80020824 *b;
    u32 i;
    PTag_80020824 *p;

    switch (D_8008A2AD) {
    case 0:
        ADDPRIMS(&OT_80020824[2], D_800937C4[D_8008A2AC], &D_800937C4[D_8008A2AC][99]);
        ADDPRIMS(&OT_80020824[2], D_80092C84[D_8008A2AC], &D_80092C84[D_8008A2AC][29]);
        break;
    case 1:
        ADDPRIMS(&OT_80020824[2], D_80096C44[D_8008A2AC], &D_80096C44[D_8008A2AC][224]);
        ADDPRIMS(&OT_80020824[2], D_80095D44[D_8008A2AC], &D_80095D44[D_8008A2AC][39]);
        break;
    }
    p = &D_8008AF04.tag;
    p->len = 1;
    D_8008AF04.code[0] = 0xE1000600;
    p->addr = OT_80020824[2].addr;
    OT_80020824[2].addr = (u32) p;
    if (D_8008A2AC == 0) {
        D_8008A2AC = 1;
    } else {
        D_8008A2AC = 0;
    }

    for (i = 0; i < D_8008A2A8; i++) {
        func_80020C34(D_8009C6D4[i].b[2], D_8009C6D4[i].b[1], D_8008A2AC, &a, &n, &m);
        a[D_8009C6D4[i].b[0]].unk2C = -1;
        a[D_8009C6D4[i].b[0]].unk28 = 0;
        a[D_8009C6D4[i].b[0]].tag.len = 0;
    }
    D_8008A2A8 = 0;

    for (i = 0; i < D_8008A2A4; i++) {
        func_80020C34((D_8009C0A4[i].w & 0xFF0000) >> 16, (D_8009C0A4[i].w & 0xFF00) >> 8, D_8008A2AC, &a, &n, &m);
        if (D_8008A2AC != 0) {
            func_80020C34((D_8009C0A4[i].w & 0xFF0000) >> 16, (D_8009C0A4[i].w & 0xFF00) >> 8, 0, &b, &n, &m);
        } else {
            func_80020C34((D_8009C0A4[i].w & 0xFF0000) >> 16, (D_8009C0A4[i].w & 0xFF00) >> 8, 1, &b, &n, &m);
        }
        func_80034D4C(&a[D_8009C0A4[i].b[0]], &b[D_8009C0A4[i].b[0]], 0x30);
        if (D_8009C0A4[i].b[0] != n - 1) {
            a[D_8009C0A4[i].b[0]].tag.addr = (u32) &a[D_8009C0A4[i].b[0] + 1];
        }
    }
    D_8008A2A4 = 0;
    return 0;
}
