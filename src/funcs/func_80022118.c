#include "common.h"

u8 *func_80034C20(s32 size);

void func_80022118(void) {
    u8 *p = func_80034C20(0x1330);

    *(s32 *) p = 0;
    *(s32 *) (p + 0xAF4) = 0;
    *(s32 *) (p + 0x1328) = 0;
    *(s32 *) (p + 0xFF8) = 0;
}
