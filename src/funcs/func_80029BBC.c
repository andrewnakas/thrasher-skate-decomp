#include "common.h"

typedef struct {
    u16 f0;
    u16 f2;
    u32 f4;
    u32 f8;
    u32 fC;
    u32 f10;
    u32 f14;
    u16 f18;
} T_29BBC_src;

typedef struct {
    u32 f0;
    u32 f4;
    u32 f8;
    u32 fC;
    u32 f10;
    u32 f14;
    u32 f18;
    u32 f1C;
    u32 f20;
    u32 f24;
    u32 f28;
    u16 f2C;
} T_29BBC_dst;

typedef struct {
    s16 v[6];
} T_29BBC_rec;

/* Build arg3 from arg2: the two 1-based record indices (f0, f2) select 12-byte
 * entries out of the table at arg0->0x48 and each contributes three 16.16 values. */
void func_80029BBC(u8 *arg0, s32 arg1, T_29BBC_src *arg2, T_29BBC_dst *arg3) {
    T_29BBC_rec *e;

    e = arg2->f0 ? (T_29BBC_rec *) (*(u8 **) (arg0 + 0x48) + arg2->f0 * 0xC - 0xC) : 0;
    if (e != 0) {
        arg3->f0 = e->v[0] << 16;
        arg3->f4 = e->v[1] << 16;
        arg3->f8 = e->v[2] << 16;
    }
    arg3->fC = arg2->f4;
    arg3->f10 = arg2->f8;
    arg3->f14 = arg2->fC;
    arg3->f18 = arg2->f10;
    e = arg2->f2 ? (T_29BBC_rec *) (*(u8 **) (arg0 + 0x48) + arg2->f2 * 0xC - 0xC) : 0;
    if (e != 0) {
        arg3->f1C = e->v[0] << 16;
        arg3->f20 = e->v[1] << 16;
        arg3->f24 = e->v[2] << 16;
    }
    arg3->f28 = arg2->f14;
    arg3->f2C = arg2->f18;
}
