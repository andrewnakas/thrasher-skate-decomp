#include "common.h"

extern u16 D_8008AE14;
extern u16 D_8008AE16;

u8 *func_8002C3A0(s32);
void func_80047804(u32, u32);
void func_8001B980(u8 *, s32);
void func_8001B760(u8 *, s32);

void func_8001B684(void) {
    u8 *p;
    s32 i;
    u32 k;
    u16 id;

    for (i = 0; i < D_8008AE16; i++) {
        p = func_8002C3A0(i);
        id = (u16)(D_8008AE14 + i);
        func_80047804(id, (*(u32 *)p >> 17) & 3);
        k = *(u8 *)p >> 4;
        switch (k) {
        case 0:
        case 1:
            break;
        case 2:
            func_8001B980(p, i);
            break;
        case 3:
        case 4:
            if (((*(u32 *)p >> 13) & 0xF) == 0) {
                func_8001B760(p, i);
            }
            break;
        }
    }
}
