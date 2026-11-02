/* cflags: -fno-strength-reduce */
#include "common.h"

typedef struct Chan_80050664 {
    u16 flags;
    u8 state;
    u8 pad3[9];
    u32 size;
    u32 thresh;
    u32 wr;
    u32 base;
    u32 rd;
    u32 pending;
    s32 pos;
    u8 pad28[0x10];
    u32 fade;
    s32 vol;
    s32 target;
    s32 step;
    u8 pad48[4];
    s32 voice;
    u8 pad50[8];
    s32 voice2;
    u8 pad5C[4];
} Chan_80050664;

typedef struct VoiceAttr_80050664 {
    u32 voice;
    u32 mask;
    s16 volL;
    s16 volR;
    u8 pad[0x34];
} VoiceAttr_80050664;

extern s32 D_8008A9C8;
extern s32 D_8008A9CC;
extern s32 D_8008A9D0;
extern Chan_80050664 D_800B0F6C[];

extern void SpuSetVoiceAttr(VoiceAttr_80050664 *);
extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern void func_8005109C(Chan_80050664 *);
extern u32 func_80051B9C(Chan_80050664 *, u32, s32 *, s32);
extern s32 func_80066D2C(s32, s32);

s32 func_80050664(void) {
    VoiceAttr_80050664 attr;
    s32 pos;
    Chan_80050664 *ch;
    Chan_80050664 *p;
    u32 mask;
    u32 i;
    s32 now;
    s32 n;
    s32 step;
    u32 len;
    u32 got;
    s32 nm;
    s32 one;
    s32 *pp;

    mask = 0;
    if (D_8008A9C8 == 0) {
        return 0;
    }
    {
        i = 0;
        nm = ~1;
        one = 1;
        pp = &pos;
        now = D_8008A9D0 + 1;
        p = D_800B0F6C;
        for (; i < 4; p++, i++) {
            if (!(p->flags & 0x8000)) {
                continue;
            }
            ch = p;
            if (p->state == 4) {
                if (ch->fade & 1) {
                    n = now - D_8008A9D0;
                    while (n--) {
                        ch->vol += ch->step;
                        if (ch->step > 0) {
                            if (ch->vol >= ch->target) {
                                ch->vol = ch->target;
                                ch->fade &= nm;
                                break;
                            }
                        } else if (ch->target >= ch->vol) {
                            ch->vol = ch->target;
                            ch->fade &= nm;
                            break;
                        }
                    }
                    attr.mask = 3;
                    if (!(ch->flags & 0x100)) {
                        attr.voice = one << ch->voice;
                        attr.volR = attr.volL = ch->vol >> 9;
                        SpuSetVoiceAttr(&attr);
                    } else {
                        attr.voice = one << ch->voice;
                        attr.volL = ch->vol >> 9;
                        attr.volR = 0;
                        SpuSetVoiceAttr(&attr);
                        attr.voice = one << ch->voice2;
                        attr.volR = attr.volL;
                        attr.volL = 0;
                        SpuSetVoiceAttr(&attr);
                    }
                    if (!(ch->fade & 1)) {
                        if (ch->fade & 2) {
                            if (ch->flags & 2) {
                                func_8005109C(ch);
                            } else {
                                ch->state = 5;
                            }
                            continue;
                        }
                    }
                }
                if (D_8008A9CC <= 0) {
                    EnterCriticalSection();
                    if (ch->wr < ch->rd) {
                        got = ch->size + ch->wr - ch->rd;
                    } else {
                        got = ch->wr - ch->rd;
                    }
                    ch->rd = ch->wr;
                    ExitCriticalSection();
                    ch->pending += got;
                    if (ch->pending >= ch->thresh) {
                        ch->flags &= ~0x2000;
                        if (ch->base + ch->pending <= ch->size) {
                            if (func_80051B9C(ch, ch->pending, &pos, 0) < got) {
                                if (!(ch->flags & 0x1000)) {
                                    ch->flags |= 0x1000;
                                    ch->pos = pos;
                                }
                            }
                        } else {
                            len = ch->size - ch->base;
                            if (func_80051B9C(ch, len, pp, 0) < len) {
                                if (!(ch->flags & 0x1000)) {
                                    ch->flags |= 0x1000;
                                    ch->pos = pos;
                                }
                                func_80051B9C(ch, ch->pending - len, pp, 0);
                            } else {
                                len = ch->pending - len;
                                if (len != 0) {
                                    if (func_80051B9C(ch, len, pp, 0) < len) {
                                        if (!(ch->flags & 0x1000)) {
                                            ch->flags |= 0x1000;
                                            ch->pos = pos;
                                        }
                                    }
                                }
                            }
                        }
                        ch->pending = 0;
                    }
                }
            }
            if (ch->flags & 0x800) {
                mask |= one << ch->voice;
                if (ch->flags & 0x100) {
                    mask |= one << ch->voice2;
                }
            }
        }
        if (mask != 0) {
            while (func_80066D2C(4, mask) == -3) {
            }
        }
        D_8008A9D0 = now;
    }
    return 0;
}
