#include "common.h"

typedef struct {
    s32 a, b, c, d;
} Tex16;

extern s32 D_8008A55C;
extern s32 D_8008B0C0;
extern s32 D_8008B0C4;
extern s32 D_8008B0F0;
extern s32 D_8008B0EC;
extern s32 D_8008B0DC[2];
extern u16 D_8008A8CC;
/* unsplit lui/lhu loads: reach the u16 globals via a non-gp neighbour */
#define D_8008A8C4 (*(&D_8008A8CC - 4))
#define D_8008A8C6 (*(&D_8008A8CC - 3))
extern u8 D_800818E4[];
extern u8 D_800820DC[];
extern Tex16 D_800AB794[];

s32 func_80033F44(const u8 *p, s32 n);
u16 func_8004691C(u8 *arg0, u16 x, u16 y, u16 z, u32 flags);
s32 func_800347FC(u16 a, u8 *p, u8 b);

void func_80034A78(void) {
    s32 one = 1;
    u16 clut;

    D_8008B0C0 = one;
    D_8008B0C4 = 2;
    if (D_8008A55C == 0) {
        clut = (D_8008A8C6 << 6) | ((D_8008A8C4 >> 4) & 0x3F);
        D_8008B0F0 = func_80033F44(D_800818E4, 0x7F6);
        *(Tex16 *) D_8008B0DC = D_800AB794[func_8004691C(D_800818E4, clut, 0x300, 0x180, 0xC00000)];
        D_8008B0EC = func_800347FC(0, D_800820DC, 0);
        D_8008A55C = one;
    }
}
