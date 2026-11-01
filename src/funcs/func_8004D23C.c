#include "common.h"

typedef struct {
    u16 flags;
    u8 ch;
    u8 pad3;
    s32 id;
    s32 timer;
    s32 pos[3];
    u32 dist;
    s16 dpitch;
    u16 pitch;
    u8 vol;
    u8 maxvol;
    s8 pan;
    u8 pad23;
} Snd;

typedef union {
    s32 w[4];
    s16 h[8];
} Vec;

extern Snd D_800AFA64[];
extern s32 D_8008A960;
extern s32 D_8008B42C;
extern u32 D_8008B430;
extern s32 D_8008B434;
extern s32 D_8008B438;

void func_80011EF4(s32 *, Vec *);
s16 func_80032DCC(s32, s32);
void func_800333C8(Vec *, s32);
u8 func_8004DEBC(s32, s32);
void func_8004E30C(u8);
void func_8004E460(u8);
void func_8004E528(u8, s32);
void func_8004E6CC(u8, s32);
void func_8004E7EC(u8, s8);
void func_8004E930(u8, s16);
s32 func_8004EB14(u8);

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

u32 func_8004D23C(void) {
    Vec v;
    Snd *s;
    u32 ret;
    u32 i;
    u32 d;
    u8 ch;

    if (D_8008A960 == 0) {
        return 0;
    }
    ret = 0;
    for (i = 0; i < 16; i++) {
        s = &D_800AFA64[i];
        if (!(s->flags & 0x8000)) {
            continue;
        }
        if (s->timer == 0) {
            continue;
        }
        if (--s->timer != 0) {
        if (s->ch != 0xFF) {
            if (func_8004EB14(s->ch) != s->id) {
                func_8004E30C(s->ch);
                s->ch = 0xFF;
                s->flags &= ~0x4000;
            }
        }
        if (s->ch == 0xFF) {
            ch = func_8004DEBC(s->id, 0xFF);
            s->ch = ch;
            if (ch == 0xFF) {
                ret = 2;
                continue;
            }
        }
        func_80011EF4(s->pos, &v);
        d = v.h[1] * v.h[1] + v.h[3] * v.h[3] + v.h[5] * v.h[5];
        if (d < D_8008B430) {
            s->vol = 0x7F - ((d >> 7) * 0x7F) / (D_8008B430 >> 7);
            func_8004E6CC(s->ch, (u8) ((u32) (s->maxvol * s->vol) >> 7));
            if (v.w[0] != 0 && v.w[2] != 0) {
                if (!(s->flags & 1) && v.w[1] != 0) {
                    func_800333C8(&v, func_80032DCC(v.w[1], v.w[2]));
                }
                s->pan = (v.h[1] * 0x7F) / D_8008B42C;
            } else {
                s->pan = 0;
            }
            func_8004E7EC(s->ch, s->pan);
            if (D_8008B438 == 0) {
                s->dpitch = -(s32) (((s32) (d - s->dist) * D_8008B434) >> 16);
                s->dpitch = MIN(MAX(s->dpitch, -700), 700);
            } else {
                s->dpitch = 0;
            }
            func_8004E930(s->ch, s->pitch + s->dpitch);
        } else {
            s->vol = 0;
            func_8004E6CC(s->ch, 0);
        }
        s->dist = d;
        if (!(s->flags & 0x4000)) {
            func_8004E460(s->ch);
            s->flags |= 0x4000;
        }
        } else {
            func_8004E528(s->ch, 0);
            s->flags &= ~0x4000;
        }
    }
    D_8008B438 = 0;
    return ret;
}
