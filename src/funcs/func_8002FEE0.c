#include "common.h"

typedef struct {
    u8 a;
    u8 b;
    u8 flag;
} Edge;

typedef struct {
    u8 pad0[2];
    u8 unk2;
} Info_8002FEE0;

Info_8002FEE0 *func_8002BAC0(u16);
u8 *func_8002E8C0(u16);
void func_8002FFDC(u8 *, u8, u8 *, u8 *, s32);
extern Edge D_8006F8B0[];

s32 func_8002FEE0(u8 *obj, u8 *out) {
    Info_8002FEE0 *info;
    Edge *e;
    u32 i;

    info = func_8002BAC0(*(u16 *) obj);
    switch ((u32) *func_8002E8C0(*(u16 *) obj)) {
    case 2:
        for (i = 0; i < 4; i++) {
            func_8002FFDC(out, info->unk2, obj + (D_8006F8B0[i].a * 8 + 0x44), obj + (D_8006F8B0[i].b * 8 + 0x44), D_8006F8B0[i].flag);
            out += 0x1C;
        }
        return i;
    case 0:
        break;
    case 3:
        func_8002FFDC(out, info->unk2, obj + 0x44, obj + 0x5C, 0);
        return 1;
    }
    return 0;
}
