#include "common.h"

void func_800290CC(s32 a0, u8 *a1, u8 *a2) {
    u8 *rec;
    u8 *p;
    u8 *out;
    s32 i;

    if ((*(u32 *) (a2 + 0x18) & 0x2000000) == 0) {
        return;
    }

    rec = (u8 *) func_8001D5B0(a0, 0x4554494C, 1);
    *(u16 *) (a1 + 0x20) = *(u16 *) (rec + 0xA);
    out = (u8 *) func_80034C20(*(u16 *) (rec + 0xA) << 5);
    *(u32 *) (a1 + 0x10) = (u32) out;

    i = *(u16 *) (rec + 0xA) - 1;
    if (i < 0) {
        return;
    }
    p = rec + 0x1E;
    do {
        *(u16 *) (out + 0) = *(u16 *) (p - 0x12);
        *(u32 *) (out + 8) = *(s16 *) (p - 0x10) << 16;
        *(u32 *) (out + 0xC) = *(s16 *) (p - 0xE) << 16;
        *(u32 *) (out + 0x10) = *(s16 *) (p - 0xC) << 16;
        *(u32 *) (out + 0x14) = *(s16 *) (p - 0xA) << 16;
        *(u32 *) (out + 0x18) = *(s16 *) (p - 8) << 16;
        *(u32 *) (out + 0x1C) = *(s16 *) (p - 6) << 16;
        *(u16 *) (out + 2) = *(u16 *) (p - 4);
        *(u16 *) (out + 4) = *(u16 *) (p - 2);
        *(u16 *) (out + 6) = *(u16 *) (p + 0);
        func_80049BF4(out + 8, out + 0x14, *(s16 *) (out + 2), *(s16 *) (out + 4), (s16) *(u16 *) (p + 0));
        p += 0x14;
        out += 0x20;
        i--;
    } while (i >= 0);
}
