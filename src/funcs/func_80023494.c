#include "common.h"

/* 0x8C-byte record; the position triple sits at +0x48. */
typedef struct {
    u8 pad0[0x48];
    s32 f48;            /* 0x48 */
    s32 f4C;            /* 0x4C */
    s32 f50;            /* 0x50 */
    u8 pad1[0x8C - 0x54];
} T_80023494_rec;

/* Output block: three 3-word vectors at +0, +0xC, +0x18 and +0x24. */
typedef struct {
    s32 v0[3];          /* 0x0  */
    s32 v1[3];          /* 0xC  */
    s32 v2[3];          /* 0x18 */
    s32 v3[3];          /* 0x24 */
} T_80023494_out;

extern s32 func_80032C28(s32, s32);
extern void func_800330A4(s32 *);
extern void func_80032FE0(s32 *);
extern void func_800335B4(s32 *, s32 *, s32 *, s32 *);

/* Distance triple between two records, folded over a third, then normalised:
   the two subtractions are kept in the +0x18 vector because each is also the
   argument of the fold, and the +0x00 vector is what the caller reads back. */
void func_80023494(T_80023494_rec *arg0, s32 arg1, s32 arg2, s32 arg3, T_80023494_out *out) {
    T_80023494_rec *a;
    T_80023494_rec *b;
    T_80023494_rec *c;
    s32 v;

    a = &arg0[arg2];
    b = &arg0[arg3];
    out->v2[0] = a->f48 - b->f48;
    out->v2[1] = a->f4C - b->f4C;
    out->v2[2] = a->f50 - b->f50;
    v = func_80032C28(out->v2[0], 0x8000);
    c = &arg0[arg1];
    out->v0[0] = c->f48 - (b->f48 + v);
    v = func_80032C28(out->v2[1], 0x8000);
    out->v0[1] = c->f4C - (b->f4C + v);
    v = func_80032C28(out->v2[2], 0x8000);
    out->v0[2] = c->f50 - (b->f50 + v);
    func_800330A4(out->v0);
    func_800330A4(out->v2);
    func_80032FE0(out->v3);
    func_800335B4(out->v1, out->v0, out->v3, out->v2);
}
