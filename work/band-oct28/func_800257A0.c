#include "common.h"

typedef struct {
    u32 count;
    u16 f4;
    u16 flags;
    u8 pad[0x64];
    u32 f6C;
    u32 f70;
    u32 f74;
    u8 pad2[0x14];
} Obj_800257A0;

void func_800257A0(Obj_800257A0 *a0) {
    u32 i;

    if (a0->count == 0) {
        return;
    }
    for (i = 0; i < a0->count; i++) {
        if (a0[i].flags & 1) {
            a0[i].f4 = 0;
            a0[i].f6C = 0;
            a0[i].f70 = 0;
            a0[i].f74 = 0;
        }
    }
}
