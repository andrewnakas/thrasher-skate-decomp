#include "common.h"

s32 func_8002BAC0(u16);

s32 func_8002BAFC(u16 idx) {
    s32 p = func_8002BAC0(idx);

    return (*(u32 *) p >> 2) & 3;
}
