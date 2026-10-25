#include "common.h"

s32 func_8002DAC4(u8 *p) {
    if (*(u32 *) p & 0x2400000) {
        return 0;
    }
    return (s32) (p + 0x84);
}
