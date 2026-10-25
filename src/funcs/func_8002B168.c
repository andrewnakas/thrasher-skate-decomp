#include "common.h"

extern u8 D_800A1C90[0x168];

s32 func_8002B168(void) {
    memset(D_800A1C90, 0, 0x168);
    return 0;
}
