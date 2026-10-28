#include "common.h"

typedef struct {
    u32 f00;
    u32 f04;
    u32 f08;
    u8 pad0C[2];
    u16 f0E;
} Rec_800579E0;

typedef struct {
    u8 pad00[0x69];
    u8 f69;
    u8 f6A;
    u8 pad6B[5];
} Ent_800579E0;

extern u8 D_800B2428[];
extern u8 D_800B2C7C[];
extern u8 D_800B2CDC[];
extern u8 D_800B2D5C[];

s32 func_80055D58();

s32 func_800579E0(s32 a0, s32 a1, s32 a2) {
    Ent_800579E0 *ent;
    Rec_800579E0 *rec;
    u8 *tbl;
    u32 mask;
    s32 r;

    if (func_80055D58(a0, a1, a2) != 4) {
        tbl = D_800B2428;
        ent = (Ent_800579E0 *) (a0 * 0x70 + (s32) tbl);
        rec = (Rec_800579E0 *) (ent->f69 * 0x30 + (s32) D_800B2C7C);
        if ((rec->f0E & 1) != 0) {
            rec = 0;
            mask = 0;
        } else if (*(s8 *) rec->f00 == 2) {
            mask = *(u32 *) (a1 * 4 + (s32) D_800B2D5C);
        } else {
            mask = *(u32 *) (a1 * 4 + ent->f6A * 0x28 + (s32) D_800B2CDC);
        }
    } else {
        rec = (Rec_800579E0 *) D_800B2C7C;
        mask = *(u32 *) (a1 * 4 + (s32) D_800B2CDC);
    }

    if (rec == 0) {
        return 0;
    }
    if (a2 == 1) {
        if ((rec->f04 & mask) != mask) {
            r = 0;
        } else {
            r = (rec->f08 & mask) != 0;
        }
    } else if (a2 == 0) {
        r = (((rec->f04 & rec->f08) & mask) ^ mask) < 1;
    } else if (a2 == 2) {
        r = ((rec->f04 & mask) ^ mask) < 1;
    } else if (a2 == 3) {
        r = ((~rec->f04 & rec->f08) & mask) != 0;
    } else {
        r = 0;
    }
    return r;
}
