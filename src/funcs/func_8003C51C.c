#include "common.h"

typedef struct {
    s16 m[3][3];
    s32 t[3];
} Mat_8003C51C;

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} Tag_8003C51C;

typedef struct {
    Tag_8003C51C tag;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
    u32 unk14;
    s16 unk18;
    s16 unk1A;
    u32 unk1C;
    s16 unk20;
    s16 unk22;
} Prim_8003C51C;

typedef struct {
    u32 w[3];
} Mode_8003C51C;

extern void ReadRotMatrix(Mat_8003C51C *);
extern s32 ReadGeomScreen(void);
extern void ReadGeomOffset(s32 *, s32 *);
extern void func_8003C290(Mat_8003C51C *, s32, s32);
extern s32 D_8008B2A4;
extern u32 D_8008B2A8[2];
extern u8 D_8008B2B4[4];
extern u8 D_8008B2D4[4];
extern s32 D_8008B2EC;
extern u32 D_8008B3AC[2];
#define D_8008B3A8 (&D_8008B3AC[-1])
#define D_8008B3A0 ((Tag_8003C51C **) &D_8008B3AC[-3])
extern Prim_8003C51C D_800A9604[];

void func_8003C51C(void) {
    Mat_8003C51C m;
    s32 ofx;
    s32 ofy;
    s32 h;
    s32 k;
    s32 v;
    s32 y;
    s32 off;
    Prim_8003C51C *p;
    Tag_8003C51C *ot;

    ReadRotMatrix(&m);
    h = ReadGeomScreen();
    ReadGeomOffset(&ofx, &ofy);
    k = 0xFFFF;
    v = -m.m[2][1] * k;
    y = (v >> 12) + m.t[1];
    v = y * h;
    y = v / k + ofy;
    y = (y + 0x78) >> 1;
    if (y > 0xF0) {
        y = 0xF0;
    }
    if (y > 0) {
        if (D_8008B2EC != 0) {
            func_8003C290(&m, y, v);
        }
        if (D_8008B2A4 != 0) {
            p = (Prim_8003C51C *) (D_8008B3A8[0] * 0x24 + (u32) D_800A9604);
            p->unk4 = D_8008B2A8[0] | (p->unk4 & 0xFF000000);
            p->unkC = D_8008B2A8[0];
            p->unk14 = D_8008B2A8[1];
            p->unk1C = D_8008B2A8[1];
            p->unk1A = y;
            p->unk22 = y;
            p->tag.addr = D_8008B3A0[0][0x5FF].addr;
            D_8008B3A0[0][0x5FF].addr = (u32) p;
        }
        off = D_8008B3A8[0];
        ot = D_8008B3A0[0];
        {
            Tag_8003C51C *q = (Tag_8003C51C *) &((Mode_8003C51C *) D_8008B2B4)[off];
            q->addr = ot[0x5FF].addr;
            ot[0x5FF].addr = (u32) q;
        }
        {
            Tag_8003C51C *q = (Tag_8003C51C *) &((Mode_8003C51C *) D_8008B2D4)[off];
            q->addr = ot[0].addr;
            ot[0].addr = (u32) q;
        }
    }
}
