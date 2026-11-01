#include "common.h"

typedef struct {
    u16 flags;
    u8 len;
} Prim_800403DC;

typedef struct {
    u16 pad0;
    u16 n;
    u8 pad4[0x24];
    u8 *prims;
    u8 pad2C[8];
} Group_800403DC;

typedef struct {
    u8 pad0[6];
    u16 nGroups;
    u16 nPrims;
    u8 padA[6];
    Group_800403DC *groups;
} Model_800403DC;

void *func_80034C20(s32);
void func_80034BD8(void *);
void func_80034D4C(void *dst, void *src, s32 n);

void func_800403DC(Model_800403DC *m) {
    u8 *a;
    u8 *b;
    u8 *c;
    u8 *pa;
    u8 *pb;
    u8 *pc;
    u8 *p;
    s32 i;
    s32 j;
    Group_800403DC *g;

    j = m->nPrims * 44;
    a = func_80034C20(j);
    b = func_80034C20(j);
    c = func_80034C20(j);
    i = m->nGroups;
    p = (u8 *) m->groups;
    g = (Group_800403DC *) p;
    while (i > 0) {
        pc = c;
        pa = a;
        pb = b;
        p = g->prims;
        for (j = g->n; j > 0; j--) {
            if (((Prim_800403DC *) p)->flags & 1) {
                if (((Prim_800403DC *) p)->flags & 0x100) {
                    func_80034D4C(pc, p, ((Prim_800403DC *) p)->len);
                    pc += ((Prim_800403DC *) p)->len;
                } else {
                    func_80034D4C(pb, p, ((Prim_800403DC *) p)->len);
                    pb += ((Prim_800403DC *) p)->len;
                }
            } else {
                func_80034D4C(pa, p, ((Prim_800403DC *) p)->len);
                pa += ((Prim_800403DC *) p)->len;
            }
            p += ((Prim_800403DC *) p)->len;
        }
        p = g->prims;
        g++;
        i--;
        j = pa - a;
        func_80034D4C(p, a, j);
        p += j;
        j = pc - c;
        func_80034D4C(p, c, j);
        p += j;
        j = pb - b;
        func_80034D4C(p, b, j);
    }
    func_80034BD8(c);
    func_80034BD8(b);
    func_80034BD8(a);
}
