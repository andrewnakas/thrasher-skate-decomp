#include "common.h"

typedef struct {
    s32 id;
    u16 h;
    u8 name[2];
    s32 c;
} Rec1D88C;

typedef struct {
    s32 used;
    u8 pad4[0xA];
    u16 cnt;
    u8 pad10[4];
    Rec1D88C recs[4];
} Ent1D88C;

typedef struct {
    s32 id;
    s16 zero;
    u16 h;
    u8 *name;
    s32 c;
} Req1D88C;

extern Ent1D88C *D_8008AEC4;

void func_8001D7C8(void);
s32 func_8001C3CC(s32 id);
s32 func_8001B40C(Req1D88C *q, s32 n);

s32 func_8001D88C(void) {
    Req1D88C q;
    Ent1D88C *e;
    Rec1D88C *r;
    s32 i;
    s32 n;

    func_8001D7C8();
    e = D_8008AEC4;
    for (i = 25; i != 0; i--, e++) {
        if (e->used == 0) {
            continue;
        }
        n = e->cnt;
        n--;
        r = e->recs;
        while (n != -1) {
            r->h = func_8001C3CC(r->id);
            q.id = r->id;
            q.zero = 0;
            q.h = r->h;
            q.name = r->name;
            q.c = r->c;
            if (func_8001B40C(&q, 1) != 0) {
                return 1;
            }
            r++;
            n--;
        }
    }
    return 0;
}
