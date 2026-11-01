#include "common.h"

extern u8 D_800827F4[];

void func_80042338(u8 *a0) {
    s16 base[4];
    u8 *rec;
    u8 *src;
    s16 *p;
    s32 i;
    s32 last;
    s32 id;
    s16 *b;

    p = (s16 *) (a0 + 0x34);
    rec = D_800827F4 + *(u16 *) (a0 + 4) * 0x30;
    memset(base, 0, 8);
    last = -1;
    i = 0;
    src = *(u8 **) (rec + 4);
    if (*(u16 *) (rec + 0xA) != 0) {
        do {
            id = src[0];
            b = base;
            p[0] = base[0] + (s8) src[1];
            p[1] = b[1] + (s8) src[2];
            p[2] = b[2] + (s8) src[3];
            if (last == id) {
                p[-1] = 1;
            }
            p[3] = 0;
            last = id;
            p += 4;
            src += 4;
            i++;
        } while (i < *(u16 *) (rec + 0xA));
    }
}
