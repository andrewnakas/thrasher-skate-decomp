#include "common.h"

typedef struct {
    u8 pad[0xC];
    s16 x;
    s16 y;
    s16 z;
    u8 pad2[0x12];
    u16 a;
    u16 b;
    u16 c;
} Rec;

extern u8 *D_8008AE18;

void func_8001BB1C(s32 idx, s32 *out, u16 *out2) {
    s32 off;

    off = idx * 6;
    out[0] = ((Rec *)((u8 *)D_8008AE18 + off))->x << 16;
    out[1] = ((Rec *)((u8 *)D_8008AE18 + off))->y << 16;
    out[2] = ((Rec *)((u8 *)D_8008AE18 + off))->z << 16;
    out2[0] = ((Rec *)((u8 *)D_8008AE18 + off))->a;
    out2[1] = ((Rec *)((u8 *)D_8008AE18 + off))->b;
    out2[2] = ((Rec *)((u8 *)D_8008AE18 + off))->c;
}
