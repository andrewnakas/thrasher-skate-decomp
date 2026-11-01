#include "common.h"

typedef struct ObjA_8002A264 {
    u16 flags;
    u8 pad2;
    u8 unk3;
    u8 pad4[0x10];
    struct ObjA_8002A264 *next;
    u8 pad18[0x14];
    u8 c[8];
    u16 idx;
} ObjA_8002A264;

typedef struct ObjB_8002A264 {
    u8 pad0[0x28];
    u8 c[6];
    u16 idx;
} ObjB_8002A264;

typedef struct Ent_8002A264 {
    u16 unk0;
    u8 pad2[0xE];
} Ent_8002A264;

extern Ent_8002A264 D_800AB794[];
extern u16 D_8008AFA4;
extern s16 func_80047420(u16);
extern s32 func_80047460(u16);
extern s32 func_8002DD38(ObjA_8002A264 *);

void func_8002A264(ObjA_8002A264 *o) {
    u16 id;
    s32 m;
    s32 t;
    s32 mask;
    s32 mul;

    for (; o != NULL; o = o->next) {
        if (o->flags & 1) {
            if (o->flags & 2) {
                t = o->idx + D_8008AFA4;
                o->idx = t;
                m = D_800AB794[(u16) t].unk0 & 0x180;
                if (m == 0) {
                    mask = 0xFF;
                    mul = 4;
                } else if (m == 0x80) {
                    mask = 0x7F;
                    mul = 2;
                } else {
                    mask = 0x3F;
                    mul = 1;
                }
                id = t;
                o->c[0] += (func_80047420(id) * mul) & mask;
                o->c[1] += func_80047460(id);
                o->c[2] += (func_80047420(id) * mul) & mask;
                o->c[3] += func_80047460(id);
                o->c[4] += (func_80047420(id) * mul) & mask;
                o->c[5] += func_80047460(id);
                o->c[6] += (func_80047420(id) * mul) & mask;
                o->c[7] += func_80047460(id);
            }
        } else if (o->flags & 2) {
            t = ((ObjB_8002A264 *) o)->idx + D_8008AFA4;
            ((ObjB_8002A264 *) o)->idx = t;
            m = D_800AB794[(u16) t].unk0 & 0x180;
            if (m == 0) {
                mask = 0xFF;
                mul = 4;
            } else if (m == 0x80) {
                mask = 0x7F;
                mul = 2;
            } else {
                mask = 0x3F;
                mul = 1;
            }
            id = t;
            ((ObjB_8002A264 *) o)->c[0] += (func_80047420(id) * mul) & mask;
            ((ObjB_8002A264 *) o)->c[1] += func_80047460(id);
            ((ObjB_8002A264 *) o)->c[2] += (func_80047420(id) * mul) & mask;
            ((ObjB_8002A264 *) o)->c[3] += func_80047460(id);
            ((ObjB_8002A264 *) o)->c[4] += (func_80047420(id) * mul) & mask;
            ((ObjB_8002A264 *) o)->c[5] += func_80047460(id);
        }
        if (o->unk3 != 0) {
            func_8002DD38(o);
        }
    }
}
