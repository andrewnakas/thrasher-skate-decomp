#include "common.h"

extern u32 D_8008B2EC;
extern u32 D_8008B2F0;
extern u32 D_8008B2F4;
extern u8 *D_8008B2FC;

typedef struct {
    u16 f0;
    u16 count;
    u8 pad4[0x18];
} Ent_C220;

void func_8003C220(s32 a0) {
    s32 i;
    Ent_C220 *tbl;

    if (D_8008B2EC == 0) {
        return;
    }
    i = D_8008B2F0 * D_8008B2F4 - 1;
    if (i < 0) {
        return;
    }
    tbl = (Ent_C220 *) D_8008B2FC;
    do {
        if (tbl[i].count != 0) {
            tbl[i].count = a0 + (u16) (tbl[i].count - 1);
        }
        i--;
    } while (i >= 0);
}
