#include "common.h"

typedef struct {
    s32 fd;
    s32 id;
    u16 h;
    u16 w;
    u8 pad0C[4];
    u8 *data;
    s32 size;
    u16 f18;
    u16 f1A;
    u8 f1C;
    u8 pad1D;
    u16 f1E;
} Obj;

typedef struct {
    s32 id;
    u8 pad[0x5C];
} FileEnt;

typedef struct {
    u16 a;
    u16 b;
} Hdr;

extern FileEnt D_800A677C[];
extern s8 D_8008A5EC[];

void *func_80034C20(s32);
void func_80034BD8(void *);
s32 func_800363F8(u8 *, s32, s32);
void func_80036020(void);
void func_800366D0(s32, s32, s32);
s32 func_80035F5C(s32, void *, s32);
void func_80034D4C(void *, void *, s32);
void func_80036074(void);
void func_80036758(s32);

Obj *func_8003682C(u8 *name) {
    Hdr hdr;
    s32 buf[7];
    Obj *o;
    s32 fd;
    s32 off;

    o = func_80034C20(0x128);
    if (o == NULL) {
        return NULL;
    }
    fd = func_800363F8(name, 0, 0);
    if (fd == 0) {
        func_80034BD8(o);
        return NULL;
    }
    func_80036020();
    func_800366D0(fd, 0, 0);
    if (func_80035F5C(fd, buf, 0x1C) == 0) {
        goto fail;
    }
    if (buf[0] == 0x2A81511C) {
        off = 0x10;
    } else {
        off = 8;
    }
    func_80034D4C(&hdr, (u8 *) buf + off, 4);
    o->fd = fd;
    o->id = D_800A677C[fd - 1].id;
    off += 4;
    o->f18 = ((hdr.a & 0x8000) >> 14) + (hdr.b >> 15);
    o->f1A = (hdr.b & 0x4000) >> 14;
    if (o->f18 == 0) {
        o->f1E = 8;
    } else {
        o->f1E = 0xC;
    }
    o->h = hdr.b & 0x3FFF;
    o->w = hdr.a & 0x1FFF;
    o->size = o->h * (o->f1E * o->w + 4);
    o->f1C = (hdr.a >> 13) & 1;
    if (o->f1C) {
        printf(D_8008A5EC, name);
    }
    o->data = func_80034C20(o->size);
    if (o->data == NULL) {
        func_80036074();
        return NULL;
    }
    func_800366D0(fd, off, 0);
    if (func_80035F5C(fd, o->data, o->size) == 0) {
    fail:
        func_80036074();
        func_80036758(fd);
        return NULL;
    }
    func_80036074();
    return o;
}
