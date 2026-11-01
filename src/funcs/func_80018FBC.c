#include "common.h"

typedef struct {
    u8 pad[0x18];
    struct Obj18FBC *slot;
} G18FBC;

typedef struct Obj18FBC {
    u16 id;
    u16 state;
    u8 pad4[4];
    s32 mem;
    s32 wC;
} Obj18FBC;

typedef struct {
    u16 id;
    u8 pad2[6];
} Ent18FBC;

typedef struct {
    u32 count;
    Ent18FBC ent[1];
} Data18FBC;

extern s32 D_8008AD64[2];

s32 func_80036A78(s32, u32, u16);
s32 func_80036B18(s32);
s32 func_800159D8(s32);
Data18FBC *func_80015E8C(s32);
void func_80036BF4(s32, void *);
Obj18FBC *func_80019444(void);
void func_80015F10(s32);
void func_80019570(u16);

s32 func_80018FBC(u16 slot, u16 id) {
    G18FBC *g;
    Obj18FBC *o;
    Data18FBC *d;
    s32 mem;
    u32 i;
    Ent18FBC *e;

    if (slot >= 2) {
        goto fail;
    }
    g = (G18FBC *) &D_8008AD64[slot];
    if (g->slot != 0) {
        return 1;
    }
    if (func_80036A78(D_8008AD64[0], id, 0) != 0) {
        return 1;
    }
    mem = func_800159D8(func_80036B18(D_8008AD64[0]));
    if (mem == 0) {
        return 1;
    }
    d = func_80015E8C(mem);
    func_80036BF4(D_8008AD64[0], d);
    o = func_80019444();
    if (o == 0) {
    fail:
        return 1;
    }
    o->state = 1;
    o->id = id;
    o->mem = mem;
    o->wC = 0;
    g->slot = o;
    func_80015F10(mem);
    e = d->ent;
    for (i = 0; i < d->count; i++) {
        func_80019570(e->id);
        e++;
    }
    return 0;
}
