/* cflags: -O3 */
#include "common.h"

extern u32 D_80082944[3];
extern volatile u32 D_80082948[3];
extern u16 D_800829A0[];
extern u16 D_80082A34[];
extern char D_80010848[];
extern char D_80010870[];

typedef struct {
    u16 unk0;
    u16 unk2;
    u8 pad4[0xE];
    u16 unk12;
} Src_8004E930;

typedef struct {
    u32 voice;
    u32 mask;
    u8 pad8[0xC];
    u16 vol;
} Attr_8004E930;

typedef struct {
    u8 pad0[8];
    Src_8004E930 *src;
    Attr_8004E930 attr;
} Voice_8004E930;

Voice_8004E930 *func_8004F1E0(u8 a0);
u16 *func_8004FE00(u16 a0, u32 a1);

#define MIN_8004E930(a, b) ((a) < (b) ? (a) : (b))
#define MAX_8004E930(a, b) ((a) < (b) ? (b) : (a))

s32 func_8004E930(u8 a0, s16 a1) {
    Voice_8004E930 *v;
    u16 *p;
    Attr_8004E930 *a;
    s32 oct;
    s32 sem;
    s32 idx;

    if (D_80082944[0] == 0) {
        printf(D_80010848, D_80010870, 0x2C9);
        exit(1);
    }
    D_80082948[0]++;
    v = func_8004F1E0(a0);
    if (v != 0) {
        p = func_8004FE00(v->src->unk12, v->src->unk0);
        a = &v->attr;
        if (p == 0) {
            printf(D_80010848, D_80010870, 0x2CE);
            exit(1);
        }
        a->mask = 0x10;
        a->vol = ((u32) p[1] * v->src->unk2) >> 12;
        if (a1 != 0) {
            oct = (s16) (a1 / 100);
            sem = (s16) (a1 % 100);
            while (sem < 0) {
                sem += 100;
                oct--;
            }
            idx = MIN_8004E930(MAX_8004E930(oct, -0x24), 0x24);
            a->vol = ((u32) a->vol * D_800829A0[idx + 0x24]) >> 12;
            a->vol = ((u32) a->vol * D_80082A34[sem]) >> 12;
        }
        SpuSetVoiceAttr(a);
    }
    D_80082948[0]--;
    return 0;
}
