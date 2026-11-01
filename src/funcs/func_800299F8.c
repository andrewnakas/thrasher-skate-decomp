#include "common.h"

typedef struct {
    s16 lo;
    s16 hi;
} Pair299F8;

typedef struct {
    u8 pad0[0xC];
    Pair299F8 v[7];
    u8 data[1];
} Chunk299F8;

typedef struct {
    u16 h0;
    u16 h2;
    s32 w[7];
    u8 tail[1];
} Info299F8;

typedef struct {
    u8 pad0[0x2C];
    Info299F8 *info;
} Obj299F8;

typedef struct {
    u8 pad0[0x1E];
    u16 h1E;
    u16 h20;
} Src299F8;

extern s32 D_8008B004;

Chunk299F8 *func_8001D5B0(s32, s32, s32);
void *func_80034C20(s32);
void *memset(void *, s32, s32);
void func_80029BBC(Obj299F8 *, s32, u8 *, u8 *);
void func_80029CCC(Obj299F8 *, s32, u8 *, u8 *);

void func_800299F8(s32 ctx, Obj299F8 *obj, Src299F8 *src) {
    s32 g = D_8008B004;
    Chunk299F8 *c;
    Info299F8 *e;
    s32 i;

    c = func_8001D5B0(ctx, 0x4A424F42, 1);
    obj->info = func_80034C20(0x80);
    memset(obj->info, 0, 0x80);
    obj->info->h0 = src->h1E;
    obj->info->h2 = src->h20;
    obj->info->w[0] = c->v[0].hi;
    obj->info->w[1] = c->v[1].hi;
    obj->info->w[2] = c->v[2].hi;
    obj->info->w[3] = c->v[3].hi;
    obj->info->w[4] = c->v[4].hi;
    obj->info->w[5] = c->v[5].hi;
    obj->info->w[6] = c->v[6].hi;
    e = obj->info;
    if (e->h0 == 0) {
        switch ((u32) e->h2) {
        case 3:
            for (i = 0; i < 2; i++) {
                func_80029BBC(obj, g, c->data + i * 0x1C, obj->info->tail + i * 0x30);
            }
            break;
        case 2:
            func_80029BBC(obj, g, c->data, e->tail);
            break;
        case 4:
            func_80029CCC(obj, g, c->data, e->tail);
            break;
        case 0:
            break;
        }
    }
}
