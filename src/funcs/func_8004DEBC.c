#include "common.h"

typedef struct Slot_8004DEBC {
    u8 used;
    u8 owner;
} Slot_8004DEBC;

typedef struct VoiceAttr_8004DEBC {
    u32 voice;
    u32 mask;
    s16 volL;
    s16 volR;
    u8 padC[8];
    u16 pitch;
    u8 pad16[6];
    u32 addr;
    u32 loop_addr;
    u8 pad24[0xC];
    u16 ar;
    u16 dr;
    u16 sr;
    u16 rr;
    u16 sl;
    u8 pad3A[6];
} VoiceAttr_8004DEBC;

typedef struct Snd_8004DEBC {
    u16 unk0;
    u16 pitch;
    u8 vol;
    s8 pan;
    u8 ar;
    u8 dr;
    u8 sr;
    u8 rr;
    u8 sl;
    u8 padB[6];
    u8 rev;
    u16 bank;
} Snd_8004DEBC;

typedef struct Voice_8004DEBC {
    u8 flags;
    u8 prio;
    u8 vol;
    s8 pan;
    s16 unk4;
    u8 slot;
    u8 pad7;
    Snd_8004DEBC *snd;
    VoiceAttr_8004DEBC attr;
} Voice_8004DEBC;

typedef struct Smp_8004DEBC {
    u16 unk0;
    u16 pitch;
} Smp_8004DEBC;

extern char D_80010848[];
extern char D_80010870[];
extern u8 D_80082948[];
extern u8 D_80082950[];
extern u8 D_80082954[];
extern u8 D_80082958[];
extern u8 D_8008295C[];
extern u8 D_80082960[];
extern Slot_8004DEBC D_800B03C4[];
extern Voice_8004DEBC D_800AFCA4[];

extern Smp_8004DEBC *func_8004FE00(u16, u16);
extern u32 *func_8004FECC(u16, u16);
extern void SpuSetVoiceAttr(VoiceAttr_8004DEBC *);
extern void SpuSetReverbVoice(s32, u32);

u8 func_8004DEBC(Snd_8004DEBC *snd, s32 prio) {
    Voice_8004DEBC *vo;
    Voice_8004DEBC *v;
    Voice_8004DEBC *base;
    Slot_8004DEBC *s;
    VoiceAttr_8004DEBC *attr;
    Smp_8004DEBC *smp;
    u32 *wave;
    s32 i;
    s32 best;
    s32 slot;
    s32 pan;
    u8 minp;
    u8 p;
    u32 l;
    u32 r;

    best = 0;
    *(volatile s32 *) D_80082948 += 1;
    i = *(volatile s32 *) D_80082954;
    while (1) {
        s = &D_800B03C4[i];
        if (s->used == 0) {
            s->used = 1;
            s->owner = 0xFF;
            *(volatile s32 *) D_80082954 = i + 1;
            slot = i;
            if (*(volatile s32 *) D_80082954 == 0x40) {
                *(volatile s32 *) D_80082954 = 0;
            }
            break;
        }
        if (++i == 0x40) {
            i = 0;
        }
        if (i == *(volatile s32 *) D_80082954) {
            printf(D_80010848, D_80010870, 0x17D);
            exit(1);
        }
    }
    vo = NULL;
    minp = 0xFF;
    i = *(volatile s32 *) D_80082950;
    base = D_800AFCA4;
    v = &base[i];
    do {
        p = v->prio;
        if (p == 0) {
            best = i;
            *(volatile s32 *) D_80082950 = best + 1;
            vo = v;
            if (*(volatile s32 *) D_80082950 == 0x18) {
                *(volatile s32 *) D_80082950 = 0;
            }
            break;
        }
        if (p <= minp) {
            minp = p;
            best = i;
        }
        i++;
        v++;
        if (i == 0x18) {
            v = base;
            i = 0;
        }
    } while (i != *(volatile s32 *) D_80082950);
    if (vo == NULL && (u8) prio >= minp) {
        vo = &D_800AFCA4[best];
        *(volatile u32 *) D_8008295C |= vo->attr.voice;
        *(volatile u32 *) D_80082958 &= ~vo->attr.voice;
        *(volatile u32 *) D_80082960 |= vo->attr.voice;
        D_800B03C4[vo->slot].owner = 0xFF;
        if (vo->flags & 1) {
            D_800B03C4[vo->slot].used = 0;
        }
        *(volatile s32 *) D_80082950 = best + 1;
        if (*(volatile s32 *) D_80082950 == 0x18) {
            *(volatile s32 *) D_80082950 = 0;
        }
    }
    if (vo != NULL) {
        vo->prio = prio;
        vo->flags = 0;
        vo->slot = slot;
        vo->unk4 = 1;
        vo->snd = snd;
        if (snd != NULL) {
            attr = &vo->attr;
            smp = func_8004FE00(snd->bank, snd->unk0);
            wave = func_8004FECC(snd->bank, smp->unk0);
            vo->vol = snd->vol;
            vo->pan = snd->pan;
            attr->mask = 0x1FF9F;
            attr->addr = *wave;
            attr->loop_addr = *wave;
            attr->pitch = (u32) (snd->pitch * smp->pitch) >> 12;
            pan = vo->pan;
            if (pan > 0) {
                r = vo->vol;
                l = ((r * (0x7F - pan)) >> 7) & 0xFF;
            } else if (pan < 0) {
                l = vo->vol;
                r = ((l * (pan + 0x7F)) >> 7) & 0xFF;
            } else {
                r = vo->vol;
                l = r;
            }
            attr->volL = l << 7;
            attr->volR = r << 7;
            attr->ar = snd->ar;
            attr->dr = snd->dr;
            attr->sr = snd->sr;
            attr->rr = snd->rr;
            attr->sl = snd->sl;
            SpuSetVoiceAttr(attr);
            SpuSetReverbVoice((snd->rev ^ 1) & 1, attr->voice);
        } else {
            vo->vol = 0x7F;
            vo->pan = 0;
        }
        D_800B03C4[(u8) slot].owner = best;
        *(volatile s32 *) D_80082948 -= 1;
        return slot;
    }
    D_800B03C4[(u8) slot].used = 0;
    *(volatile s32 *) D_80082948 -= 1;
    return 0xFF;
}
