#include "common.h"

typedef struct {
    char name[0x14];
    s32 vals[12];
    u8 pad44[0x18];
    u8 bytes[5];
    u8 pad61;
    u8 b62;
    u8 b63;
    u8 pad64;
    u8 b65;
    u8 pad66[7];
    u8 b6D;
    u8 pad6E[2];
} Rec_80057090;

typedef struct {
    u8 pad0[0x4D0];
    s32 flags;
    Rec_80057090 rec[6];
} Tbl_80057090;

extern Tbl_80057090 D_800B2508;

s32 func_80057090(u8 idx, char *name, u8 *o3, u8 *o4, s32 *sum, u8 *o6, u8 *o7, u8 *o8) {
    s32 i;
    u32 mask;

    if (idx >= 6) {
        return 7;
    }

    if ((D_800B2508.flags & (mask = 1 << idx)) == 0) {
        return 7;
    }
    strcpy(name, D_800B2508.rec[idx].name);
    *o3 = D_800B2508.rec[idx].b65;
    *o4 = D_800B2508.rec[idx].b62;
    *sum = 0;
    for (i = 0; i < 12; i++) {
        *sum += D_800B2508.rec[idx].vals[i];
    }
    for (i = 0; i < 5; i++) {
        o6[i] = D_800B2508.rec[idx].bytes[i];
    }
    *o7 = D_800B2508.rec[idx].b6D;
    *o8 = D_800B2508.rec[idx].b63;
    return 0;
}
