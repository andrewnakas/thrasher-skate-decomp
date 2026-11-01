#include "common.h"

typedef struct {
    s32 f0;
    s32 f4;
    u16 f8;
    u16 fA;
    s32 fC;
} Table;

typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 f6;
    s32 f8;
} Slot;

typedef struct {
    u16 key;
    u16 dst;
    s32 arg;
    s32 changed;
} Msg;

typedef struct {
    s32 idx;
    u16 off;
    u16 dst;
    void (*fn)(Msg *);
    s32 arg;
} Entry;

extern void func_8001C540(void);
extern void func_8001C810(s32, u16, Slot *);
extern Slot *func_8001C930(s32, u16);
extern void func_8003B9F8(s32 a);
extern void func_800465CC(u16, u16);
extern void func_800477D0(u16, u16);
extern Table *D_8008AE5C;
extern Entry *D_8008AE64;
extern u16 D_8008AE68;

s32 func_8001C62C(void) {
    Msg msg;
    Entry *e;
    Table *t;
    Slot *s;
    s32 i;
    s32 v;
    s32 sum;
    s32 changed;
    u16 prev;
    u16 key;

    prev = 0;
    func_8001C540();
    e = D_8008AE64;
    for (i = 0; i < D_8008AE68; i++) {
        v = ((i << 10) / D_8008AE68) * 307;
        if (v < 0) {
            v += 0x3FF;
        }
        func_8003B9F8((v >> 10) + 0x1CC);
        t = D_8008AE5C + e->idx;
        sum = t->f8 + e->off;
        key = sum;
        s = func_8001C930(e->idx, key);
        if (s->f4 != key || (changed = 0, s->f8 != t->f4)) {
            func_8001C810(e->idx, sum, s);
            changed = 1;
        }
        if (e->dst != 0 && e->dst != 0xFFFF) {
            func_800465CC(s->f6, e->dst);
        }
        if (t->fC & 0x800000) {
            func_800477D0(prev, e->dst);
        }
        if (e->fn != NULL) {
            msg.key = s->f6;
            msg.dst = e->dst;
            msg.arg = e->arg;
            msg.changed = changed;
            e->fn(&msg);
        }
        prev = e->dst;
        e++;
    }
    return 0;
}
