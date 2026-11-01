#include "common.h"

typedef struct Free_80015760 {
    struct Free_80015760 *prev;
    struct Free_80015760 *next;
    s32 size;
    s32 csum;
} Free_80015760;

typedef struct {
    u8 used;
    u8 lock;
    u8 b2;
    u8 b3;
    u8 *ptr;
    s32 size;
    s32 csum;
} Handle_80015760;

extern s32 func_80015D88(void);
extern void func_800161DC(Free_80015760 *);
extern void func_80016204(Free_80015760 *);
extern void func_80016264(Handle_80015760 *);
extern void func_800162FC(void);
extern void *memset(void *, s32, u32);
extern u8 *D_8008AD38;
extern u8 *D_8008AD3C;
extern u8 *D_8008AD40;
extern Free_80015760 *D_8008AD4C;
extern s32 D_8008AD50;

s32 func_80015760(Free_80015760 *blk, s32 size) {
    s32 h;
    Handle_80015760 *e;
    Free_80015760 *f;
    Free_80015760 *next;
    Free_80015760 *prev;
    Free_80015760 *nf;
    s32 bsize;
    Free_80015760 *p;
    Free_80015760 *n;
    u8 *end;

    h = func_80015D88();
    if (h == 0) {
        goto end;
    }
    e = (Handle_80015760 *) (D_8008AD38 - h * 16);
    if (D_8008AD3C < (u8 *) blk + size + 0x10) {
        if (D_8008AD50 == 1) {
            f = D_8008AD4C;
            if (f != (Free_80015760 *) -1) {
                func_80016204(f);
                while (f->next != NULL) {
                    f = f->next;
                }
                f->size += 0x10;
                func_800161DC(f);
                D_8008AD50 = 0;
                D_8008AD3C += 0x10;
            }
        }
    end:
        return 0;
    }
    D_8008AD50 = 0;
    e->used = 1;
    e->lock = 0;
    e->b2 = 0;
    e->ptr = (u8 *) blk;
    e->size = size;
    func_80016264(e);
    end = e->ptr + size;
    if (D_8008AD40 < end) {
        D_8008AD40 = end;
    }
    p = blk->prev;
    n = blk->next;
    bsize = blk->size;
    if (D_8008AD40 == D_8008AD3C) {
        D_8008AD4C = (Free_80015760 *) -1;
        next = prev = NULL;
        nf = NULL;
    } else {
        prev = p;
        nf = (Free_80015760 *) (e->ptr + size);
        next = n;
        if ((u8 *) nf + 0x10 > (u8 *) blk + bsize) {
            e->size = bsize;
            func_80016264(e);
            if (prev == NULL) {
                if (next == NULL) {
                    D_8008AD4C = (Free_80015760 *) -1;
                } else {
                    D_8008AD4C = next;
                    next->prev = NULL;
                }
            } else if (next == NULL) {
                prev->next = NULL;
            } else {
                prev->next = next;
                next->prev = prev;
            }
            nf = NULL;
        } else {
            nf->prev = prev;
            nf->next = next;
            nf->size = bsize - size;
            if (nf->prev != NULL) {
                nf->prev->next = nf;
            }
            if (nf->next != NULL) {
                nf->next->prev = nf;
            }
            if (nf->prev == NULL) {
                D_8008AD4C = nf;
            }
        }
    }
    memset(e->ptr, 0xFF, e->size);
    if (prev != NULL) {
        func_800161DC(prev);
    }
    if (next != NULL) {
        func_800161DC(next);
    }
    if (nf != NULL) {
        func_800161DC(nf);
    }
    func_800162FC();
    return h;
}
