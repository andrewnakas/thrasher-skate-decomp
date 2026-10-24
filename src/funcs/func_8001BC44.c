#include "common.h"

typedef struct {
    u8 pad[0x3C];
    u32 flags;
} Rec;

extern u8 *D_80089FD0;
extern Rec **D_80089FD4;
extern s32 func_8002BA54(void);
extern u8 *func_8001A430(s16 *);
extern void func_80014310(u8 *);
extern u32 *func_8002BAC0(u16);

void func_8001BC44(void) {
    s32 i;
    s32 n;
    s16 v;
    u16 idx;
    u8 *r;

    n = func_8002BA54();
    if (n == 0) {
        return;
    }
    i = n - 1;
    do {
        idx = i;
        if (D_80089FD0[i] == 0) {
            i--;
            continue;
        }
        v = i;
        r = func_8001A430(&v);
        D_80089FD4[i] = (Rec *)r;
        func_80014310(r);
        if (*func_8002BAC0(idx) & 1) {
            D_80089FD4[i]->flags |= 0x10;
        }
        i--;
    } while (i != -1);
}
