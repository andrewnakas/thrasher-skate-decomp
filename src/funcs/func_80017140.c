#include "common.h"

typedef struct {
    s32 f0;
    u16 type;
    u8 pad6[6];
    s32 fC;
    u8 pad10[8];
    u16 f18;
    u8 pad1A[2];
    s32 f1C;
    s32 f20;
    u8 pad24[0xC];
    s32 f30;
    s32 f34;
    u8 pad38[4];
    s32 f3C;
    u16 f40;
    u8 pad42[2];
    s32 f44;
    s32 f48;
    s32 f4C;
} Ent;

extern Ent *D_8008AD90;
extern s32 D_8008AD94;
extern s32 D_8008AD88;

Ent *func_80015E8C(s32);
void func_80015F10(s32);

#define RET(v)                              \
    do {                                    \
        r = (v);                            \
        if (!had) {                         \
            D_8008AD90 = NULL;              \
            func_80015F10(D_8008AD94);      \
        }                                   \
        return r;                           \
    } while (0)

s32 func_80017140(u16 key) {
    Ent *e;
    u8 had;
    s32 r;

    if (D_8008AD90 == NULL) {
        D_8008AD90 = func_80015E8C(D_8008AD94);
        had = 0;
    } else {
        had = 1;
    }
    e = &D_8008AD90[D_8008AD88];
    switch (key) {
    case 1:
        if (e->type == 1) {
            RET(e->f0);
        }
        break;
    case 2:
        if (e->type == 2) {
            RET(e->f0);
        }
        break;
    case 3:
        if (e->type == 3) {
            RET(e->f0);
        }
        break;
    case 5:
        RET(e->fC);
    case 7:
        if (e->f18 & 2) {
            RET(1);
        }
        RET(0);
    case 8:
        if (e->f18 & 1) {
            RET(1);
        }
        RET(0);
    case 9:
        if (e->f18 & 4) {
            RET(1);
        }
        RET(0);
    case 12:
        if (e->f18 & 8) {
            RET(1);
        }
        RET(0);
    case 13:
        if (e->f18 & 0x10) {
            RET(1);
        }
        RET(0);
    case 10:
        RET(e->f20);
    case 11:
        RET(e->f1C);
    case 16:
        RET(e->f34);
    case 15:
        RET(e->f30);
    case 17:
        if (e->f40 & 2) {
            RET(1);
        }
        RET(0);
    case 18:
        if (e->f40 & 1) {
            RET(1);
        }
        RET(0);
    case 19:
        if (e->f40 & 4) {
            RET(1);
        }
        RET(0);
    case 22:
        RET(e->f3C);
    case 20:
        RET(e->f48);
    case 21:
        RET(e->f44);
    case 23:
        RET(e->f4C);
    }
    RET(0);
}
