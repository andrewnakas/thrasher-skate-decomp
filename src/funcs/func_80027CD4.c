#include "common.h"

typedef struct {
    u16 flags;
    u8 b2;
    u8 b3;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    u16 e;
    u16 refs[4];
    u16 ext[4];
} Rec_80027CD4;

typedef struct {
    u8 pad0[0xA];
    u16 count;
    u16 w[4];
    Rec_80027CD4 recs[1];
} Res_80027CD4;

typedef struct {
    u16 flags;
    u8 size;
    u8 b3;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    union {
        s32 v;
        u16 idx;
    } e;
    u8 idx[4];
    u8 *ptr[3];
    s16 ext[8];
} Node_80027CD4;

typedef struct {
    u8 *verts;
    Node_80027CD4 *nodes;
    u16 pad8;
    u16 count;
    u8 b[4];
    u8 pad10[8];
} Sub_80027CD4;

typedef struct {
    u8 pad0[0x48];
    Sub_80027CD4 sub[1];
} Obj_80027CD4;

typedef struct {
    u8 pad0[0xA];
    u8 n;
} Arg_80027CD4;

extern u8 *func_8001D5B0(u8 *a, u32 tag, s32 n);
extern void *func_80034C20(u32);
extern void *func_80034CF0(s32);
extern void func_80034BD8(void *);
extern void func_8002DCCC(Node_80027CD4 *);
extern void *memset(void *, s32, u32);
extern u8 D_8006F82C[];
extern s32 D_8008AFE0;
extern Node_80027CD4 **D_8008B004[2];

void func_80027CD4(u8 *a0, Obj_80027CD4 *obj, Arg_80027CD4 *arg) {
    s32 i;
    s32 first;
    Res_80027CD4 *res;
    Rec_80027CD4 *rec;
    Node_80027CD4 *n;
    Node_80027CD4 *m;
    Node_80027CD4 **t;
    s32 j;
    u32 k;
    s32 r;
    s32 q;
    u8 *p;
    s16 *x;
    Node_80027CD4 *end;

    first = 1;
    for (i = 0; i < arg->n; i++) {
        res = (Res_80027CD4 *) func_8001D5B0(a0, 0x45434146, first);
        j = 0;
        obj->sub[i].nodes = func_80034C20(res->count * 0x38);
        for (; j < 4u; j++) {
            obj->sub[i].b[j] = res->w[j];
        }
        rec = res->recs;
        D_8008B004[i] = func_80034CF0(res->count * 4);
        memset(D_8008B004[i], 0, res->count * 4);
        t = D_8008B004[i];
        n = obj->sub[i].nodes;
        for (j = res->count - 1; j >= 0; j--) {
            if (rec->flags == 0xFFFF) {
                *t++ = NULL;
                rec++;
            } else {
                *t++ = n;
                n->flags = rec->flags;
                n->size = D_8006F82C[n->flags & 3];
                n->a = rec->a;
                n->b = rec->b;
                n->c = rec->c;
                n->d = rec->d;
                if (abs(n->b) < 0x1999) {
                    n->flags |= 0x80;
                }
                r = 2;
                n->e.v = rec->e;
                if (n->flags & 1) {
                    r = 3;
                }
                for (q = 0; r >= 0; r--, q++) {
                    if (rec->refs[r] != 0) {
                        p = obj->sub[i].verts + rec->refs[r] * 0xC - 0xC;
                    } else {
                        p = NULL;
                    }
                    n->ptr[q] = p;
                    n->idx[q] = rec->refs[r] != 0 ? (u8) rec->refs[r] - 1 : 0;
                }
                if (n->flags & 1) {
                    if (n->flags & 2) {
                        x = n->ext;
                        x[2] = rec->ext[3];
                        x[3] = rec->ext[2];
                        x[4] = rec->ext[1];
                        x[5] = rec->ext[0];
                        x[6] = rec->b2 - 1;
                    }
                } else {
                    if (n->flags & 2) {
                        x = n->ext;
                        x[0] = rec->ext[2];
                        x[1] = rec->ext[1];
                        x[2] = rec->ext[0];
                        x[3] = rec->b2 - 1;
                    }
                }
                n->b3 = rec->b3;
                if (n->b3) {
                    func_8002DCCC(n);
                }
                rec++;
                n = (Node_80027CD4 *) ((u8 *) n + n->size);
                obj->sub[i].count++;
            }
        }
        end = n;
        n = obj->sub[i].nodes;
        for (j = obj->sub[i].count - 1; j >= 0; j--) {
            u16 ix = n->e.idx;

            if (ix != 0) {
                n->e.v = (s32) D_8008B004[i][ix - 1];
            } else {
                n->e.v = 0;
            }
            n = (Node_80027CD4 *) ((u8 *) n + n->size);
        }
        D_8008AFE0 += obj->sub[i].count;
        func_80034BD8(end);
        first = 0;
    }
}
