#include "common.h"

typedef struct Voice_80052874 {
    u8 id;
    u8 pad1[3];
    s32 voice;
    s32 addr;
} Voice_80052874;

typedef struct Stream_80052874 {
    u16 flags;
    u8 state;
    u8 pad3;
    u32 size;
    u32 half;
    u32 wr;
    u32 base;
    u32 rd;
    u32 fill;
    s32 endpos;
    void *src;
    s32 unk24;
    s32 unk28;
    s32 fade;
    s32 vol;
    s32 target;
    s32 step;
    Voice_80052874 voices[2];
    s32 unk54;
} Stream_80052874;

typedef struct VoiceAttr_80052874 {
    u32 voice;
    u32 mask;
    s16 volL;
    s16 volR;
    u8 pad[0x34];
} VoiceAttr_80052874;

extern s32 D_8008A9EC;
extern s32 D_8008A9F0;
extern s32 D_8008A9F4;
extern s32 D_8008A9F8;
extern s32 D_8008A9FC;
extern s32 D_8008B454;
extern Stream_80052874 D_800B134C;
extern s32 D_800B1364[];
extern u8 D_800B134E[];
extern u8 D_800B13DC[];
extern void func_8005CBD8(s32);
extern void func_8005CBEC(s32, s32, s32);
extern void SpuSetVoiceAttr(VoiceAttr_80052874 *);
extern u32 func_80053774(u32, s32 *, s32);
extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);

extern void *memset(void *, s32, s32);

s32 func_80052874(void) {
    VoiceAttr_80052874 attr;
    s32 pos;
    s32 now;
    s32 n;
    u32 len;
    u32 got;
    s32 *pp;

    if (D_8008A9EC == 0) {
        return 0;
    }
    now = D_8008A9F8 + 1;
    if (D_8008A9FC != 0) {
        if (D_8008A9FC == 1 && D_8008A9F0 <= 0) {
            D_800B134E[0] = 1;
            memset(D_800B13DC, 0, 0x90);
            D_8008A9F4 = 0;
            D_8008B454 = 0;
            func_8005CBD8(0);
            func_8005CBEC(7, 0, 0);
            D_8008A9FC = 0;
            return 0x204;
        }
        D_8008A9FC--;
    }
    if (D_800B134C.state == 4) {
        if (D_800B134C.fade & 1) {
            n = now - D_8008A9F8;
            while (n--) {
                D_800B134C.vol += D_800B134C.step;
                if (D_800B134C.step > 0) {
                    if (D_800B134C.vol >= D_800B134C.target) {
                        D_800B134C.vol = D_800B134C.target;
                        D_800B134C.fade &= ~1;
                        break;
                    }
                } else if (D_800B134C.target >= D_800B134C.vol) {
                    D_800B134C.vol = D_800B134C.target;
                    D_800B134C.fade &= ~1;
                    break;
                }
            }
            {
                Stream_80052874 *s = &D_800B134C;

                attr.mask = 3;
                if (!(s->flags & 0x200)) {
                    attr.voice = 1 << s->voices[0].voice;
                    attr.volL = s->vol >> 9;
                    attr.volR = attr.volL;
                    SpuSetVoiceAttr(&attr);
                } else {
                    attr.volR = 0;
                    attr.voice = 1 << s->voices[0].voice;
                    attr.volL = s->vol >> 9;
                    SpuSetVoiceAttr(&attr);
                    attr.voice = 1 << s->voices[1].voice;
                    attr.volR = attr.volL;
                    attr.volL = 0;
                    SpuSetVoiceAttr(&attr);
                }
            }
            {
                Stream_80052874 *s = &D_800B134C;

                if (!(s->fade & 1)) {
                    if (s->fade & 2) {
                        s->state = 6;
                    }
                }
            }
        }
        if (D_8008A9F0 <= 0) {
            Stream_80052874 *s;

            EnterCriticalSection();
            {
                Stream_80052874 *c = &D_800B134C;

                if (c->wr < c->rd) {
                    got = c->size + c->wr - c->rd;
                } else {
                    got = c->wr - c->rd;
                }
            }
            s = &D_800B134C;
            s->rd = s->wr;
            ExitCriticalSection();
            s->fill += got;
            if (s->fill >= s->half) {
                D_800B134C.flags &= ~0x800;
                if (s->base + s->fill <= s->size) {
                    len = s->fill;
                    if (func_80053774(len, &pos, 0) < len) {
                        if (!(D_800B134C.flags & 0x1000)) {
                            D_800B134C.flags |= 0x1000;
                            s->endpos = pos;
                        }
                    }
                } else {
                    len = s->size - s->base;
                    pp = &pos;
                    if (func_80053774(len, pp, 0) < len) {
                        if (!(D_800B134C.flags & 0x1000)) {
                            D_800B134C.flags |= 0x1000;
                            s->endpos = pos;
                        }
                        func_80053774(s->fill - len, pp, 0);
                    } else {
                        len = s->fill - len;
                        if (len != 0) {
                            if (func_80053774(len, pp, 0) < len) {
                                if (!(D_800B134C.flags & 0x1000)) {
                                    D_800B134C.flags |= 0x1000;
                                    s->endpos = pos;
                                }
                            }
                        }
                    }
                }
                D_800B1364[0] = 0;
            }
        }
    }
    D_8008A9F8 = now;
    return 0;
}
