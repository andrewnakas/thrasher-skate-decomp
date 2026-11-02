/* cflags: -mno-split-addresses */
#include "common.h"

typedef struct {
    s32 f00;
    u8 pad[0x3C];
} S_800843E8;

extern u32 D_8008A560;
extern s32 D_8008B0FC;
extern s32 D_8008B0F4;
extern S_800843E8 D_800843E8;

void func_80034BD8(u32);

s32 func_80034B98(void) {
    s32 t = D_800843E8.f00;

    D_8008A560 = -1;
    D_8008B0FC = t;
    func_80034BD8(t);
    D_8008B0F4 = 0x801FC000;
    return 0;
}

