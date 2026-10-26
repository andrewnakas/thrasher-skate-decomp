#include "common.h"

s32 func_8002C77C(s32, s16, s16, s16);

s32 func_8002C818(s32 arg0, s32 *arg1) {
    s32 n;
    s32 *v;

    n = (*(u16 *) arg1 & 1) ? 4 : 3;
    n--;
    for (; n != -1; n--) {
        v = (s32 *) arg1[n + 7];
        if (func_8002C77C(arg0, *(s16 *) v, *(s16 *) ((u8 *) v + 2), *(s16 *) ((u8 *) v + 4)) == 0) {
            return 0;
        }
    }
    return 1;
}
