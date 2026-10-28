#include "common.h"

extern u32 *D_8008B048;

void func_8002C284(s16 *tab, u8 *node);

void func_8002C284(s16 *tab, u8 *node) {
    u8 *c;
    s32 v;

    if (node == 0) {
        return;
    }
    if (node[0] == 0x6C) {
        goto emit;
    }
    if (node[0] != 0x70) {
        return;
    }
    v = (tab[node[1]] + *(s16 *) (node + 2)) << 16;
    if (v < -0x100) {
        c = *(u8 **) (node + 8);
        if (c != 0) {
            func_8002C284(tab, c);
            return;
        }
        goto emit;
    }
    if (v >= 0x101) {
        c = *(u8 **) (node + 0xC);
        if (c != 0) {
            func_8002C284(tab, c);
            return;
        }
        goto emit;
    }
    c = *(u8 **) (node + 8);
    if (c != 0) {
        func_8002C284(tab, c);
    } else {
        *D_8008B048 = *(u32 *) (node + 4);
        D_8008B048 += 1;
    }
    c = *(u8 **) (node + 0xC);
    if (c != 0) {
        func_8002C284(tab, c);
        return;
    }
emit:
    *D_8008B048 = *(u32 *) (node + 4);
    D_8008B048 += 1;
}
