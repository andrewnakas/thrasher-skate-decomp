#include "common.h"

extern s32 D_8008A9EC;
extern s32 D_8008A9F0;
extern s32 D_8008A9F4;
extern s32 D_8008A9F8;
extern s32 D_8008A9FC;
extern s32 D_8008B454;
extern u8 D_800B13DC[];
extern u8 D_800B134E[];
extern u8 D_800B1364[];

extern void *memset(void *, s32, u32);
extern void func_8005CBD8(s32);
extern s32 func_8005CBEC(s32, s32, s32);
extern s32 func_80053774(s32, void *, s32);
extern void SpuSetVoiceAttr(void *);
extern void EnterCriticalSection(void);
extern void ExitCriticalSection(void);

typedef struct S_80052874 {
    u16 flags;
    u8 unk2;
    u8 pad3;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    u8 pad20[0xC];
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    u8 pad3C[4];
    s32 unk40;
    u8 pad44[8];
    s32 unk4C;
} S_80052874;

typedef struct VoiceAttr_80052874 {
    s32 mask;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    u8 padC[0x34];
} VoiceAttr_80052874;

extern S_80052874 D_800B134C;

s32 func_80052874(void) {
    S_80052874 *p;
    VoiceAttr_80052874 attr;
    u8 buf[8];
    s32 prev;
    s32 state;
    s32 n;
    s32 step;
    s32 delta;
    s32 value;
    s32 got;
    s32 mask;

    if (D_8008A9EC == 0) {
        return 0;
    }

    prev = D_8008A9F8 + 1;
    state = D_8008A9FC;
    if (state == 0) {
    } else if (state == 1 && D_8008A9F0 <= 0) {
        D_800B134E[0] = state;
        memset(D_800B13DC, 0, 0x90);
        D_8008A9F4 = 0;
        D_8008B454 = 0;
        func_8005CBD8(0);
        func_8005CBEC(7, 0, 0);
        D_8008A9FC = 0;
        return 0x204;
    } else {
        D_8008A9FC--;
    }

    p = &D_800B134C;
    if (p->unk2 == 4) {
        if (p->unk2C & 1) {
            n = prev - D_8008A9F8;
            if (n != 0) {
                step = p->unk38;
                do {
                    p->unk30 += step;
                    if ((step > 0) ? (p->unk30 >= p->unk34) : (p->unk30 <= p->unk34)) {
                        p->unk30 = p->unk34;
                        p->unk2C &= ~1;
                        break;
                    }
                } while (--n != 0);
            }
        }

        value = p->unk30 >> 9;
        attr.unk4 = 3;
        mask = 1 << p->unk40;
        if (D_800B134C.flags & 0x200) {
            attr.unkA = 0;
            attr.mask = mask;
            attr.unk8 = value;
            SpuSetVoiceAttr(&attr);
            attr.mask = mask | (1 << p->unk4C);
            attr.unk8 = 0;
            attr.unkA = value;
            SpuSetVoiceAttr(&attr);
        } else {
            attr.mask = mask;
            attr.unk8 = value;
            attr.unkA = value;
            SpuSetVoiceAttr(&attr);
        }

        if (!(p->unk2C & 1) && (p->unk2C & 2)) {
            p->unk2 = 6;
        }

        if (D_8008A9F0 > 0) {
            goto done;
        }

        EnterCriticalSection();
        p = &D_800B134C;
        if ((u32) p->unkC < (u32) p->unk14) {
            delta = p->unk4 + p->unkC - p->unk14;
        } else {
            delta = p->unkC - p->unk14;
        }
        p->unk14 = p->unkC;
        ExitCriticalSection();

        n = p->unk18 + delta;
        p->unk18 = n;
        if ((u32) n < (u32) p->unk8) {
            goto done;
        }

        D_800B134C.flags &= 0xF7FF;
        if ((u32) (p->unk10 + n) > (u32) p->unk4) {
            step = p->unk4 - p->unk10;
            got = func_80053774(step, buf, 0);
            if (got < step) {
                if (!(D_800B134C.flags & 0x1000)) {
                    D_800B134C.flags |= 0x1000;
                    p->unk1C = *(s32 *) buf;
                }
                func_80053774(p->unk18 - step, buf, 0);
                goto clear;
            }
            n = p->unk18 - step;
            if (n == 0) {
                goto clear;
            }
        }
        got = func_80053774(n, buf, 0);
        if (got < n && !(D_800B134C.flags & 0x1000)) {
            D_800B134C.flags |= 0x1000;
            p->unk1C = *(s32 *) buf;
        }
    clear:
        *(s32 *) D_800B1364 = 0;
    }
done:
    D_8008A9F8 = prev;
    return 0;
}
