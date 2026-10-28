#include "common.h"

typedef struct {
    u16 v0;
    u8 pad2[2];
    u8 b4;
    u8 pad5;
    u8 b6;
    u8 pad7[9];
} T_8004669C;

extern T_8004669C D_800AB794[];

s32 func_8004683C(u8, u16, u16);
void func_80047494(T_8004669C *, s16);
void func_800474A4(T_8004669C *, s16);
s32 func_80047454(T_8004669C *);
s32 func_80047414(T_8004669C *);
void func_800476FC(T_8004669C *, s16);
void func_80047780(T_8004669C *, s16);
void func_80047268(u16);

void func_8004669C(u16 a0, u8 a1, u8 a2, s32 a3, u16 a4, u16 a5, u16 a6) {
    s32 a3_l = a3;

    T_8004669C *p;
    u32 r;
    u32 s0;
    u32 s1;
    u32 s3;
    u32 m;
    u32 x;

    p = &D_800AB794[a0];
    r = func_8004683C(a2, a3_l, a4);
    func_80047494(p, (s16) r);
    func_800474A4(p, r >> 16);
    s3 = 0;
    if (a1 != 4) {
        s3 = 2;
        if (a1 == 8) {
            s3 = 1;
        }
    }
    s0 = func_80047454(p);
    s1 = func_80047414(p);
    r = func_80047454(p);
    p->v0 = (s3 << 7) | ((s16) (s0 & 0x100) >> 4) | ((s1 & 0x3FF) >> 6) | ((r & 0x200) << 2);
    func_800476FC(p, (s16) a5);
    func_80047780(p, (s16) a6);
    func_80047268(a0);
    m = (16 / a1) - 1;
    x = a3_l & m;
    p->b4 += x;
    p->b6 += x;
}
