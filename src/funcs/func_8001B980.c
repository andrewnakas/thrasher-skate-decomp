#include "common.h"

extern u16 D_8008AE14;
extern u16 D_8008AE16;

void *func_8002C3C0(s32, s32);
u8 *func_8002C3A0(s32);
void func_800477D0(u32, u32);
void func_8001D9C8(s32, void *, s32);

void func_8001B980(u8 *arg0, s32 arg1) {
    s32 t[3];
    struct {
        u16 a;
        u16 b;
        s32 c;
        s32 d;
        s32 e;
        s16 f;
        s16 g;
    } s;
    u8 pad[8]; /* reserved tail of the descriptor block */
    u8 *p;
    s32 i;
    s32 key;
    u32 v;

    t[0] = (s32)func_8002C3C0(arg1, 3);
    if (t[0] == 0) {
        return;
    }
    t[1] = (s32)func_8002C3C0(arg1, 4);
    t[2] = (s32)func_8002C3C0(arg1, 5);
    key = (*(u32 *)arg0 >> 8);
    key = key & 0x1F;
    for (i = 0; i < D_8008AE16; i++) {
        p = func_8002C3A0(i);
        v = *(u32 *)p;
        if (((v >> 4) & 0xF) != 1 && ((v >> 4) & 0xF) != 4) {
            continue;
        }
        if (((v >> 8) & 0x1F) != key) {
            continue;
        }
        func_800477D0((u16)(D_8008AE14 + arg1), (u16)(D_8008AE14 + i));
        s.a = 0x1000;
        if (*(u8 *)(t[0] + 4) == 0xFF) {
            s.a = 0x1008;
        }
        s.c = t[0] + 5;
        s.b = (u16)(D_8008AE14 + i);
        if (t[1] != 0) {
            s.d = t[1] + 4;
            s.g = key;
        } else {
            s.d = 0;
            s.g = -1;
        }
        if (t[2] != 0) {
            s.e = t[2] + 5;
            s.f = *(u8 *)(t[2] + 4);
        } else {
            s.e = 0;
            s.f = -1;
        }
        func_8001D9C8(4, &s, 0);
    }
}
