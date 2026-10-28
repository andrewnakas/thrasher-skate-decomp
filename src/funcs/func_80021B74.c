#include "common.h"

typedef struct {
    u8 pad0[0x8];
    u16 x0;             /* 0x8 */
    u16 y0;             /* 0xA */
    u8 padC[0x4];
    u16 x1;             /* 0x10 */
    u16 y1;             /* 0x12 */
    u8 pad14[0x4];
    u16 x2;             /* 0x18 */
    u16 y2;             /* 0x1A */
    u8 pad1C[0x4];
    u16 x3;             /* 0x20 */
    u16 y3;             /* 0x22 */
    u8 pad24[0x8];
    s32 next;           /* 0x2C */
} Rec_80021B74;

extern u8 D_8008A2AC;
extern s32 D_8009C6D4[];
extern u32 D_8009C0A4[];
extern u32 D_8008A2A4;
extern u32 D_8008A2A8;

void func_80020C34(s32, u32, u8, s32 *, s32 *, s32 *);

s32 func_80021B74(u32 arg0, s32 arg1, s32 arg2) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 idx;
    u32 id;
    Rec_80021B74 *rec;
    u32 i;
    u32 k;

    id = arg0;
    func_80020C34((id >> 16) & 0xFF, (id & 0xFF00) >> 8, D_8008A2AC,
                  &sp18, &sp1C, &sp20);
    idx = id & 0xFF;
    if ((u32) idx >= (u32) sp1C) {
        return 1;
    }
    if (idx < 0) {
        return 1;
    }
    while (id != 0xFFFFFFFFU) {
        rec = (Rec_80021B74 *) ((id & 0xFF) * 0x30 + sp18);
        rec->x0 = rec->x0 + arg1;
        rec->y0 = rec->y0 + arg2;
        rec->x1 = rec->x1 + arg1;
        rec->y1 = rec->y1 + arg2;
        rec->x2 = rec->x2 + arg1;
        rec->y2 = rec->y2 + arg2;
        rec->x3 = rec->x3 + arg1;
        rec->y3 = rec->y3 + arg2;
        for (i = 0; i < D_8008A2A8; i++) {
            if (D_8009C6D4[i] == id) {
                D_8008A2A8 -= 1;
                for (k = i; k < D_8008A2A8; k++) {
                    D_8009C6D4[k] = D_8009C6D4[k + 1];
                }
            }
        }
        D_8009C0A4[D_8008A2A4++] = id;
        id = ((Rec_80021B74 *) ((id & 0xFF) * 0x30 + sp18))->next;
    }
    return 0;
}
