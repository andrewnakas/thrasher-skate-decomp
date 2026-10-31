#include "common.h"

extern u8 D_80089F74[];

s32 func_800162D0(void *);
s32 sprintf(u8 *, u8 *, void *);

void func_8001628C(void *arg0) {
    u8 buf[0x100];

    if (*(s32 *) ((u8 *) arg0 + 0xC) != func_800162D0(arg0)) {
        sprintf(buf, D_80089F74, arg0);
    }
}
