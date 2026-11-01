#include "common.h"

typedef struct Node {
    u32 unk0;
    s32 unk4;
    struct Node *next;
} Node;

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
extern s8 D_800108B0[];
extern s8 D_8008A9D4[];

Node *func_80051E14(s32, s32);
void func_80051F3C(Node *);
void func_80051574(Hdl *, s32 *);
void func_80051AE4(Node *);
u32 func_80051B9C(Hdl *, s32, s32 *, s32);

s32 func_800511C0(Hdl *s, s32 a, s32 b) {
    Node *new;
    Node *n;
    Node *next;
    s32 state;
    s32 tmp;
    s32 ret;
    s32 st;

    if (D_8008A9C8 == 0) {
        printf(D_800108B0, D_8008A9D4, 0x2F1);
        exit(1);
    }
    if (s->state == 8) {
        return 0x208;
    }
    new = func_80051E14(a, b);
    if (new != NULL) {
        ret = 0x206;
        if ((new->unk0 & 0xFFFFFF) == (*(u32 *) s->head.unk0 & 0xFFFFFF)) {
            func_80051574(s, &state);
            for (n = &s->head; n != NULL; n = next) {
                next = n->next;
                func_80051F3C((Node *) n->unk0);
                func_80051AE4(n);
            }
            s->head.unk0 = (u32) new;
            s->head.unk4 = 0;
            s->head.next = NULL;
            s->unk18 = 0;
            s->flags &= ~0x2000;
            if (func_80051B9C(s, s->unkC, &tmp, 1) < (u32) s->unkC) {
                s->flags |= 0x1000;
                s->unk24 = tmp;
            } else {
                s->unk24 = 0;
                s->flags &= ~0x1000;
            }
            s->unk20 = 0;
            st = state;
            if (st == 2) {
                s->state = st;
            } else {
                s->state = 1;
            }
            return 0;
        }
        func_80051F3C(new);
    } else {
        ret = 0x201;
    }
    return ret;
}
