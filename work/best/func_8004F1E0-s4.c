#include "common.h"

extern u8 D_800B03C4[];
extern u8 D_800AFCA4[];

u8 *func_8004F1E0(u32 a0) {
    u32 *r = NULL;
    u32 i = a0 & 0xFF;
    u8 *e;
    u32 idx;

    if (i < 0x40) {
        e = D_800B03C4 + i * 2;
        if (e[0] != 0) {
            idx = e[1];
            if (idx != 0xFF) {
                if (idx < 0x18) {
                    r = (s32) idx * 0x4C + (u16) D_800AFCA4;
                }
            }
        }
    }
    return (u8 *) r;
}
