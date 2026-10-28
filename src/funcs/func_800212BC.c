#include "common.h"

/* Table entry, 0x10 bytes, indexed by the low half-word of arg1. */
typedef struct {
    u8 pad0[0x4];
    u8 f4;              /* 0x4 */
    u8 pad5[0x7];
    u8 fC;              /* 0xC */
    u8 padD[0x3];
} T_800212BC_ent;

/* Active record, 0x30 bytes, indexed by the low byte of arg0. */
typedef struct {
    u8 pad0[0x8];
    u16 f8;             /* 0x8 */
    u8 padA[0x6];
    s16 f10;            /* 0x10 */
    u8 pad12[0x2];
    s8 f14;             /* 0x14 */
    u8 pad15[0xB];
    s16 f20;            /* 0x20 */
    u8 pad22[0x2];
    s8 f24;             /* 0x24 */
    u8 pad25[0x3];
    u8 f28;             /* 0x28 */
    u8 pad29[0x7];
} T_800212BC_rec;

extern u8 D_800AB794[];
extern s32 D_8009C6D4[];
extern u32 D_8009C0A4[];
extern u32 D_8008A2A4;
extern u32 D_8008A2A8;
extern u8 D_8008A2AC;

s32 func_80020C34(s32, u32, u8, s32 *, s32 *, s32 *);

s32 func_800212BC(u32 arg0, s32 arg1, u32 arg2) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    T_800212BC_ent *entry;
    T_800212BC_rec *rec;
    u32 var_s0;
    u32 i;
    u32 k;

    var_s0 = arg2;
    if (arg0 != 0xFFFFFFFFU) {
        entry = (T_800212BC_ent *) (((arg1 & 0xFFFF) * 0x10) + D_800AB794);
        if (entry->fC < var_s0) {
            var_s0 = entry->fC;
        }
        func_80020C34((arg0 >> 16) & 0xFF, (arg0 & 0xFF00) >> 8, D_8008A2AC, &sp18, &sp1C, &sp20);
        rec = (T_800212BC_rec *) ((arg0 & 0xFF) * 0x30 + sp18);
        if (rec->f28 == 2) {
            rec->f10 = rec->f8 + var_s0;
            rec->f14 = entry->f4 + var_s0;
            rec->f20 = rec->f8 + var_s0;
            rec->f24 = entry->f4 + var_s0;
            for (i = 0; i < D_8008A2A8; i++) {
                if (D_8009C6D4[i] == arg0) {
                    D_8008A2A8 -= 1;
                    for (k = i; k < D_8008A2A8; k++) {
                        D_8009C6D4[k] = D_8009C6D4[k + 1];
                    }
                }
            }
            D_8009C0A4[D_8008A2A4++] = arg0;
            return arg0;
        }
    }
    return -1;
}
