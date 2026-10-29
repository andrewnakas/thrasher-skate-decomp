#include "common.h"

typedef struct Obj {
    u8 pad0[8];
    struct Obj *child;
    u8 pad1[0x34];
    struct Obj *next;
} Obj;

void func_8002AEF4(Obj *);

void func_8002B0E0(Obj *arg0) {
    Obj *p;

    p = arg0->child;
    while (p != 0) {
        func_8002AEF4(p);
        p = p->next;
    }
}
