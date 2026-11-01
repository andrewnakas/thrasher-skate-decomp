#include "common.h"

typedef struct {
    u16 x;
    u8 pad2[2];
    u16 y;
    u8 pad6[2];
    u16 z;
    u8 padA[2];
    s32 w;
} SrcV27BA0;

typedef struct {
    u8 pad0[0xA];
    u16 n;
    SrcV27BA0 v[1];
} Chunk27BA0;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u8 pad6[2];
    s32 w;
} DstV27BA0;

typedef struct {
    DstV27BA0 *verts;
    u8 pad4[4];
    u16 nverts;
    u8 padA[0xE];
} Part27BA0;

typedef struct {
    u8 pad0[0x48];
    Part27BA0 parts[1];
} Obj27BA0;

typedef struct {
    u8 pad0[0xA];
    u8 cnt;
} Hdr27BA0;

extern s32 D_8008AFE4;
extern s32 D_8008B084;

Chunk27BA0 *func_8001D5B0(s32 ctx, s32 tag, s32 first);
DstV27BA0 *func_80034C20(s32 size);

void func_80027BA0(s32 ctx, Obj27BA0 *obj, Hdr27BA0 *hdr) {
    Chunk27BA0 *c;
    s32 i;
    s32 j;
    s32 first;
    s32 n;
    DstV27BA0 *d;
    SrcV27BA0 *sv;

    for (i = 0, first = 1; i < hdr->cnt; i++, first = 0) {
        c = func_8001D5B0(ctx, 0x54524556, first);
        obj->parts[i].verts = func_80034C20(c->n * 12);
        obj->parts[i].nverts = c->n;
        d = obj->parts[i].verts;
        sv = c->v;
        for (j = c->n - 1; j >= 0; j--) {
            d->x = sv->x;
            d->y = sv->y;
            d->z = sv->z;
            d->w = sv->w;
            d++;
            sv++;
        }
        D_8008AFE4 += c->n;
        n = c->n;
        if (n < D_8008B084) {
            n = D_8008B084;
        }
        D_8008B084 = n;
    }
}
