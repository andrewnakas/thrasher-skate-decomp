#include "common.h"

extern s32 D_8008B354;
extern s32 D_8008B348;
extern u8 *D_8008B34C;
extern u32 D_8008B350;
extern u32 D_8008B364;

s32 func_80041538(u8 *a0) {
    u8 *h;
    u8 *rec;
    u32 x;
    u32 child;

    D_8008B354++;
    (&D_8008B364)[D_8008B354] = (u32) a0;
    if (D_8008B348 & 1) {
        h = D_8008B34C;
        x = (u32) a0 - *(u32 *) (h + 0x10);
        rec = *(u8 **) (h + 0x24) + (x / 26) * 16 + 0x10;
        *(u32 *) rec = (u32) a0;
        *(u16 *) (rec + 0x8) = *(u16 *) (a0 + 0xC);
        *(u16 *) (rec + 0xA) = *(u16 *) (a0 + 0xE);
        *(u16 *) (rec + 0xC) = *(u16 *) (a0 + 0x10);
        child = *(u32 *) (a0 + 0x20);
        D_8008B350 = (u32) h;
        D_8008B350 = (u32) rec;
        if (child != 0) {
            *(u8 *) (rec + 0xF) = (u8) (((u32) child - *(u32 *) (h + 0x10)) / 26 + 1);
        } else {
            *(u8 *) (rec + 0xF) = 0;
        }
        child = *(u32 *) (a0 + 0x24);
        if (child != 0) {
            *(u8 *) (rec + 0xE) = (u8) (((u32) child - *(u32 *) (h + 0x10)) / 26 + 1);
        } else {
            *(u8 *) (rec + 0xE) = 0;
        }
        D_8008B350 = (u32) (rec + 0x10);
    }

    child = *(u32 *) (a0 + 0x20);
    if (child != 0) {
        do {
            child = func_80041538((u8 *) child);
        } while (child != 0);
    }

    func_800416A8(a0);
    D_8008B354--;
    return *(s32 *) (a0 + 0x24);
}
