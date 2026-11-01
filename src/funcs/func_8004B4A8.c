/* ext = 0 at the head of the else arm: reload_cse turns the loop init i = 0 into a copy of $s6, and reorg pulls ext = 0 into the bne delay slot. */
#include "common.h"

typedef struct Ctx_8004B4A8 {
    u8 pad0[3];
    u8 unk3;
    u8 pad4[8];
    u8 unkC;
    u8 padD[3];
    u8 unk10;
    u8 pad11[3];
    u8 unk14;
    u8 pad15[3];
    u8 unk18;
    u8 pad19[0xF];
    u8 *pc;
} Ctx_8004B4A8;

typedef struct Op_8004B4A8 {
    Ctx_8004B4A8 *ctx;
    s32 arg;
    union {
        u8 b[2];
        s32 w;
    } u8;
    s32 (*fn)();
} Op_8004B4A8;

extern u32 func_8004BE4C(u8 *p);
extern s32 func_8004B7BC();
extern s32 func_8004BA34();
extern s32 func_8004BBB8();
extern s32 func_8004BC50();

s32 func_8004B4A8(Ctx_8004B4A8 *c, Op_8004B4A8 *o) {
    u8 buf[4];
    u8 *p;
    u8 op;
    u8 hi;
    u8 i;
    u8 sel;
    u8 v;
    s32 len;
    s32 ext;
    s32 ret;

    o->ctx = c;
    p = c->pc;
    len = 0;
    op = *p++;
    hi = op & 0xF8;
    switch (op & 7) {
    case 0:
        o->arg = 0;
        break;
    case 1:
        o->arg = *p++;
        break;
    case 2:
        o->arg = func_8004BE4C(p);
        p += 4;
        break;
    case 3:
        o->arg = 0;
        p += 1;
        break;
    case 4:
        o->arg = p[1];
        p += 2;
        break;
    case 5:
        o->arg = func_8004BE4C(p + 1);
        p += 5;
        break;
    case 6:
        o->arg = 0;
        p += 4;
        break;
    case 7:
        o->arg = func_8004BE4C(p + 4);
        p += 8;
        break;
    }
    if (hi == 0xF8) {
        ext = 1;
        hi = *p;
        p += ext;
        sel = *p;
        p += ext;
        for (i = 0; i < 4; i++) {
            switch (sel & 2) {
            case 1:
                v = *p++;
                buf[i] = v;
                break;
            case 0:
                break;
            case 2:
                p += 2;
                v = *p++;
                buf[i] = v;
                break;
            case 3:
                switch (*p++) {
                case 0:
                    v = c->unkC;
                    buf[i] = v;
                    break;
                case 1:
                    v = c->unk10;
                    buf[i] = v;
                    break;
                case 2:
                    v = c->unk14;
                    buf[i] = v;
                    break;
                case 3:
                    v = c->unk18;
                    buf[i] = v;
                    break;
                case 7:
                    break;
                }
                break;
            }
            sel >>= 2;
        }
    } else {
        ext = 0;
        for (i = 0; i < 2; i++) {
            buf[i] = p[i];
        }
    }
    ret = 1;
    switch (hi) {
    case 0:
        o->fn = func_8004B7BC;
        o->u8.b[0] = buf[0];
        o->u8.b[1] = buf[1];
        len = 2;
        break;
    case 8:
        o->fn = func_8004B7BC;
        o->u8.b[0] = buf[0];
        o->u8.b[1] = c->unk3;
        len = 1;
        break;
    case 0x10:
        o->fn = func_8004BA34;
        o->u8.b[0] = buf[0];
        o->u8.b[1] = buf[1];
        len = 2;
        break;
    case 0x18:
        o->fn = func_8004BBB8;
        o->u8.b[0] = buf[0];
        o->u8.b[1] = buf[1];
        len = 2;
        break;
    case 0x20:
    case 0x28:
    case 0x38:
    case 0x40:
        break;
    case 0x30:
        o->fn = func_8004BC50;
        o->u8.w = func_8004BE4C(p);
        len = 4;
        break;
    default:
        ret = 0;
        break;
    }
    if (!ext) {
        s32 q = len + (s32) p;
        p = (u8 *) q;
    }
    c->pc = p;
    return ret;
}
