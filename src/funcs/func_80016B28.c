#include "common.h"

extern s32 D_8008AD88;
extern s32 D_8008AD90;
extern s32 D_8008AD94;
extern s16 D_8008AD74;
extern s16 D_8008AD76;
extern s16 D_8008AD78;
extern s16 D_8008AD7A;

s32 func_80015E8C(s32);
void func_80015F10(s32);
void func_800387C8(void);
u8 *func_80019518(s32);
void func_800398B0(u8 *, s32, s32);
void func_8001954C(s32);
void func_80038864(s32, s32, s32, s32, s32, s32, s32);

void func_80016B28(void) {
    u8 *rec;
    u8 *p;
    u8 created;
    u16 v;

    if (D_8008AD90 == 0) {
        D_8008AD90 = func_80015E8C(D_8008AD94);
        created = 0;
    } else {
        created = 1;
    }
    rec = (u8 *)D_8008AD90 + D_8008AD88 * 0x50;
    func_800387C8();
    v = *(u16 *)(rec + 4);
    switch (v) {
    case 1:
        p = func_80019518(*(s32 *)rec);
        func_800398B0(p, *(u16 *)(p + 4), *(u16 *)(p + 6));
        func_8001954C(*(s32 *)rec);
        break;
    case 2:
    case 3:
    case 4:
        break;
    default:
        func_80038864(*(s32 *)(rec + 0xC), 0, 0, D_8008AD74, D_8008AD76,
                      D_8008AD78, D_8008AD7A);
        break;
    }
    if (created == 0) {
        D_8008AD90 = 0;
        func_80015F10(D_8008AD94);
    }
}
