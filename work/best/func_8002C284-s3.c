#include "common.h"

extern s32 *D_8008B048;

typedef struct Node {
    u8 kind;
    u8 idx;
    s16 off;
    s32 val;
    struct Node *a;
    struct Node *b;
} Node;

void func_8002C284(s16 *tbl, Node *n) {
    s32 v;
    s32 *p;

    if (n == 0) {
        return;
    }
    if (n->kind == 0x6C) {
        p = D_8008B048;
        *p = n->val;
        D_8008B048 = p + 1;
        return;
    }
    if (n->kind != 0x70) {
        return;
    }
    v = (*(s16 *) ((s32) n->idx * 2 + (u32) tbl) + n->off) << 16;
    if (v < -0x100) {
        if (n->a == 0) {
            p = D_8008B048;
            *p = n->val;
            D_8008B048 = p + 1;
            return;
        }
        func_8002C284(tbl, n->a);
        return;
    }
    if (v >= 0x101) {
        if (n->b == 0) {
            p = D_8008B048;
            *p = n->val;
            D_8008B048 = p + 1;
            return;
        }
        func_8002C284(tbl, n->b);
        return;
    }
    if (n->a != 0) {
        func_8002C284(tbl, n->a);
    } else {
        p = D_8008B048;
        *p = n->val;
        D_8008B048 = p + 1;
    }
    if (n->b == 0) {
        p = D_8008B048;
        *p = n->val;
        D_8008B048 = p + 1;
        return;
    }
    func_8002C284(tbl, n->b);
}
