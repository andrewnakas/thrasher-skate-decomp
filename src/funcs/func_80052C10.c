#include "common.h"

extern s32 D_8008A9EC;
extern u8 D_80010920[];
extern u8 D_8008AA00[];

typedef struct Voice_80052C10 {
    u8 id;
    u8 pad1[3];
    s32 voice;
    s32 addr;
} Voice_80052C10;

typedef struct Stream_80052C10 {
    u16 flags;
    u8 state;
    u8 pad3;
    u32 size;
    u32 half;
    u8 padC[4];
    s32 unk10;
    u8 pad14[4];
    s32 unk18;
    s32 unk1C;
    void *src;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad30[0xC];
    Voice_80052C10 voices[2];
    s32 unk54;
} Stream_80052C10;

typedef struct Src_80052C10 {
    u8 pad0[8];
    u16 rate;
    u8 chans;
} Src_80052C10;

typedef struct VoiceAttr_80052C10 {
    u32 voice;
    u32 mask;
    s16 volL;
    s16 volR;
    s16 volmodeL;
    s16 volmodeR;
    s16 volxL;
    s16 volxR;
    u16 pitch;
    u16 note;
    u16 sample_note;
    s16 envx;
    u32 addr;
    u32 loop_addr;
    s32 a_mode;
    s32 s_mode;
    s32 r_mode;
    u16 ar;
    u16 dr;
    u16 sr;
    u16 rr;
    u16 sl;
    u16 adsr1;
    u16 adsr2;
    u16 pad3E;
} VoiceAttr_80052C10;

extern Stream_80052C10 D_800B134C;
extern u8 D_800B1388[]; /* &D_800B134C.voices[0].id */

extern Src_80052C10 *func_80053A4C(s32, s32);
extern void func_8004E30C(u8);
extern void func_80053B34(Src_80052C10 *);
extern u8 func_8004DEBC(s32, s32);
extern s32 func_8004EECC(u8);
extern void SpuSetVoiceAttr(VoiceAttr_80052C10 *);
extern void SpuFlush(s32);
extern u32 func_80053774(u32, s32 *, s32);

s32 func_80052C10(s32 name, s32 mode, s32 arg2) {
    VoiceAttr_80052C10 attr;
    s32 pos;
    Src_80052C10 *src;
    s32 ret;
    s32 voice;
    u32 addr;

    if (!D_8008A9EC) {
        printf(D_80010920, D_8008AA00, 0x1D6);
        exit(1);
    }
    src = func_80053A4C(name, mode);
    if (src != NULL) {
    if (D_800B134C.src != NULL) {
        func_8004E30C(D_800B134C.voices[0].id);
        if (D_800B134C.flags & 0x200) {
            func_8004E30C(D_800B134C.voices[1].id);
        }
        func_80053B34(D_800B134C.src);
    }
    D_800B134C.src = src;
    D_800B134C.unk24 = arg2;
    D_800B134C.unk28 = 0;
    D_800B134C.unk2C = 0;
    D_800B134C.half = D_800B134C.size >> 1;
    if (mode & 0x10) {
        D_800B134C.flags |= 0x10;
    } else {
        D_800B134C.flags &= ~0x10;
    }
    if (src->chans == 2) {
        D_800B134C.flags |= 0x200;
    } else {
        D_800B134C.flags &= ~0x200;
    }
    D_800B134C.voices[0].id = func_8004DEBC(0, 0xFF);
    if (D_800B134C.voices[0].id == 0xFF) {
        ret = 0x202;
        goto release;
    }
    {
    s32 v;
    v = func_8004EECC(D_800B134C.voices[0].id);
    D_800B134C.voices[0].voice = v;
    attr.mask = 0x1FF93;
    attr.volL = 0x3FFF;
    attr.volR = (src->chans == 2) ? 0 : 0x3FFF;
    attr.pitch = ((u32) src->rate << 12) / 44100;
    attr.a_mode = 1;
    attr.s_mode = 1;
    attr.r_mode = 3;
    attr.ar = 0;
    attr.rr = 0;
    attr.dr = 0xF;
    attr.sr = 0x7F;
    attr.sl = 0xF;
    attr.voice = 1 << v;
    attr.addr = D_800B134C.voices[0].addr;
    attr.loop_addr = D_800B134C.voices[0].addr;
    }
    SpuSetVoiceAttr(&attr);
    SpuFlush(0);
    ret = 0;
    if (D_800B134C.flags & 0x200) {
        D_800B134C.voices[1].id = func_8004DEBC(0, 0xFF);
        if (D_800B134C.voices[1].id != 0xFF) {
            voice = D_800B134C.voices[1].voice = func_8004EECC(D_800B134C.voices[1].id);
            attr.volL = 0;
            attr.volR = 0x3FFF;
            attr.voice = 1 << voice;
            addr = D_800B134C.voices[0].addr + (D_800B134C.size >> 1);
            D_800B134C.voices[1].addr = addr;
            attr.addr = addr;
            attr.loop_addr = addr;
            SpuSetVoiceAttr(&attr);
            SpuFlush(0);
        } else {
            ret = 0x202;
        }
    } else {
        D_800B134C.flags &= ~0x200;
    }
    if (ret == 0) {
        D_800B134C.flags &= ~0x800;
        D_800B134C.unk10 = 0;
        if (func_80053774(D_800B134C.size, &pos, 1) < D_800B134C.size) {
            D_800B134C.flags |= 0x1000;
            D_800B134C.unk1C = pos;
        } else {
            D_800B134C.unk1C = 0;
            D_800B134C.flags &= ~0x1000;
        }
        D_800B134C.state = 2;
        D_800B134C.unk18 = 0;
        return 0;
    }
    func_8004E30C(D_800B1388[0]);
release:
    func_80053B34(src);
    } else {
        ret = 0x201;
    }
    D_800B134C.flags = 0;
    return ret;
}
