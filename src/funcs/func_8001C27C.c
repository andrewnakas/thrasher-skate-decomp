#include "common.h"

s32 func_8001CAA8(void);
s32 func_8001C62C(void);

s32 func_8001C27C(void) {
    if (func_8001CAA8() != 0) {
        return 1;
    }
    return func_8001C62C() != 0;
}
