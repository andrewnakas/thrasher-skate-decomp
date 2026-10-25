#include "common.h"

extern void func_80023004(void);
extern void func_80023494(u8 *, s32, s32, s32, u8 *);
extern void func_80033E14(u8 *, u8 *);
extern void func_8001483C(u8 *, s16 *, u8 *, u8 *, u8 *);
extern void func_80012214(u8 *, u8 *);
extern void func_80014764(u8 *, s32);

void func_80027478(u8 *a0, u8 *a1) {
    u8 buf[0x30];
    s16 t[3];
    u32 i;
    s32 off;

    func_80023004();
    func_80023494(a0, 0, 1, 2, buf);
    i = 0;
    off = 4;
    do {
        func_80033E14(buf, a0 + off + 4);
        i++;
        off += 0x8C;
    } while (i < 3);
    t[2] = 0;
    t[1] = 0;
    t[0] = 0;
    func_8001483C(a1, t, buf + 0xC, buf, buf);
    func_80012214(a1, a0 + 0x131C);
    func_80014764(a1, 0);
}
