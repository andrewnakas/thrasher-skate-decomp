#include "common.h"

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 unk3;
    struct {
        u16 unk0;
        u8 data[6];
        u8 cnt;
        u8 pad9;
        u16 unkA;
    } sub[2];
    u8 pad1C[0x10];
    s16 unk2C[4];
    u16 unk34;
    u8 unk36;
    u8 unk37;
    u8 pad38[2];
} Src_80028498;

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
    u8 unk6;
    u8 unk7;
    u8 pad8[2];
    struct {
        s16 id;
        u8 data[6];
        u8 cnt;
        u8 pad9;
        u16 unkA;
    } sub[2];
    u8 pad22[2];
    u8 unk24;
    u8 pad25[3];
    s32 unk28[4];
} Dst_80028498;

typedef struct {
    u8 pad0[0x58];
    Dst_80028498 *list;
    s32 n;
} G_80028498;

typedef struct {
    s16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    u8 pad1A[2];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
} A_80028498;

typedef struct {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} B_80028498;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u8 pad12[2];
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
} C_80028498;

typedef struct {
    s32 unk0;
    s16 unk4;
    u16 na;
    u16 nb;
    u16 nc;
    s32 size;
    A_80028498 *a;
    B_80028498 *b;
    C_80028498 *c;
    u8 *d;
    s32 unk20;
} Mdl_80028498;

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[2];
    u16 na;
    u16 nb;
    u16 nc;
} MHdr_80028498;

typedef struct {
    u8 pad0[2];
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 padE[6];
    s32 unk14;
    u8 pad18[4];
    u16 unk1C;
    u8 pad1E[2];
} MOb_80028498;

typedef struct {
    u8 hdr[0xC];
    MOb_80028498 r[1];
} MObC_80028498;

typedef struct {
    u16 flags;
    u8 unk2;
    u8 pad3;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u8 pad16[2];
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u8 pad1E[2];
} MFa_80028498;

typedef struct {
    u8 hdr[0xC];
    MFa_80028498 r[1];
} MFaC_80028498;

typedef struct {
    u8 pad0[2];
    u16 unk2;
    u16 unk4;
    u16 unk6;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    u8 pad14[4];
} MVt_80028498;

typedef struct {
    u8 hdr[0xC];
    MVt_80028498 r[1];
} MVtC_80028498;

extern G_80028498 D_800A4F00;
extern s32 D_800A4F5C;

extern u8 *func_8001D5B0(s32, s32, s32);
extern s32 func_80032C28(s32, s32);
extern void func_80034C14(void);
extern Dst_80028498 *func_80034C20(s32);
extern void *func_80034CF0(s32);
extern void func_80034D30(void *);
extern void func_80034D4C(void *, void *, s32);
extern void func_8003FAEC(Mdl_80028498 *, s32, s32);

#define REL(p, base) ((p) ? (s32) (p) - (s32) (base) : 0)

void func_80028498(s32 arg0) {
    Src_80028498 *src;
    Dst_80028498 *dst;
    u8 *hdr;
    s32 i;
    s32 j;
    s32 k;
    s32 first;
    Mdl_80028498 *mdl;
    MHdr_80028498 *mh;
    A_80028498 *a;
    B_80028498 *b;
    C_80028498 *c;
    u8 *d;

    first = 1;
    hdr = func_8001D5B0(arg0, 0x444F5250, first);
    src = (Src_80028498 *) (hdr + 0xC);
    i = 0;
    D_800A4F00.n = *(u16 *) (hdr + 0xA);
    dst = func_80034C20(D_800A4F00.n * sizeof(Dst_80028498));
    D_800A4F00.list = dst;
    if (D_800A4F00.n > 0) {
        do {
            dst->unk0 = src->unk0;
            dst->unk2 = src->unk3;
            dst->unk4 = src->unk34;
            dst->unk6 = src->unk36;
            dst->unk7 = src->unk37;
            dst->unk24 = src->unk2;
            dst->unk28[0] = func_80032C28(src->unk2C[0] << 8, 0x640000);
            dst->unk28[1] = func_80032C28(src->unk2C[1] << 8, 0x640000);
            dst->unk28[2] = func_80032C28(src->unk2C[2] << 8, 0x640000);
            dst->unk28[3] = func_80032C28(src->unk2C[3] << 8, 0x640000);
            for (j = 0; j < 2; j++) {
                dst->sub[j].id = (s16) (i * 2 - 0x8000) + j;
                dst->sub[j].cnt = src->sub[j].cnt;
                func_80034D4C(dst->sub[j].data, src->sub[j].data, dst->sub[j].cnt);
                dst->sub[j].unkA = src->sub[j].unkA;
            }
            dst++;
            src++;
            i++;
        } while (i < D_800A4F00.n);
    }

    i = 0;
    dst = D_800A4F00.list;
    if (D_800A4F00.n > 0) {
        do {
            for (k = 0; k < (s32) ((*(u32 *) dst >> 2) & 3); k++) {
                mh = (MHdr_80028498 *) func_8001D5B0(arg0, 0x44484F4D, first);
                mdl = func_80034CF0(sizeof(Mdl_80028498));
                mdl->unk0 = mh->unkC;
                mdl->unk4 = 0;
                mdl->na = mh->na;
                mdl->nb = mh->nb;
                mdl->nc = mh->nc;
                mdl->unk20 = 0;
                a = func_80034CF0(mdl->na * sizeof(A_80028498));
                b = func_80034CF0(mdl->nb * sizeof(B_80028498));
                c = func_80034CF0(mdl->nc * sizeof(C_80028498));
                d = func_80034CF0(mdl->nb * 0x2C);
                mdl->a = a;
                mdl->b = b;
                mdl->c = c;
                mdl->d = d;
                {
                    MObC_80028498 *ch = (MObC_80028498 *) func_8001D5B0(arg0, 0x424F4F4D, first);
                    A_80028498 *pa = a;
                    for (j = 0; j < mdl->na; j++) {
                        pa->unk0 = 0;
                        pa->unk2 = ch->r[j].unk2;
                        pa->unk4 = ch->r[j].unk4;
                        pa->unk6 = ch->r[j].unk6;
                        pa->unk8 = ch->r[j].unk8;
                        pa->unkC = ch->r[j].unkA;
                        pa->unk10 = ch->r[j].unkC;
                        pa->unk14 = 0;
                        pa->unk16 = 0;
                        pa->unk18 = 0;
                        pa->unk1C = (ch->r[j].unk14 * 100) >> 16;
                        pa->unk20 = 0;
                        pa->unk24 = 0;
                        pa->unk28 = ch->r[j].unk1C;
                        pa->unk2C = (s32) mdl->b;
                        pa->unk30 = (s32) mdl->d;
                        pa->unk34 = 0;
                        pa->unk38 = 0;
                        pa->unk3C = 0;
                        pa->unk40 = 0;
                        pa++;
                    }
                }
                {
                    MFaC_80028498 *ch = (MFaC_80028498 *) func_8001D5B0(arg0, 0x41464F4D, first);
                    B_80028498 *pb = b;
                    for (j = 0; j < mdl->nb; j++) {
                        pb->unk1 = 0;
                        if (ch->r[j].flags & 4) {
                            pb->unk1 = 2;
                        }
                        if (ch->r[j].flags & 0x40) {
                            pb->unk1 |= 4;
                        }
                        pb->unk2 = ch->r[j].unk4 >> 4;
                        pb->unk4 = ch->r[j].unk8 >> 4;
                        pb->unk6 = ch->r[j].unkC >> 4;
                        pb->unk8 = ch->r[j].unk14 ? (s32) (&mdl->c[ch->r[j].unk14] - 1) : 0;
                        pb->unkC = ch->r[j].unk12 ? (s32) (&mdl->c[ch->r[j].unk12] - 1) : 0;
                        pb->unk10 = ch->r[j].unk10 ? (s32) (&mdl->c[ch->r[j].unk10] - 1) : 0;
                        pb++;
                    }
                    {
                        MVtC_80028498 *vc = (MVtC_80028498 *) func_8001D5B0(arg0, 0x54564F4D, first);
                        C_80028498 *pc = c;
                        for (j = 0; j < mdl->nc; j++) {
                            pc->unk0 = 0;
                            pc->unk4 = 0;
                            pc->unk8 = 0;
                            pc->unkA = 0;
                            pc->unkC = vc->r[j].unk2;
                            pc->unkE = vc->r[j].unk4;
                            pc->unk10 = vc->r[j].unk6;
                            pc->unk14 = vc->r[j].unk8 >> 4;
                            pc->unk16 = vc->r[j].unkC >> 4;
                            pc->unk18 = vc->r[j].unk10 >> 4;
                            pc->unk1A = 0;
                            pc++;
                        }
                    }
                    {
                        B_80028498 *p = b;
                        u8 *q = d;
                        MFa_80028498 *ps = ch->r;
                        for (j = 0; j < mdl->nb; j++) {
                            if (ps->unk2 != 0) {
                                p->unk0 = 0x1B;
                                q[3] = 9;
                                q[7] = 0x34;
                                *(s16 *) (q + 0x1A) = ps->unk2 - 1;
                                *(u16 *) (q + 0xC) = ps->unk1C;
                                *(u16 *) (q + 0x18) = ps->unk1A;
                                *(u16 *) (q + 0x24) = ps->unk18;
                                q += 0x28;
                            } else {
                                p->unk0 = 0x13;
                                q[3] = 6;
                                q[7] = 0x30;
                                q += 0x1C;
                            }
                            p++;
                            ps++;
                        }
                        mdl->size = (s32) p - (s32) b;
                    }
                }
                func_80034C14();
                mdl->a = (A_80028498 *) REL(mdl->a, mdl);
                mdl->b = (B_80028498 *) REL(mdl->b, mdl);
                mdl->c = (C_80028498 *) REL(mdl->c, mdl);
                mdl->d = (u8 *) REL(mdl->d, mdl);
                {
                    A_80028498 *pa = a;
                    for (j = 0; j < mdl->na; j++, pa++) {
                        { s32 v = pa->unk20; s32 r = 0; if (v) r = v - (s32) mdl; pa->unk20 = r; }
                        { s32 v = pa->unk24; s32 r = 0; if (v) r = v - (s32) mdl; pa->unk24 = r; }
                        { s32 v = pa->unk2C; s32 r = 0; if (v) r = v - (s32) mdl; pa->unk2C = r; }
                        
                    }
                }
                {
                    B_80028498 *pb = b;
                    for (j = 0; j < mdl->nb; j++, pb++) {
                        { s32 v = pb->unk8; s32 r = 0; if (v) r = v - (s32) mdl; pb->unk8 = r; }
                        { s32 v = pb->unkC; s32 r = 0; if (v) r = v - (s32) mdl; pb->unkC = r; }
                        { s32 v = pb->unk10; s32 r = 0; if (v) r = v - (s32) mdl; pb->unk10 = r; }
                        { s32 v = pb->unk14; s32 r = 0; if (v) r = v - (s32) mdl; pb->unk14 = r; }
                        
                    }
                }
                func_8003FAEC(mdl, (u16) (i * 2 - 0x8000 + k), 0);
                func_80034C14();
                first = 0;
                func_80034D30(d);
                func_80034D30(c);
                func_80034D30(b);
                func_80034D30(a);
                func_80034D30(mdl);
            }
            i++;
            dst++;
        } while (i < D_800A4F00.n);
    }
}
