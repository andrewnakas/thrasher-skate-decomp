#include "common.h"

typedef struct {
    u8 pad0[0x10];
    u32 dist;
    u8 pad14[4];
} Lod_8002BD64;

typedef struct Obj_8002BD64 {
    u32 flags;
    u8 pad4[0x18];
    u16 nlod;
    u8 pad1E[0x2A];
    Lod_8002BD64 lod[3];
    Lod_8002BD64 *cur;
    struct Obj_8002BD64 *next;
} Obj_8002BD64;

typedef struct {
    u8 pad0[0x54];
    s32 node;
} Cam_8002BD64;

extern u8 *func_8002BF9C(s32, s16 *);
extern s32 func_8003C77C(Obj_8002BD64 *, s32 *);
extern s32 func_8003C8C4(Obj_8002BD64 *);
extern void func_8002A9E0(Obj_8002BD64 *);
extern void func_8002B0E0(Obj_8002BD64 *);
extern void func_8002B124(Obj_8002BD64 *);
extern void func_8002BCB0(Obj_8002BD64 *);
extern void func_8002BCF4(Obj_8002BD64 *);
extern Obj_8002BD64 *D_800A4F04[];
extern Obj_8002BD64 **D_8008B328;
#define D_8008B324 (*(&D_8008B328 - 1))

void func_8002BD64(Cam_8002BD64 *cam, s16 *pos) {
    s32 d;
    s32 lim;
    u32 *p;
    u32 bits;
    u32 mask;
    Obj_8002BD64 *o;
    s32 i;
    Lod_8002BD64 *l;

    mask = 0;
    bits = 0;
    p = (u32 *) (func_8002BF9C(cam->node, pos) + 0xC);
    o = D_800A4F04[0];
    lim = 0xC5C0FF;
    do {
        mask <<= 1;
        if (mask == 0) {
            mask = 1;
            bits = *p++;
        }
        if (!(bits & mask) || func_8003C77C(o, &d) != 0) {
            if (o->flags & 0x40) {
                func_8002B124(o);
                func_8002BCF4(o);
            }
            o->flags &= ~0x41;
            if (o->flags & 8) {
                d = func_8003C8C4(o);
                if (d <= lim) {
                    func_8002A9E0(o);
                }
            }
        } else {
            if (d < 0x2710000) {
                if (!(o->flags & 0x40)) {
                    o->flags |= 0x40;
                    func_8002B0E0(o);
                    func_8002BCB0(o);
                }
            } else {
                if (o->flags & 0x40) {
                    o->flags &= ~0x40;
                    func_8002B124(o);
                    func_8002BCF4(o);
                }
            }
            o->flags |= 1;
            if (d <= lim && (o->flags & 8)) {
                func_8002A9E0(o);
            }
            i = o->nlod - 1;
            if (i != 0) {
                l = &o->lod[i];
                while (i > 0 && l->dist < (u32) d) {
                    i--;
                    l--;
                }
                { s32 k = i + 1; o->cur = &o->lod[o->nlod - k]; }
            } else {
                o->cur = &o->lod[0];
            }
            *D_8008B324++ = o;
        }
        o = o->next;
    } while (o != NULL);
}
