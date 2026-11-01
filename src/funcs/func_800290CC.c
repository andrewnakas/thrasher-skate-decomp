#include "common.h"

typedef struct {
    u16 id;
    s16 v[6];
    u16 a;
    u16 b;
    u16 c;
} LiteRec;

typedef struct {
    u8 pad0[0xA];
    u16 n;
    LiteRec rec[1];
} LiteChunk;

typedef struct {
    u16 id;
    s16 a;
    s16 b;
    s16 c;
    s32 pos[3];
    s32 dir[3];
} Light;

typedef struct {
    u8 pad0[0x10];
    Light *lights;
    u8 pad14[0xC];
    u16 nLights;
} LiteOwner;

typedef struct {
    u8 pad0[0x18];
    u32 flags;
} LiteSrc;

void *func_8001D5B0(s32, s32, s32);
void *func_80034C20(s32);
s32 func_80049BF4(s32 *a0, s32 *a1, s16 a2, s16 a3, s16 a4);

void func_800290CC(s32 file, LiteOwner *o, LiteSrc *src) {
    LiteChunk *ch;
    LiteRec *r;
    Light *l;
    s32 i;

    if (!(src->flags & 0x2000000)) {
        return;
    }
    ch = func_8001D5B0(file, 0x4554494C, 1);
    o->nLights = ch->n;
    r = ch->rec;
    o->lights = func_80034C20(ch->n * 32);
    l = o->lights;
    for (i = ch->n - 1; i >= 0; i--) {
        l->id = r->id;
        l->pos[0] = r->v[0] << 16;
        l->pos[1] = r->v[1] << 16;
        l->pos[2] = r->v[2] << 16;
        l->dir[0] = r->v[3] << 16;
        l->dir[1] = r->v[4] << 16;
        l->dir[2] = r->v[5] << 16;
        l->a = r->a;
        l->b = r->b;
        l->c = r->c;
        func_80049BF4(l->pos, l->dir, l->a, l->b, l->c);
        l++;
        r++;
    }
}
