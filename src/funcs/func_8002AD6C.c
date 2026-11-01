#include "common.h"

typedef struct {
    u8 pad0[4];
    u8 *tab;            /* 0x04 */
    u8 pad8[0x44];
    s32 n;              /* 0x4C */
    u8 *p;              /* 0x50 */
} G_8002AD6C;

extern G_8002AD6C D_800A4F00;

void func_8002AD6C(void) {
    u8 *p;
    s32 i;
    s32 j;
    s32 k;
    u8 *v;
    u8 *m;
    u8 *t;

    p = D_800A4F00.p;
    for (i = 0; i < D_800A4F00.n; p += 0x20, i++) {
        j = p[5] - 1;
        if (j < 0) {
            continue;
        }
        do {
            v = ((u8 **) (p + 0x10))[j];
            m = *(u8 **) (v + 4);
            t = D_800A4F00.tab + *(u8 *) v * 156;
            for (k = *(u8 *) (v + 1); k > 0; k--) {
                s32 o = *(u8 *) (m + 4) * 12;

                *(u32 *) m = *(u32 *) (*(u8 **) (t + 0x48) + o + 8);
                m += 8;
            }
            j--;
        } while (j >= 0);
    }
}
