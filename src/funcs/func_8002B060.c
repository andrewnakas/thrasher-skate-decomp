/* cflags: -mno-split-addresses */
#include "common.h"

typedef struct {
    u8 pad0[0x1C];
    u8 *f1C;
    u8 pad20[0xA];
    u16 f2A;
} T_8002B060;

/* D_800A1C90 is a table of 36-byte records; the s16 status field sits at +2. */
extern s32 D_800A1C90[][9];
void func_8001BEB4(void *);

void func_8002B060(T_8002B060 *arg0) {
    s32 (*w)[9] = D_800A1C90;

    if ((*(u32 *) (arg0->f1C + 4) & 0x8000) || arg0->f2A == 0xFF || ((s16 *) w)[arg0->f2A * 18 + 1] == 0) {
        func_8001BEB4(arg0->f1C);
        arg0->f1C = 0;
    }
}
