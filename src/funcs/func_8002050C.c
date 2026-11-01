#include "common.h"

typedef struct {
    u8 key;
    u8 pad[15];
} Rec_8002050C;

typedef struct {
    s32 count;
    u8 pad[4];
    Rec_8002050C *arr;
} Tab_8002050C;

extern Tab_8002050C *D_8008AEE4[2];

u8 func_8002050C(s32 id, u8 key) {
    Tab_8002050C *t = D_8008AEE4[id];
    s32 i = t->count;
    Rec_8002050C *p;

    i--;
    if (i != -1) {
        p = (Rec_8002050C *) ((i << 4) + (s32) t->arr);
        do {
            if (key == p->key) {
                return i;
            }
            i--;
            p--;
        } while (i != -1);
    }
    return 0;
}
