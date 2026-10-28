#include "common.h"

extern u8 D_800A4F00[];

void func_8002AC14(u8 *s, u32 rgb) {
    s32 i;
    s32 j;
    s32 cr;
    s32 cg;
    s32 cb;
    u8 *rec;
    u8 *tbl;
    u8 *out;
    u8 *base;
    s32 n;
    s32 scale;
    s32 a;

    i = (s32) s[5] - 1;
    if (i < 0) {
        return;
    }
    cr = rgb & 0xFF;
    cg = (rgb >> 8) & 0xFF;
    cb = (rgb >> 16) & 0xFF;
    for (; i >= 0; i--) {
        rec = *(u8 **) (s + 0x10 + i * 4);
        tbl = *(u8 **) (rec + 4);
        n = rec[1];
        base = (u8 *) ((u32) *(u8 **) (D_800A4F00 + 4) + rec[0] * 0x9C);
        for (j = n; j > 0; j--) {
            out = (u8 *) ((u32) *(u8 **) (base + 0x48) + tbl[4] * 0xC);
            scale = tbl[5] << 9;
            a = (((cr - 0x80) * scale) >> 16) + tbl[0];
            if (a >= 0x100) {
                a = 0xFF;
            }
            if (a < 0) {
                a = 0;
            }
            out[8] = a;
            a = (((cg - 0x80) * scale) >> 16) + tbl[1];
            if (a >= 0x100) {
                a = 0xFF;
            }
            if (a < 0) {
                a = 0;
            }
            out[9] = a;
            a = (((cb - 0x80) * scale) >> 16) + tbl[2];
            if (a >= 0x100) {
                a = 0xFF;
            }
            if (a < 0) {
                a = 0;
            }
            out[0xA] = a;
            out = (u8 *) ((u32) *(u8 **) (base + 0x48) + tbl[4] * 0xC);
            tbl += 8;
        }
    }
}
