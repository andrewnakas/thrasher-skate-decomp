#include "common.h"

extern s32 func_80047B28(s32, s32, s32);
extern s32 func_80047C94(s32, s32, s32);
extern s32 func_80047EF0(s32, s32, s32);
extern s32 func_8004813C(s32);
extern s8 D_8008A8B4;

s32 func_8004836C(s32 a0, s32 a1, s32 a2) {
    s32 ret = 1;
    s32 r = func_8004813C(a0);

    if (r != 0) {
        /* case order from jtbl_80010654 (1..5) */
        switch (r) {
            case 1:
                D_8008A8B4 = 0;
                ret = func_80047C94(a0, a1, a2);
                break;
            case 5:
                D_8008A8B4 = 1;
                ret = func_80047C94(a0, a1, a2);
                break;
            case 2:
                ret = func_80047B28(a0, a1, a2);
                break;
            case 3:
                break;
            case 4:
                ret = func_80047EF0(a0, a1, a2);
                break;
        }
    }
    return ret;
}
