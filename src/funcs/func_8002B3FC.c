#include "common.h"

typedef struct {
    s32 x, y, z;
} Vec_8002B3FC;

typedef struct {
    u32 flags;
} Zone_8002B3FC;

typedef struct {
    u8 pad0[0xA];
    s16 x;
    s16 y;
    s16 z;
    u8 pad10[0xC];
    s32 inside;
    u8 pad20[0xC];
    s32 grid;
    u8 pad30[0xC];
    Zone_8002B3FC *zone;
} Ent_8002B3FC;

extern Zone_8002B3FC **func_8002C1B4(Vec_8002B3FC *, s32);
extern s32 func_8002B674(Ent_8002B3FC *, Zone_8002B3FC *);
extern void func_8002B564(Ent_8002B3FC *, Zone_8002B3FC *);
extern void func_8002B2B0(Ent_8002B3FC *, Zone_8002B3FC *);
extern void func_8002B57C(Ent_8002B3FC *, Zone_8002B3FC *);
extern void func_8002AEF4(Ent_8002B3FC *);
extern void func_8002B060(Ent_8002B3FC *);

void func_8002B3FC(Ent_8002B3FC *e) {
    Vec_8002B3FC tmp;
    Vec_8002B3FC v;
    Zone_8002B3FC **list;
    Zone_8002B3FC *z;
    s32 left;

    v.x = e->x << 16;
    v.y = e->y << 16;
    left = 0;
    v.z = e->z << 16;
    tmp = v;
    list = func_8002C1B4(&tmp, e->grid);
    z = e->zone;
    do {
        if (func_8002B674(e, z) != 0) {
            if (e->zone != z) {
                if (e->zone == NULL) {
                    func_8002B564(e, z);
                } else {
                    func_8002B2B0(e, z);
                }
            }
        } else if (e->zone == z) {
            func_8002B57C(e, z);
            left = 1;
        }
        z = *list++;
    } while (z != NULL);
    if (left) {
        if (e->zone->flags & 0x40) {
            if (e->inside == 0) {
                func_8002AEF4(e);
            }
        } else if (e->inside != 0) {
            func_8002B060(e);
        }
    }
}
