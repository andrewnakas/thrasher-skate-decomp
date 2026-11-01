#include "common.h"

typedef struct Node {
    u8 type;
    u8 pad1[3];
    void *data;
    struct Node *left;
    struct Node *right;
} Node;

extern s32 D_8008A328;
extern s32 D_8008AFF4;

void func_8002A264(void *);

void func_8002A198(Node *n) {
    u32 t;

    if (n == NULL) {
        return;
    }
    D_8008A328++;
    if (D_8008AFF4 < D_8008A328) {
        D_8008AFF4 = D_8008A328;
    }
    t = n->type;
    if (t == 'p') {
        goto node;
    }
    if (t == 'l') {
        goto leaf;
    }
    goto end;
node:
    func_8002A198(n->left);
    if (n->data != NULL) {
        func_8002A264(n->data);
    }
    func_8002A198(n->right);
    t = n->type;
leaf:
    {
        /* The u8 narrowing copy keeps gcc from threading the 'l' dispatch past this test. */
        u8 type = t;

        if (type == 'l' && n->data != NULL) {
            func_8002A264(n->data);
        }
    }
end:
    D_8008A328--;
}
