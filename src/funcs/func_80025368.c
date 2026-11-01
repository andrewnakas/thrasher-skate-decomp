#include "common.h"

extern s32 D_8008A2BC;
extern s32 D_8008AF34[2];
extern s32 D_8008AF3C[2];
extern s32 D_8008AF44[2];
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

typedef struct {
    u8 pad0[6];
    u16 flags;          /* 0x06 */
    u8 pad8[0x84];
} Ent_80025368;

typedef struct {
    u8 pad0[0x1C];
    s32 used;           /* 0x1C */
} A_80025368;

typedef struct {
    s32 used;           /* 0x00 */
    u8 pad4[0x24];
} B_80025368;

typedef struct {
    u32 count;                  /* 0x0000 */
    u8 pad4[0xAE0 - 4];
    A_80025368 a[42];           /* 0x0AE0 */
    B_80025368 b[1];            /* 0x1020 */
} State_80025368;

extern void func_80024720(State_80025368 *, s32);
extern void func_80025004(State_80025368 *, s32);
extern void func_80024D6C(State_80025368 *, s32);

#define SLOT32(i) (st->a[i].used)
#define SLOT40(i) (st->b[i].used)

void func_80025368(State_80025368 *st, s32 arg1) {
    u32 i;

    func_80024720(st, arg1);
    if (D_8008AF34[D_8008A2BC] != 0) {
        func_80025004(st, arg1);
    }
    if (D_8008AF44[D_8008A2BC] != 0) {
        func_80024D6C(st, arg1);
    }
    D_8008AF3C[D_8008A2BC] = 1;
    for (i = 0; i < st->count; i++) {
        if (((Ent_80025368 *) st)[i].flags & 1) {
            return;
        }
    }
    SLOT32(D_8008A2E0) = 0;
    SLOT32(D_8008A2E4) = 0;
    SLOT32(D_8008A2E8) = 0;
    SLOT32(D_8008A2EC) = 0;
    SLOT32(D_8008A2F0) = 0;
    SLOT32(D_8008A2F4) = 0;
    SLOT32(D_8008A2F8) = 0;
    SLOT32(D_8008A2FC) = 0;
    SLOT40(D_8008A2CC) = 0;
    SLOT40(D_8008A2D4) = 0;
    SLOT40(D_8008A2C8) = 0;
    SLOT40(D_8008A2D0) = 0;
    SLOT40(D_8008A2D8) = 0;
    SLOT40(D_8008A2DC) = 0;
}
