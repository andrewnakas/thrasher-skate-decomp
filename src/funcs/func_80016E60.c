#include "common.h"

extern u8 *D_8008AD90;
extern s32 D_8008AD94;
extern s32 D_8008AD88;

u8 *func_80015E8C(s32);
void func_80015F10(s32);

void func_80016E60(u16 arg0, s32 arg1) {
    u8 made;
    u8 *p;

    if (D_8008AD90 == NULL) {
        D_8008AD90 = func_80015E8C(D_8008AD94);
        made = 0;
    } else {
        made = 1;
    }
    p = D_8008AD90 + D_8008AD88 * 0x50;
    switch (arg0) {
    case 1:
        *(u16 *)(p + 4) = 1;
        *(s32 *)(p + 0) = arg1;
        break;
    case 2:
        *(u16 *)(p + 4) = 2;
        *(s32 *)(p + 0) = arg1;
        break;
    case 3:
        *(u16 *)(p + 4) = 3;
        *(s32 *)(p + 0) = arg1;
        break;
    case 4:
        *(u16 *)(p + 4) = 4;
        break;
    case 5:
        *(s32 *)(p + 0xC) = arg1;
        break;
    case 6:
        if (arg1 != 0) {
            *(u16 *)(p + 0x10) |= 2;
        } else {
            *(u16 *)(p + 0x10) &= 0xFFFD;
        }
        break;
    case 7:
        if (arg1 != 0) {
            *(u16 *)(p + 0x18) |= 2;
        } else {
            *(u16 *)(p + 0x18) &= 0xFFFD;
        }
        break;
    case 14:
        *(u16 *)(p + 0x24) = arg1;
        break;
    case 8:
        if (arg1 != 0) {
            *(u16 *)(p + 0x18) |= 1;
        } else {
            *(u16 *)(p + 0x18) &= 0xFFFE;
        }
        break;
    case 9:
        if (arg1 != 0) {
            *(u16 *)(p + 0x18) |= 4;
        } else {
            *(u16 *)(p + 0x18) &= 0xFFFB;
        }
        break;
    case 12:
        if (arg1 != 0) {
            *(u16 *)(p + 0x18) |= 8;
        } else {
            *(u16 *)(p + 0x18) &= 0xFFF7;
        }
        break;
    case 13:
        if (arg1 != 0) {
            *(u16 *)(p + 0x18) |= 0x10;
        } else {
            *(u16 *)(p + 0x18) &= 0xFFEF;
        }
        break;
    case 10:
        *(s32 *)(p + 0x20) = arg1;
        break;
    case 11:
        *(s32 *)(p + 0x1C) = arg1;
        break;
    case 16:
        *(s32 *)(p + 0x34) = arg1;
        break;
    case 15:
        *(s32 *)(p + 0x30) = arg1;
        break;
    case 17:
        if (arg1 != 0) {
            *(u16 *)(p + 0x40) |= 2;
        } else {
            *(u16 *)(p + 0x40) &= 0xFFFD;
        }
        break;
    case 18:
        if (arg1 != 0) {
            *(u16 *)(p + 0x40) |= 1;
        } else {
            *(u16 *)(p + 0x40) &= 0xFFFE;
        }
        break;
    case 19:
        if (arg1 != 0) {
            *(u16 *)(p + 0x40) |= 4;
        } else {
            *(u16 *)(p + 0x40) &= 0xFFFB;
        }
        break;
    case 22:
        *(s32 *)(p + 0x3C) = arg1;
        break;
    case 20:
        *(s32 *)(p + 0x48) = arg1;
        break;
    case 21:
        *(s32 *)(p + 0x44) = arg1;
        break;
    case 23:
        *(s32 *)(p + 0x4C) = arg1;
        break;
    }
    if (made == 0) {
        D_8008AD90 = NULL;
        func_80015F10(D_8008AD94);
    }
}
