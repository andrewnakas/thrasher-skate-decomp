#include "common.h"

typedef struct {
    u8 pad0[4];
    s32 key;
    u16 h8;
    u8 padA[0x6E];
} Item1CAA8;

typedef struct {
    s32 arg;
    void *p;
    Item1CAA8 *item;
    u16 n;
    u16 c;
    s32 out;
} Msg1CAA8;

typedef struct {
    s32 key;
    u16 count;
    u8 pad6[2];
    s32 arg;
    void (*cb)(Msg1CAA8 *);
} Rule1CAA8;

extern Rule1CAA8 *D_8008AE4C;
extern u16 D_8008AE50;
extern u16 D_8008AE58;
extern Item1CAA8 *D_8008AE38;
extern s32 D_8008AE3C;

void func_8003B9F8(s32);
void *func_8001CC5C(Item1CAA8 *, u16, s32 *);

s32 func_8001CAA8(void) {
    Msg1CAA8 msg;
    s32 out;
    Rule1CAA8 *r;
    Item1CAA8 *it;
    void *p;
    s32 i;
    u16 n;
    u16 c;

    r = D_8008AE4C;
    D_8008AE58 = 0;
    for (i = 0; i < D_8008AE50; r++, i++) {
        func_8003B9F8((((i << 10) / D_8008AE50) * 51) / 1024 + 0x199);
        n = 0;
        for (it = D_8008AE38; it < (Item1CAA8 *) ((u8 *) D_8008AE38 + D_8008AE3C); it++) {
            if (r->key != it->key) {
                continue;
            }
            if (r->count == 0xFFFF) {
                c = it->h8;
            } else {
                c = it->h8 + r->count;
            }
            p = func_8001CC5C(it, c, &out);
            if (p == 0) {
                return 1;
            }
            if (r->cb != 0) {
                msg.arg = r->arg;
                msg.p = p;
                msg.item = it;
                msg.n = n;
                msg.out = out;
                r->cb(&msg);
            }
            if (r->count == n) {
                break;
            }
            n++;
        }
    }
    return 0;
}
