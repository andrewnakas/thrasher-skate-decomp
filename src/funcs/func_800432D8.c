#include "common.h"

typedef struct {
    s32 f0;             /* 0x0 */
    s32 f4;             /* 0x4 */
    s32 f8;             /* 0x8 */
    s32 fC;             /* 0xC */
    s32 f10;            /* 0x10 */
} T_800432D8_node;

extern u8 D_8008B384[];

void func_800432D8(s32 arg0, T_800432D8_node *arg1, s32 arg2, s32 arg3) {
    T_800432D8_node *node;
    T_800432D8_node **slot;

    if (arg2 == 0x1000) {
        return;
    }
    slot = (T_800432D8_node **) (D_8008B384 + arg3 * 4);
    node = (*slot)++;
    node->f0 = arg0;
    node->f4 = arg1->f0;
    node->f8 = arg1->f4;
    node->fC = arg1->f8;
    node->f10 = arg2;
}
