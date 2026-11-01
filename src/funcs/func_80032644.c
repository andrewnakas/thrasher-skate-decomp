#include "common.h"

extern s32 func_8005D2C8(s32 a0);
extern s32 func_8005D2D8(s32 *a0);

s32 func_80032644(s32 a0, s32 *a1, s32 *a2, s32 *a3, s32 *a4)
{
    s32 v;

    if (func_8005D2C8(a0) != 0) {
        return 1;
    }
    if (func_8005D2D8(a1) == 0) {
        return 1;
    }
    v = *a1 & 7;
    if (v == 1) {
        if (a2 != NULL) {
            *a2 = 2;
        }
        if (a4 != NULL) {
            *a4 = 0x7F;
        }
        if (a3 != NULL) {
            *a3 = 1;
        }
        return 0;
    }
    if (v == 0) {
        if (a2 != NULL) {
            *a2 = 4;
        }
        if (a4 != NULL) {
            *a4 = 0xFF;
        }
        if (a3 != NULL) {
            *a3 = 0;
        }
        return 0;
    }
    if (a2 != NULL) {
        *a2 = 1;
    }
    if (a4 != NULL) {
        *a4 = 0x3F;
    }
    if (a3 != NULL) {
        *a3 = 2;
    }
    return 0;
}
