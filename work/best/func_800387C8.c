#include "common.h"

extern u32 D_8008A790[];
extern u32 D_8008A788[];
extern u32 D_8008B33C[];
extern u32 D_8008B3A0[4];
extern u32 D_8008B3A8[4];
extern u32 D_8008B3AC[4];
extern u32 D_8008B3B0[4];
extern u32 D_8008B1A0;

s32 func_80059FFC(u32 *, s32);
void func_8003A054(s32);

void func_800387C8(void) {
    u32 i;
    u32 p;

    p = D_8008A790[D_8008B3A8[0]];
    D_8008B3A0[0] = p;
    D_8008B1A0 = p + 0x7FC;
    func_80059FFC((u32 *) p, 0x200);
    i = D_8008B3A8[0];
    D_8008B3AC[0] = D_8008A788[i];
    D_8008B3B0[0] = D_8008B33C[i];
    func_8003A054(0);
}
