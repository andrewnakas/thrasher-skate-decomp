#include "common.h"

void func_8002B8CC(u8 *, s32 *);

void func_8002B870(u8 *p, s32 *src) {
    s32 t[3];

    t[0] = src[0] - (*(s16 *) (p + 0xA) << 16);
    t[1] = src[1] - (*(s16 *) (p + 0xC) << 16);
    t[2] = src[2] - (*(s16 *) (p + 0xE) << 16);
    func_8002B8CC(p, t);
}
