#include "common.h"

typedef struct {
    s32 count;
    u8 pad[4];
    u8 *arr;
} T;

extern u8 *D_8008AEE4;

u8 func_8002050C(s32 id, u8 key) {
    s32 sentinel = -1;
    T *t = (T *) *(u8 **) ((u8 *) &D_8008AEE4 + id * 4);
    s32 i = t->count;
    u8 *p;

    if (--i == sentinel) {
        return 0;
    }
    p = i * 16 + t->arr;
    do {
        if (key == *p) {
            return i;
        }
        p -= 16;
    } while (--i != sentinel);
    return 0;
}
