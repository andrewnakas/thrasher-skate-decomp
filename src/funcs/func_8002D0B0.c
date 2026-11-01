#include "common.h"

/* Raw offsets into D_800A1C50 keep the stores ahead of the gp loads. */
extern u8 D_800A1C50[];
extern s16 D_8008AFC4;
extern s16 D_8008AFC6;
extern s16 D_8008AFC8;
extern s16 D_8008AFCC;
extern s16 D_8008AFCE;
extern s16 D_8008AFD0;
extern s32 D_8008AFB4;
extern s32 D_8008AFB8;
extern s32 D_8008AFBC;

extern s32 func_8002D198(u8 *p, s32 *pt, s32 *val);
extern s32 func_8002D330(u8 *p, s32 a, s32 b, s32 c);

s32 func_8002D0B0(u8 *s) {
    s32 pt[4];
    s32 val[2];
    s32 r;
    u8 *g;
    s16 x;
    s16 y;
    s16 z;

    r = 0;
    g = D_800A1C50;
    do {
        if ((*(u16 *) s & 0x20) == 0 && func_8002D198(s + 4, pt, val) != 0
            && func_8002D330(s, pt[0], pt[1], pt[2]) != 0) {
            x = pt[0] >> 16;
            y = pt[1] >> 16;
            z = pt[2] >> 16;
            *(u8 **) (g + 0x1C) = s;
            *(s16 *) (g + 0x20) = x;
            *(s16 *) (g + 0x22) = y;
            *(s16 *) (g + 0x24) = z;
            *(s32 *) (g + 0x28) = val[0];
            D_8008AFCC = x;
            D_8008AFB4 = x - D_8008AFC4;
            D_8008AFCE = y;
            D_8008AFD0 = z;
            D_8008AFB8 = y - D_8008AFC6;
            D_8008AFBC = z - D_8008AFC8;
            r = 1;
        }
        s = *(u8 **) (s + 0x14);
    } while (s != 0);
    return r;
}
