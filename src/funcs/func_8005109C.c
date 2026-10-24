#include "common.h"

extern s32 D_8008A9C8;
extern s8 D_8008A9D4[];
extern u8 D_800108B0[];
extern void func_80034BD8();
extern void func_80051F3C();
extern void func_80051AE4();

typedef struct Node_8005109C {
    s32 unk0;
    u8 pad4[4];
    struct Node_8005109C *unk8;
} Node_8005109C;

typedef struct S_8005109C {
    u16 flags;
    u8 type;
    u8 pad3;
    s32 unk4;
    u8 pad8[0x24];
    Node_8005109C first;
} S_8005109C;

s32 func_8005109C(S_8005109C *s) {
    Node_8005109C *n;
    Node_8005109C *next;

    if (!D_8008A9C8) {
        printf(D_800108B0, D_8008A9D4, 0x2B8);
        exit(1);
    }

    if (s->type != 8) {
        if (!(s->flags & 0x4000)) {
            func_80034BD8(s->unk4);
        }

        for (n = &s->first; n; n = next) {
            next = n->unk8;
            func_80051F3C(n->unk0);
            func_80051AE4(n);
        }

        s->type = 8;
    }

    return 0;
}
