#include "common.h"

typedef struct {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
    u8 pad4[4];
    s32 data;
    u8 padC[2];
    u16 id;
} Src_4ADA4;

typedef struct {
    u16 flags;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 pad7;
    Src_4ADA4 *src;
    u8 padC[0x10];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[4];
    u32 unk30;
    u32 unk34;
    s32 unk38;
    u8 pad3C[8];
    u16 unk44;
    u8 pad46[2];
} Voice_4ADA4;

s32 func_8004FD98(u16, u8);
s32 func_8005011C(u16, u8);
extern s32 D_8008A938;
/* D_8008A934 read with an unsplit lui/lw: spelled as a neighbour minus an offset */
extern s32 D_8008A93C[2];
#define D_8008A934 (D_8008A93C[-2])
extern s32 D_8008B3FC;
extern Voice_4ADA4 *D_800AEA24[];
extern Voice_4ADA4 D_800AEAA4[];

s32 func_8004ADA4(Src_4ADA4 *src, u16 flags) {
    Voice_4ADA4 *p;
    Voice_4ADA4 *v;
    Voice_4ADA4 *base;
    s32 i;
    Src_4ADA4 *s;
    u32 rate;
    u32 q;
    s32 d;
    u8 a;

    s = src;
    i = D_8008B3FC;
    base = D_800AEAA4;
    p = &base[i];
    D_8008A938++;
    do {
        if (!(p->flags & 0x8000)) {
            v = p;
            v->flags = 0x8000;
            D_8008B3FC = i + 1;
            if (i + 1 == 0x20) {
                D_8008B3FC = 0;
            }
            break;
        }
        i++;
        p++;
        if (i == 0x20) {
            p = base;
            i = 0;
        }
        v = NULL;
    } while (i != D_8008B3FC);
    if (v != NULL) {
        v->unk2 = 0;
        rate = D_8008A934;
        q = 0x3E8000 / rate;
        v->flags |= flags & 0xFFFC;
        d = s->data;
        v->unk3 = 0x7F;
        v->unk38 = 0;
        v->unk28 = v->unk24 = d + 4;
        v->unk34 = (rate << 12) / 1000;
        v->unk30 = q;
        a = s->a;
        v->unk5 = 0x7F;
        v->unk4 = a;
        a = s->b;
        v->src = src;
        v->unk6 = a;
        if (s->c != 0xFF) {
            v->unk1C = func_8004FD98(v->unk44, s->c);
        } else {
            v->unk1C = 0;
        }
        if (s->d != 0xFF) {
            v->unk20 = func_8005011C(v->unk44, s->d);
        } else {
            v->unk20 = 0;
        }
        v->unk44 = s->id;
        D_800AEA24[i] = v;
        D_8008A938--;
        return (u8) i;
    }
    D_8008A938--;
    return 0xFF;
}
