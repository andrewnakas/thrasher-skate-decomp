#include "common.h"

typedef struct FreeBlock {
    struct FreeBlock *previous;
    struct FreeBlock *next;
    s32 size;
    u32 check;
} FreeBlock;

extern s32 func_80015760(FreeBlock *, s32);
extern void func_800162FC(void);
extern s32 D_80089F68;
extern s32 D_80089F6C;
extern s32 D_80089F70;
extern FreeBlock *D_8008AD4C;

s32 func_800159D8(u32 requested) {
    s32 remainder;
    s32 result;
    u32 size;
    FreeBlock *block;

    if (D_80089F68 == 0) {
        goto failure;
    }
    result = 0;
    if (requested == 0) {
        goto done;
    }
    func_800162FC();
    block = D_8008AD4C;
    if (block == (FreeBlock *)-1) {
    failure:
        result = 0;
        goto done;
    }
    if (requested < 0x10U) {
        requested = 0x10;
    }
    size = requested;
    remainder = size & 3;
    if (remainder != 0) {
        remainder -= 4;
        size -= remainder;
    }
    D_80089F70++;
    D_80089F6C += size;
next_block:
    if ((u32)block->size < size) {
        block = block->next;
        result = 0;
        if (block != NULL) {
            goto next_block;
        }
        goto done;
    }
    result = func_80015760(block, size);
done:
    return result;
}
