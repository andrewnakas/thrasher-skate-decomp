#include "common.h"

extern void func_80023004(void);
extern void func_80023494(void *a, s32 b, s32 c, s32 d, void *buf);
extern void func_80033E14(void *buf, void *src);
extern void func_8001483C(void *a, s16 *tri, void *b, void *c, void *d);
extern void func_80012214(void *a, void *b);
extern void func_80014764(void *a, s32 b);

void func_80027478(u8 *a0, u8 *a1) {
    u8 buf[0x30];
    s16 tri[3];
    u32 i;
    u32 off;

    func_80023004();
    func_80023494(a0, 0, 1, 2, buf);
    for (i = 0, off = 4; i < 3; i++, off += 0x8C) {
        func_80033E14(buf, a0 + off + 4);
    }
    tri[2] = 0;
    tri[1] = 0;
    tri[0] = 0;
    func_8001483C(a1, tri, buf + 0xC, buf, buf);
    func_80012214(a1, a0 + 0x131C);
    func_80014764(a1, 0);
}
