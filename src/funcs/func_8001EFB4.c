#include "common.h"

typedef struct Spr_8001EFB4 {
    struct Spr_8001EFB4 *next;
    s32 life;
    s32 pos[3];
    s32 vx;
    s32 vy;
    s32 vz;
    u8 c[6];
    u16 dc[3];
    s32 *unk2C;
} Spr_8001EFB4;

typedef struct Emit_8001EFB4 {
    u16 flags;
    u16 type;
    u8 pad4[0xC];
    s32 unk10[3];
    s32 unk1C;
    u16 unk20;
    u8 pad22[2];
    Spr_8001EFB4 *sprites;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    u8 limit;
    u8 count;
    u8 rate;
    u8 frac;
    u8 pad38[0x10];
    s32 ax;
    s32 ay;
    s32 az;
    u8 pad54[2];
    u16 timer;
    s32 unk58;
    u8 mode;
} Emit_8001EFB4;

typedef struct {
    u16 unk0;
    u16 flags;
    u8 pad4[0x48];
} TableEntry;

typedef struct {
    s32 unk0;
    s32 pos[3];
    s32 pad10[2];
} Prev_8001EFB4;

extern TableEntry D_8006F2C0[];
extern void func_8001446C(s32, s32, s32 *, s32 *, s32);
extern void func_8001E4F0(Emit_8001EFB4 *);
extern s32 func_80032C28(s32, s32);
extern void func_80049230(s32, s32, s32 *, Prev_8001EFB4 *);
extern s32 func_8001E900(Emit_8001EFB4 *, Spr_8001EFB4 *);

void func_8001EFB4(Emit_8001EFB4 *o) {
    Prev_8001EFB4 prev;
    Spr_8001EFB4 *s;
    u16 flags;
    s32 tf;
    s32 n;
    s32 arg;

    flags = o->flags;
    if (o->timer != 0) {
        o->timer--;
        if (o->mode & 1) {
            o->unk10[0] = o->unk28;
            o->unk10[1] = o->unk2C;
            o->unk10[2] = o->unk30;
            if (o->unk20 != 0xFF) {
                if (o->flags & 0x1000) {
                    func_8001446C(o->unk1C, o->unk20, o->unk10, o->unk10, 5);
                } else {
                    func_8001446C(o->unk1C, o->unk20, o->unk10, o->unk10, 1);
                }
            }
        }
        o->frac = o->frac + o->rate;
        n = o->frac / 16;
        o->frac -= n * 16;
        for (n--; n != -1; n--) {
            if (o->count < o->limit) {
                func_8001E4F0(o);
            }
        }
    }
    tf = D_8006F2C0[o->type].flags;
    if (flags & 0x8000) {
        tf |= 0x100;
    }
    s = o->sprites;
    arg = o->unk58;
    if (s != NULL) {

        do {
            prev.pos[0] = s->pos[0];
            prev.pos[1] = s->pos[1];
            prev.pos[2] = s->pos[2];
            s->pos[0] += s->vx;
            s->pos[1] += s->vy;
            s->pos[2] += s->vz;
            if (o->mode & 2) {
                s->unk2C[4] = s->pos[0];
                s->unk2C[5] = s->pos[1];
                s->unk2C[6] = s->pos[2];
            }
            if (flags & 0x2000) {
                s->vz = func_80032C28(s->vz, o->az);
                s->vx = func_80032C28(s->vx, o->ax);
            } else {
                s->vx += o->ax;
                s->vz += o->az;
            }
            if (flags & 0x4000) {
                s->vy = func_80032C28(s->vy, o->ay);
            } else {
                s->vy += o->ay;
            }
            *(u16 *) &s->c[0] += s->dc[0];
            *(u16 *) &s->c[2] += s->dc[1];
            *(u16 *) &s->c[4] += s->dc[2];
            if (!(o->mode & 2)) {
                prev.unk0 = arg;
                func_80049230(tf, s->c[1] | (s->c[3] << 8) | (s->c[5] << 16), s->pos, &prev);
            }
            if (--s->life == 0) {
                if (func_8001E900(o, s)) {
                    return;
                }
            }
            s = s->next;
        } while (s != NULL);
    }
}
