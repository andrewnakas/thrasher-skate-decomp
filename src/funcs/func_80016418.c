#include "common.h"

extern char D_80089F94[];
extern u8 D_80092614[];

s32 strncmp(const char *, const char *, s32);

s32 func_80016418(u8 *arg0) {
    if (strncmp((char *)arg0, D_80089F94, 4) != 0) {
        return 1;
    }
    *(u8 **)(D_80092614 + (*(u16 *)(arg0 + 4) >> 12) * 4) = arg0;
    return 0;
}
