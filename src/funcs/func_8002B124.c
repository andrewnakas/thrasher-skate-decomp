#include "common.h"

void func_8002B060(s32 *);

void func_8002B124(s32 *p) {
    s32 *n = (s32 *) p[2];

    while (n != 0) {
        func_8002B060(n);
        n = (s32 *) n[0x10];
    }
}
