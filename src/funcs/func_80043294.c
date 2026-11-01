#include "common.h"

extern u8 D_800AAB94[];
extern u8 D_800AB6D4[];
/* D_8008B38C / D_8008B394 are spelled as their neighbour minus 4: a small (<=8 byte)
   declaration with sym-N makes gcc emit macro accesses, which the assembler expands
   to the game's unsplit lui/addiu and lui $at stores. */
extern u8 *D_8008B390[1];
extern u8 *D_8008B398[2];

void func_80043294(void) {
    u8 *p;
    u8 **o;
    s32 i;

    i = 2;
    o = &D_8008B390[-1];
    p = D_800AAB94;
    p += 0x780;
    do {
        *o = p;
        o--;
        i--;
        p -= 0x3C0;
    } while (i >= 0);
    D_8008B398[-1] = D_800AB6D4;
}
