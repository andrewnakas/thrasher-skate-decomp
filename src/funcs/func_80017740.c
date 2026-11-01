#include "common.h"

extern u32 D_8008AD64;

extern u8 *func_80019630(u32 a0);
extern u8 *func_80019670(u32 a0);
extern s32 func_80036A78(u32 a0, u32 a1, u32 a2);
extern u8 *func_80036B18(u32 a0);
extern u8 *func_800159D8(u8 *a0);
extern u8 *func_80015E8C(u8 *a0);
extern void func_80036BF4(u32 a0, u8 *a1);
extern void func_80015F10(u8 *a0);
extern u8 *func_80019444(void);
extern u8 *func_80019518(u8 *a0);
extern void func_80039D1C(u8 *a0);
extern void func_8001954C(u8 *a0);

s32 func_80017740(u16 id, s32 flag) {
    u8 *p;
    u8 *w;
    u8 *res;
    u32 slot;
    u32 val;
    u32 sel;

    if (id & 0xE000) {
        return 0;
    }
    slot = id;
    res = func_80019630(slot);
    if (res != NULL) {
        return (s32) res;
    }
    p = func_80019670(slot);
    sel = 1;
    if (p != NULL) {
        if (*(u16 *) (p + 2) & 1) {
            flag = sel;
        }
        slot = *(u32 *) (p + 8);
        val = *(u32 *) (p + 0xC);
    } else {
        sel = 0;
        val = sel;
        if (func_80036A78(D_8008AD64, slot, sel) != 0) {
            return 0;
        }
        slot = (u32) func_800159D8(func_80036B18(D_8008AD64));
        if (slot == 0) {
            return 0;
        }
        func_80036BF4(D_8008AD64, func_80015E8C((u8 *) slot));
        func_80015F10((u8 *) slot);
    }
    res = func_80019444();
    if (res == NULL) {
        return 0;
    }
    *(u16 *) (res + 2) = 0;
    if (flag != 0) {
        /* both arms identical: the extra use of sel sets its s-reg priority */
        if (sel) {
            *(u16 *) (res + 2) = 1;
        } else {
            *(u16 *) (res + 2) = 1;
        }
    }
    if (sel != 0) {
        *(u16 *) (res + 2) |= 2;
    }
    *(u16 *) res = (u16) id;
    *(u32 *) (res + 8) = slot;
    *(u32 *) (res + 0xC) = val;
    w = func_80019518(res);
    if (*(u32 *) (w + 0xC) != 0) {
        func_80039D1C(w + *(u32 *) (w + 0xC));
    }
    func_8001954C(res);
    return (s32) res;
}
