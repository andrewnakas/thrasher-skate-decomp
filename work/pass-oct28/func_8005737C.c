#include "common.h"

typedef struct {
    u32 *ptr;     /* 0x00 */
    u8 pad4[0x8]; /* 0x04 */
    u16 unkC;     /* 0x0C */
    u16 unkE;     /* 0x0E */
    u8 pad10[0x20];
} Rec_8005737C;

extern Rec_8005737C D_800B2C7C[];
extern u32 D_800B2CDC[3][10];
extern u32 D_800B2D5C[10];
extern u32 *func_80034F14(s32);

void func_8005737C(void) {
    u32 *p;
    u32 i;
    u32 j;

    i = 0;
    do {
        p = func_80034F14(0);
        D_800B2C7C[i].ptr = p;
        D_800B2C7C[i].unkE = 0;
        D_800B2C7C[i].unkC = 0;
        if (*(u16 *) ((u8 *) p + 2) & 1) {
            D_800B2C7C[i].unkE |= 1;
        }
        i++;
    } while (i < 2);

    j = 0;
    do {
        switch (j) {
        case 0:
            D_800B2CDC[j][0] = 0x20;
            D_800B2CDC[j][1] = 0x80;
            D_800B2CDC[j][2] = 0x40;
            D_800B2CDC[j][3] = 0x10;
            D_800B2CDC[j][4] = 0x100;
            D_800B2CDC[j][5] = 0x200;
            D_800B2CDC[j][6] = 0xC00;
            D_800B2CDC[j][7] = 0x2000;
            D_800B2CDC[j][8] = 0x400;
            D_800B2CDC[j][9] = 0x800;
            break;
        case 1:
            D_800B2CDC[j][0] = 0x80;
            D_800B2CDC[j][1] = 0x40;
            D_800B2CDC[j][2] = 0x20;
            D_800B2CDC[j][3] = 0x10;
            D_800B2CDC[j][4] = 0x200;
            D_800B2CDC[j][5] = 0x800;
            D_800B2CDC[j][6] = 0x500;
            D_800B2CDC[j][7] = 0x2000;
            D_800B2CDC[j][8] = 0x400;
            D_800B2CDC[j][9] = 0x100;
            break;
        case 2:
            D_800B2CDC[j][0] = 0x80;
            D_800B2CDC[j][1] = 0x20;
            D_800B2CDC[j][2] = 0x10;
            D_800B2CDC[j][3] = 0x40;
            D_800B2CDC[j][4] = 0x100;
            D_800B2CDC[j][5] = 0x400;
            D_800B2CDC[j][6] = 0xA00;
            D_800B2CDC[j][7] = 0x2000;
            D_800B2CDC[j][8] = 0x200;
            D_800B2CDC[j][9] = 0x800;
            break;
        }
        j++;
    } while (j < 3);

    D_800B2D5C[0] = 0x20;
    D_800B2D5C[1] = 0x80;
    D_800B2D5C[2] = 0x40;
    D_800B2D5C[3] = 0x10;
    D_800B2D5C[4] = 0x100;
    D_800B2D5C[5] = 0x200;
    D_800B2D5C[6] = 0x50;
    D_800B2D5C[7] = 0x150;
    D_800B2D5C[8] = 0;
    D_800B2D5C[9] = 0;
}
