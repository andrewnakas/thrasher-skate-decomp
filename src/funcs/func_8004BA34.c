#include "common.h"

typedef struct Voice_8004BA34 {
    u8 flags;
    u8 vol;
    u8 pad2[6];
    u8 ch;
    u8 pad9[7];
    struct Voice_8004BA34 *next;
} Voice_8004BA34;

typedef struct {
    u8 pad0[4];
    u8 vol;
    u8 mvol;
    s8 pan;
    u8 pad7[0x15];
    s32 f1C;
    s32 f20;
    u8 pad24[0x14];
    Voice_8004BA34 *voices;
    u8 pad3C[8];
    u16 id;
} Snd_8004BA34;

typedef struct {
    Snd_8004BA34 *snd;
    u32 f4;
    u8 op;
    u8 arg;
} Req_8004BA34;

void func_8004E6CC(u8, u8);
void func_8004E7EC(u8, s8);
s32 func_8004FD98(u16, u8);
s32 func_8005011C(u16, u8);

s32 func_8004BA34(Req_8004BA34 *req) {
    Snd_8004BA34 *s;
    Voice_8004BA34 *v;

    s = req->snd;
    switch (req->op) {
    case 0:
        s->mvol = req->arg;
        for (v = s->voices; v != NULL; v = v->next) {
            if (!(v->flags & 2)) {
                func_8004E6CC(v->ch, (u8)((u32)((u8)((u32)(v->vol * s->vol) >> 7) * s->mvol) >> 7));
            }
        }
        break;
    case 1:
        s->pan = req->arg;
        for (v = s->voices; v != NULL; v = v->next) {
            if (!(v->flags & 2)) {
                func_8004E7EC(v->ch, s->pan);
            }
        }
        break;
    case 2:
    case 3:
        break;
    case 4:
        if (req->arg != 0xFF) {
            s->f1C = func_8004FD98(s->id, req->arg);
        } else {
            s->f1C = 0;
        }
        break;
    case 5:
        if (req->arg != 0xFF) {
            s->f20 = func_8005011C(s->id, req->arg);
        } else {
            s->f20 = 0;
        }
        break;
    default:
        return 0;
    }
    return 1;
}
