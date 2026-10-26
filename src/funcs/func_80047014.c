#include "common.h"

typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 f6;
    u32 w0;
    u32 w1;
} Ent_80047014;

extern Ent_80047014 D_800AB794[];

s32 func_8004734C(s32);
s32 func_800474B4(s32);
s32 func_80047578(s32);
s32 func_800476C8(s32);
s32 func_8004763C(s32);
s32 func_8004774C(s32);
s32 func_80047680(s32);
void func_800498FC(s32, s32, s32, s32, s32);
void func_8004862C(s32, s32);
void *memset(void *, s32, u32);

void func_80047014(s32 id) {
    Ent_80047014 *base;
    Ent_80047014 *rec;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 n;

    id &= 0xFFFF;
    a = func_8004734C(id);
    b = func_800474B4(id);
    c = func_80047578(id);
    d = func_800476C8(id);
    e = func_8004763C(id);
    /* rounded size in 8-byte units; the original bias-tests the pre-rounded sum and then
       shifts it as an unsigned value, so the guard has to be written out */
    n = (d & 0xFFFF) * (e & 0xFF) + 7;
    if (n < 0) {
        n += 7;
    }
    d = (u32)n >> 3;
    e = func_8004774C(id);
    func_800498FC(a & 0xFF, b & 0xFFFF, c & 0xFFFF, d & 0xFFFF, e & 0xFFFF);
    e = func_80047680(id);
    base = D_800AB794;
    rec = &base[id];
    func_8004862C(rec->f2, (s16)e);
    memset(rec, 0, 0x10);
}
