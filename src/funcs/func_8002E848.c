#include "common.h"

extern void func_80033428(s32 *vec, s16 a, s32 b);

void func_8002E848(u32 *a, u32 *b, s32 c) {
    s32 buf[3];

    buf[0] = *a;
    buf[1] = 0;
    buf[2] = *b;
    func_80033428(buf, (s16) c, c);
    *a = buf[0];
    *b = buf[2];
}
