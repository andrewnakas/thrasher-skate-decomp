#include "common.h"

extern u8 D_800AAB94[];
extern u8 D_800AB6D4[];
extern u8 D_8008B38C[0xC];
typedef struct {
    u32 p;
    u32 pad[3];
} Slot_80043294;

extern u32 D_8008B394[];

void func_80043294(void) {
    u8 *p;
    u8 **o;
    s32 i;

    i = 2;
    o = (u8 **) D_8008B38C;
    p = D_800AAB94;
    p += 0x780;
    do {
        *o = p;
        o--;
        i--;
        p -= 0x3C0;
    } while (i >= 0);
    D_8008B394[0] = (u32) D_800AB6D4;
}
