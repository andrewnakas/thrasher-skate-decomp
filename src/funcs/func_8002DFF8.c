#include "common.h"

typedef struct BspNode {
    u8 type;
    u8 axis;
    s16 dist;
    s32 pad4;
    struct BspNode *back;
    struct BspNode *front;
} BspNode;

void func_8002CF58(BspNode *, s32);
extern s32 D_8008AFA0;
extern s16 D_8008AFC4[4];
extern s32 D_8008B064;

void func_8002DFF8(BspNode *node) {
    s32 d;

    if (node != NULL) {
        if (node->type == 0x70) {
            d = D_8008AFC4[node->axis] + node->dist;
            D_8008AFA0 = d;
            func_8002CF58(node, d);
            if (abs(d) < D_8008B064) {
                func_8002DFF8(node->back);
                func_8002DFF8(node->front);
            } else if (d < 0) {
                func_8002DFF8(node->back);
            } else {
                func_8002DFF8(node->front);
            }
        } else if (node->type == 0x6C) {
            func_8002CF58(node, D_8008AFA0);
        }
    }
}
