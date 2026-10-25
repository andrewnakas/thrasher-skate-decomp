#include "common.h"

typedef struct Node {
    u8 pad0[4];
    struct Node *next;
    u32 ofs;
} Node;

extern Node *D_8008AD4C;
extern u8 *D_8008AD38;
extern u8 *D_8008AD3C;

void func_80016204(Node *);
void func_8001628C(u8 *);
s32 func_80015D38(u32);
s32 sprintf(u8 *, const char *, ...);

void func_800162FC(void) {
    u8 buf[0x100];
    Node *e;
    s32 i;
    u8 *p;

    i = 0;
    e = D_8008AD4C;
    if (e != (Node *)-1 && e != NULL) {
        do {
            func_80016204(e);
            if (e->next != NULL && *(Node **)e->next != e) {
                sprintf(buf, "ZMEMDMM: Links do not match at %x\n", e);
                return;
            }
            e = e->next;
        } while (e != NULL);
    }
    if (D_8008AD3C != D_8008AD38) {
        do {
            p = D_8008AD38 - (++i) * 16;
            func_8001628C(p);
        } while (D_8008AD3C < p);
    }
    e = D_8008AD4C;
    if (e->next != NULL) {
        do {
            if (!func_80015D38((u32)((u8 *)e + e->ofs))) break;
            e = e->next;
        } while (e->next != NULL);
    }
}
