#include "common.h"

typedef struct {
    u8 pad0[4];
    u8 *data;
    u16 pc;
    u8 wait;
    u8 note;
    u8 unkC;
    u8 sp;
    u8 cnt[2];
    u16 lpc[2];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
} Seq_8001DD58;

typedef struct {
    u16 flags;
    u8 pad2[0x22];
    Seq_8001DD58 seq;
} Chan_8001DD58;

typedef void (*SeqFn_8001DD58)(Chan_8001DD58 *, s32, s32, s32);

extern s32 D_8008AEBC;
extern SeqFn_8001DD58 *D_8008AEC8;
extern s32 func_80011B48(void);
extern void func_8001DB74(Chan_8001DD58 *);
extern void func_8001DC58(Chan_8001DD58 *, s32);
extern s32 func_80032C28(s32, s32);

#define RD(s) ((s)->data[(s)->pc++])
#define RD32(s) (RD(s) | (RD(s) << 8) | ((RD(s) | (RD(s) << 8)) << 16))

s32 func_8001DD58(Chan_8001DD58 *chan) {
    Seq_8001DD58 *s;
    u32 note;
    u8 c;
    u8 v;
    s32 t;

    s = &chan->seq;
    note = s->note;
    D_8008AEBC = 0;
    chan->flags &= ~0x20;
    while (--s->wait == 0xFF && D_8008AEBC == 0) {
        c = RD(s);
        if ((s8) c >= 0) {
            s->note = c;
            if (chan->flags & 8) {
                s->wait = 1;
            } else {
                s->wait = RD(s);
            }
            continue;
        }
        s->wait = 0;
        switch (c) {
        case 0x80:
            D_8008AEBC = 1;
            break;
        case 0x81:
            s->pc = 0;
            break;
        case 0x82:
            s->cnt[s->sp] = RD(s);
            s->lpc[s->sp] = s->pc;
            s->sp++;
            break;
        case 0x83:
            v = --s->cnt[s->sp - 1];
            if (v != 0) {
                s->pc = s->lpc[s->sp - 1];
                if ((s8) v == -2) {
                    s->cnt[s->sp - 1] = 0xFF;
                }
            } else {
                s->sp--;
            }
            break;
        case 0x84:
            func_8001DB74(chan);
            return 1;
        case 0x85:
            s->note++;
            break;
        case 0x86:
            s->note--;
            break;
        case 0x87:
            s->wait = RD(s);
            break;
        case 0x88:
            t = func_80011B48();
            s->wait = (u32) ((t & 0xFFFF) * (s8) RD(s)) >> 16;
            break;
        case 0x89:
            chan->flags ^= 0x400;
            break;
        case 0x8A:
            chan->flags ^= 0x800;
            break;
        case 0x8B:
            s->unkC = RD(s);
            break;
        case 0x8C:
            t = RD(s) << 10;
            s->unk18 = func_80032C28(s->unk18, t);
            s->unk1C = func_80032C28(s->unk1C, t);
            break;
        case 0x8D:
            t = RD(s) << 10;
            s->unk18 += t;
            s->unk1C += t;
            break;
        case 0x8E:
            t = RD(s) << 10;
            s->unk18 = t;
            s->unk1C = t;
            break;
        case 0x8F:
            {
                s32 a;
                s32 b;
                s32 d;
                c = RD(s);
                a = RD32(s);
                b = RD32(s);
                d = RD32(s);
                D_8008AEC8[c](chan, a, b, d);
            }
            break;
        case 0x90:
            func_8001DC58(chan, (s8) RD(s));
            break;
        case 0x91:
            s->pc = (s8) RD(s);
            break;
        case 0x92:
            s->unk14 = RD32(s);
            break;
        }
    }
    if (note != s->note) {
        chan->flags |= 0x20;
    }
    return D_8008AEBC;
}
