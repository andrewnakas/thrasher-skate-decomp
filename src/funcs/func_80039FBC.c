#include "common.h"

extern void func_8003A160(s32 a0);

void func_80039FBC(u8 *a0) {
    func_8003A160(a0[0]);
    func_8003A160(*(u16 *) a0 >> 8);
}
