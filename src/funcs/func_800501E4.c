/* D_80082940 via its neighbour (one unsplit lw, like func_8004F5EC) so the gp load of D_8008A99C schedules first. */
#include "common.h"

typedef struct {
    u32 addr;
    u32 size;
} Wave_800501E4;

typedef struct {
    u8 pad0[0x10];
    s32 nInst;
    u8 *inst;
    s32 f18;
    u8 pad1C[4];
    u32 nWave;
    Wave_800501E4 *wave;
    s32 f28;
    u8 pad2C[4];
    s32 f30;
    u8 pad34[0xC];
    s32 f40;
} Bank_800501E4;

typedef struct {
    u32 flags;
    Bank_800501E4 *bank;
    void *buf;
    u8 padC[4];
} Slot_800501E4;

extern Slot_800501E4 D_800B066C[];
extern u8 D_80010888[];
extern s8 D_8008A9A0[];
extern s32 D_8008A97C;
extern s32 D_8008A980;
extern s32 D_8008A984;
extern s32 D_8008A988;
extern s32 D_8008A98C;
extern s32 D_8008A990;
extern s32 D_8008A994;
extern s32 D_8008A998;
extern s32 D_8008A99C;
extern s32 D_8008294C;
#define D_80082940 (*(&D_8008294C - 3))

void func_8004EDF8(u8 *);
void SpuFree(u32);
void func_80034BD8(void *);

void func_800501E4(u16 id) {
    Slot_800501E4 *s = &D_800B066C[id];
    Bank_800501E4 *b = s->bank;
    s32 i;
    u32 total;

    if (!(s->flags & 1)) {
        printf(D_80010888, D_8008A9A0, 0x2C0);
        exit(1);
    }
    for (i = b->nInst - 1; i >= 0; i--) {
        func_8004EDF8(b->inst + i * 20);
    }
    D_8008A97C -= b->nInst;
    D_8008A980 -= b->f18;
    if (s->flags & 2) {
        total = 0;
        for (i = 0; i < b->nWave; i++) {
            total += b->wave[i].size;
        }
        SpuFree(b->wave->addr);
        D_8008A99C -= (total + 0x3F) & ~0x3F;
        D_8008A998 = 0x7EFF0 - D_8008A99C - D_80082940;
        D_8008A984 -= b->nWave;
    } else {
        D_8008A988 -= b->nWave;
    }
    D_8008A98C -= b->f28;
    D_8008A990 -= b->f30;
    D_8008A994 -= b->f40;
    if (s->buf != NULL) {
        func_80034BD8(s->buf);
    }
    s->bank = NULL;
    s->flags = 0;
}
