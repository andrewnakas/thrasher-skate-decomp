#include "common.h"

s32 func_80012024(s32);
s32 func_800120B8(s32, s32);

s32 func_80012078(s32 p) {
    s32 t = func_80012024(p);

    if (t == 0) {
        return 0;
    }
    return func_800120B8(p, t);
}
