#include "common.h"

void func_8002AEF4(s32 *);

void func_8002B0E0(s32 *p) {
    s32 *n = (s32 *) p[2];

    while (n != 0) {
        func_8002AEF4(n);
        n = (s32 *) n[0x10];
    }
}
