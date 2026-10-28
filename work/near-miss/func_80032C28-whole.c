#include "common.h"

u32 func_80032C28(s32 a0, s32 a1) {
    unsigned long long p = (unsigned long long) a0 * (unsigned long long) a1;

    return (u32) (p >> 16);
}
