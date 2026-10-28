#include "common.h"

extern u8 D_800A4F00[];

s32 func_8002BA64(u16 id) {
    u8 *base = D_800A4F00;
    s32 i = *(s32 *) (base + 0x5C);
    u32 want = (u32) id & 0xFFFF;
    u8 *table;
    u8 *p;

    i--;
    if (i >= 0) {
        table = *(u8 **) (base + 0x58);
        p = (u8 *) ((u32) i * 0x38 + (u32) table);
        do {
            if (*(u16 *) (p + 4) == want) {
                return i;
            }
            i--;
            p -= 0x38;
        } while (i >= 0);
    }
    return 0;
}
