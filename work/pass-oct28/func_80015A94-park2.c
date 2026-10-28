#include "common.h"

typedef struct S_80015A94_Blk {
    u32 unk0;
    u32 unk4;
    u32 size;
    u8 padC[4];
} S_80015A94_Blk;

extern u8 *D_8008AD38;
extern u8 *D_8008AD3C;
extern u8 *D_8008AD4C;
extern u8 *D_8008AD40;
extern s32 D_80089F70;
extern s32 D_80089F6C;

extern void func_800162FC(void);
extern void func_8001628C(u8 *p);
extern void func_80016264(u8 *p);
extern void func_800161DC(u8 *p);
extern void *memset(void *dst, s32 c, u32 n);

void func_80015A94(u32 a0) {
    u8 *p;
    u8 *blk;
    u8 *node;
    u8 *next;
    u8 *prev;
    u32 size;
    u32 i;
    u8 *pp;

    p = D_8008AD38 - (a0 << 4);

    if (a0 == 0) {
        return;
    }
    if (p < D_8008AD3C) {
        return;
    }
    if (*p == 0) {
        return;
    }

    func_800162FC();
    func_8001628C(p);
    *p = 0;
    func_80016264(p);

    blk = *(u8 **) (p + 4);
    size = *(u32 *) (p + 8);

    D_80089F70 -= 1;
    D_80089F6C -= size;
    memset(blk, 0xFF, size);
    *(u32 *) (blk + 8) = size;

    node = D_8008AD4C;
    if (blk < node) {
        if (node != (u8 *) -1) {
            *(u8 **) node = blk;
            *(u8 **) (blk + 4) = node;
        } else {
            *(u8 **) (blk + 4) = 0;
        }
        *(u8 **) blk = 0;
        D_8008AD4C = blk;
        goto inserted;
    }

    while (node < blk && *(u8 **) (node + 4) != 0) {
        node = *(u8 **) (node + 4);
    }
    if (*(u8 **) (node + 4) == 0) {
        if (node < blk) {
            *(u8 **) (node + 4) = blk;
            *(u8 **) blk = node;
            *(u8 **) (blk + 4) = 0;
            goto inserted;
        }
    }
    next = *(u8 **) node;
    *(u8 **) (blk + 4) = node;
    *(u8 **) blk = next;
    next = *(u8 **) node;
    *(u8 **) (next + 4) = blk;
    *(u8 **) node = blk;

inserted:
    prev = *(u8 **) (blk + 4);
    next = *(u8 **) blk;

    if (prev != 0 && (u8 *) blk + *(u32 *) (blk + 8) == prev) {
        *(u32 *) (blk + 8) += *(u32 *) (prev + 8);
        pp = *(u8 **) (prev + 4);
        if (pp != 0) {
            *(u8 **) pp = blk;
            *(u8 **) (blk + 4) = *(u8 **) (pp + 4);
            memset(pp, 0xFF, 0x10);
        } else {
            *(u8 **) (blk + 4) = 0;
            memset(prev, 0xFF, 0x10);
        }
    }

    if (next != 0 && (u8 *) next + *(u32 *) (next + 8) == (u8 *) blk) {
        prev = *(u8 **) (blk + 4);
        *(u32 *) (next + 8) += *(u32 *) (blk + 8);
        *(u8 **) (next + 4) = prev;
        if (prev != 0) {
            *(u8 **) prev = next;
        }
        memset(blk, 0xFF, 0x10);
        blk = 0;
    }

    node = D_8008AD4C;
    while (*(u8 **) (node + 4) != 0) {
        node = *(u8 **) (node + 4);
    }
    D_8008AD40 = node;

    if (next != 0) {
        func_800161DC(next);
    }
    if (prev != 0) {
        func_800161DC(prev);
    }
    if (blk != 0) {
        func_800161DC(blk);
    }
    func_800162FC();
}
