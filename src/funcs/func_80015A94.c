#include "common.h"

typedef struct FreeBlock {
    struct FreeBlock *previous;
    struct FreeBlock *next;
    s32 size;
    u32 check;
} FreeBlock;

typedef struct {
    u8 active, f1, f2, pad3;
    FreeBlock *data;
    s32 size;
    u32 check;
} Entry;

extern void func_800161DC(FreeBlock *);
extern void func_80016264(Entry *);
extern void func_8001628C(Entry *);
extern void func_800162FC(void);
extern void *memset(void *, s32, u32);
extern s32 D_80089F6C;
extern s32 D_80089F70;
extern u8 *D_8008AD38;
extern u32 D_8008AD3C;
extern FreeBlock *D_8008AD40;
extern FreeBlock *D_8008AD4C;

void func_80015A94(s32 handle) {
    Entry *entry;
    FreeBlock *block, *node, *next, *previous, *adjacent;
    FreeBlock *following, *current, *old_previous, *tail, *insert_previous;
    s32 size;
    s32 block_size, previous_size;

    entry = (Entry *)(D_8008AD38 - handle * 0x10);
    if (handle != 0 && (u32)entry >= D_8008AD3C && entry->active != 0) {
        func_800162FC();
        func_8001628C(entry);
        entry->active = 0;
        func_80016264(entry);
        block = entry->data;
        size = entry->size;
        D_80089F70--;
        D_80089F6C -= size;
        memset(block, 0xFF, entry->size);
        node = D_8008AD4C;
        block->size = entry->size;
        if ((u32)block < (u32)node) {
            if (node != (FreeBlock *)-1) {
                node->previous = block;
                block->next = node;
            } else {
                block->next = NULL;
            }
            block->previous = NULL;
            D_8008AD4C = block;
        } else {
            while ((u32)node < (u32)block && node->next != NULL) {
                node = node->next;
            }
            if (node->next == NULL && (u32)node < (u32)block) {
                node->next = block;
                block->previous = node;
                block->next = NULL;
            } else {
                insert_previous = node->previous;
                block->next = node;
                block->previous = insert_previous;
                node->previous->next = block;
                node->previous = block;
            }
        }
        next = block->next;
        previous = block->previous;
        if (next != NULL) {
            block_size = block->size;
            adjacent = (FreeBlock *)((u8 *)block + block_size);
            if (adjacent == next) {
                next = next->next;
                block->size = block_size + adjacent->size;
                current = block->next;
                following = current->next;
                if (following != NULL) {
                    following->previous = block;
                    block->next = block->next->next;
                    memset(adjacent, 0xFF, 0x10);
                } else {
                    memset(current, 0xFF, 0x10);
                    block->next = NULL;
                }
            }
        }
        old_previous = block->previous;
        if (old_previous != NULL) {
            previous_size = old_previous->size;
            if ((FreeBlock *)((u8 *)old_previous + previous_size) == block) {
                next = block->next;
                old_previous->size = previous_size + block->size;
                block->previous->next = block->next;
                if (next != NULL) {
                    block->next->previous = block->previous;
                }
                memset(block, 0xFF, 0x10);
                block = NULL;
            }
        }
        tail = D_8008AD4C;
        if (tail->next != NULL) {
            do {
                tail = tail->next;
            } while (tail->next != NULL);
        }
        D_8008AD40 = tail;
        if (previous != NULL) {
            func_800161DC(previous);
        }
        if (next != NULL) {
            func_800161DC(next);
        }
        if (block != NULL) {
            func_800161DC(block);
        }
        func_800162FC();
    }
}
