#include "common.h"

typedef struct {
    s32 f0;
    s32 f4;
    u16 f8;
    u16 pad0;
    s32 pad1;
} Table;

typedef struct {
    s32 idx;
    u16 f4;
} Node;

extern Table *D_8008AE5C;

/* Order two nodes by their table rows: primary key first, then the offset sum. */
s32 func_8001C4BC(Node **arg0, Node **arg1) {
    Table *ta;
    Table *tb;
    Node *a;
    Node *b;
    s32 ka;
    s32 kb;

    a = *arg0;
    b = *arg1;
    ta = D_8008AE5C + a->idx;
    tb = D_8008AE5C + b->idx;
    ka = ta->f4;
    kb = tb->f4;
    if (ka != kb) {
        if (ka < kb) {
            return -1;
        }
        return 1;
    }
    ka = ta->f8 + a->f4;
    kb = tb->f8 + b->f4;
    if (ka != kb) {
        if (ka < kb) {
            return -1;
        }
        return 1;
    }
    return 0;
}
