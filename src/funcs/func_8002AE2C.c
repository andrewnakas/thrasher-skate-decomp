#include "common.h"

extern u32 D_800A4F04[4];
extern u8 *func_8002BAC0(u32);
extern u8 *func_8002AB64(s32, s32 *);
extern void func_8002AC14(u8 *, u32);

void func_8002AE2C(void) {
    u8 *s1;
    u8 *s0;
    u8 *q;
    s32 v[3];

    s1 = (u8 *) D_800A4F04[0];
    while (s1 != 0) {
        s0 = *(u8 **) (s1 + 8);
        while (s0 != 0) {
            if ((*(u32 *) func_8002BAC0(*(u16 *) s0) & 0x10) != 0) {
                v[0] = *(s16 *) (s0 + 0xA) << 16;
                v[1] = *(s16 *) (s0 + 0xC) << 16;
                v[2] = *(s16 *) (s0 + 0xE) << 16;
                q = func_8002AB64(-2, v);
                *(u32 *) (s0 + 0x20) = (u32) q;
                if (q != 0) {
                    func_8002AC14(q, *(u32 *) (q + 0xC));
                }
            }
            s0 = *(u8 **) (s0 + 0x40);
        }
        s1 = *(u8 **) (s1 + 0x94);
    }
}
