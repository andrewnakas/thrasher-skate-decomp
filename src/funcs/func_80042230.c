#include "common.h"

typedef struct {
    u8 pad0[8];
    u16 count;
    u8 padA[0xA];
    u8 *list;
} Src_80042230;

void func_80042230(Src_80042230 *p, u32 mask, u32 set) {
    s32 n;
    u8 *e;

    n = p->count;
    e = p->list;
    while (n > 0) {
        *(u16 *)e = (*(u16 *)e & mask) | set;
        n--;
        e += e[2];
    }
}
