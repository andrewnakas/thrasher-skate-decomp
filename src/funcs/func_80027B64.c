#include "common.h"

extern u16 D_8008AFA4;
void func_8003C768(s32 a0, s32 a1);
void func_8003C220(s32 a0);

void func_80027B64(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 v = a2 & 0xFFFF;

    D_8008AFA4 = a2;
    func_8003C768(v, a3 & 0xFFFF);
    func_8003C220(v);
}
