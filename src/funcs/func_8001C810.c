#include "common.h"

typedef struct {
    u32 f0;
    u32 f4;
    u32 f8;
    u32 flags;
} S_8001C810;

extern u32 D_8008AE5C;
extern u32 D_8008AE70[2];

extern void func_80046584(u32 a0);
extern u32 func_80046EFC(u32 a0, u32 a1, u32 a2, u32 a3, u32 out);

u32 func_8001C810(u32 idx, u32 id, u8 *p) {
    S_8001C810 *e = (S_8001C810 *) (D_8008AE5C + (idx << 4));
    u32 src = e->flags;
    u32 out = (src & 0x20000000) ? 0x80000000 : 0;
    u16 t;
    u32 f4;

    t = id;
    if (src & 0x10000000) {
        out |= 0x10000000;
    }
    if (src & 0x08000000) {
        out |= 0x20000000;
    }
    if (src & 0x00800000) {
        out |= 0x11000000;
    }
    if (src & 0x40000000) {
        out |= 0x40000000;
    }
    out |= src & 0x06000000;
    func_80046584(D_8008AE70[e->f4]);
    t = func_80046EFC(t, p[1], p[2], p[3], out);
    out = t;
    if (out == 0xFFFF) {
        return 0xFFFF;
    }
    func_80046584(D_8008AE70[0]);
    *(u16 *) (p + 4) = id;
    f4 = e->f4;
    *(u16 *) (p + 6) = t;
    *(u32 *) (p + 8) = f4;
    return out;
}
