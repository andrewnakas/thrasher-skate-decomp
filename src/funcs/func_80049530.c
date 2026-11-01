#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 u;
    s16 v;
} Zone_80049530;

extern void func_8004966C(s16 *, s16 *, s16 *, u16, u16);
extern Zone_80049530 D_800828B4[];
/* zone count; read through a cast so it is a non-gp scalar MEM (not in_struct):
   loads hoist past the in_struct Cell stores, and the lui is rematerialised per use */
extern u8 D_8008A800[];
#define COUNT (*(s32 *) D_8008A800)

typedef struct {
    s32 v;
} Cell_80049530;

extern Cell_80049530 **D_8008A8EC;
extern s32 D_8008A8F4;

void func_80049530(void) {
    s16 ax, ay, az;
    s16 bx, by, bz;
    s32 i;
    s32 j;
    Cell_80049530 *p;
    Zone_80049530 *z;

    i = 0;
    if (COUNT > 0) {
        do {
            p = D_8008A8EC[i];
            for (j = 0x1F; j >= 0; j--) {
                p->v = -1;
                p++;
            }
            i++;
        } while (i < COUNT);
        i = 0;
    }
    D_8008A8F4 = 0;
    z = D_800828B4;
    if (COUNT > 0) {
        do {
            if (z->u < 0x100) {
                ax = i;
                az = 0;
                ay = z->u;
                func_8004966C(&ax, &ay, &az, 0x100 - z->u, 0x100);
            }
            if (z->v < 0x100) {
                bx = i;
                by = 0;
                bz = z->v;
                func_8004966C(&bx, &by, &bz, 0x100, 0x100 - z->v);
            }
            z++;
            i++;
        } while (i < COUNT);
    }
    D_8008A8F4 = 1;
}
