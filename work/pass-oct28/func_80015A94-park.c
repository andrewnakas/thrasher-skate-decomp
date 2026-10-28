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

    if (a0 == 0) {
        return;
    }

    p = D_8008AD38 - (a0 << 4);
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
    if (prev != 0) {
        i = *(u32 *) (blk + 8);
        if ((u8 *) ((u8 *) prev + i) != prev) {
            goto done;
        }
        next = *(u8 **) (prev + 4);
        i = *(u32 *) (((u8 *) prev) + i + 8);
        *(u32 *) (blk + 8) = i;
        if (*(u8 **) (prev + 4) != 0) {
            *(u8 **) (*(u8 **) (prev + 4)) = blk;
            *(u8 **) (blk + 4) = *(u8 **) (*(u8 **) (prev + 4) + 4);
            memset(*(u8 **) (blk + 4), 0, 0x10);
        } else {
            memset(prev, 0, 0x10);
            *(u8 **) (blk + 4) = 0;
        }
    }

done:
    (void) next;
    (void) prev;
}
