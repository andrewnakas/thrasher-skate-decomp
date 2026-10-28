#include "common.h"

extern u8 D_800B0F6C[];
extern u8 D_8008A934[0x40];
extern u8 D_8008A998[0x40];
extern s32 D_8008A9C8;

extern void func_8005109C(u8 *p);
extern s32 func_80066FE4(void);
extern void VSync(s32 a0);
extern void func_80066EC0(void);
extern void func_800670AC(s32 a0);
extern void func_80067088(s32 a0);
extern void func_80067064(s32 a0);
extern void SpuFree(s32 a0);
extern void func_8004E30C(s32 a0);
extern void SpuSetKey(s32 a0, u32 a1);

s32 func_800504D4(void) {
    u8 *p;
    u8 *q;
    u8 *r;
    u32 i;
    u32 j;
    s32 n;
    u32 key;

    p = D_800B0F6C;
    for (i = 0; i < 4; i++, p += 0x60) {
        if (*(u16 *) p & 0x8000) {
            func_8005109C(p);
        }
    }

    n = *(s32 *) D_8008A934 * 10;
    do {
        if (func_80066FE4() == 3) {
            break;
        }
        if (--n == 0) {
            break;
        }
        VSync(0);
    } while (1);

    func_80066EC0();
    func_800670AC(0);
    func_80067088(0);
    func_80067064(0);

    key = 0;
    q = D_800B0F6C;
    r = D_800B0F6C;
    do {
        for (j = 0; j <= ((*(u16 *) r >> 8) & 1); j++) {
            p = r + j * 0xC;
            if (*(s32 *) (p + 0x50) != -1) {
                SpuFree(*(s32 *) (p + 0x50));
                *(s32 *) (p + 0x50) = -1;
                *(s32 *) D_8008A998 += 0x1000;
                func_8004E30C(*(u8 *) (r + 0x48));
                key |= 1 << *(s32 *) (p + 0x4C);
            }
        }
        r += 0x60;
        q += 0x6C;
    } while (q < D_800B0F6C + 0x1B0);

    SpuSetKey(0, key);
    D_8008A9C8 = 0;
    return 0;
}
