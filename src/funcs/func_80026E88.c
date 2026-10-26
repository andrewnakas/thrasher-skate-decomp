#include "common.h"

void func_80026E88(s32 *src, s32 *dst) {
    s32 i;

    for (i = 2; i >= 0; i--) {
        dst[i] = src[i * 3];
        dst[i + 3] = src[i * 3 + 1];
        dst[i + 6] = src[i * 3 + 2];
    }
}
