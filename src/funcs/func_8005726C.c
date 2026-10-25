#include "common.h"

extern u8 D_8008ABF0;

void func_8005726C(s32 unused, u32 mode) {
    if (mode == 0) {
        return;
    }
    switch (mode) {
    case 1:
    case 2:
        D_8008ABF0 = mode;
        break;
    case 3:
        D_8008ABF0 = 8;
        break;
    }
}
