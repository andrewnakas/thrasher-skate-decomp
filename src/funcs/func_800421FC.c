#include "common.h"

typedef struct {
    u16 unk0;
    u8 pad2[0x32];
} Entry_800421FC;

typedef struct {
    u8 pad0[6];
    u16 count;
    u8 pad8[8];
    Entry_800421FC *list;
} Src_800421FC;

void func_800421FC(Src_800421FC *p, u32 mask, u32 set) {
    s32 n;
    Entry_800421FC *e;

    n = p->count;
    e = p->list;
    while (n > 0) {
        e->unk0 = (e->unk0 & mask) | set;
        n--;
        e++;
    }
}
