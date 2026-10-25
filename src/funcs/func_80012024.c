#include "common.h"

extern s32 D_80089F44;
extern s32 D_80089F48;

s32 func_80012024(void) {
    u8 *p = (u8 *) D_80089F48;
    u8 *end = p + D_80089F44 * 0x1C0;

    while (p < end) {
        if (*(s32 *) p == 0) {
            return (s32) p;
        }
        p += 0x1C0;
    }
    return 0;
}
