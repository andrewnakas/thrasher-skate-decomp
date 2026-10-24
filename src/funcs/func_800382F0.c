#include "common.h"

extern u32 func_8001659C(u8 *);
extern void func_8001651C(u8 *, u8 *);
extern void func_80037B4C(u8 *, u8 *);

u8 *func_800382F0(u8 *a0, u8 *a1) {
    if (func_8001659C(a0) < 9) {
        func_80037B4C(a0, a1);
    } else {
        func_8001651C(a1, a0);
    }
    return a1;
}
