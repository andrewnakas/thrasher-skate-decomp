/* a4 r6: for+break search, r = &tbl[i] inside the found arm, unkE = 1 literal, found = 1 last. */
#include "common.h"

extern s32 D_8008A570;
extern s32 D_8008B10C;
extern s8 D_8008B100[8];

typedef struct {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[4];
} Sub_800358A8;

typedef struct {
    u8 pad0[8];
    s8 slot;
    s8 unk9;
    s8 unkA;
    s8 unkB;
    s8 unkC;
    s8 unkD;
    s8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 pad13;
} Rec_800358A8;

extern Sub_800358A8 D_800A6294[];
extern Rec_800358A8 D_800A6244[];

void func_8003599C(void);

void func_800358A8(void) {
    s32 i;
    s32 k;
    s32 found;
    Rec_800358A8 *r;

    if (D_8008A570 == 0) {
        func_8003599C();
    }
    D_8008B10C = 0;

    for (i = 0; i < 4; i++) {
        if (D_800A6244[i].slot != -1) {
            continue;
        }
        found = 0;
        for (k = 0; k < 8; k++) {
            if (D_800A6294[k].unk4 != -1 && D_8008B100[k] == -1) {
                r = &D_800A6244[i];
                r->slot = k;
                D_8008B100[k] = i;
                r->unk9 = 0;
                r->unkA = 0;
                r->unkB = 0;
                r->unkC = 0;
                r->unkD = 0;
                r->unkE = 1;
                r->unkF = 0xFF;
                r->unk10 = 0xFF;
                r->unk11 = 0xFF;
                r->unk12 = 0xFF;
                found = 1;
                break;
            }
        }
        if (found == 0) {
            D_800A6244[i].slot = -1;
            D_8008B10C = 1;
        }
    }
}
