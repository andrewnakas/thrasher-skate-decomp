#include "common.h"

typedef struct Node {
    u32 unk0;
    s32 unk4;
    struct Node *next;
} Node;

typedef struct {
    s32 used;
    Node node;
} Slot;

typedef struct {
    u16 flags;
    u8 state;
    u8 pad3;
    u8 pad4[8];
    s32 unkC;
    u8 pad10[8];
    s32 unk18;
    u8 pad1C[4];
    s32 unk20;
    s32 unk24;
    u8 pad28[4];
    Node head;
} Hdl;

extern s32 D_8008A9C8;
extern s32 D_8008B44C;
extern Slot D_800B124C[16];
extern s8 D_800108B0[];
extern s8 D_8008A9D4[];

Node *func_80051E14(s32, s32);
void func_80051F3C(Node *);
u32 func_80051B9C(Hdl *, s32, s32 *, s32);

s32 func_80051354(Hdl *s, s32 a, s32 b) {
    Node *new;
    Node *n;
    Node *p;
    s32 tmp;
    s32 i;

    if (D_8008A9C8 == 0) {
        printf(D_800108B0, D_8008A9D4, 0x357);
        exit(1);
    }
    if (s->state == 8) {
        return 0x208;
    }
    new = func_80051E14(a, b);
    if (new != NULL) {
    if ((new->unk0 & 0xFFFFFF) != (*(u32 *) s->head.unk0 & 0xFFFFFF)) {
        return 0x206;
    }
    p = &s->head;
    if (s->flags & 0x1000) {
        s->unk18 = s->unk24;
        func_80051F3C((Node *) s->head.unk0);
        s->head.unk0 = (u32) new;
        p->unk4 = 0;
        p->next = NULL;
        s->unk20 = 0;
        if (func_80051B9C(s, s->unkC - s->unk24, &tmp, 0) < (u32) (s->unkC - s->unk24)) {
            s->flags |= 0x1000;
            s->unk24 = tmp;
        } else {
            s->unk24 = 0;
            s->flags &= ~0x1000;
        }
    } else {
        i = D_8008B44C;
        do {
            if (D_800B124C[i].used == 0) {
                D_800B124C[i].used = 1;
                n = &D_800B124C[i].node;
                D_8008B44C = i + 1;
                if (i + 1 == 16) {
                    D_8008B44C = 0;
                }
                goto found;
            }
            i++;
            if (i == 16) {
                i = 0;
            }
        } while (i != D_8008B44C);
        n = NULL;
    found:
        if (n == NULL) {
            printf(D_800108B0, D_8008A9D4, 0x385);
            exit(1);
        }
        n->unk0 = (u32) new;
        n->unk4 = 0;
        if (b & 1) {
            n->next = p->next;
        } else {
            while (p->next != NULL) {
                p = p->next;
            }
            n->next = NULL;
        }
        p->next = n;
    }
    return 0;
    }
    return 0x201;
}
