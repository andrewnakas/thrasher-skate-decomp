#include "common.h"

typedef struct Node_8004B1D4 {
    u8 flags;
    u8 pad0[7];
    u8 val;
    u8 pad1[7];
    struct Node_8004B1D4 *next;
} Node_8004B1D4;

typedef struct {
    u16 flags;
    u8 state;
    u8 pad0[0x35];
    Node_8004B1D4 *list;
} Ent_8004B1D4;

extern u8 D_80010670[];
extern u8 D_8008A93C[];
extern u32 D_8008A938;
extern Ent_8004B1D4 *D_800AEA24[];

void printf(u8 *fmt, u8 *msg, ...);
void exit(s32 code);
s32 func_8004B41C(Ent_8004B1D4 *e);
void func_8004E528(u8 v, s32 a);

s32 func_8004B1D4(u8 idx) {
    Ent_8004B1D4 *e;
    Node_8004B1D4 *n;

    D_8008A938++;
    if (idx >= 0x20) {
        printf(D_80010670, D_8008A93C, 0x1AB);
        exit(1);
    }
    e = D_800AEA24[idx];
    if (e == 0) {
        printf(D_80010670, D_8008A93C, 0x1AD);
        exit(1);
    }
    if (func_8004B41C(e) != 0) {
        switch (e->flags & 3) {
        case 0:
            n = e->list;
            while (n != 0) {
                if ((n->flags & 2) == 0) {
                    func_8004E528(n->val, 0);
                }
                n = n->next;
            }
            e->state = 2;
            D_8008A938--;
            return 0;
        case 1:
            break;
        default:
            e->flags |= 0x4000;
            break;
        }
    }
    e->state = 2;
    D_8008A938--;
    return 0;
}
