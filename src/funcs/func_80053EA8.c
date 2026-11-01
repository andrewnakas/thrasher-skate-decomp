#include "common.h"

typedef struct {
    u8 flags;
    u8 b1;
    u8 pad2[0x1E];
    s32 w20;
} Slot53EA8;

extern Slot53EA8 D_800B13DC[4];
extern s32 D_8008B454;

Slot53EA8 *func_80053EA8(void) {
    Slot53EA8 *r = 0;
    s32 i = D_8008B454;

    do {
        Slot53EA8 *p = &D_800B13DC[i];
        if (!(p->flags & 1)) {
            r = p;
            p->flags = 1;
            r->b1 = 0;
            r->w20 = 0;
            if (++D_8008B454 == 4) {
                D_8008B454 = 0;
            }
            break;
        }
        if (++i == 4) {
            i = 0;
        }
    } while (i != D_8008B454);
    return r;
}
