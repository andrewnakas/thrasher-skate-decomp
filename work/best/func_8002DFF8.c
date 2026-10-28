#include "common.h"

extern u8 D_8008AFC4;
extern s32 D_8008AFA0;
extern s32 D_8008B064;
extern void func_8002CF58();

void func_8002DFF8(u8 *node)
{
    s32 v;
    s32 a;

    if (node == 0) {
        return;
    }
    if (node[0] == 0x70) {
        u8 *b = &D_8008AFC4;

        v = *(s16 *) (b + node[1] * 2) + *(s16 *) (node + 2);
        D_8008AFA0 = v;
        func_8002CF58(node, v);
        a = v;
        if (a < 0) {
            a = -a;
        }
        if (a < D_8008B064) {
            func_8002DFF8(*(u8 **) (node + 8));
        } else if (v < 0) {
            func_8002DFF8(*(u8 **) (node + 8));
            return;
        }
        func_8002DFF8(*(u8 **) (node + 0xC));
        return;
    }
    if (node[0] == 0x6C) {
        func_8002CF58(node, D_8008AFA0);
    }
}
