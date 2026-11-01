/* cflags: -O3 */
#include "common.h"

typedef struct {
    u8 pad0[2];
    u8 f2;
    s8 f3;
    s32 f4;
    u8 *p8;
} Rec_8004E7EC;

typedef struct {
    u8 pad0[4];
    s32 f4;
    s16 f8;
    s16 fA;
} Attr_8004E7EC;

extern s32 D_80082944[];
extern volatile s32 D_80082948[3];
extern u8 D_80010848[];
extern u8 D_80010870[];

Rec_8004E7EC *func_8004F1E0(u8);
void SpuSetVoiceAttr(Attr_8004E7EC *);

#define MIN_8004E7EC(a, b) ((a) < (b) ? (a) : (b))
#define MAX_8004E7EC(a, b) ((a) < (b) ? (b) : (a))

s32 func_8004E7EC(u8 a0, s32 a1) {
    Rec_8004E7EC *p;
    Attr_8004E7EC *attr;
    s32 v;
    u32 l;
    u32 r;
    s32 f;

    if (!D_80082944[0]) {
        printf(D_80010848, D_80010870, 0x2A3);
        exit(1);
    }
    D_80082948[0]++;
    p = func_8004F1E0(a0);
    if (p) {
        p->f3 = MIN_8004E7EC(MAX_8004E7EC((s8) a1 + ((s8 *) p->p8)[5], -0x7F), 0x7F);
        f = p->f3;
        if (f > 0) {
            r = p->f2;
            l = ((r * (0x7F - f)) >> 7) & 0xFF;
        } else if (f < 0) {
            l = p->f2;
            r = ((l * (0x7F + f)) >> 7) & 0xFF;
        } else {
            l = p->f2;
            r = l;
        }
        attr = (Attr_8004E7EC *) ((u8 *) p + 0xC);
        attr->f4 = 3;
        attr->f8 = l << 7;
        attr->fA = r << 7;
        SpuSetVoiceAttr(attr);
    }
    D_80082948[0]--;
    return 0;
}
