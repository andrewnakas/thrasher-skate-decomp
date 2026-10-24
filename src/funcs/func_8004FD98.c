#include "common.h"

extern u8 D_800B066C[];

typedef struct Ent_8004FD98 {
    u8 pad0[0x10];
    u32 count;
    u8 *data;
} Ent_8004FD98;

u8 *func_8004FD98(u16 a0, u32 a1) {
    u8 *r;
    Ent_8004FD98 *e;

    if (a0 < 0x10) {
        r = D_800B066C + a0 * 0x10;
        if (*(u32 *) r & 1) {
            e = *(Ent_8004FD98 **) (r + 4);
            if (a1 < e->count) {
                return e->data + a1 * 20;
            }
        }
    }

    return 0;
}
