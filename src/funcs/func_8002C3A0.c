#include "common.h"

extern u8 *D_8008AFA8;

u8 *func_8002C3A0(s32 i) {
    if (D_8008AFA8 == 0) {
        return 0;
    }
    return D_8008AFA8 + i * 8;
}
