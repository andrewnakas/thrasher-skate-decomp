#include "common.h"

typedef struct {
    s32 count;
    u8 pad[4];
    u8 *arr;
} T_8002050C;

extern u8 *D_8008AEE4;

u8 func_8002050C(s32 id, u8 key) {
    s32 off = id * 4;
    T_8002050C *t = (T_8002050C *) *(u8 **) ((u8 *) &D_8008AEE4 + off);
    s32 i = t->count;
    u8 *p;

    if (--i == -1) {
        return 0;
    }
    p = (u8 *) (i * 16 + (s32) t->arr);
    do {
        if (key == *p) {
            return (u8) i;
        }
        p -= 16;
    } while (--i != -1);
    return 0;
}
