#include "common.h"

extern u8 D_800A4F00[];

typedef struct {
    u8 pad0[0xA];
    u16 count;
    u8 recs[6];
} Src_800294FC;

typedef struct {
    u8 kind;
    u8 f1;
    u16 f2;
    u32 f4;
    u32 f8;
    u32 w[4];
} Out_800294FC;

extern u8 *func_8001D5B0(u32 a0, u32 tag, s32 a2);
extern u8 *func_80034C20(u32 size);

void func_800294FC(u32 a0, u32 a1, u8 *a2) {
    Src_800294FC *src;
    Out_800294FC *out;
    Out_800294FC *dp;
    u8 *sp;
    s32 i;
    s32 j;
    u32 v;

    if (!(*(u32 *) (a2 + 0x18) & 0x40000)) {
        return;
    }
    src = (Src_800294FC *) func_8001D5B0(a0, 0x53565053, 1);
    out = (Out_800294FC *) func_80034C20(src->count * 0x1C);
    *(u8 **) (D_800A4F00 + 0x54) = (u8 *) out;
    sp = (u8 *) src + 0xC;
    dp = out;
    for (i = src->count - 1; i >= 0; i--) {
        dp->f1 = sp[0];
        dp->f2 = *(u16 *) (sp + 2);
        v = *(u16 *) (sp + 4);
        if (v != 0) {
            dp->f4 = (u32) (*(u8 **) (D_800A4F00 + 0x54) + v * 0x1C - 0x1C);
        } else {
            dp->f4 = 0;
        }
        v = *(u16 *) (sp + 6);
        if (v != 0) {
            dp->f8 = (u32) (*(u8 **) (D_800A4F00 + 0x54) + v * 0x1C - 0x1C);
        } else {
            dp->f8 = 0;
        }
        dp->kind = (dp->f4 != 0 || dp->f8 != 0) ? 0x70 : 0x6C;
        for (j = 0; j < 4; j++) {
            dp->w[j] = *(u32 *) (sp + 8 + j * 4);
        }
        sp += 0x18;
        dp++;
    }
}
