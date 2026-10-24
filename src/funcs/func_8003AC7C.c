#include "common.h"

extern s32 D_8008B1F4;
extern u8 *D_8008B208;
extern u8 D_800A9444[];
extern u32 func_8003AB00(void *p);
extern u32 func_8003AB20(void *p);
extern s32 func_8003AB44(void *p);
extern void func_8005A104(u32 *p);

void func_8003AC7C(void) {
    u8 *p;
    u8 *lim;
    u32 v;
    s32 n;

    p = D_8008B208;
    if (D_8008B1F4 != 0) {
        p -= 0x14;
        if (p < D_800A9444) {
            return;
        }
        lim = D_800A9444;
        do {
            if ((*(u16 *) p & 1) == 0) {
                v = func_8003AB00(p);
                n = func_8003AB44(p);
                func_8005A104(&((u32 *) v)[n - 1]);
            }
            p -= 0x14;
        } while (p >= lim);
    } else {
        p -= 0x14;
        if (p < D_800A9444) {
            return;
        }
        lim = D_800A9444;
        do {
            if ((*(u16 *) p & 1) == 0) {
                v = func_8003AB20(p);
                n = func_8003AB44(p);
                func_8005A104(&((u32 *) v)[n - 1]);
            }
            p -= 0x14;
        } while (p >= lim);
    }
}
