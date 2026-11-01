/* p is reused: first the allocated buffer, then the copy length. */
#include "common.h"

typedef struct {
    u8 pad0[4];
    s32 size;
    u8 pad8[2];
    u16 unkA;
    u8 data[1];
} Chunk29488;

Chunk29488 *func_8001D5B0(s32 a0, s32 tag, s32 n);
s32 func_80034C20(s32);
void func_80034D4C(s32 a0, void *a1, s32 a2);
extern s32 D_8008AFA8;
extern s32 D_8008AFAC;

void func_80029488(s32 arg0, s32 arg1, u8 *arg2) {
    s32 n;
    Chunk29488 *c;
    s32 p;
    s32 buf[2];

    if (*(s32 *) (arg2 + 0x18) & 0x800000) {
        c = func_8001D5B0(arg0, 0x4954414D, 1);
        n = c->size - 4;
        D_8008AFAC = c->unkA;
        p = func_80034C20(n);
        D_8008AFA8 = p;
        p = n;
        func_80034D4C(D_8008AFA8, c->data, p);
    }
}
