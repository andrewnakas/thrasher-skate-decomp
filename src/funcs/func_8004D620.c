#include "common.h"

typedef struct {
    u16 flags;
    u8 unk2;
    u8 pad3;
    s32 unk4;
    u8 pad8[0x10];
    s32 unk18;
    u8 pad1C[2];
    s16 unk1E;
    u8 pad20;
    u8 unk21;
    u8 pad22[2];
} Ent_8004D620;

extern s32 D_8008A960;
extern s32 D_8008A964;
extern char D_80010820[];
extern char D_8008A96C[];
extern Ent_8004D620 D_800AFA64[];
s32 func_8004D8DC(s32, s16 *);

s32 func_8004D620(s32 val, s16 *src, u16 flags) {
    Ent_8004D620 *e;
    u8 *base;
    u8 *p;
    u32 i;
    u16 f;
    s32 sum;

    if (D_8008A960 == 0) {
        printf(D_80010820, D_8008A96C, 0xEF);
        exit(1);
    }
    e = 0;
    i = D_8008A964;
    f = (flags & 0xBFFF) | 0x8000;
    base = (u8 *) D_800AFA64;
    p = base + i * 0x24;
    do {
        if (!(*(u16 *) p & 0x8000)) {
            e = (Ent_8004D620 *) p;
            e->flags = f;
            D_8008A964 = i + 1;
            if (i + 1 == 0x10) {
                D_8008A964 = 0;
            }
            break;
        }
        i++;
        p += 0x24;
        if (i == 0x10) {
            p = base;
            i = 0;
        }
    } while (i == D_8008A964);
    if (e != 0) {
        e->unk2 = 0xFF;
        e->unk4 = val;
        e->unk21 = 0x7F;
        e->unk1E = 0;
        sum = src[1] * src[1] + src[3] * src[3] + src[5] * src[5];
        e->unk18 = sum;
        func_8004D8DC(i & 0xFFFF, src);
        return i & 0xFFFF;
    }
    return 0xFFFF;
}
