#include "common.h"

extern u8 D_8008AD64[8];

typedef struct Node_80019670 {
    u8 pad0[8];
    s32 handle;
    s32 unkC;
} Node_80019670;

typedef struct Tbl_80019670 {
    u32 count;
    struct {
        s32 key;
        s32 val;
    } items[1];
} Tbl_80019670;

s32 func_80015E8C(s32);
void func_80015F10(s32);

s32 func_80019670(u16 arg0) {
    Node_80019670 *n;
    Tbl_80019670 *e;
    s32 *slot;
    s32 *it;
    s32 i;
    u32 k;

    for (i = 0; i < 2; i++) {
        slot = (s32 *) (D_8008AD64 + i * 4);
        n = (Node_80019670 *) *(s32 *) ((u8 *) slot + 0x18);
        if (n == 0) {
            continue;
        }
        e = (Tbl_80019670 *) func_80015E8C(n->handle);
        it = &e->items[0].key;
        for (k = 0; k < e->count; k++, it += 2) {
            if (it[0] == arg0) {
                func_80015F10(n->handle);
                n->unkC = it[1];
                return (s32) n;
            }
        }
        func_80015F10(n->handle);
    }
    return 0;
}
