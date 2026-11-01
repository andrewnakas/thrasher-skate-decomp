#include "common.h"

typedef struct {
    s32 *data;
    s32 arg;
    s32 *hdr;
    s32 *body;
    s32 n;
} Snd_80014170;

typedef struct {
    u16 a;
    u16 n;
} Hdr_80014170;

extern s32 D_80089F4C;
extern s32 D_8008AD14[2];
extern s32 *D_8008AD28;

Snd_80014170 *func_80014170(s32 *data, s32 arg, s32 reuse) {
    Snd_80014170 *e;
    s32 *p;

    if (D_80089F4C == 0) {
        D_8008AD28 = data;
    }
    if (reuse != 0 && D_80089F4C != 0) {
        e = (Snd_80014170 *)D_8008AD14;
    } else {
        e = &((Snd_80014170 *)D_8008AD14)[D_80089F4C];
        D_80089F4C++;
    }
    p = data;
    e->data = p;
    e->arg = arg;
    if (*p == 0x2A81511C) {
        p += 4;
        e->data += 4;
    } else if (*(u8 *)p == 0xFF) {
        p += 2;
    }
    e->hdr = p;
    p++;
    e->body = p;
    e->n = ((Hdr_80014170 *)e->hdr)->n;
    return e;
}
