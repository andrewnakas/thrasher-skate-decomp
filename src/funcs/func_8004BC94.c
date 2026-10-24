#include "common.h"

typedef struct Node_8004BC94 {
    u8 pad0[0xC];
    u32 size;
    struct Node_8004BC94 *next;
} Node_8004BC94;

typedef struct {
    u8 pad0[0x38];
    Node_8004BC94 *head;
} Pool_8004BC94;

void func_8004BC94(Pool_8004BC94 *a, Node_8004BC94 *n) {
    Node_8004BC94 *cur;
    Node_8004BC94 *prev;
    u32 need;
    u32 sum;
    u32 total;

    prev = 0;
    sum = 0;
    cur = a->head;
    if (cur != 0) {
        need = n->size;
        while (1) {
            total = sum + cur->size;
            if (need < total) {
                break;
            }
            prev = cur;
            cur = cur->next;
            sum = total;
            if (cur == 0) {
                break;
            }
        }
    }
    if (prev != 0) {
        prev->next = n;
        n->size -= sum;
    } else {
        a->head = n;
    }
    n->next = cur;
    if (cur != 0) {
        cur->size -= n->size;
    }
}
