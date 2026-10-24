#include "common.h"

void func_8005689C(u8 *p) {
    s32 i;
    s32 v;

    v = -1;
    for (i = 2; i >= 0; i--) {
        *(s32 *) (p + 0x44 + i * 4) = v;
    }
}
