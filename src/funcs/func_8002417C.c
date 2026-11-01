#include "common.h"

typedef struct {
    u8 pad0[0x48];
    s32 y;
    u8 pad4C[0x8C - 0x4C];
} Node_8002417C;

typedef struct {
    u32 count;
    Node_8002417C n[16];
} Body_8002417C;

typedef struct {
    s32 type;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
} Part_8002417C;

typedef struct {
    s32 type;
    s32 num;
    Node_8002417C *a;
    Node_8002417C *b;
    Node_8002417C *c;
    Node_8002417C *d;
    Node_8002417C *e;
    s32 g1C;
    s32 k;
} Link_8002417C;

extern Body_8002417C *func_80022118(void);
extern s32 func_80022148(Body_8002417C *, Part_8002417C *);
extern s32 func_8002221C(Body_8002417C *, s32, s32, s32);
extern s32 func_80022308(Body_8002417C *, Link_8002417C *);
extern s32 func_800223AC(Body_8002417C *, Link_8002417C *);
extern void func_80023ECC(Body_8002417C *, s32);
extern s32 func_80032C28(s32, s32);
extern s32 D_8008A2B8;
extern s32 D_8008A2C8;
extern s32 D_8008A2CC;
extern s32 D_8008A2D0;
extern s32 D_8008A2D4;
extern s32 D_8008A2D8;
extern s32 D_8008A2DC;
extern s32 D_8008A2E0;
extern s32 D_8008A2E4;
extern s32 D_8008A2E8;
extern s32 D_8008A2EC;
extern s32 D_8008A2F0;
extern s32 D_8008A2F4;
extern s32 D_8008A2F8;
extern s32 D_8008A2FC;
extern s32 D_8008A300;
extern Body_8002417C *D_8008AF2C[2];

Body_8002417C *func_8002417C(s32 arg0) {
    Part_8002417C part;
    Link_8002417C link;
    s32 min;
    Body_8002417C *b;
    u32 i;

    min = 0x1F40000;
    b = func_80022118();
    if (b != NULL) {
        part.type = 1;
        part.f10 = func_80032C28(0x1999, 0x40000);
        part.f14 = func_80032C28(0xB333, 0x10000);
        part.f18 = 0x10000;
        func_80022148(b, &part);
        part.f10 = func_80032C28(0x1999, 0x10000);
        func_80022148(b, &part);
        func_80022148(b, &part);
        func_80022148(b, &part);
        func_80022148(b, &part);
        func_80022148(b, &part);
        func_80022148(b, &part);
        func_80022148(b, &part);
        func_80022148(b, &part);
        func_80022148(b, &part);
        func_80022148(b, &part);
        func_80022148(b, &part);
        func_80022148(b, &part);
        func_80022148(b, &part);
        func_80023ECC(b, arg0);
        func_8002221C(b, 0, 1, 0x100000);
        func_8002221C(b, 0, 2, 0x100000);
        func_8002221C(b, 1, 2, 0x100000);
        func_8002221C(b, 7, 0, 0x200000);
        func_8002221C(b, 8, 0, 0x200000);
        func_8002221C(b, 7, 8, 0x100000);
        func_8002221C(b, 7, 1, 0x200000);
        func_8002221C(b, 7, 2, 0x200000);
        func_8002221C(b, 8, 1, 0x200000);
        func_8002221C(b, 8, 2, 0x200000);
        D_8008A2F4 = func_8002221C(b, 2, 4, 0x100000);
        D_8008A2FC = func_8002221C(b, 4, 6, 0x100000);
        D_8008A2F0 = func_8002221C(b, 1, 3, 0x100000);
        D_8008A2F8 = func_8002221C(b, 3, 5, 0x100000);
        D_8008A2E4 = func_8002221C(b, 8, 10, 0x100000);
        D_8008A2EC = func_8002221C(b, 10, 12, 0x100000);
        D_8008A2E0 = func_8002221C(b, 7, 9, 0x100000);
        D_8008A2E8 = func_8002221C(b, 9, 11, 0x100000);
        D_8008A300 = func_8002221C(b, 13, 0, 0x33333);
        D_8008A300 = func_8002221C(b, 13, 7, 0x100000);
        D_8008A300 = func_8002221C(b, 13, 8, 0x100000);
        link.a = &b->n[4];
        link.b = &b->n[6];
        link.a = &b->n[3];
        link.b = &b->n[5];
        link.a = &b->n[9];
        link.b = &b->n[11];
        link.a = &b->n[10];
        link.b = &b->n[12];
        link.type = 4;
        link.num = 2;
        link.a = &b->n[8];
        link.b = &b->n[9];
        link.c = &b->n[7];
        link.d = &b->n[8];
        link.e = &b->n[9];
        link.k = 0x13333;
        link.g1C = 2;
        D_8008A2D8 = func_80022308(b, &link);
        link.type = 1;
        link.num = 2;
        link.a = &b->n[7];
        link.b = &b->n[10];
        link.c = &b->n[8];
        link.d = &b->n[7];
        link.e = &b->n[10];
        link.k = 0x13333;
        link.g1C = 2;
        D_8008A2DC = func_80022308(b, &link);
        link.type = 4;
        link.num = 2;
        link.a = &b->n[2];
        link.b = &b->n[3];
        link.c = &b->n[1];
        link.d = &b->n[2];
        link.e = &b->n[3];
        link.k = 0x8000;
        link.g1C = 2;
        D_8008A2CC = func_80022308(b, &link);
        link.type = 1;
        link.num = 2;
        link.a = &b->n[1];
        link.b = &b->n[4];
        link.c = &b->n[2];
        link.d = &b->n[1];
        link.e = &b->n[4];
        link.k = 0x8000;
        link.g1C = 2;
        D_8008A2D4 = func_80022308(b, &link);
        link.type = 2;
        link.num = 5;
        link.k = 0x10000;
        link.a = &b->n[2];
        link.b = &b->n[3];
        link.c = &b->n[1];
        link.d = &b->n[2];
        link.e = &b->n[3];
        link.g1C = 1;
        D_8008A2C8 = func_800223AC(b, &link);
        link.k = 0x10000;
        link.type = 2;
        link.num = 2;
        link.a = &b->n[1];
        link.b = &b->n[4];
        link.c = &b->n[2];
        link.d = &b->n[1];
        link.e = &b->n[4];
        link.g1C = 1;
        D_8008A2D0 = func_800223AC(b, &link);
        for (i = 0; i < b->count; i++) {
            if (b->n[i].y < min) {
                min = b->n[i].y;
            }
        }
        for (i = 0; i < b->count; i++) {
            b->n[i].y -= min;
        }
    }
    D_8008AF2C[D_8008A2B8] = b;
    D_8008A2B8++;
    if (D_8008A2B8 >= 2) {
        D_8008A2B8 = 0;
    }
    return b;
}
