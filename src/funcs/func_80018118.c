#include "common.h"

typedef struct {
    u16 id;
    u16 flags;
    u8 pad4[4];
    s32 mem;
    s32 data;
} Obj18118;

extern s32 D_8008AD64[2];

Obj18118 *func_80019630(u16);
Obj18118 *func_80019670(u16);
s32 func_80036A78(s32, u32, u16);
s32 func_80036B18(s32);
s32 func_800159D8(s32);
void *func_80015E8C(s32);
void func_80036BF4(s32, void *);
void func_80015F10(s32);
Obj18118 *func_80019444(void);
u8 *func_80019518(Obj18118 *);
void func_80039D90(u8 *);
void func_8001954C(Obj18118 *);

Obj18118 *func_80018118(u16 id, s32 flag) {
    Obj18118 *o;
    Obj18118 *src;
    s32 mem;
    s32 data;
    s32 shared;
    u8 *x;

    if ((id & 0xE000) != 0x8000) {
        return 0;
    }
    o = func_80019630(id);
    if (o != 0) {
        return o;
    }
    src = func_80019670(id);
    if (src != 0) {
        shared = 1;
        if (src->flags & 1) {
            flag = 1;
        }
        mem = src->mem;
        data = src->data;
    } else {
        shared = 0;
        data = 0;
        if (func_80036A78(D_8008AD64[0], id, 0) != 0) {
            return 0;
        }
        mem = func_800159D8(func_80036B18(D_8008AD64[0]));
        if (mem == 0) {
            return 0;
        }
        func_80036BF4(D_8008AD64[0], func_80015E8C(mem));
        func_80015F10(mem);
    }
    o = func_80019444();
    if (o == 0) {
        return 0;
    }
    o->flags = 0;
    if (flag) {
        o->flags = 1;
    }
    if (shared) {
        o->flags |= 2;
    }
    o->id = id;
    o->mem = mem;
    o->data = data;
    x = func_80019518(o);
    if (*(s32 *) (x + 0x10) != 0) {
        func_80039D90(x + *(s32 *) (x + 0x10));
    }
    func_8001954C(o);
    return o;
}
