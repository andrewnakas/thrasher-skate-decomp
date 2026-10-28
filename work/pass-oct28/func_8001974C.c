#include "common.h"

extern s32 func_80019630(u32);
extern u8 *func_80019670(u32);
extern s32 func_80036A78(u32, u32, s32);
extern u32 func_80036B18(u32);
extern u8 *func_800159D8(u32);
extern void func_80036BF4(u32, s32);
extern s32 func_80015E8C(u8 *);
extern void func_80015F10(u8 *);
extern u8 *func_80019444(void);
extern u32 D_8008AD64;

u8 *func_8001974C(u32 a0, s32 a1) {
    u8 *r;
    u8 *p;
    u32 s0;
    u32 s2;
    s32 flag;
    u32 key;

    if ((a0 & 0xE000) != 0xA000) {
        return 0;
    }
    key = a0 & 0xFFFF;
    r = (u8 *) func_80019630(key);
    if (r != 0) {
        return r;
    }
    p = func_80019670(key);
    if (p != 0) {
        flag = 1;
        s0 = *(u32 *) (p + 8);
        s2 = *(u32 *) (p + 0xC);
    } else {
        flag = 0;
        s2 = 0;
        if (func_80036A78(D_8008AD64, key, 0) != 0) {
            return 0;
        }
        s0 = func_800159D8(func_80036B18(D_8008AD64));
        if (s0 == 0) {
            return 0;
        }
        func_80036BF4(D_8008AD64, func_80015E8C((u8 *) s0));
        func_80015F10((u8 *) s0);
    }
    r = func_80019444();
    if (r == 0) {
        return 0;
    }
    *(u16 *) (r + 2) = (a1 != 0) ? 1 : 0;
    if (flag != 0) {
        *(u16 *) (r + 2) |= 2;
    }
    *(u16 *) (r + 0) = a0;
    *(u32 *) (r + 8) = s0;
    *(u32 *) (r + 0xC) = s2;
    return r;
}
