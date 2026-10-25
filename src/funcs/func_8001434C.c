#include "common.h"

extern u8 *D_80089F48;
extern s32 D_80089F44;

void func_800143BC(u8 *);

void func_8001434C(void) {
    u8 *p;
    s32 i;

    if (D_80089F48 == NULL) {
        return;
    }
    p = D_80089F48;
    for (i = 0; i < D_80089F44; i++) {
        if (*(s32 *)(p + 4) & 1) {
            func_800143BC(p);
        }
        p += 0x1C0;
    }
}
