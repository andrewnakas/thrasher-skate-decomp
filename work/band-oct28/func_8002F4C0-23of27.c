#include "common.h"

extern s32 func_80032C54(s32, s32);

s32 func_8002F4C0(s32 a0, s32 a1, u8 *a2) {
    if (a2 == 0) {
        goto fail;
    }
    if (*(s32 *) (a2 + 4) != 0) {
        return func_80032C54(-(*(s32 *) (a2 + 0) * a0 + *(s32 *) (a2 + 8) * a1
            + *(s32 *) (a2 + 0xC)), *(s32 *) (a2 + 4));
    }
fail:
    return 0x27100000;
}
