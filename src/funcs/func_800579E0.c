/* near-miss 12/109: btn/mode s1/s2 swap (btn wants s1) and tbl = lui v0/addiu v1 vs game lui v1/addiu v1 */
#include "common.h"

typedef struct {
    s8 *type;
    u32 cur;
    u32 prev;
    u16 unkC;
    u16 flags;
    u8 pad10[0x20];
} Pad_800579E0;

typedef struct {
    u8 pad0[0x69];
    u8 port;
    u8 map;
    u8 pad6B[5];
} Player_800579E0;

extern s32 func_80055D58();
extern Player_800579E0 D_800B2428[];
extern Pad_800579E0 D_800B2C7C[];
extern u32 D_800B2CDC[][10];
extern u32 D_800B2D5C[];

s32 func_800579E0(s32 pl, s32 btn, s32 mode) {
    Pad_800579E0 *p;
    u32 mask;
    s32 r;

    if (func_80055D58() != 4) {
        p = &D_800B2C7C[D_800B2428[pl].port];
        if (!(p->flags & 1)) {
            if (*p->type != 2) {
                mask = D_800B2CDC[D_800B2428[pl].map][btn];
            } else {
                mask = D_800B2D5C[btn];
            }
        } else {
            p = NULL;
            mask = 0;
        }
    } else {
        p = D_800B2C7C;
        mask = D_800B2CDC[0][btn];
    }
    if (p != NULL) {
    switch ((u32) mode) {
        case 0:
            return (p->cur & p->prev & mask) == mask;
        case 1:
            r = 0;
            if ((p->cur & mask) == mask) {
                r = (p->prev & mask) != r;
            }
            return r;
        case 2:
            return (p->cur & mask) == mask;
        case 3:
            return (~p->cur & p->prev & mask) != 0;
        default:
            return 0;
    }
    }
    return 0;
}
