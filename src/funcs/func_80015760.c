#include "common.h"

typedef struct FreeBlock {
    struct FreeBlock *previous;
    struct FreeBlock *next;
    s32 size;
    u32 check;
} FreeBlock;

typedef struct {
    u8 active, f1, f2, pad3;
    u8 *data;
    s32 size;
    u32 check;
} Entry;

extern s32 func_80015D88(void);
extern void func_800161DC(FreeBlock *);
extern void func_80016204(FreeBlock *);
extern void func_80016264(Entry *);
extern void func_800162FC(void);
extern void *memset(void *, s32, u32);
extern u8 *D_8008AD38;
extern u32 D_8008AD3C;
extern u32 D_8008AD40;
extern FreeBlock *D_8008AD4C;
extern s32 D_8008AD50;

s32 func_80015760(FreeBlock *block, s32 size) {
    Entry *entry;
    FreeBlock *tail;
    FreeBlock *remainder;
    FreeBlock *previous;
    FreeBlock *next;
    FreeBlock *old_next;
    FreeBlock *old_previous;
    FreeBlock *preceding;
    FreeBlock *following;
    s32 old_size;
    s32 handle;
    u32 end;
    u32 minimum_end;

    handle = func_80015D88();
    if (handle == 0) {
        goto failure;
    }
    entry = (Entry *)(D_8008AD38 - handle * 0x10);
    if (D_8008AD3C < (u32)((u8 *)block + size + 0x10)) {
        if (D_8008AD50 == 1) {
            tail = D_8008AD4C;
            if (tail != (FreeBlock *)-1) {
                func_80016204(tail);
                if (tail->next != NULL) {
                    do {
                        tail = tail->next;
                    } while (tail->next != NULL);
                }
                tail->size += 0x10;
                func_800161DC(tail);
                D_8008AD50 = 0;
                D_8008AD3C += 0x10;
            }
        }
    failure:
        return 0;
    }
    D_8008AD50 = 0;
    entry->active = 1;
    entry->f1 = 0;
    entry->f2 = 0;
    entry->data = (u8 *)block;
    entry->size = size;
    func_80016264(entry);
    end = (u32)entry->data + size;
    if (D_8008AD40 < end) {
        D_8008AD40 = end;
    }
    old_previous = block->previous;
    old_next = block->next;
    old_size = block->size;
    if (D_8008AD40 == D_8008AD3C) {
        D_8008AD4C = (FreeBlock *)-1;
        previous = NULL;
        next = NULL;
        remainder = NULL;
    } else {
        previous = old_previous;
        remainder = (FreeBlock *)(entry->data + size);
        next = old_next;
        minimum_end = (u32)((u8 *)remainder + 0x10);
        if ((u32)((u8 *)block + old_size) < minimum_end) {
            entry->size = old_size;
            func_80016264(entry);
            if (previous == NULL) {
                if (next == NULL) {
                    D_8008AD4C = (FreeBlock *)-1;
                    remainder = NULL;
                } else {
                    D_8008AD4C = next;
                    next->previous = NULL;
                }
            } else {
                if (next == NULL) {
                    previous->next = NULL;
                } else {
                    previous->next = next;
                    next->previous = previous;
                }
            }
            remainder = NULL;
        } else {
            remainder->previous = previous;
            remainder->next = next;
            remainder->size = old_size - size;
            preceding = remainder->previous;
            if (preceding != NULL) {
                preceding->next = remainder;
            }
            following = remainder->next;
            if (following != NULL) {
                following->previous = remainder;
            }
            if (remainder->previous == NULL) {
                D_8008AD4C = remainder;
            }
        }
    }
    memset(entry->data, 0xFF, entry->size);
    if (previous != NULL) {
        func_800161DC(previous);
    }
    if (next != NULL) {
        func_800161DC(next);
    }
    if (remainder != NULL) {
        func_800161DC(remainder);
    }
    func_800162FC();
    return handle;
}
