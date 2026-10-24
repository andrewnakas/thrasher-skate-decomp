#include "common.h"

typedef struct {
    u8 buf[0x18];
    u16 d[4];
} Frame_8003AE0C;

extern void func_8005A760(u16 *buf);
extern void VSync(s32 a);
extern void func_8003AD7C(void *d, s32 a, s32 b, s32 c, s32 e);

void func_8003AE0C(void) {
    Frame_8003AE0C f;

    func_8005A760((u16 *) f.buf);
    f.d[0] = 0;
    f.d[1] = 0;
    f.d[2] = *(u16 *) (f.buf + 4);
    f.d[3] = 0x200;
    VSync(0);
    func_8003AD7C(f.d, 0, 0, 0, 1);
    VSync(0);
    func_8003AD7C(f.d, 0, 0, 0, 1);
}
