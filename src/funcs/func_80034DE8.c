#include "common.h"

typedef struct {
    u8 b0;
    s8 b1;
    s16 h2;
    s32 w4;
    s32 w8;
    s32 wC;
    u8 pad10[0x1C];
} Pad34DE8;

typedef struct {
    u8 pad0[4];
    s32 w4;
    u8 pad8[4];
} Ent34DE8;

typedef struct {
    s32 w0;
    u8 pad4[0x10];
} Slot34DE8;

extern s16 D_8008B128;
extern Pad34DE8 D_800A6084[10];
extern u8 D_800A62F4[0x22];
extern u8 D_800A6318[0x22];
extern Ent34DE8 D_800A6294[8];
extern s8 D_8008B100[8];
extern Slot34DE8 D_800A6244[4];
extern s32 D_8008B10C;

void PadInitMtap(u8 *a, u8 *b);
void func_8005ED28(void);

void func_80034DE8(void) {
    s32 i;
    Pad34DE8 *p;

    D_8008B128 = 0;
    p = D_800A6084;
    i = 0;
    do {
        i++;
        p->b0 = 0;
        p->b1 = -1;
        p->h2 = 0;
        p->w4 = 0;
        p->w8 = 0;
        p->wC = 0;
        p++;
    } while (i < 10);
    PadInitMtap(D_800A62F4, D_800A6318);
    func_8005ED28();
    for (i = 0; i < 8; i++) {
        D_800A6294[i].w4 = 0;
        D_8008B100[i] = -1;
    }
    for (i = 0; i < 0x22; i++) {
        ((volatile u8 *) D_800A62F4)[i] = 0;
    }
    for (i = 0; i < 0x22; i++) {
        ((volatile u8 *) D_800A6318)[i] = 0;
    }
    for (i = 3; i >= 0; i--) {
        D_800A6244[i].w0 = 0;
    }
    D_8008B10C = 0;
}
