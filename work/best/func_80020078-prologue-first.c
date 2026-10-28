#include "common.h"

typedef struct {
    u32 count;
    u16 f04;
    u8 pad6[2];
    u8 *tab;
    u8 *f0C;
} Desc_80020078;

extern u8 D_8006F818[];
extern s32 func_80045D78();

s32 func_80020078(u32 a0, s16 a1, s16 a2, Desc_80020078 *d, u16 p5, u8 p6)
{
    u32 found = 0;
    s32 i = found;
    u32 idx = found;
    u32 n;
    u8 key;
    u8 *p;

    n = d->count;
    if (n != 0) {
        key = a0 & 0xFF;
        p = d->tab;
        for (i = 0; i < n; i++, p += 16) {
            if (key == p[0]) {
                found = 1;
                idx = i;
            }
            if (found != 0) {
                break;
            }
        }
    }
    *(u16 *) (D_8006F818 + 0x2) = 0;
    *(u16 *) (D_8006F818 + 0x4) = 0;
    *(u16 *) (D_8006F818 + 0x6) = *(u16 *) d->f0C;
    *(u16 *) (D_8006F818 + 0x8) = *(u16 *) (d->tab + idx * 16 + 4);
    *(u16 *) (D_8006F818 + 0xA) = *(u16 *) (d->tab + idx * 16 + 8);
    *(u16 *) (D_8006F818 + 0xC) = *(u16 *) (d->tab + idx * 16 + 0xC);
    *(u16 *) (D_8006F818 + 0xE) = d->f04;
    *(u16 *) (D_8006F818 + 0x10) = p5;
    func_80045D78((s16) a1, (s16) a2, p6 & 0xFF, p6 & 0xFF, D_8006F818);
    return (u16) (*(u32 *) (d->tab + idx * 16 + 0xC) * (u8) p6);
}
