#include "common.h"

extern u32 D_800A974C[];
extern void func_80042330(void);

void func_80042300(void) {
    u32 fn = (u32) func_80042330;
    s32 i = 9;
    u32 *p = D_800A974C;

    p += 9;
    while (i >= 0) {
        *p = fn;
        p--;
        i--;
    }
}
