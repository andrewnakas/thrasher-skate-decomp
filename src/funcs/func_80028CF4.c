#include "common.h"

typedef struct {
    u8 type;
    u8 pad1[3];
    u16 x;
    u16 y;
    u16 z;
    u16 len;
    s32 dx;
    s32 dy;
    s32 dz;
    u8 pad18[0xC];
    s32 nx;
    s32 ny;
    s32 nz;
} Rec_80028CF4;

typedef struct {
    u8 pad0[0xA];
    u16 count;
    Rec_80028CF4 recs[1];
} Res_80028CF4;

typedef struct {
    u8 flags;
    u8 type;
    s16 x0;
    s16 y0;
    s16 z0;
    s16 x1;
    s16 y1;
    s16 z1;
    u16 len;
    s32 dx;
    s32 dy;
    s32 dz;
} Edge_80028CF4;

typedef struct Node_80028CF4 {
    u8 pad0[0x24];
    Edge_80028CF4 *edges;
    s16 n;
    u8 pad2A[0x16];
    struct Node_80028CF4 *next;
} Node_80028CF4;

typedef struct {
    u8 pad0[8];
    Node_80028CF4 *nodes;
    Edge_80028CF4 *edges;
    u8 pad10[0xE];
    u16 count;
} Obj_80028CF4;

typedef struct {
    u8 pad0[0x18];
    u32 flags;
} Arg_80028CF4;

extern u8 *func_8001D5B0(u8 *a, u32 tag, s32 n);
extern void *func_80034C20(u32);
extern void func_80034C8C(void *, s32);
extern void func_80034D4C(void *, void *, s32);
extern void func_8002CB00(Edge_80028CF4 *, s32 *);
extern void func_800335B4(s32 *, s32 *, u8 *, s32 *);
extern s32 func_8002FE80(Node_80028CF4 *, void **);
extern u8 D_80089F18[0x100];
extern s32 D_8008AFE8;

#define SIGN(v) ((v) > 0 ? 1 : ((v) < 0 ? -1 : 0))

void func_80028CF4(u8 *a0, Obj_80028CF4 *obj, Arg_80028CF4 *arg) {
    s32 v[4];
    s32 tmp[4];
    void *src;
    Res_80028CF4 *res;
    Rec_80028CF4 *rec;
    Edge_80028CF4 *e;
    Node_80028CF4 *node;
    s32 total;
    s32 i;
    s32 cnt;
    s32 sz;

    obj->edges = NULL;
    total = 0;
    if (arg->flags & 0x04000000) {
        res = (Res_80028CF4 *) func_8001D5B0(a0, 0x45474445, 1);
        obj->count = res->count;
        rec = res->recs;
        total = res->count * sizeof(Edge_80028CF4);
        obj->edges = func_80034C20(total);
        e = obj->edges;
        for (i = res->count - 1; i >= 0; i--) {
            e->flags = 0;
            e->type = rec->type;
            e->x0 = rec->x;
            e->y0 = rec->y;
            e->z0 = rec->z;
            e->len = rec->len;
            e->dx = rec->dx;
            e->dy = rec->dy;
            e->dz = rec->dz;
            e->x1 = e->x0 + ((e->dx * e->len) >> 16);
            e->y1 = e->y0 + ((e->dy * e->len) >> 16);
            e->z1 = e->z0 + ((e->dz * e->len) >> 16);
            if (rec->nx != 0 || rec->ny != 0 || rec->nz != 0) {
                func_8002CB00(e, tmp);
                func_800335B4(v, tmp, D_80089F18, &e->dx);
                if (SIGN(v[0]) != SIGN(rec->nx) || SIGN(v[1]) != SIGN(rec->ny) || SIGN(v[2]) != SIGN(rec->nz)) {
                    e->flags |= 2;
                } else {
                    e->flags |= 1;
                }
            }
            e++;
            rec++;
        }
        D_8008AFE8 += res->count;
    }
    node = obj->nodes;
    e = obj->edges + obj->count;
    while (node != NULL) {
        cnt = func_8002FE80(node, &src);
        if (cnt != 0) {
            sz = cnt * sizeof(Edge_80028CF4);
            total += sz;
            if (e == NULL) {
                e = func_80034C20(total);
                obj->edges = e;
            } else {
                func_80034C8C(obj->edges, total);
            }
            func_80034D4C(e, src, sz);
            node->edges = e;
            node->n = cnt;
            e += cnt;
            obj->count += cnt;
        } else {
            node->edges = NULL;
            node->n = 0;
        }
        D_8008AFE8 += node->n;
        node = node->next;
    }
}
