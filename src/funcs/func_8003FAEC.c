#include "common.h"

typedef struct Elem_8003FAEC {
    u8 pad0[0xC];
    s16 unkC;
    s16 unkE;
    s16 unk10;
    u8 pad12[0xE];
    u8 *unk20;
    u8 *unk24;
    u8 *unk28;
    u8 pad2C[8];
} Elem_8003FAEC;

typedef struct Rec_8003FAEC {
    u8 pad0[2];
    u8 size;
    u8 pad3[0xD];
    u8 *unk10;
    u8 *unk14;
    u8 *unk18;
    u8 *unk1C;
} Rec_8003FAEC;

typedef struct Hdr_8003FAEC {
    u32 flags;
    u16 id;
    u16 nElems;
    u16 nRecs;
    u8 padA[4];
    u16 unkE;
    Elem_8003FAEC *elems;
    Rec_8003FAEC *recs;
    u8 *unk18;
    u8 *unk1C;
    s32 unk20;
    u8 *unk24;
    u8 *unk28;
    s32 unk2C;
} Hdr_8003FAEC;

extern Hdr_8003FAEC *func_8003FD48(void *);
extern Hdr_8003FAEC *func_80040EB8(Hdr_8003FAEC *);
extern void func_80041374(Hdr_8003FAEC *, s32, s32);
extern void func_8003F9F8(Hdr_8003FAEC *, s32);
extern u8 *func_80034C20(s32);
extern void memset(void *, s32, s32);

Hdr_8003FAEC *func_8003FAEC(void *src, u16 id, s32 mode) {
    Hdr_8003FAEC *h;
    Elem_8003FAEC *e;
    Rec_8003FAEC *r;
    u8 *buf;
    u16 i;

    h = func_8003FD48(src);
    h->flags &= ~0x203;
    h->id = id;
    h->elems = (Elem_8003FAEC *) (h->elems ? (u32) h->elems + (u32) h : 0);
    h->recs = (Rec_8003FAEC *) (h->recs ? (u32) h->recs + (u32) h : 0);
    h->unk18 = (u8 *) (h->unk18 ? (u32) h->unk18 + (u32) h : 0);
    h->unk1C = (u8 *) (h->unk1C ? (u32) h->unk1C + (u32) h : 0);
    h->unk28 = (u8 *) (h->unk28 ? (u32) h->unk28 + (u32) h : 0);

    e = h->elems;
    for (i = 0; i < h->nElems; i++, e++) {
        e->unk20 = (u8 *) (e->unk20 ? (u32) e->unk20 + (u32) h : 0);
        e->unk24 = (u8 *) (e->unk24 ? (u32) e->unk24 + (u32) h : 0);
        e->unk28 = (u8 *) (e->unk28 ? (u32) e->unk28 + (u32) h : 0);
    }

    r = h->recs;
    for (i = 0; i < h->nRecs; i++) {
        r->unk10 = (u8 *) (r->unk10 ? (u32) r->unk10 + (u32) h : 0);
        r->unk14 = (u8 *) (r->unk14 ? (u32) r->unk14 + (u32) h : 0);
        r->unk18 = (u8 *) (r->unk18 ? (u32) r->unk18 + (u32) h : 0);
        r->unk1C = (u8 *) (r->unk1C ? (u32) r->unk1C + (u32) h : 0);
        r = (Rec_8003FAEC *) ((u8 *) r + r->size);
    }

    h->unk2C = h->elems->unkE;
    h->elems->unkC = 0;
    h->elems->unkE = 0;
    h->elems->unk10 = 0;
    buf = func_80034C20(0x1F0);
    h->unk24 = buf;
    memset(buf, 0, 0x1F0);
    h->unkE = h->nElems;
    if (mode & 1) {
        h = func_80040EB8(h);
    }
    func_80041374(h, 0, 3);
    func_80041374(h, 0, 0xC);
    if (mode & 2) {
        h->unk1C = func_80034C20(h->unk20 * 2);
    }
    func_8003F9F8(h, id);
    return h;
}
