#include "common.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} PTag_8004912C;

extern u8 *D_8008B3B0;

void func_8004912C(s32 a0, u32 a1) {
    u8 *p;
    u32 tag;
    u32 flag;

    p = (&D_8008B3B0)[-1];
    if (p == (u8 *) -1) {
        return;
    }

    p[3] = 3;
    p[7] = 0x60;
    tag = a1 | 0x60000000;
    flag = a0 & 4;
    *(u32 *) (p + 4) = tag;
    if (flag != 0) {
        *(u32 *) (p + 4) = tag | 0x2000000;
    }

    {
        u8 *link = (&D_8008B3B0)[-4];
        *(u32 *) (p + 8) = 0;
        *(u32 *) (p + 0xC) = 0xF00200;
        ((PTag_8004912C *) p)->addr = ((PTag_8004912C *) link)[1].addr;
        ((PTag_8004912C *) link)[1].addr = (u32) p;
    }
    p += 0x10;

    if (flag != 0) {
        u8 *link;
        p[3] = 1;
        link = (&D_8008B3B0)[-4];
        *(u32 *) (p + 4) = ((a0 & 3) << 5) | 0xE1000280;
        *(u32 *) p = (*(u32 *) p & 0xFF000000) | (*(u32 *) (link + 4) & 0xFFFFFF);
        *(u32 *) (link + 4) = (*(u32 *) (link + 4) & 0xFF000000) | ((u32) p & 0xFFFFFF);
        p += 8;
    }

    (&D_8008B3B0)[-1] = p;
}
