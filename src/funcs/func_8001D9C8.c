/* a4 r5: fail path written out at the !found and init==NULL sites (cross-jumped; loop.c moves found=1 after the barrier); flags before type. */
#include "common.h"

typedef struct Obj_8001D9C8 {
    u16 flags;
    u16 type;
    s32 f4;
    struct Obj_8001D9C8 **owner;
    u8 padC[0x2C];
    s32 color;
    s32 sx;
    s32 sy;
    u8 pad44[0x28];
} Obj_8001D9C8;

typedef struct {
    s32 (*init)(Obj_8001D9C8 *, s32);
    s32 f4;
    s32 pad8;
    u16 flags;
    u8 padE[0x36];
} ObjDef_8001D9C8;

extern s32 D_8008AEAC;
extern Obj_8001D9C8 *D_8008AEB0;
extern ObjDef_8001D9C8 *D_8008AEC4;
extern char D_8008A1DC[];
extern char D_8008A1F0[];

char *func_80020048(u16 i);
void func_8001DC58(Obj_8001D9C8 *s, s32 v);

Obj_8001D9C8 *func_8001D9C8(u32 type, s32 arg, Obj_8001D9C8 **out) {
    s32 n = D_8008AEAC;
    Obj_8001D9C8 *o = D_8008AEB0;
    s32 found = 0;
    ObjDef_8001D9C8 *def;
    char *name;
    char buf[0x40];

    for (; n > 0; n--, o++) {
        if (!(o->flags & 1)) {
            found = 1;
            break;
        }
    }
    if (!found) {
        if (out != NULL) {
            *out = NULL;
        }
        return NULL;
    }
    if (type >= 0x12) {
        goto fail;
    }
    if (D_8008AEC4[type].init == NULL) {
        name = func_80020048(type);
        if (name != NULL) {
            sprintf(buf, D_8008A1DC, name);
        } else {
            sprintf(buf, D_8008A1F0, type);
        }
        if (out != NULL) {
            *out = NULL;
        }
        return NULL;
    }
    memset(o, 0, sizeof(Obj_8001D9C8));
    def = &D_8008AEC4[type];
    o->flags = def->flags;
    o->type = type;
    o->f4 = def->f4;
    if (o->flags & 0x10) {
        o->sx = 0x10000;
        o->sy = 0x10000;
    }
    if (o->flags & 2) {
        o->color = 0x808080;
    }
    o->flags |= 1;
    if (def->init(o, arg) != 0) {
        o->flags &= ~1;
    fail:
        if (out != NULL) {
            *out = NULL;
        }
        return NULL;
    }
    func_8001DC58(o, 0);
    o->owner = out;
    if (out != NULL) {
        *out = o;
    }
    return o;
}
