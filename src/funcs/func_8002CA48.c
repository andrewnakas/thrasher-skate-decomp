#include "common.h"

u8 *func_80034C20(s32 size);
void func_8002C8B8(u8 *p);

u8 *func_8002CA48(u8 *a0, u32 *a1) {
    u8 *p = a0;

    if (p == 0) {
        p = func_80034C20(0xC);
    }
    memset(p, 0, 0xC);
    *(u32 *) p = 0xC;
    func_8002C8B8(p);
    *a1 = *(u32 *) p;
    return p;
}
