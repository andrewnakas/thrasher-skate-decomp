#include "common.h"

s32 func_80015E8C(s32);

s32 func_80019518(s32 *p) {
    s32 r = func_80015E8C(p[2]);

    return r + p[3];
}
