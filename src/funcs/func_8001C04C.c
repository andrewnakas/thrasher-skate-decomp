#include "common.h"

s32 func_8002CA48(s32, s32 *);

s32 func_8001C04C(s32 a0, s32 *out) {
    s32 v;
    s32 r = func_8002CA48(a0, &v);

    if (out != 0) {
        *out = v;
    }
    return r;
}
