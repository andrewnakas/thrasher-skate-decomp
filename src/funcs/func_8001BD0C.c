#include "common.h"

extern u16 D_8008AE12;

u8 *func_8001D0A0(s32);
u8 *func_8002BAC0(s32);
void func_8001C2B8(u32, u32, u32, u32, u32);

/* One sprite per entry of the 12-byte record arg1 selects from the table, with the
 * count stored at +0x12 clamped to 4. */
void func_8001BD0C(u8 *arg0, s32 arg1) {
    u8 *p;
    u8 *q;
    s32 n;
    s32 i;
    s32 off;
    u8 *addr;
    u32 val;

    p = func_8001D0A0(D_8008AE12);
    q = func_8002BAC0(*(u16 *) (arg0 + 4));
    off = arg1 * 12;
    if ((u32) *(u8 *) (q + off + 0x12) < 4) {
        n = *(u8 *) (q + off + 0x12);
    } else {
        n = 4;
    }
    for (i = 0; i < n; i++) {
        addr = (u8 *) ((q + (i + (arg1 * 12))) + 0xC);
        val = *addr;
        func_8001C2B8(0x2A, (u16) (*(u16 *) (p + 4) + val), (u16) (*(u16 *) (arg0 + 6) + i), 0, 0);
    }
}
