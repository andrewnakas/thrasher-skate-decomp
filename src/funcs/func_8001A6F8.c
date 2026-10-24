#include "common.h"

extern s32 D_8008ADCC;
extern u8 D_80092654[];

u8 *func_8001A6F8(s32 *arg0) {
    arg0[0] = D_8008ADCC;
    return D_80092654;
}
