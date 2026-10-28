#include "common.h"

typedef struct {
    u8 pad0[0x128];
    u32 f128;
    u32 f12C;
    u32 f130;
} Blk_8003BDB8;

extern u32 D_8008B284;
extern u32 D_8008B278;
extern u32 D_8008B29C;
extern u32 D_8008B2A0;
extern u32 D_8008B260;
extern u32 D_8008B268;
extern u32 D_8008B26C;
extern u32 D_8008B270;
extern u16 D_8008B288;
extern u16 D_8008B28A;
extern u16 D_8008B28C;
extern u32 D_8008B27C;
extern u32 D_8008B280;
extern u32 D_8008B25C;
extern u32 D_8008B264;
extern u8 D_8008234C[];

void func_8003BE34(s32 arg);

void func_8003BDB8(void) {
    Blk_8003BDB8 *p;
    s32 v;
    u32 a;
    u32 b;

    b = (u32) 0xFFFF << 16;
    a = 0x10000;
    D_8008B284 = a;
    D_8008B278 = a;
    D_8008B29C = a;
    D_8008B2A0 = a;
    p = (Blk_8003BDB8 *) D_8008234C;
    D_8008B260 = b;
    v = 0x1000;
    D_8008B268 = 0;
    D_8008B26C = 0;
    D_8008B270 = 0;
    D_8008B288 = 0;
    D_8008B28A = 0;
    D_8008B28C = 0;
    D_8008B27C = 0;
    D_8008B280 = 0;
    D_8008B25C = 0;
    D_8008B264 = 0;
    p->f128 = v;
    p->f12C = v;
    p->f130 = v;
    func_8003BE34(0x271C);
}
