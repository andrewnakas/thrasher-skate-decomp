#include "common.h"

/* 0x10-byte table entry in D_800AB794, indexed by the low word of arg1 */
typedef struct {
    u16 f0;
    u16 f2;
    u8 f4;
    u8 f5;
    u8 f6;
    u8 f7;
    u8 pad8[4];
    u8 fC;
    u8 fD;
    u8 padE[2];
} ENT_8002103C;

/* 0x30-byte sprite record, indexed by the id's low byte */
typedef struct {
    u8 pad0[3];
    u8 f3;
    u8 f4;
    u8 f5;
    u8 f6;
    u8 f7;
    u16 f8;
    u16 fA;
    u8 fC;
    u8 fD;
    u16 fE;
    u16 f10;
    u16 f12;
    u8 f14;
    u8 f15;
    u16 f16;
    u16 f18;
    u16 f1A;
    u8 f1C;
    u8 f1D;
    u16 f20;
    u16 f22;
    u8 f24;
    u8 f25;
    u8 pad26[2];
    u8 f28;
    u8 f29;
    u8 pad2A[6];
} SPR_8002103C;

extern ENT_8002103C D_800AB794[];
extern u32 D_8009C0A4[];
extern s32 D_8009C6D4[];
extern u32 D_8008A2A4;
extern u32 D_8008A2A8;
extern u8 D_8008A2AC;

s32 func_80020D74(s32, s32);
void func_80020C34(s32, u32, u8, s32 *, s32 *, s32 *);

s32 func_8002103C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    ENT_8002103C *e;
    SPR_8002103C *r;
    s32 id;
    u32 i;
    u32 k;

    id = func_80020D74(a0 & 0xFF, 0);
    if (id == -1) {
        return -1;
    }
    func_80020C34((id >> 16) & 0xFF, (id & 0xFF00) >> 8, D_8008A2AC, &sp18, &sp1C, &sp20);
    e = (ENT_8002103C *) ((a1 & 0xFFFF) * 0x10 + D_800AB794);
    r = (SPR_8002103C *) ((id & 0xFF) * 0x30 + sp18);
    r->f3 = 9;
    r->f7 = 0x2C;
    r->f4 = 0xFF;
    r->f5 = 0xFF;
    r->f6 = 0xFF;
    r->fE = e->f2;
    r->f16 = e->f0;
    if ((a4 & 0xFF) != 0) {
        r->f7 |= 2;
    }
    r->f8 = a2;
    r->fA = a3;
    r->fC = e->f4;
    r->fD = e->f5;
    r->f12 = a3;
    r->f10 = e->fC + a2;
    r->f14 = e->f6;
    r->f18 = a2;
    r->f15 = e->f5;
    r->f1A = e->fD + a3;
    r->f1C = e->f4;
    r->f1D = e->f7;
    r->f20 = e->fC + a2;
    r->f22 = e->fD + a3;
    r->f24 = e->f6;
    r->f25 = e->f7;
    r->f28 = 2;
    r->f29 = a4;
    D_8009C0A4[D_8008A2A4++] = id;
    for (i = 0; i < D_8008A2A8; i++) {
        if (D_8009C6D4[i] == id) {
            D_8008A2A8 -= 1;
            for (k = i; k < D_8008A2A8; k++) {
                D_8009C6D4[k] = D_8009C6D4[k + 1];
            }
        }
    }
    return id;
}
