#include "common.h"

typedef struct Node {
    s32 id;
    s32 key;
    struct Node *next;
} Node;

extern Node *D_8008B050;
extern Node *D_8008B04C;

void func_8002CF94(s32 arg0, s32 arg1) {
    Node *p;
    Node *cur;
    Node *prev;

    p = D_8008B050;
    if (p == NULL) {
        D_8008B050 = D_8008B04C;
        D_8008B04C->next = NULL;
        goto insert;
    }
    cur = p;
    prev = NULL;
    while (cur != NULL && arg1 >= cur->key) {
        prev = cur;
        cur = cur->next;
    }
    if (prev == NULL) {
        D_8008B050 = D_8008B04C;
    } else {
        prev->next = D_8008B04C;
    }
    D_8008B04C->next = cur;
insert:
    D_8008B04C->id = arg0;
    D_8008B04C->key = arg1;
    D_8008B04C++;
}
