#include "common.h"

typedef struct FreeBlock {
    struct FreeBlock *previous;
    struct FreeBlock *next;
    s32 size;
    u32 check;
} FreeBlock;

extern void func_800161DC(FreeBlock *);
extern FreeBlock *func_80034C20(s32);
extern void *memset(void *, s32, u32);
extern s32 D_80089F68;
extern s32 D_80089F6C;
extern s32 D_80089F70;
extern FreeBlock *D_8008AD34;
extern u8 *D_8008AD38;
extern u32 D_8008AD3C;
extern u32 D_8008AD40;
extern s32 D_8008AD44;
extern s32 D_8008AD48;
extern FreeBlock *D_8008AD4C;
extern s32 D_8008AD50;

s32 func_80015684(s32 unused, s32 size) {
    s32 remainder;
    FreeBlock *block;
    u8 *end;

    if (D_80089F68 == 0) {
        remainder = size & 3;
        D_80089F6C = 0;
        D_80089F70 = 0;
        D_8008AD44 = size;
        if (remainder != 0) {
            remainder -= 4;
            D_8008AD44 = size - remainder;
        }
        block = func_80034C20(D_8008AD44);
        D_8008AD34 = block;
        if (block != NULL) {
            D_8008AD40 = (u32)block;
            D_8008AD48 = 0;
            D_8008AD50 = 0;
            end = (u8 *)block + D_8008AD44;
            D_8008AD38 = end;
            D_8008AD3C = (u32)end;
            memset(block, 0xFF, D_8008AD44);
            D_8008AD4C = D_8008AD34;
            D_8008AD34->previous = NULL;
            D_8008AD34->next = NULL;
            D_8008AD34->size = D_8008AD44 - sizeof(FreeBlock);
            func_800161DC(D_8008AD34);
            D_80089F68 = 1;
            return 0;
        }
    }
    return 1;
}
