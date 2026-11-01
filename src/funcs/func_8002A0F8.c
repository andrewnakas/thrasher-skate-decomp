/* cflags: -fno-strength-reduce */
#include "common.h"

typedef struct Sub_8002A0F8 {
    u8 pad0[4];
    s32 a;
    u8 pad8[0x10];
} Sub_8002A0F8;

typedef struct Node_8002A0F8 {
    u8 pad0[0x1C];
    u16 n;
    u8 pad1E[0xA];
    s32 head;
    u8 pad2C[0x1C];
    Sub_8002A0F8 seg[3];
    u8 pad90[4];
    struct Node_8002A0F8 *next;
} Node_8002A0F8;

typedef struct {
    u8 pad0[4];
    Node_8002A0F8 *first;
} List_8002A0F8;

extern void func_8002A198(s32);
extern void func_8002A264(s32);
extern void func_8002AE2C(void);

void func_8002A0F8(List_8002A0F8 *l) {
    Node_8002A0F8 *n;
    s32 i;

    for (n = l->first; n != NULL; n = n->next) {
        func_8002A198(n->head);
        i = 0;
        while (i < n->n - 1) {
            i++;
            func_8002A264(n->seg[i].a);
        }
    }
    func_8002AE2C();
}
