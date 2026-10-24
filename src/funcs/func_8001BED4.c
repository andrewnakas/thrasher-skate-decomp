#include "common.h"

extern u8 D_8006E764[];
extern u8 D_8006E83C[0x10];

s32 func_80016904(s32 *);

s32 func_8001BED4(s32 arg0) {
    u8 *base = D_8006E764;
    u8 *e = base + arg0 * 0x18;

    if (*(s32 *)(e + 0xC) == 0) {
        return 1;
    }
    *(s32 *)D_8006E83C = (s32)e;
    func_80016904((s32 *)D_8006E83C);
    return 0;
}
