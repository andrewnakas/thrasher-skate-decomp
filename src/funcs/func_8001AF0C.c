#include "common.h"

typedef struct {
    u8 pad[8];
    u32 *list;
} Ctx;

extern void func_8001C2B8(u32, u32, u32, u32, u32);

void func_8001AF0C(Ctx *c, s32 a1, u16 mode, s32 a3, s32 count, u16 flag) {
    s32 i;

    if (flag != 0) {
        return;
    }
    if (count <= 0) {
        return;
    }
    i = 0;
    do {
        if (mode == 1) {
            func_8001C2B8(*(u32 *)((u32)c->list + ((u32)i << 2) + 0x20), a3 & 0xFFFF, (u16)(a1 + i), 0, 0);
        } else {
            func_8001C2B8(0, (a3 + i) & 0xFFFF, (u16)(a1 + i), 0, 0);
        }
        i++;
    } while (i < count);
}
