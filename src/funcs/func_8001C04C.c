#include "common.h"

s32 func_8002CA48(s32, s32 *);

s32 func_8001C04C(s32 arg0, s32 *arg1) {
    s32 tmp;
    s32 r;

    r = func_8002CA48(arg0, &tmp);
    if (arg1 != 0) {
        *arg1 = tmp;
    }
    return r;
}
