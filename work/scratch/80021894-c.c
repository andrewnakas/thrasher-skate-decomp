#include "common.h"

typedef struct {
    u8 f00[3];
    u8 f03;
    u8 f04[0x24];
    u8 f28;
    u8 f29[3];
    s32 f2C;
} Node;

extern u8 D_8008A2AC;
extern u32 D_8008A2A4;
extern u32 D_8008A2A8;
extern s32 D_8009C0A4[];
extern s32 D_8009C6D4[];

s32 func_80020C34(u8, u8, u8, s32 **, s32 *, s32 *);

s32 func_80021894(u32 id) {
    u8 *tab;
    u32 cnt;
    s32 extra;
    Node *node;
    s32 next;
    u32 i;
    u32 j;

    func_80020C34((u8) (id >> 16), (u8) ((id & 0xFF00) >> 8), D_8008A2AC, (s32 **) &tab, (s32 *) &cnt, &extra);

    if ((id & 0xFF) >= cnt || (s32) (id & 0xFF) < 0) {
        return 1;
    }

    while (id != (u32) -1) {
        node = (Node *) ((u32) (0x30 * (id & 0xFF)) + (u32) tab);
        next = node->f2C;
        node->f28 = 0;
        node->f2C = -1;
        *((u8 *) tab + 0x30 * (id & 0xFF) + 3) = 0;

        D_8009C6D4[D_8008A2A8++] = id;

        for (i = 0; i < D_8008A2A4; i++) {
            if (D_8009C0A4[i] == (s32) id) {
                D_8008A2A4--;
                for (j = i; j < D_8008A2A4; j++) {
                    D_8009C0A4[j] = D_8009C0A4[j + 1];
                }
            }
        }

        id = next;
    }

    return 0;
}
