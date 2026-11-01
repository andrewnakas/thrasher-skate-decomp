#include "common.h"

typedef struct {
    u8 type;
    u8 pad1;
    u16 ref;
    u16 l;
    u16 r;
    s32 x;
    s32 pad0C;
    s32 z;
    s32 y;
} Rec_800280BC;

typedef struct {
    u8 pad0[0xA];
    u16 count;
    Rec_800280BC recs[1];
} Res_800280BC;

typedef struct {
    u8 type;
    u8 flag;
    s16 w;
    s32 ref;
    void *l;
    void *r;
} Node_800280BC;

typedef struct {
    u8 pad0[4];
    Node_800280BC *nodes;
    u8 pad8[0x20];
    Node_800280BC *root;
} Obj_800280BC;

typedef struct {
    u8 pad0[0x1C];
    u16 root;
} Arg_800280BC;

extern u8 *func_8001D5B0(u8 *a, u32 tag, s32 n);
extern void *func_80034C20(u32);
extern void func_80034BD8(void *);
extern s32 *D_8008B004;
extern s32 D_8008AFD8;
extern s32 D_8008AFDC;

void func_800280BC(u8 *a0, Obj_800280BC *obj, Arg_800280BC *arg) {
    Res_800280BC *res;
    Node_800280BC **table;
    Node_800280BC **t;
    Node_800280BC *n;
    Rec_800280BC *rec;
    s32 i;
    Node_800280BC *root;
    s32 v;

    res = (Res_800280BC *) func_8001D5B0(a0, 0x45444F4E, 1);
    obj->nodes = func_80034C20(res->count * 16);
    table = func_80034C20(res->count * 4);
    if (arg->root != 0) {
        root = (Node_800280BC *) ((u8 *) obj->nodes + arg->root * 16 - 16);
    } else {
        root = NULL;
    }
    rec = res->recs;
    obj->root = root;
    n = obj->nodes;
    t = table;
    for (i = res->count - 1; i >= 0; i--) {
        *t = n;
        n->type = rec->type;
        t++;
        if (rec->ref != 0) {
            v = D_8008B004[rec->ref - 1];
        } else {
            v = 0;
        }
        n->ref = v;
        if (n->type == 0x6C) {
            D_8008AFD8++;
            n = (Node_800280BC *) ((u8 *) n + 8);
        } else {
            if (rec->x == 0x10000) {
                n->flag = 0;
            } else if (rec->z == 0x10000) {
                n->flag = 2;
            }
            n->w = rec->y >> 16;
            n++;
        }
        rec++;
    }
    n = obj->nodes;
    rec = res->recs;
    for (i = res->count - 1; i >= 0; i--) {
        if (n->type == 0x6C) {
            n = (Node_800280BC *) ((u8 *) n + 8);
        } else {
            if (rec->l != 0) {
                v = (s32) table[rec->l - 1];
            } else {
                v = 0;
            }
            n->l = (void *) v;
            if (rec->r != 0) {
                v = (s32) table[rec->r - 1];
            } else {
                v = 0;
            }
            n->r = (void *) v;
            n++;
        }
        rec++;
    }
    func_80034BD8(table);
    func_80034BD8(n);
    D_8008AFDC += res->count;
}
