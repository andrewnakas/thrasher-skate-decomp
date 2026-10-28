#include "common.h"

typedef union {
    long long ll;
    u32 w[2];
} Wide_80032C28;

u32 func_80032C28(s32 a, s32 b) {
    Wide_80032C28 u;

    u.ll = (long long) a * b;
    return (u.w[0] >> 16) | (u.w[1] << 16);
}
