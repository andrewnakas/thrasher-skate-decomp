#include "common.h"

extern s32 D_8008B384[];
extern u8 *D_8008B060;

void p1(s32 a) { u8 *old; old = D_8008B060; D_8008B060 = old + 0x10; *(s32 *)old = a; }
void p2(s32 a) { u8 *old; old = D_8008B060; D_8008B060 = old + 0x10; old[0] = a; }
void p3(s32 a) { s32 old; old = (s32)D_8008B060; D_8008B060 = (u8 *)(old + 0x10); *(s32 *)old = a; }
void p4(s32 a) { u8 *old; u8 *next; old = D_8008B060; next = old + 0x10; D_8008B060 = next; *(s32 *)old = a; }
void p5(s32 a, s32 i) { u8 *p; u8 *slot; slot = D_8008B060 + i * 4; p = *(u8 **)slot; *(u8 **)slot = p + 0x10; *(s32 *)p = a; }
void p6(s32 a) { u8 *old; old = D_8008B060; D_8008B060 += 0x10; *(s32 *)old = a; }
void p7(s32 a) { u8 *old; old = D_8008B060; D_8008B060 = old + 0x10; *(s32 *)old = a; old = 0; }
