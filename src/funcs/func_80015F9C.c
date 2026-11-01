#include "common.h"

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    u32 size;
} Node;

extern Node *D_8008AD4C;
extern Node *D_8008AD40;
extern u8 *D_8008AD38;
extern s32 D_8008AD48;

void func_80016204(Node *);
void func_800161DC(Node *);
void func_8001628C(u8 *);
void func_80016264(u8 *);
void func_800162FC(void);
s32 func_80015D38(u32);
void func_80034D4C(void *a0, void *a1, s32 a2);

s32 func_80015F9C(void) {
    Node *e;
    Node *next;
    Node *dst;
    u32 size;
    u8 *src;
    u8 *h;
    s32 idx;

    if (D_8008AD48 > 0) {
        return 1;
    }
    if (D_8008AD4C == (Node *) -1) {
        return 0;
    }
    if (D_8008AD4C->prev == NULL && D_8008AD4C->next == NULL) {
        return 0;
    }
    func_800162FC();
    e = D_8008AD4C;
    if (e->next != NULL) {
        do {
            next = e->next;
            size = e->size;
            func_80016204(e);
            if (next != NULL) {
                func_80016204(next);
            }
            src = (u8 *) e + size;
            idx = func_80015D38((u32) src);
            dst = e;
            if (idx == 0) {
                return 1;
            }
            h = D_8008AD38 - idx * 16;
            func_8001628C(h);
            if (src < (u8 *) e + *(u32 *) (h + 8)) {
                u32 *s = (u32 *) src;
                u32 *d = (u32 *) dst;
                s32 n = *(u32 *) (h + 8) >> 2;
                while (n-- != 0) {
                    *d++ = *s++;
                }
            } else {
                func_80034D4C(dst, src, *(u32 *) (h + 8));
            }
            *(Node **) (h + 4) = dst;
            func_80016264(h);
            e = (Node *) (*(u8 **) (h + 4) + *(u32 *) (h + 8));
            e->next = next;
            e->prev = NULL;
            e->size = size;
            if (e->next != NULL) {
                e->next->prev = e;
                if ((Node *) ((u8 *) e + e->size) == e->next) {
                    e->size += e->next->size;
                    if (e->next->next != NULL) {
                        e->next->next->prev = e;
                        e->next = e->next->next;
                    } else {
                        e->next = NULL;
                    }
                }
            }
            D_8008AD4C = e;
            func_800161DC(e);
            if (e->next != NULL) {
                func_800161DC(e->next);
            }
            func_800162FC();
        } while (e->next != NULL);
    }
    e = D_8008AD4C;
    while (e->next != NULL) {
        e = e->next;
    }
    D_8008AD40 = e;
    return 0;
}
