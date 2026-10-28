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

    if (n == 0) {
        return;
    }
    if (n->kind == 0x6C) {
        *D_8008B048++ = n->val;
        return;
    }
    if (n->kind != 0x70) {
        return;
    }
    v = (tbl[n->idx] + n->off) << 16;
    if (v < -0x100) {
        if (n->a) {
            func_8002C284(tbl, n->a);
        } else {
            *D_8008B048++ = n->val;
        }
    } else if (v >= 0x101) {
        if (n->b) {
            func_8002C284(tbl, n->b);
        } else {
            *D_8008B048++ = n->val;
        }
    } else {
        if (n->a) {
            func_8002C284(tbl, n->a);
        } else {
            *D_8008B048++ = n->val;
        }
        if (n->b) {
            func_8002C284(tbl, n->b);
        } else {
            *D_8008B048++ = n->val;
        }
    }
}
