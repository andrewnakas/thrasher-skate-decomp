#include "common.h"

/* Source record: two 12-byte index selectors and four words plus a timeout. */
typedef struct {
    u16 sel0;
    u16 sel1;
    u32 f4;
    u32 f8;
    u32 fC;
    u32 f10;
    u32 f14;
    u16 f18;
} T_80029BBC_src;

/* Output: three 8.16 fixed-point triples, four copied words, one word, one u16. */
typedef struct {
    u32 v0x;
    u32 v0y;
    u32 v0z;
    u32 fC;
    u32 f10;
    u32 f14;
    u32 f18;
    u32 v1x;
    u32 v1y;
    u32 v1z;
    u32 f28;
    u16 f2C;
} T_80029BBC_dst;

/* 12-byte table entry, three 16-bit angles; the selectors are biased by one. */
typedef struct {
    s16 v[6];
} T_80029BBC_entry;

/* Copies the two selected table entries (as 8.16 fixed point) and the record's
   trailing words into the caller's block. A zero selector selects nothing, so
   the destination keeps whatever it already held. */
void func_80029BBC(u8 *arg0, s32 arg1, T_80029BBC_src *arg2, T_80029BBC_dst *arg3) {
    T_80029BBC_entry *e;

    e = arg2->sel0 ? (T_80029BBC_entry *) (*(u8 **) (arg0 + 0x48) + arg2->sel0 * 0xC - 0xC) : 0;
    if (e != 0) {
        arg3->v0x = e->v[0] << 16;
        arg3->v0y = e->v[1] << 16;
        arg3->v0z = e->v[2] << 16;
    }
    arg3->fC = arg2->f4;
    arg3->f10 = arg2->f8;
    arg3->f14 = arg2->fC;
    arg3->f18 = arg2->f10;
    e = arg2->sel1 ? (T_80029BBC_entry *) (*(u8 **) (arg0 + 0x48) + arg2->sel1 * 0xC - 0xC) : 0;
    if (e != 0) {
        arg3->v1x = e->v[0] << 16;
        arg3->v1y = e->v[1] << 16;
        arg3->v1z = e->v[2] << 16;
    }
    arg3->f28 = arg2->f14;
    arg3->f2C = arg2->f18;
}
