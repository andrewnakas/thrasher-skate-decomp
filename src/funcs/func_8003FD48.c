#include "common.h"

typedef struct {
    u32 f0;
    u16 f4;
    u16 n6;
    u16 n8;
    u16 nA;
    s32 fC;
    u32 off10;
    u32 off14;
    u32 off18;
    u32 off1C;
} InHdr_8003FD48;

typedef struct {
    u32 f0;
    u16 f4;
    u16 n6;
    u16 n8;
    u16 nA;
    u16 fC;
    u16 fE;
    u32 off10;
    u32 off14;
    u32 off18;
    u32 f1C;
    s32 f20;
    u8 pad24[4];
    s32 f28;
    u8 pad2C[4];
    s32 f30;
    u8 pad34[0x174 - 0x34];
} OutHdr_8003FD48;

typedef struct {
    u16 f0;
    u8 f2[6];
    u16 f8;
    u16 fA;
    u16 fC;
    u16 fE;
    u16 f10;
    u16 f12;
    u16 f14;
    u16 f16;
    u16 f18;
    u16 f1A;
    u16 f1C;
    u16 f1E;
    u32 f20;
    u32 f24;
    u16 f28;
    u16 f2A;
    u32 f2C;
    u8 pad30[0x14];
} InA_8003FD48;

typedef struct {
    u16 f0;
    u16 f2;
    u8 f4[6];
    u16 fA;
    u16 fC;
    u16 fE;
    u16 f10;
    u16 f12;
    u16 f14;
    u16 f16;
    u16 f18;
    u16 f1A;
    u16 f1C;
    u16 f1E;
    u32 f20;
    u32 f24;
    u32 f28;
    u32 f2C;
    u32 f30;
} OutA_8003FD48;

typedef struct {
    u8 pad0[0xC];
    u8 fC[6];
    u16 f12;
    s16 f14;
    s16 f16;
    s16 f18;
    u16 f1A;
} InB_8003FD48;

typedef struct {
    u8 f0[6];
    u8 f6;
    u8 f7;
    s16 f8;
    s16 fA;
    s16 fC;
    u16 fE;
} OutB_8003FD48;

typedef struct {
    u8 f0;
    u8 f1;
    u8 f2[6];
    u32 f8[4];
} InC_8003FD48;

typedef struct {
    u16 f0;
    u8 size;
    u8 type;
    u8 f4[6];
    u8 fA;
    u8 fB;
    u8 padC[4];
    u32 f10[4];
    u16 d[5];
} OutC_8003FD48;

extern u8 *func_80034C14(void);
extern OutHdr_8003FD48 *func_80034C20(s32);
extern void func_80034C8C(void *, s32);
extern void func_80034D4C(void *, void *, s32);
extern void *memset(void *, s32, u32);
extern u8 D_8008251C[];
extern u8 D_8008A7DC[8];
#define D_8008A7D4 (&D_8008A7DC[-8])

OutHdr_8003FD48 *func_8003FD48(InHdr_8003FD48 *in) {
    InA_8003FD48 *ia;
    InC_8003FD48 *ic;
    InB_8003FD48 *ib;
    u8 *q;
    OutA_8003FD48 *oa;
    OutB_8003FD48 *ob;
    OutC_8003FD48 *oc;
    OutC_8003FD48 *oc0;
    OutC_8003FD48 *end;
    OutHdr_8003FD48 *out;
    s32 size;
    s32 i;
    s32 i2;
    s32 k;
    u32 v;
    u16 nlit;
    u8 t;
    u16 *d;

    ia = (InA_8003FD48 *) ((u8 *) in + in->off10);
    ic = (InC_8003FD48 *) ((u8 *) in + in->off14);
    ib = (InB_8003FD48 *) ((u8 *) in + in->off18);
    q = (u8 *) in + in->off1C;
    out = (OutHdr_8003FD48 *) func_80034C14();
    oa = (OutA_8003FD48 *) ((u8 *) out + 0x174);
    ob = (OutB_8003FD48 *) (oa + in->n6);
    oc = (OutC_8003FD48 *) (ob + in->nA);
    size = (u8 *) oc - (u8 *) out;
    size += in->n8 * 0x2C;
    out = func_80034C20(size);
    memset(out, 0, size);
    out->f0 = in->f0;
    out->n6 = in->n6;
    out->n8 = in->n8;
    out->nA = in->nA;
    out->off10 = (u8 *) oa - (u8 *) out;
    out->off14 = (u8 *) oc - (u8 *) out;
    out->off18 = (u8 *) ob - (u8 *) out;
    out->f20 = in->fC;
    out->f1C = 0;
    out->f30 = 0;
    for (i = 0; i < out->n6; i++) {
        oa->f0 = ia->f0 & 0xFFFE;
        func_80034D4C(oa->f4, ia->f2, 6);
        oa->fC = ia->f8;
        oa->fE = ia->fC;
        oa->f10 = ia->f10;
        oa->f14 = ia->f14;
        oa->f16 = ia->f16;
        oa->f18 = ia->f18;
        oa->f1C = ia->f1C;
        oa->f2 = ia->f28;
        oa->fA = 0;
        oa->f12 = 0;
        oa->f2C = 0;
        v = ia->f20;
        if (v != 0) {
            v -= 0x24;
            v /= sizeof(InA_8003FD48);
            v *= sizeof(OutA_8003FD48);
            v += 0x174;
        }
        oa->f20 = v;
        v = ia->f24;
        if (v != 0) {
            v -= 0x24;
            v /= sizeof(InA_8003FD48);
            v *= sizeof(OutA_8003FD48);
            v += 0x174;
        }
        oa->f24 = v;
        oa++;
        ia++;
    }
    nlit = 1;
    ia -= out->n6;
    oa -= out->n6;
    for (i2 = 0; i2 < out->nA; i2++) {
        if (ib->f1A != 0) {
            ob->f6 = nlit++;
            ob->f7 = 0x7F - (ib->f1A >> 1);
        } else {
            ob->f6 = 0;
        }
        if (*(s32 *) &ib->f14 != 0 || ib->f18 != 0) {
            ob->f8 = ib->f14;
            ob->fA = ib->f16;
            ob->fC = ib->f18;
        } else {
            ob->f8 = 0x1000;
            ob->fA = 0;
            ob->fC = 0;
        }
        func_80034D4C(ob, ib->fC, 6);
        ob++;
        ib++;
    }
    v = (nlit - 1) * 16;
    oc = (OutC_8003FD48 *) ((u8 *) oc + v);
    oc0 = oc;
    out->off14 += v;
    out->nA += nlit - 1;
    for (i = 0; i < out->n8; i++) {
        t = D_8008251C[ic->f0];
        oc->type = t;
        {
            u8 *tb = D_8008A7D4;

            oc->size = tb[t];
        }
        oc->f0 = ic->f1;
        oc->fA = 0;
        oc->fB = 0;
        func_80034D4C(oc->f4, ic->f2, 6);
        for (k = 0; k < 4; k++) {
            v = ic->f8[k];
            if (v != 0) {
                v -= in->off18;
                v /= sizeof(InB_8003FD48);
                v *= sizeof(OutB_8003FD48);
                v += out->off18;
            }
            oc->f10[k] = v;
        }
        d = oc->d;
        switch (oc->type) {
        case 3:
            d[0] = *(u16 *) (q + 0xC);
            d[1] = *(u16 *) (q + 0x14);
            d[2] = *(u16 *) (q + 0x1C);
            d[3] = *(u16 *) (q + 0x24);
            d[4] = *(u16 *) (q + 0x16);
            q += 0x28;
            break;
        case 2:
            d[0] = *(u16 *) (q + 0xC);
            d[1] = *(u16 *) (q + 0x14);
            d[2] = *(u16 *) (q + 0x1C);
            d[3] = *(u16 *) (q + 0x16);
            q += 0x20;
            break;
        case 1:
            *(u32 *) d = *(u32 *) (q + 4);
            q += 0x18;
            break;
        case 0:
            *(u32 *) d = *(u32 *) (q + 4);
            q += 0x14;
            break;
        case 6:
            d[0] = *(u16 *) (q + 0xC);
            d[1] = *(u16 *) (q + 0x18);
            d[2] = *(u16 *) (q + 0x24);
            d[3] = *(u16 *) (q + 0x1A);
            q += 0x28;
            break;
        case 4:
            q += 0x1C;
            break;
        case 5:
            break;
        }
        ic++;
        oc = (OutC_8003FD48 *) ((u8 *) oc + oc->size);
    }
    end = oc;
    oc = oc0;
    for (i = 0; i < out->n6; i++) {
        v = ia->f2C;
        oc0 = oc;
        if (v != 0) {
            v -= in->off14;
            v /= sizeof(InC_8003FD48);
            for (k = v; k > 0; k--) {
                oc0 = (OutC_8003FD48 *) ((u8 *) oc0 + oc0->size);
            }
            v = (u8 *) oc0 - (u8 *) oc;
            v += out->off14;
        }
        oa->f28 = v;
        oa++;
        ia++;
    }
    out->fC = nlit - 1;
    out->f28 = size = (u8 *) end - (u8 *) out;
    func_80034C8C(out, size + out->fC * 16);
    return out;
}
