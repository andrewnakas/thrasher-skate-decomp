#include "common.h"

typedef struct {
    s32 sq;             /* 0x0 */
    s32 v;              /* 0x4 */
    u8 pad8[0x10];      /* 0x8 */
} Sub_8002A044;

typedef struct Node_8002A044 {
    s32 flags;                      /* 0x00 */
    u8 pad4[0x18];                  /* 0x04 */
    u16 cnt;                        /* 0x1C */
    u8 pad1E[0x3A];                 /* 0x1E */
    Sub_8002A044 sub[2];            /* 0x58 */
    u8 pad88[0xC];                  /* 0x88 */
    struct Node_8002A044 *next;     /* 0x94 */
} Node_8002A044;

extern s32 D_8008B010;

extern void func_8003B754(s32, s32 *);

void func_8002A044(u8 *a0) {
    s32 t;
    Node_8002A044 *n;
    s32 i;
    s32 x;

    func_8003B754(0, &t);
    n = *(Node_8002A044 **) (a0 + 4);
    t += D_8008B010;
    for (; n != 0; n = n->next) {
        if (n->flags & 0x20) {
            for (i = 1; i < n->cnt; i++) {
                x = t + n->sub[i].v;
                n->sub[i].sq = x * x;
            }
        }
    }
}
