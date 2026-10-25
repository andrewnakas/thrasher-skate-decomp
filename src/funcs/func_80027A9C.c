#include "common.h"

extern s32 func_8001D080(void);
extern s32 func_80036A78(s32, s32, s32);
extern s32 func_80036B18(s32);
extern s32 func_80034CF0(s32);
extern s32 func_80036BF4(s32, s32);

s32 func_80027A9C(s32 a0, s32 *a1) {
    s32 q;
    s32 r;

    if (func_80036A78(func_8001D080(), a0, 0)) {
        return 0;
    }
    q = func_80036B18(func_8001D080());
    r = func_80034CF0(q);
    if (!r) {
        return 0;
    }
    if (a1) {
        *a1 = q;
    }
    if (func_80036BF4(func_8001D080(), r)) {
        return 0;
    }
    return r;
}
