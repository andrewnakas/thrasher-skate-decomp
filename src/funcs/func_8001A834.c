#include "common.h"

typedef struct {
    s16 count;
    u16 base;
    u8 keys[1];
} Remap_8001A834;

typedef struct {
    u16 base;
    volatile u8 count;
} Def_8001A834;

typedef struct {
    u16 id;
    u8 pad2[2];
    s32 remapA;
    s32 remapB;
} Req_8001A834;

typedef struct {
    u8 pad0[0x20];
    s32 chan[12];
} Obj_8001A834;

extern void func_8001C2B8(s32, u16, u16, s32, s32);
extern Def_8001A834 *func_8001D198(u16);
extern Remap_8001A834 *func_8001D1E8(u16, s32, u16);

void func_8001A834(Obj_8001A834 *o, Req_8001A834 *r, s32 arg2) {
    Remap_8001A834 *ma;
    Remap_8001A834 *mb;
    Def_8001A834 *d;
    u8 n;
    s32 i;
    s32 j;
    s32 v;
    s32 first;

    mb = ma = NULL;
    first = arg2;
    if (r->remapA != 0) {
        ma = func_8001D1E8(r->id, 0, r->remapA);
    }
    if (r->remapB != 0) {
        mb = func_8001D1E8(r->id, 1, r->remapB);
        do {
            n = 12;
        } while (0);
    } else {
        do {
            n = 12;
        } while (0);
    }
    d = func_8001D198(r->id);
    do {
        if (n > d->count) {
            n = d->count;
        }
    } while (0);
    do {
        for (i = 0; i < n; i++) {
            v = d->base + i;
            if (ma != NULL) {
                j = ma->count;
                for (j--; j != -1; j--) {
                    if (ma->keys[j] == i) {
                        v = ma->base + j;
                        break;
                    }
                }
            }
            if (mb != NULL) {
                j = mb->count;
                for (j--; j != -1; j--) {
                    if (mb->keys[j] == i) {
                        v = mb->base + j;
                        break;
                    }
                }
            }
            func_8001C2B8(o->chan[i], v, first + i, 0, 0);
        }
    } while (0);
}
