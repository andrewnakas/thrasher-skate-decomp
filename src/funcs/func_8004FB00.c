#include "common.h"

extern u8 D_800B066C[];
extern void func_800501E4(u16 a0);

typedef struct Rec_8004FB00 {
    u32 flags;
    u8 pad4[0xC];
} Rec_8004FB00;

void func_8004FB00(u16 a0) {
    Rec_8004FB00 *r;
    u32 i;

    if (a0 != 0xFFFF) {
        func_800501E4(a0);
        return;
    }

    for (i = 0, r = (Rec_8004FB00 *) D_800B066C; i < 0x10; i++, r++) {
        if (r->flags & 1) {
            func_800501E4(i);
        }
    }
}
