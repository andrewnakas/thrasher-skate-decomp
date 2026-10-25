#include "common.h"

typedef struct N_80019630 {
    u16 key;
    u16 pad;
    struct N_80019630 *next;
} N_80019630;

extern N_80019630 *D_8008AD70;

N_80019630 *func_80019630(u16 key) {
    N_80019630 *n = D_8008AD70;

    while (n != 0) {
        if (n->key == key) {
            return n;
        }
        n = n->next;
    }
    return 0;
}
