/* cflags: -O3 */
#include "common.h"

extern u32 D_80082944[3];
extern volatile u32 D_80082948[3];
extern char D_80010848[];
extern char D_80010870[];

u8 *func_8004F1E0(u32);
void SpuSetVoiceAttr(void *);

s32 func_8004E6CC(u32 a0, u32 a1) {
    u8 *p;
    u8 *q;
    u32 t;
    u32 l;
    u32 r;
    s32 f;

    if (D_80082944[0] == 0) {
        printf(D_80010848, D_80010870, 0x27E);
        exit(1);
    }
    D_80082948[0]++;
    p = func_8004F1E0(a0 & 0xFF);
    if (p != 0) {
        q = *(u8 **) (p + 8);
        t = (a1 & 0xFF) * q[4];
        p[2] = t >> 7;
        f = (s8) p[3];
        if (f > 0) {
            r = p[2];
            l = ((r * (0x7F - f)) >> 7) & 0xFF;
        } else if (f < 0) {
            l = p[2];
            r = ((l * (0x7F + f)) >> 7) & 0xFF;
        } else {
            l = p[2];
            r = l;
        }
        p += 0xC;
        *(u32 *) (p + 4) = 3;
        *(u16 *) (p + 8) = l << 7;
        *(u16 *) (p + 0xA) = r << 7;
        SpuSetVoiceAttr(p);
    }
    D_80082948[0]--;
    return 0;
}
