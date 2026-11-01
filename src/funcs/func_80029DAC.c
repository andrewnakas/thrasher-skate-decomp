#include "common.h"

typedef struct Hdr_80029DAC {
    u8 pad0[0xA];
    u8 unkA;
    u8 padB;
    s32 unkC[3];
    s32 unk18;
    u8 pad1C[2];
    u16 type;
    u8 pad20[4];
    s32 unk24;
} Hdr_80029DAC;

typedef struct Slot_80029DAC {
    u8 pad0[0x10];
    s32 sq;
    s32 val;
} Slot_80029DAC;

typedef struct Out_80029DAC {
    s32 unk0;
    u8 pad4[0x18];
    u16 unk1C;
    u8 pad1E[0x12];
    s32 unk30;
    u8 pad34[0x14];
    Slot_80029DAC slots[3];
    u8 pad90[4];
    s32 unk94;
    s32 unk98;
} Out_80029DAC;

extern s32 D_8008AFD4;
extern s32 D_8008A324;
extern u8 *D_8008B00C;

extern u8 *func_8001D428(s32, s32);
extern Hdr_80029DAC *func_8001D5B0(u8 *, u32, s32);
extern s32 func_80034C14(void);
extern void func_8001D4D4(u8 *);
extern void func_80034D30(u8 *);
extern void memset(void *, s32, s32);
extern void func_80027BA0(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_80027CD4(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_800280BC(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_800299F8(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_800282E4(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_80028CF4(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_800290CC(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_8002921C(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_80029320(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_80028498(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_80029664(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_80029488(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_800294FC(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_8002980C(u8 *, Out_80029DAC *, Hdr_80029DAC *);
extern void func_80029420(u8 *, Out_80029DAC *, Hdr_80029DAC *);

Out_80029DAC *func_80029DAC(Out_80029DAC *out, s32 file) {
    u8 *h;
    Hdr_80029DAC *hdr;
    s32 t0;
    s32 i;
    s32 v;

    h = func_8001D428(file, 0);
    memset(out, 0, 0x9C);
    hdr = func_8001D5B0(h, 0x5053425A, 1);
    t0 = func_80034C14();
    switch (hdr->type) {
    case 0:
    case 2:
        out->unk94 = 0;
        out->unk98 = 0;
        out->unk0 = hdr->unk18;
        out->unk30 = hdr->unk24;
        out->unk1C = hdr->unkA;
        for (i = 2; i >= 0; i--) {
            if (hdr->unkC[i] != 0) {
                out->slots[i].sq = hdr->unkC[i] * hdr->unkC[i];
                out->slots[i].val = hdr->unkC[i];
            } else {
                out->slots[i].sq = (&D_8008A324)[i - 2] * (&D_8008A324)[i - 2];
                out->slots[i].val = (&D_8008A324)[i - 2];
            }
        }
        func_80027BA0(h, out, hdr);
        func_80027CD4(h, out, hdr);
        func_800280BC(h, out, hdr);
        func_800299F8(h, out, hdr);
        func_800282E4(h, out, hdr);
        func_80028CF4(h, out, hdr);
        func_800290CC(h, out, hdr);
        func_8002921C(h, out, hdr);
        func_80029320(h, out, hdr);
        for (i = 2; i >= 0; i--) {
            if ((&D_8008B00C)[i - 2] != 0) {
                func_80034D30((&D_8008B00C)[i - 2]);
                (&D_8008B00C)[i - 2] = 0;
            }
        }
        break;
    case 5:
        func_80028498(h, out, hdr);
        func_80029664(h, out, hdr);
        func_80029488(h, out, hdr);
        func_800294FC(h, out, hdr);
        func_8002980C(h, out, hdr);
        break;
    case 1:
        func_80029420(h, out, hdr);
        break;
    }
    D_8008AFD4 += func_80034C14() - t0;
    func_8001D4D4(h);
    return out;
}
