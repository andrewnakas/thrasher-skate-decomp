/* cflags: -mno-split-addresses */
#include "common.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} PTag_80038864;

typedef struct {
    PTag_80038864 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 w, h;
} Tile_80038864;

extern PTag_80038864 *D_8008B1A0;
extern u16 D_8008B1A4;
extern u8 *D_8008B3B0[];

extern u8 *func_80039FF4(PTag_80038864 *ot, u8 *p, u16 tpage);

void func_80038864(u32 rgb, u8 semi, s32 abr, s16 x0, s32 y0, s32 x1, s32 y1) {
    u8 *p;
    u16 a;

    p = D_8008B3B0[-1];
    ((Tile_80038864 *)p)->tag.len = 3;
    ((Tile_80038864 *)p)->code = 0x60;
    ((Tile_80038864 *)p)->x0 = x0;
    ((Tile_80038864 *)p)->y0 = y0;
    ((Tile_80038864 *)p)->w = x1 - x0;
    ((Tile_80038864 *)p)->h = y1 - y0;
    ((Tile_80038864 *)p)->r0 = rgb;
    ((Tile_80038864 *)p)->g0 = rgb >> 8;
    ((Tile_80038864 *)p)->b0 = rgb >> 16;
    if (semi == 1) {
        ((Tile_80038864 *)p)->code |= 2;
    }
    a = abr & 3;
    ((Tile_80038864 *)p)->y0 += 0x78;
    ((Tile_80038864 *)p)->tag.addr = D_8008B1A0->addr;
    D_8008B1A0->addr = (u32)p;
    p += 0x10;
    if (D_8008B1A4 != ((a << 5) | 0x80)) {
        p = func_80039FF4(D_8008B1A0, p, (a << 5) | 0x80);
    }
    D_8008B3B0[-1] = p;
    D_8008B1A0--;
}
