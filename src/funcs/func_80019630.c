#include "common.h"

typedef struct Node {
    u16 id;
    u16 pad;
    struct Node *next;
} Node;

extern Node *D_8008AD70;

s32 func_80019630(u16 id) {
    Node *n;

    n = D_8008AD70;
    while (n != 0) {
        if (n->id == id) {
            return (s32) n;
        }
        n = n->next;
    }
    return 0;
}
