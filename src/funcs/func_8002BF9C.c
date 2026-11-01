#include "common.h"

typedef struct BspNode {
    u8 type;
    u8 axis;
    s16 dist;
    struct BspNode *back;
    struct BspNode *front;
} BspNode;

extern s32 D_8008A32C[2];

BspNode *func_8002BF9C(BspNode *node, s16 *pos) {
    s32 leaf = 0x6C;

    if (node != NULL) {
    loop:
        if (node->type == leaf) {
            return node;
        }
        if (pos[node->axis] + node->dist > 0) {
            node = node->front;
        } else {
            node = node->back;
        }
        goto loop;
    }
    return (BspNode *) D_8008A32C;
}
