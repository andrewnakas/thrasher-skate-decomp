#include "common.h"

typedef struct {
    u16 base;
    u16 first;
} Range_80038610;

extern u16 D_80082280[];
extern Range_80038610 D_8008A670[2];
extern char D_8008A67C[];

s32 func_80038610(u8 c) {
    s32 idx;
    u8 sub;
    u32 code;
    u32 hi;
    s32 off;
    u8 unused[2];

    idx = 0;
    sub = idx;
    if ((u8) (c - 0x20) < 0x10) {
        sub = 1;
    } else if ((u8) (c - 0x30) < 0xA) {
    } else if ((u8) (c - 0x3A) < 0x7) {
        sub = 0xB;
    } else if ((u8) (c - 0x41) < 0x1A) {
        idx = 1;
    } else if ((u8) (c - 0x5B) < 0x6) {
        sub = 0x25;
    } else if ((u8) (c - 0x61) < 0x1A) {
        idx = 2;
    } else if ((u8) (c - 0x7B) < 0x4) {
        sub = 0x3F;
    } else {
        printf(D_8008A67C, c);
        return 0;
    }

    if (sub) {
        u16 *tbl = D_80082280;
        s32 cc = c;
        off = sub + 0x1F;
        code = tbl[cc - off];
    } else {
        code = D_8008A670[idx].base + c - D_8008A670[idx].first;
    }
    hi = (code >> 8) & 0xFF;
    code = (code << 8) | hi;
    return (u16) code;
}
