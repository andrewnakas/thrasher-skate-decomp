#include "common.h"

extern s32 D_8008B01C;

extern void func_8003B9F8(s32 a);
extern void func_80027880(u8 *p, s32 i);
extern s32 func_80049CCC(void);
extern void func_8004A094(void);
extern void func_8002AD6C(void);

s32 func_80027798(u8 *s) {
    s32 i;
    s32 q;
    s32 v;

    for (i = 0; i < D_8008B01C - 1; i++) {
        q = (i << 10) / (D_8008B01C - 1);
        v = q * 307;
        if (v < 0) {
            v += 0x3FF;
        }
        func_8003B9F8((v >> 10) + 0x66);
        func_80027880(s, i);
    }
    if (func_80049CCC() == 0) {
        func_8004A094();
    }
    func_8002AD6C();
    return 0;
}
