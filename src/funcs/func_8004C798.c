#include "common.h"

typedef struct {
    u8 f0;
    u8 f1;
    u16 f2;
    u16 f4;
    u16 pad6;
    s32 f8;
} Slot;

typedef struct {
    u8 type;
    u8 cnt;
    u8 pad2[10];
} Sub;

typedef struct {
    u8 n;
    u8 pad1[3];
    Sub *ptr;
} Ent;

typedef struct {
    u8 flags;
    u8 count;
    u16 base;
    u8 bits[8];
    Ent ent[1];
} Seq;

extern u8 D_8008B408[4];
extern char D_800107F8[];
extern char D_8008A950[];

u32 func_80011B48(void);
u32 func_8004CCA0(Seq *, u32);
u32 func_8004CD28(Slot *, Seq *, u32, Sub *, u32 *, u32 *);
s32 func_8004FECC(u16, u32);
void func_800511C0(s32, s32, u8);
void func_80051354(s32, s32, u8);
void func_800515FC(s32);

s32 func_8004C798(u8 id, Seq *seq) {
    Slot *slot;
    Seq *s;
    Ent *e;
    s32 err;
    u32 a;
    u32 b;
    u32 j;
    u32 k;
    u32 idx;
    u32 n;
    u32 r;

    slot = &((Slot *) D_8008B408)[id];
    err = 0;
    if (slot->f8 == 0) {
        printf(D_800107F8, D_8008A950, 0x1FB);
        exit(1);
    }
    switch (seq->flags & 1) {
    case 0:
        s = seq;
        k = func_80011B48() % s->count;
        for (n = 0; n < s->count; n++) {
            if (!((s->bits[k >> 3] >> (k & 7)) & 1)) {
                break;
            }
            if (++k == s->count) {
                k = 0;
            }
        }
        if (n == s->count) {
            if (seq->flags & 0x20) {
                err = 0x602;
            } else {
                for (j = 0; j < 8; j++) {
                    s->bits[j] = 0;
                }
            }
        }
        if (!(seq->flags & 0x20)) {
            a = s->base + k;
            if (a == slot->f4) {
                if (s->count >= 2) {
                    k++;
                    k %= s->count;
                } else {
                    err = 0x602;
                }
            }
        }
        if (err == 0) {
            a = s->base + k;
            func_800511C0(slot->f8, func_8004FECC(slot->f2, a), slot->f0);
            slot->f4 = a;
            s->bits[k >> 3] |= 1 << (k & 7);
        }
        break;
    case 1:
        n = 0;
        j = 0;
        s = seq;
        for (; j < s->count; j++) {
            e = &s->ent[j];
            switch (e->ptr->type) {
            case 0:
                n += e->ptr->cnt;
                break;
            case 1:
            case 2:
                n++;
                break;
            default:
                printf(D_800107F8, D_8008A950, 0x23B);
                exit(1);
            }
        }
        if (n == 0) {
            goto fail;
        }
        k = func_80011B48() % n;
        idx = func_8004CCA0(s, k);
        if (seq->flags & 0x20) {
            for (j = 0; j < n; j++) {
                if (!((s->bits[idx >> 3] >> (idx & 7)) & 1)) {
                    break;
                }
                if (++k == n) {
                    k = 0;
                }
                idx = func_8004CCA0(s, k);
            }
            if (j == n) {
                err = 0x602;
            }
        }
        if (err == 0) {
            e = &s->ent[idx];
            r = func_8004CD28(slot, seq, idx, e->ptr, &a, &b);
            if (r == 0) {
                goto fail;
            }
            func_800511C0(slot->f8, func_8004FECC(slot->f2, a), slot->f0);
            slot->f4 = a;
            if (r >= 2) {
                func_80051354(slot->f8, func_8004FECC(slot->f2, b), slot->f0);
                slot->f4 = b;
            }
            for (j = 1; j < e->n; j++) {
                r = func_8004CD28(slot, seq, idx, &e->ptr[j], &a, &b);
                if (r != 0) {
                    func_80051354(slot->f8, func_8004FECC(slot->f2, a), slot->f0);
                    slot->f4 = a;
                    if (r >= 2) {
                        func_80051354(slot->f8, func_8004FECC(slot->f2, b), slot->f0);
                        slot->f4 = b;
                    }
                }
            }
        }
        break;
    fail:
        err = 0x602;
        break;
    }
    if (err == 0) {
        func_800515FC(slot->f8);
        slot->f1 = seq->flags & 0xC0;
    }
    return err;
}
