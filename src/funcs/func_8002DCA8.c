#include "common.h"

typedef struct {
    u32 f00;
    u32 f04;
    u32 f08;
} Rec_8002DCA8;

extern u8 D_8006F834[0x100];

void func_8002DCA8(u8 idx, s32 value) {
    Rec_8002DCA8 *tab = (Rec_8002DCA8 *) D_8006F834;

    tab[idx].f08 = value;
}
