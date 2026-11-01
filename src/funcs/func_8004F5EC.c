/* D_80082940 is read through its neighbour (*(&D_8008294C - 3)) so gcc emits one unsplit lw that the
 * assembler expands, letting the gp-relative D_8008A99C load schedule first. */
#include "common.h"

extern s32 SpuIsTransferCompleted(s32);
extern s32 SpuMalloc(s32);
extern void SpuRead(u32, u32);
extern void SpuSetTransferStartAddr(s32);
extern void VSync(s32);
extern s32 strncmp(void *, void *, s32);
extern void exit(s32) __attribute__((noreturn));

extern u8 D_80010888[];
extern u8 D_8008A9A0[];
extern u8 D_8008A9B8[];
extern u8 D_8008A9C0[];
extern s32 D_8008294C;
#define D_80082940 (*(&D_8008294C - 3))
extern s32 D_8008A97C;
extern s32 D_8008A980;
extern s32 D_8008A984;
extern s32 D_8008A98C;
extern s32 D_8008A990;
extern s32 D_8008A994;
extern s32 D_8008A998;
extern s32 D_8008A99C;
extern u8 D_800B066C[];

typedef struct {
    u32 flags;
    u32 base;
    u32 unk8;
    u32 unkC;
} Slot_8004F5EC;

typedef struct {
    u8 pad0[0x12];
    u16 bank;
} A_8004F5EC;

typedef struct {
    u8 pad0[6];
    u16 bank;
    u8 pad8[4];
} B_8004F5EC;

typedef struct {
    u32 addr;
    u32 size;
} C_8004F5EC;

typedef struct {
    u8 pad0[8];
    u32 addr;
    u8 padC[2];
    u16 bank;
} E_8004F5EC;

typedef struct {
    u8 pad0[4];
    u32 addr;
} DE_8004F5EC;

typedef struct {
    u8 flags;
    u8 n;
    u8 pad2[0xA];
    DE_8004F5EC e[1];
} D_8004F5EC;

typedef struct {
    u8 pad0[2];
    u16 bank;
} F_8004F5EC;

typedef struct {
    u8 pad0[4];
    u8 magic[0xC];
    u32 nA;
    A_8004F5EC *a;
    u32 nB;
    B_8004F5EC *b;
    u32 nC;
    C_8004F5EC *c;
    u32 nD;
    D_8004F5EC **d;
    u32 nE;
    E_8004F5EC *e;
    u8 pad38[8];
    u32 nF;
    F_8004F5EC **f;
} Hdr_8004F5EC;

s32 func_8004F5EC(u8 *arg0, s32 spu, u16 *id) {
    Hdr_8004F5EC *h;
    Slot_8004F5EC *slot;
    Slot_8004F5EC *s;
    u32 i;
    u32 j;
    u32 k;
    u32 total;
    s32 addr;

    slot = NULL;
    for (i = 0; i < 0x10; i++) { s = &((Slot_8004F5EC *) D_800B066C)[i];
        if (!(s->flags & 1)) {
            slot = s;
            if (spu != 0) {
                slot->flags = 3;
            } else {
                slot->flags = 1;
            }
            slot->unk8 = 0;
            slot->unkC = 0;
            *id = i;
            break;
        }
    }
    if (slot == NULL) {
        printf(D_80010888, D_8008A9A0, 0x13C);
        exit(1);
    }
    slot->base = (u32) arg0;
    h = (Hdr_8004F5EC *) arg0;
    if (strncmp(arg0, D_8008A9B8, 4) != 0) {
        printf(D_80010888, D_8008A9A0, 0x13F);
        exit(1);
    }
    if (strncmp(h->magic, D_8008A9C0, 4) != 0) {
        printf(D_80010888, D_8008A9A0, 0x140);
        exit(1);
    }
    h->a = (A_8004F5EC *) ((u8 *) h->a + (u32) h);
    h->b = (B_8004F5EC *) ((u8 *) h->b + (u32) h);
    h->e = (E_8004F5EC *) ((u8 *) h->e + (u32) h);
    h->c = (C_8004F5EC *) ((u8 *) h->c + (u32) h);
    h->d = (D_8004F5EC **) ((u8 *) h->d + (u32) h);
    h->f = (F_8004F5EC **) ((u8 *) h->f + (u32) h);

    for (i = 0; i < h->nA; i++) {
        h->a[i].bank = *id;
    }
    D_8008A97C += h->nA;

    for (i = 0; i < h->nB; i++) {
        h->b[i].bank = *id;
    }
    D_8008A980 += h->nB;

    for (i = 0; i < h->nD; i++) {
        *(u32 *) &h->d[i] += slot->base;
        {
            D_8004F5EC *d;
            d = h->d[i];
            if (d->flags & 1) {
                D_8004F5EC *dd = d;
                for (k = 0; k < dd->n; k++) {
                    u32 off = k * 8 + 0xC;
                    ((DE_8004F5EC *) (off + (u8 *) dd))->addr += slot->base;
                }
            }
        }
    }
    D_8008A98C += h->nD;

    for (i = 0; i < h->nE; i++) {
        h->e[i].addr += slot->base;
        h->e[i].bank = *id;
    }
    D_8008A990 += h->nE;

    for (i = 0; i < h->nF; i++) {
        *(u32 *) &h->f[i] += slot->base;
        h->f[i]->bank = *id;
    }
    D_8008A994 += h->nF;

    if (spu != 0) {
        total = 0;
        for (i = 0; i < h->nC; i++) {
            total += h->c[i].size;
        }
        total = (total + 0x3F) & ~0x3F;
        addr = SpuMalloc(total);
        if (addr == -1) {
            printf(D_80010888, D_8008A9A0, 0x173);
            exit(1);
        }
        D_8008A99C += total;
        D_8008A998 = 0x7EFF0 - D_8008A99C - D_80082940;
        i = 300;
        while (SpuIsTransferCompleted(0) == 0 && --i != 0) {
            VSync(0);
        }
        SpuSetTransferStartAddr(addr);
        SpuRead(slot->base + h->c[0].addr, total);
        i = 300;
        while (SpuIsTransferCompleted(0) == 0 && --i != 0) {
            VSync(0);
        }
        for (i = 0; i < h->nC; i++) {
            h->c[i].addr = addr;
            addr += h->c[i].size;
        }
        D_8008A984 += h->nC;
    }
    return 0;
}
