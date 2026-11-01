#include "common.h"

typedef struct {
    u16 f0;
    u8 pad2;
    u8 f3;
    u8 f4;
    u8 f5;
    s8 f6;
    u8 pad7[0x1C - 0x7];
    s32 f1C;
    s32 f20;
    u8 pad24[0x34 - 0x24];
    u32 f34;
} Snd;

typedef struct {
    u8 f0;
    u8 f1;
    s16 f2;
    s32 f4;
    u8 f8;
    u8 pad9[3];
    u32 fC;
    s32 f10;
} Voice;

typedef struct {
    Snd *snd;
    u32 f4;
    u8 f8;
    u8 f9;
} Req;

extern Voice D_800AF3A4[];
extern s32 D_8008B400;
extern s32 D_8008B404;

s32 func_8004BD98(s32, u8, s32 *, u16 *);
u8 func_8004DEBC(s32, s32);
void func_8004E930(u8, s16);
void func_8004E6CC(u8, s32);
void func_8004E7EC(u8, s8);
void func_8004E460(u8);
void func_8004BC94(Snd *, Voice *);

s32 func_8004B7BC(Req *req) {
    s32 id;
    u16 pitch;
    Snd *s;
    Voice *v;
    Voice *p;
    Voice *base;
    s32 i;
    u32 n;
    u8 ch;

    s = req->snd;
    s->f3 = req->f9;
    id = 0;
    if (s->f1C != 0) {
        id = s->f1C;
        pitch = (req->f8 - 0x3C) * 100;
    } else if (s->f20 != 0) {
        func_8004BD98(s->f20, req->f8, &id, &pitch);
    }
    v = NULL;
    if (id == 0) {
        return 0;
    }
    i = D_8008B400;
    base = D_800AF3A4;
    p = &base[i];
    do {
        if (!(p->f0 & 1)) {
            v = p;
            i++;
            v->f0 = 1;
            v->f10 = 0;
            if (i == 0x40) {
                i = 0;
            }
            D_8008B400 = i;
            break;
        }
        i++;
        p++;
        if (i == 0x40) {
            p = base;
            i = 0;
        }
    } while (i != D_8008B400);
    if (v == NULL) {
        goto out;
    }
    v->f4 = id;
    v->f1 = req->f9;
    v->f2 = pitch;
    n = (req->f4 * s->f34) >> 12;
    if (n == 0) {
        n = 1;
    }
    v->fC = n;
    if (!(s->f0 & 0x2000) && (D_8008B404 == 0 || !(s->f0 & 0x1000))) {
        ch = func_8004DEBC(id, 0xFF);
        v->f8 = ch;
        if (ch == 0xFF) {
            goto fail;
        }
        func_8004E930(v->f8, v->f2);
        func_8004E6CC(v->f8, (u8) ((u32) ((u8) ((u32) (v->f1 * s->f4) >> 7) * s->f5) >> 7));
        func_8004E7EC(v->f8, s->f6);
        func_8004E460(v->f8);
        func_8004BC94(s, v);
        return 1;
    }
    v->f0 |= 2;
    func_8004BC94(s, v);
    return 1;
fail:
    v->f0 = 0;
    if (i != 0) {
        D_8008B400 = i - 1;
    } else {
        D_8008B400 = 0x3F;
    }
out:
    return 0;
}
