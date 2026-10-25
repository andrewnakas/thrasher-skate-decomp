#include "common.h"

typedef struct N_8002B57C {
    u8 pad0[0x3C];
    s32 f3C;
    struct N_8002B57C *next;
} N_8002B57C;

typedef struct {
    u8 pad0[0x8];
    N_8002B57C *head;
} H_8002B57C;

void func_8002B57C(N_8002B57C *self, H_8002B57C *h) {
    N_8002B57C *n;

    self->f3C = 0;
    n = h->head;
    if (n == self) {
        h->head = self->next;
        return;
    }
    if (n != 0) {
        do {
            N_8002B57C *nx = n->next;

            if (nx == self) {
                n->next = self->next;
                self->next = 0;
                return;
            }
            n = nx;
        } while (n != 0);
    }
}
