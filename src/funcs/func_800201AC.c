#include "common.h"

s32 strlen(const char *);
u16 func_80020078(u8 c, s16 x, s16 y, s32 a3, u16 a4, u8 a5);

void func_800201AC(u8 *str, s16 x, s16 y, s32 a3, u16 a4, u8 a5) {
    u16 len;
    u16 i;
    s16 cx;

    len = strlen(str);
    cx = x;
    for (i = 0; i < len; i++) {
        cx += (s16) func_80020078(str[i], cx, y, a3, a4, a5) + 1;
    }
}
