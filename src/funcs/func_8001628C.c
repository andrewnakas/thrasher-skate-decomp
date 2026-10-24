#include "common.h"

extern char D_80089F74[];

s32 func_800162D0(void *);
s32 sprintf(char *, const char *, ...);

void func_8001628C(u8 *arg0) {
    char buf[0x100];

    if (*(s32 *)(arg0 + 0xC) != func_800162D0(arg0)) {
        sprintf(buf, D_80089F74, arg0);
    }
}
